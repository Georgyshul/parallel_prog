#ifndef EXP_LINEAR_LINEAR_H_
#define EXP_LINEAR_LINEAR_H_

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double run_linear_avg_time(int array_length, int experiments_number,
                           FILE *log_fd);
double run_linear_operations_count(int array_length, int experiments_number,
                                   FILE *log_fd);

#endif  // EXP_LINEAR_LINEAR_H_