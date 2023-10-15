#include "linear.h"

double shell_sort_linear(int *array, int array_length) {
    double start = omp_get_wtime();

    for (int s = array_length / 2; s > 0; s /= 2) {
        for (int i = 0; i < s; i++) {
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


    double end = omp_get_wtime();
    return end - start;
}