#include "entry.h"

#define MAX_FILE_NAME_LENGTH 50
#define AMOUNT_OF_PARALLEL_TYPES 1


static const char LOG_FILE_NAME[MAX_FILE_NAME_LENGTH] = {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', 'o', 'm', 'p', '.', 'c', 's', 'v', '\0'};


int main() {
    const int array_length = 10000000;
    const int range = 1000000;

    int *array = (int*)calloc(array_length, sizeof(int));

    stats stat[AMOUNT_OF_PARALLEL_TYPES];
    memset(stat, 0, sizeof(stat));

    for (int i = 0; i < NUM_RUNS; i++) {
        generate_array(array, array_length, range);
        make_experiment(array, array_length, stat);
    }
    calculate_stats(stat);

    free(array);

    return 0;
}

void make_experiment(int *array, int array_length, stats *stat) {
    int max;

    double exec_time_linear = find_max_linear(array, array_length, &max);

    for (int num_threads = 1; num_threads <= MAX_THREADS_NUMBER; num_threads++) {
        double exec_time_omp;

        if (num_threads == 1) {
            exec_time_omp = exec_time_linear;
        } else {
            exec_time_omp = find_max_n_threads_omp(array, array_length, num_threads, &max);
        }

        stat[0].avg_exec_time_array[num_threads - 1] += exec_time_omp;
    }
}

void generate_array(int *array, int array_length, int range) {
    for (int i = 0; i < array_length; i++) {
        array[i] = rand() % range;
    }

    array[rand() % array_length] = range + 1;
}

void calculate_stats(stats *stat) {
    
    FILE *avg_fd1 = fopen(LOG_FILE_NAME, "w");

    for (int i = 0; i < MAX_THREADS_NUMBER; i++) {
        stat[0].avg_exec_time_array[i] /= NUM_RUNS;
    }

    for (int i = 0; i < MAX_THREADS_NUMBER; i++) {
        fprintf(avg_fd1, "%d,%f\n", i + 1, stat[0].avg_exec_time_array[i]);
    }

    fclose(avg_fd1);
}
