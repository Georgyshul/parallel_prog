#include "parallel.h"

double shell_sort_n_threads(int *array, int array_length, int num_threads) {
    int s, i;
    double start = omp_get_wtime();

    for (s = array_length / 2; s > 0; s /= 2) {
        #pragma omp parallel num_threads(num_threads) shared(array,s,array_length) private (i) default(none)
        {
        #pragma omp for
        for (i = 0; i < s; i++) {
            for (int j = i + s; j < array_length; j += s) {
                int key = array[j];
                int k = j - s;
                while (k >= 0 && array[k] > key) {
                    array[k + s] = array[k];
                    k -= s;
                }
                array[k + s] = key;
            }
        }
        }
    }

    double end = omp_get_wtime();
    return end - start;
}