#ifndef EXP_PARALLEL_PARALLEL_H_
#define EXP_PARALLEL_PARALLEL_H_

#include <omp.h>
#include <time.h>

double find_max_n_threads_omp(int *array, int array_length, int num_threads, int *max);

#endif  // EXP_PARALLEL_PARALLEL_H_