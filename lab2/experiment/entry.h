#ifndef EXP_ENTRY_H_
#define EXP_ENTRY_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "parallel/parallel.h"

#define MAX_THREADS_NUMBER 20
#define RUNS_PER_ARRAY_TYPE 5

#define AMOUNT_OF_ARRAY_TYPES 7

#define ELEMENT_IS_FIRST 0
#define ELEMENT_IN_BEGINNING 1
#define ELEMENT_IN_END 2
#define ELEMENT_IS_LAST 3
#define ELEMENT_IN_MIDDLE 4
#define ELEMENT_NOT_EXIST 5
#define ELEMENT_EVERYWHERE 6

// enum {
//     inFirst,
//     inSec,
//     size
// }

// for (int i = 0; i < size; ++i) {

// }


typedef struct stats {
    double avg_exec_time_array[MAX_THREADS_NUMBER];

    double speedup_array[MAX_THREADS_NUMBER];

    double efficiency_array[MAX_THREADS_NUMBER];
} stats;


void make_experiment(int *array, int target, int array_length, int array_type, FILE *log_fd, stats *stat);
void check_result(int *array, int target, int idx, int array_type, FILE *log_fd);

void generate_array(int **array, int array_length, int target, int array_type);

void generate_element_is_first(int **array, int target, int array_length);
void generate_element_in_beginning(int **array, int target, int array_length);
void generate_element_in_end(int **array, int target, int array_length);
void generate_element_is_last(int **array, int target, int array_length);
void generate_element_in_middle(int **array, int target, int array_length);
void generate_element_not_exist(int **array, int target, int array_length);
void generate_element_everywhere(int **array, int target, int array_length);
void generate_rand_array_without_target(int **array, int target, int array_length);

void calculate_stats(stats *stat, int array_type, FILE *stat_fd);

#endif  // EXP_ENTRY_H_