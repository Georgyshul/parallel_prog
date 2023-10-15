#ifndef EXP_ENTRY_H_
#define EXP_ENTRY_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "parallel/parallel.h"
#include "linear/linear.h"

#define MAX_THREADS_NUMBER 10
#define RUNS_PER_ARRAY_TYPE 10

#define AMOUNT_OF_ARRAY_TYPES 7

#define ORDERED 0
#define REVERSE_ORDERED 1
#define RANDOM 2
#define LOW_RANGE 3  // = many common numbers
#define HALF_ORDERED 4
#define HALF_REVERSE_ORDERED 5

// #define ELEMENT_IS_FIRST 0
// #define ELEMENT_IN_BEGINNING 1
// #define ELEMENT_IN_END 2
// #define ELEMENT_IS_LAST 3
// #define ELEMENT_IN_MIDDLE 4
// #define ELEMENT_NOT_EXIST 5
// #define ELEMENT_EVERYWHERE 6




typedef struct stats {
    double avg_exec_time_array[MAX_THREADS_NUMBER];

    double speedup_array[MAX_THREADS_NUMBER];

    double efficiency_array[MAX_THREADS_NUMBER];
} stats;

void generate_array(int *array, int *sorted_array, int array_length, int array_type);
void generate_random_array(int *array, int array_length, int range);

void make_experiment(int *array, int *sorted_array ,int array_length, int array_type, stats *stat);
int check_result(int *array, int *sorted_array, int array_length);

void calculate_stats(stats *stat, int array_type, FILE *stat_fd);



int comp(const void *elem1, const void *elem2);
void _print_arrays(int *array, int *sorted_array, int array_length);
void _copy_array(int *dest, int *src, int array_length);

#endif  // EXP_ENTRY_H_