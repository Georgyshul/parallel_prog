#ifndef EXP_ENTRY_H_
#define EXP_ENTRY_H_

#include <stdio.h>
#include <stdlib.h>

void return_stats(double avg_linear_time, int avg_linear_operations,
                  double *avg_parallel_exec_time, int max_threads_number,
                  FILE *log_fd);

#endif  // EXP_ENTRY_H_