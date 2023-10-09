#ifndef EXP_PARALLEL_PARALLEL_H_
#define EXP_PARALLEL_PARALLEL_H_

#include <omp.h>

double find_occurance_n_threads(int *array, int target, int array_length, int num_threads, int *idx);

#endif  // EXP_PARALLEL_PARALLEL_H_