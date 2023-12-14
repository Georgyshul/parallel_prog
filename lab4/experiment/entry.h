#ifndef EXP_ENTRY_H_
#define EXP_ENTRY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "parallel/parallel.h"
#include "linear/linear.h"

#define MAX_THREADS_NUMBER 20
#define NUM_RUNS 50

typedef struct stats {
    double avg_exec_time_array[MAX_THREADS_NUMBER];

    double speedup_array[MAX_THREADS_NUMBER];

    double efficiency_array[MAX_THREADS_NUMBER];
} stats;


void generate_array(int *array, int array_length, int range);

void make_experiment(int *array, int array_length, stats *stat);

void calculate_stats(stats *stat);

#endif  // EXP_ENTRY_H_