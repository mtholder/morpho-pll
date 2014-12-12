/** 
 * PLL (version 1.0.0) a software library for phylogenetic inference
 * Copyright (C) 2013 Tomas Flouri and Alexandros Stamatakis
 *
 * Derived from 
 * RAxML-HPC, a program for sequential and parallel estimation of phylogenetic
 * trees by Alexandros Stamatakis
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For any other enquiries send an Email to Tomas Flouri
 * Tomas.Flouri@h-its.org
 *
 * When publishing work that uses PLL please cite PLL
 * 
 * @file stack.c
 * @brief Generic stack implementation
 *
 * Detailed description to appear soon.
 */
#include <stdio.h>
#include "stack.h"
#include "mem_alloc.h"

int pllStackSize (pllStack ** stack)
{
  pllStack * top;
  int size = 0;
  top = *stack;
 
  while (top)
  {
    ++ size;
    top = top->next;
  }
  
  return (size);
}

int 
pllStackPush (pllStack ** head, void * item)
{
  pllStack * new;
 
  new = (pllStack *) rax_malloc (sizeof (pllStack));
  if (!new) return (0);
 
  new->item = item;
  new->next = *head;
  *head     = new;
 
  return (1);
}

void * pllStackPop (pllStack ** head)
{
  void * item;
  pllStack * tmp;
  if (!*head) return (NULL);
 
  tmp     = (*head);
  item    = (*head)->item;
  (*head) = (*head)->next;
  rax_free (tmp);
 
  return (item);
}
 
void 
pllStackClear (pllStack ** stack)
{
  while (*stack) pllStackPop (stack);
}




#if defined (NON_POSIX)
/* Implement the strndup function.
   Copyright (C) 2005 Free Software Foundation, Inc.
   Written by Kaveh R. Ghazi <ghazi@caip.rutgers.edu>.

This file is part of the libiberty library.
Libiberty is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Libiberty is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with libiberty; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
Boston, MA 02110-1301, USA.  */
/* fetched from http://opensource.apple.com/source/gcc/gcc-5575.11/libiberty/strndup.c 
on 12-Dec.-2014
*/
/*

@deftypefn Extension char* strndup (const char *@var{s}, size_t @var{n})

Returns a pointer to a copy of @var{s} with at most @var{n} characters
in memory obtained from @code{malloc}, or @code{NULL} if insufficient
memory was available.  The result is always NUL terminated.

@end deftypefn

*/


char *
strndup (const char *s, size_t n)
{
  char *result;
  size_t len = strlen (s);

  if (n < len)
    len = n;

  result = (char *) malloc (len + 1);
  if (!result)
    return 0;

  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}

#endif
