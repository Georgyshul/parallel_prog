#ifndef EXP_PARALLEL_PARALLEL_H_
#define EXP_PARALLEL_PARALLEL_H_

#include <omp.h>

double shell_sort_n_threads(int *array, int array_length, int num_threads);

#endif  // EXP_PARALLEL_PARALLEL_H_