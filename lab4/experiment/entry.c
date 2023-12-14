#include "entry.h"

#define MAX_FILE_NAME_LENGTH 40
#define AMOUNT_OF_PARALLEL_TYPES 7


static const char LOG_FILE_NAME[AMOUNT_OF_PARALLEL_TYPES]
                                      [MAX_FILE_NAME_LENGTH] = {
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '0', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '1', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '2', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '3', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '4', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '5', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '6', '.', 'c', 's', 'v', '\0'}};


int main() {
    const int array_length = 10000000;
    const int range = 1000000;

    int *array = (int*)calloc(array_length, sizeof(int));

    stats stat[7];
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
        double exec_time1;
        double exec_time2;
        double exec_time3;
        double exec_time4;
        double exec_time5;
        double exec_time6;
        double exec_time7;

        if (num_threads == 1) {
            exec_time1 = exec_time_linear;
            exec_time2 = exec_time_linear;
            exec_time3 = exec_time_linear;
            exec_time4 = exec_time_linear;
            exec_time5 = exec_time_linear;
            exec_time6 = exec_time_linear;
            exec_time7 = exec_time_linear;
        } else {
            exec_time1 = find_max_n_threads_static(array, array_length, num_threads, &max);
            exec_time2 = find_max_n_threads_dynamic(array, array_length, num_threads, &max);
            exec_time3 = find_max_n_threads_guided(array, array_length, num_threads, &max);
            exec_time4 = find_max_n_threads_auto(array, array_length, num_threads, &max);
            exec_time5 = find_max_n_threads_static_chunk(array, array_length, num_threads, &max);
            exec_time6 = find_max_n_threads_dynamic_chunk(array, array_length, num_threads, &max);
            exec_time7 = find_max_n_threads_guided_chunk(array, array_length, num_threads, &max);
        }

        stat[0].avg_exec_time_array[num_threads - 1] += exec_time1;
        stat[1].avg_exec_time_array[num_threads - 1] += exec_time2;
        stat[2].avg_exec_time_array[num_threads - 1] += exec_time3;
        stat[3].avg_exec_time_array[num_threads - 1] += exec_time4;
        stat[4].avg_exec_time_array[num_threads - 1] += exec_time5;
        stat[5].avg_exec_time_array[num_threads - 1] += exec_time6;
        stat[6].avg_exec_time_array[num_threads - 1] += exec_time7;
    }
}

void generate_array(int *array, int array_length, int range) {
    for (int i = 0; i < array_length; i++) {
        array[i] = rand() % range;
    }

    array[rand() % array_length] = range + 1;
}

void calculate_stats(stats *stat) {
    
    FILE *avg_fd1 = fopen(LOG_FILE_NAME[0], "w");
    FILE *avg_fd2 = fopen(LOG_FILE_NAME[1], "w");
    FILE *avg_fd3 = fopen(LOG_FILE_NAME[2], "w");
    FILE *avg_fd4 = fopen(LOG_FILE_NAME[3], "w");
    FILE *avg_fd5 = fopen(LOG_FILE_NAME[4], "w");
    FILE *avg_fd6 = fopen(LOG_FILE_NAME[5], "w");
    FILE *avg_fd7 = fopen(LOG_FILE_NAME[6], "w");

    for (int i = 0; i < MAX_THREADS_NUMBER; i++) {
        stat[0].avg_exec_time_array[i] /= NUM_RUNS;
        stat[1].avg_exec_time_array[i] /= NUM_RUNS;
        stat[2].avg_exec_time_array[i] /= NUM_RUNS;
        stat[3].avg_exec_time_array[i] /= NUM_RUNS;
        stat[4].avg_exec_time_array[i] /= NUM_RUNS;
        stat[5].avg_exec_time_array[i] /= NUM_RUNS;
        stat[6].avg_exec_time_array[i] /= NUM_RUNS;
    }

    for (int i = 0; i < MAX_THREADS_NUMBER; i++) {
        fprintf(avg_fd1, "%d,%f\n", i + 1, stat[0].avg_exec_time_array[i]);
        fprintf(avg_fd2, "%d,%f\n", i + 1, stat[1].avg_exec_time_array[i]);
        fprintf(avg_fd3, "%d,%f\n", i + 1, stat[2].avg_exec_time_array[i]);
        fprintf(avg_fd4, "%d,%f\n", i + 1, stat[3].avg_exec_time_array[i]);
        fprintf(avg_fd5, "%d,%f\n", i + 1, stat[4].avg_exec_time_array[i]);
        fprintf(avg_fd6, "%d,%f\n", i + 1, stat[5].avg_exec_time_array[i]);
        fprintf(avg_fd7, "%d,%f\n", i + 1, stat[6].avg_exec_time_array[i]);
    }

    fclose(avg_fd1);
    fclose(avg_fd2);
    fclose(avg_fd3);
    fclose(avg_fd4);
    fclose(avg_fd5);
    fclose(avg_fd6);
    fclose(avg_fd7);
}
