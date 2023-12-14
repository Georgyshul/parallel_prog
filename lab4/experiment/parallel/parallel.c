#include "parallel.h"

double find_max_n_threads_static(int *array, int array_length, int num_threads, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads) shared(array, array_length) reduction(max: val) default(none)
    {
        #pragma omp for schedule(static)
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

double find_max_n_threads_static_chunk(int *array, int array_length, int num_threads, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads) shared(array, array_length) reduction(max: val) default(none)
    {
        #pragma omp for schedule(static, 1000)
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

double find_max_n_threads_dynamic(int *array, int array_length, int num_threads, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads) shared(array, array_length) reduction(max: val) default(none)
    {
        #pragma omp for schedule(dynamic, 100)
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

double find_max_n_threads_dynamic_chunk(int *array, int array_length, int num_threads, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads) shared(array, array_length) reduction(max: val) default(none)
    {
        #pragma omp for schedule(dynamic, 1000)
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

double find_max_n_threads_guided(int *array, int array_length, int num_threads, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads) shared(array, array_length) reduction(max: val) default(none)
    {
        #pragma omp for schedule(guided)
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

double find_max_n_threads_guided_chunk(int *array, int array_length, int num_threads, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads) shared(array, array_length) reduction(max: val) default(none)
    {
        #pragma omp for schedule(guided, 1000)
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

double find_max_n_threads_auto(int *array, int array_length, int num_threads, int *max) {
    *max = array[0];
    int val = *max;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads) shared(array, array_length) reduction(max: val) default(none)
    {
        #pragma omp for schedule(auto)
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