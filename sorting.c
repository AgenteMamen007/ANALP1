/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"

#include <stdio.h>

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
  /* Your code */
  int i, j, a, n = 0;
  if (!array || ip < 0 || iu < 0 || ip > iu) {
    return ERR;
  }

  for (i = ip+1; i <= iu; i++) {
    a = array[i];
    j = i - 1;

    while (j >= ip) {
      n++; /*Contamos la comparacion del bucle mas interno: array[j] > a*/
      if (array[j] > a) {
        array[j+1] = array[j];
        j--;
      } else {
          break;
      }
    }

    array[j+1] = a;
  }

  return n;
}


/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
/*int BubbleSort(int* array, int ip, int iu)
{
  /* Your code */
/*}
*/






