#ifndef ERRCODES_H
#define ERRCODES_H

#define  PLL_NNI_P_TIP                  1 << 0          /**< Node p is a tip */
#define  PLL_NNI_Q_TIP                  1 << 1          /**< Node p->back is a tip */

#define  PLL_PARTITION_OUT_OF_BOUNDS    1 << 0      /**< Trying to access a partition index that is out of bounds */
#define  PLL_BASE_FREQUENCIES_DO_NOT_SUM_TO_1 1 << 1      /**< base frequencies don't sum to 1.0 */

#define PLL_LINKAGE_LIST_OUT_OF_BOUNDS 1 << 0      /**< trying to link a partition index that is out of bounds */

#define PLL_SUBSTITUTION_RATE_OUT_OF_BOUNDS 1 << 0 /**< trying  to set a substitution rate to a value that is out of bounds */
#define PLL_INVALID_Q_MATRIX_SYMMETRY       1 << 1 /**< specifyng an invalid parameter symmetry in the Q matrix */
#define PLL_Q_MATRIX_SYMMETRY_OUT_OF_BOUNDS 1 << 2 /**<specifying a Q matrix symmetry that is out of bounds */

#define PLL_UNKNOWN_MOLECULAR_DATA_TYPE 1 << 0 /**<PLL is trying to do something for an unknown data type */

#define PLL_INCONSISTENT_SUBST_RATE_OPTIMIZATION_SETTING 1 << 0 /**<PLL detected an inconsistent setting for the Q matrix rate optimization */
#define PLL_INCONSISTENT_Q_MATRIX_SYMMETRIES_ACROSS_LINKED_PARTITIONS 1 << 1 /**<Q matrix symmetry vector is not identical for linked partitions */
#define PLL_INCONSISTENT_Q_MATRIX_ENTRIES_ACROSS_LINKED_PARTITIONS 1 << 2 /**<Q matrix entries are not identical for linked partitions */
#define PLL_INCONSISTENT_ALPHA_STATES_ACROSS_LINKED_PARTITIONS 1 << 3 /**<alpha states are not identical across linked partitions */
#define PLL_INCONSISTENT_ALPHA_VALUES_ACROSS_LINKED_PARTITIONS 1 << 4 /**<alpha values are not identical across linked partitions */
#define PLL_INCONSISTENT_FREQUENCY_STATES_ACROSS_LINKED_PARTITIONS 1 << 5 /**<frequency states are not identical across linked partitions */
#define PLL_INCONSISTENT_FREQUENCY_VALUES_ACROSS_LINKED_PARTITIONS 1 << 6 /**<frequency values are not identical across linked partitions */

#define PLL_NEWICK_ROOTED_TREE          1 << 0          /**< @brief Binary root detected */
#define PLL_NEWICK_BAD_STRUCTURE        1 << 1          /**< @brief Errornous tree detected */

#endif
