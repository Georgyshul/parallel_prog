#ifndef EXP_ENTRY_H_
#define EXP_ENTRY_H_

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define RUNS_PER_ARRAY_TYPE 10

#define AMOUNT_OF_ARRAY_TYPES 8

#define ORDERED 0
#define REVERSE_ORDERED 1
#define RANDOM 2
#define LOW_RANGE 3  // = many common numbers
#define FIRST_HALF_ORDERED 4
#define FIRST_HALF_REVERSE_ORDERED 5
#define FIRST_QUATER_ORDERED 6
#define FIRST_QUATER_REVERSE_ORDERED 7


void generate_array(int *array, int *sorted_array, int array_length, int array_type);
void generate_sort_array(int *array, int *sorted_array, int array_length, int range);

void shell_sort(int *array, int array_length);
int *merge(int *array1, int len1, int *array2, int len2);
int check_result(int *array, int *sorted_array, int array_length);

int comp(const void *elem1, const void *elem2);
int comp_rev(const void *elem1, const void *elem2);
void _print_arrays(int *array, int *sorted_array, int array_length);
void _copy_array(int *dest, int *src, int array_length);

#endif  // EXP_ENTRY_H_