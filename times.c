/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/***************************************************/
/* Function: average_sorting_time Date: 7/10/2026  */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  int i, current_ob;
  int min_ob = -1, max_ob = -1;
  double total_ob = 0.0; 
  int **perms = NULL;
  clock_t start, end;

  if (!metodo || !ptime || n_perms <= 0 || N <= 0) {
    return ERR;
  }

  perms = generate_permutations(n_perms, N);
  if (!perms) {
    return ERR;
  }

  start = clock();
  if (start == (clock_t)-1) {
    for (i = 0; i < n_perms; i++) free(perms[i]);
    free(perms);
    return ERR;
  }

  for (i = 0; i < n_perms; i++) {
    current_ob = metodo(perms[i], 0, N - 1);
    
    if (current_ob == ERR) {
      for (i = 0; i < n_perms; i++) free(perms[i]);
      free(perms);
      return ERR;
    }

    total_ob += current_ob;
    if (i == 0) {
      min_ob = current_ob;
      max_ob = current_ob;
    } else {
      if (current_ob < min_ob) min_ob = current_ob;
      if (current_ob > max_ob) max_ob = current_ob;
    }
  }

  end = clock();
  if (end == (clock_t)-1) {
    for (i = 0; i < n_perms; i++) free(perms[i]);
    free(perms);
    return ERR;
  }

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = ((double)(end - start) / CLOCKS_PER_SEC) / (double)n_perms;
  ptime->average_ob = total_ob / (double)n_perms;
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;

  for (i = 0; i < n_perms; i++) {
    free(perms[i]);
  }
  free(perms);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date: 7/10/2026*/
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  int n_times, i, N;
  PTIME_AA times = NULL;

  if (!method || !file || num_min < 1 || num_max < num_min || incr <= 0 || n_perms <= 0) {
    return ERR;
  }

  n_times = ((num_max - num_min) / incr) + 1;

  times = (PTIME_AA) malloc(n_times * sizeof(TIME_AA));
  if (!times) {
    return ERR;
  }

  for (i = 0, N = num_min; i < n_times; i++, N += incr) {
    if (average_sorting_time(method, n_perms, N, &times[i]) == ERR) {
      free(times);
      return ERR;
    }
  }

  if (save_time_table(file, times, n_times) == ERR) {
    free(times);
    return ERR;
  }

  free(times);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date: 7/10/2026       */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE* f = NULL;
  int i;

  if (!file || !ptime || n_times <= 0) {
    return ERR;
  }

  f = fopen(file, "w");
  if (!f) {
    return ERR;
  }

  for (i = 0; i < n_times; i++) {
    if (fprintf(f, "%d %d %f %f %d %d\n", 
                ptime[i].N, 
                ptime[i].n_elems, 
                ptime[i].time, 
                ptime[i].average_ob, 
                ptime[i].min_ob, 
                ptime[i].max_ob) < 0) {
      
      fclose(f);
      return ERR;
    }
  }

  if (fclose(f) == EOF) {
    return ERR;
  }

  return OK;
}