#ifndef EXP_PARALLEL_PARALLEL_H_
#define EXP_PARALLEL_PARALLEL_H_

#include <omp.h>
#include <time.h>

double find_max_n_threads_static(int *array, int array_length, int num_threads, int *max);
double find_max_n_threads_static_chunk(int *array, int array_length, int num_threads, int *max);

double find_max_n_threads_dynamic(int *array, int array_length, int num_threads, int *max);
double find_max_n_threads_dynamic_chunk(int *array, int array_length, int num_threads, int *max);

double find_max_n_threads_guided(int *array, int array_length, int num_threads, int *max);
double find_max_n_threads_guided_chunk(int *array, int array_length, int num_threads, int *max);

double find_max_n_threads_auto(int *array, int array_length, int num_threads, int *max);

#endif  // EXP_PARALLEL_PARALLEL_H_