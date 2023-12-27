#include "parallel.h"

double find_max_n_threads_omp(int *array, int array_length, int num_threads, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads) shared(array, array_length) reduction(max: val) default(none)
    {
        #pragma omp for
        for (int j = 0; j < array_length; j++) {
            if (array[j] > val) {
                val = array[j];
            }
        }
    }
    *max = val;
    double end = omp_get_wtime();

    return end - start;
}