#include "linear.h"

double shell_sort_linear(int *array, int array_length) {
    double start = omp_get_wtime();

    for (int s = array_length / 2; s > 0; s /= 2) {
        for (int i = s; i < array_length; ++i) {
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
                int temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
    }


    double end = omp_get_wtime();
    return end - start;
}