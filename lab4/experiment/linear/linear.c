#include "linear.h"

double find_max_linear(int *array, int array_length, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    for (int j = 0; j < array_length; j++) {
        if (array[j] > val) {
            val = array[j];
        }
    }

    *max = val;
    double end = omp_get_wtime();

    return end - start;
}