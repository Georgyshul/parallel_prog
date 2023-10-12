#include "parallel.h"

double find_occurance_n_threads(int *array, int target, int array_length, int num_threads, int *idx) {

    *idx = -1;
    double start = omp_get_wtime();

#pragma omp parallel num_threads(num_threads) shared(array, target, array_length, idx)
    {
#pragma omp for
    for (int i = 0; i < array_length; i++) {
        if (*idx == -1) {
            if (array[i] == target) {
#pragma omp critical
                *idx = i;
            }
        } else { i = array_length; }
    }
    }

    double end = omp_get_wtime();
    return end - start;
}