#ifndef EXP_PARALLEL_PARALLEL_H_
#define EXP_PARALLEL_PARALLEL_H_

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double *run_parallel_avg_time(int array_length, int experiments_number,
                              int max_threads_number, FILE *log_fd);
double run_n_threads(int *exp_array, int array_length, int threads);

#endif  // EXP_PARALLEL_PARALLEL_H_