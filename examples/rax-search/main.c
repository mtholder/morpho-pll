#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pll.h>

int main (int argc, char * argv[])
{
  pllAlignmentData * alignmentData;
  pllInstance * tr;
  pllNewickTree * newick;
  partitionList * partitions;
  pllQueue * partitionInfo;
  int i;
  pllInstanceAttr attr;
  pllRearrangeList * rearrangeList;

#ifdef _FINE_GRAIN_MPI
  pllInitMPI (&argc, &argv);
#endif

  if (argc < 4)
   {
     fprintf (stderr, "usage: %s [phylip-file] [newick-file] [partition-file] [threads]\n", argv[0]);
     return (EXIT_FAILURE);
   }


  /* Set the PLL instance attributes */
  attr.rateHetModel     = PLL_GAMMA;
  attr.fastScaling      = PLL_FALSE;
  attr.saveMemory       = PLL_FALSE;
  attr.useRecom         = PLL_FALSE;
  attr.randomNumberSeed = 0xDEADBEEF;
  attr.numberOfThreads  = (argc > 4) ? (atoi(argv[4]) > 0 ? atoi(argv[4]) : 8) : 8;            /* This only affects the pthreads version */

  /* Create a PLL tree */
  tr = pllCreateInstance (&attr);

  /* Parse a PHYLIP file */
  alignmentData = pllParseAlignmentFile (PLL_FORMAT_PHYLIP, argv[1]);


  if (!alignmentData)
   {
     fprintf (stderr, "Error while parsing %s\n", argv[1]);
     return (EXIT_FAILURE);
   }

  /* Parse a NEWICK file */
  newick = pllNewickParseFile (argv[2]);

  if (!newick)
   {
     fprintf (stderr, "Error while parsing newick file %s\n", argv[2]);
     return (EXIT_FAILURE);
   }
  if (!pllValidateNewick (newick))  /* check whether the valid newick tree is also a tree that can be processed with our nodeptr structure */
   {
     fprintf (stderr, "Invalid phylogenetic tree\n");
     printf ("%d\n", errno);
     //return (EXIT_FAILURE);
   }

  /* Parse the partitions file into a partition queue structure */
  partitionInfo = pllPartitionParse (argv[3]);
  
  /* Validate the partitions */
  if (!pllPartitionsValidate (partitionInfo, alignmentData))
   {
     fprintf (stderr, "Error: Partitions do not cover all sites\n");
     return (EXIT_FAILURE);
   }

  /* Commit the partitions and build a partitions structure */
  partitions = pllPartitionsCommit (partitionInfo, alignmentData);

  /* We don't need the the intermedia partition queue structure anymore */
  pllQueuePartitionsDestroy (&partitionInfo);

  /* eliminate duplicate sites from the alignment and update weights vector */
  pllAlignmentRemoveDups (alignmentData, partitions);

  /* Set the topology of the PLL tree from a parsed newick tree */
  pllTreeInitTopologyNewick (tr, newick, PLL_TRUE);

  /* Or instead of the previous function use the next commented line to create
     a random tree topology 
  pllTreeInitTopologyRandom (tr, alignmentData->sequenceCount, alignmentData->sequenceLabels); */

  /* Connect the alignment and partition structure with the tree structure */
  if (!pllLoadAlignment (tr, alignmentData, partitions))
   {
     fprintf (stderr, "Incompatible tree/alignment combination\n");
     return (EXIT_FAILURE);
   }
  
  /* Initialize the model. Note that this function will also perform a full
     tree traversal and evaluate the likelihood of the tree. Therefore, you
     have the guarantee that tr->likelihood the valid likelihood */
  pllInitModel(tr, partitions);
  printf ("Log-likelihood of topology before branch length optimization: %f\n", tr->likelihood);

  pllOptimizeBranchLengths (tr, partitions, 64);
  printf ("Log-likelihood of topology after branch length optimization: %f\n", tr->likelihood);
  printf ("bailing out...\n");

  return 0;
  pllRaxmlSearchAlgorithm (tr, partitions, PLL_TRUE);
  printf ("Log-likelihood of topology after search: %f\n", tr->likelihood);
  pllOptimizeBranchLengths (tr, partitions, 64);
  printf ("Log-likelihood of search topology after branch length optimization: %f\n", tr->likelihood);

  /* Do some cleanup */
  pllAlignmentDataDestroy (alignmentData);
  pllNewickParseDestroy (&newick);

# if ! defined(NON_POSIX)
  pllPartitionsDestroy (tr, &partitions);
  pllDestroyInstance (tr);
# endif
  
  return (EXIT_SUCCESS);
}
