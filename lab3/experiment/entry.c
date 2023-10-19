#include "entry.h"

#define MAX_FILE_NAME_LENGTH 40


static const char LOG_FILE_NAME[AMOUNT_OF_ARRAY_TYPES * 3]
                                      [MAX_FILE_NAME_LENGTH] = {
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '0', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '1', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '2', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '3', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '4', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '5', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '6', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '7', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '0', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '1', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '2', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '3', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '4', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '5', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '6', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '7', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '0', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '1', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '2', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '3', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '4', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '5', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '6', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '7', '.', 'c', 's', 'v', '\0'}};


int main() {
    const int array_length = 100000;

    FILE *stat_fd = fopen("stat.txt", "w+");

    int *array = (int*)calloc(array_length, sizeof(int));
    int *sorted_array = (int*)calloc(array_length, sizeof(int));

    for (int array_type = 0; array_type < AMOUNT_OF_ARRAY_TYPES; array_type++) {
        stats stat = {{0}, {0}, {0}};
        for (int i = 0; i < RUNS_PER_ARRAY_TYPE; i++) {
            generate_array(array, sorted_array, array_length, array_type);
            make_experiment(array, sorted_array, array_length, array_type, &stat);
        }
        fprintf(stat_fd, "Array type %d\n------------\n", array_type);
        calculate_stats(&stat, array_type, stat_fd);
    }

    free(array);
    free(sorted_array);
    fclose(stat_fd);

    return 0;
}

void make_experiment(int *array, int *sorted_array ,int array_length, int array_type, stats *stat) {
    int *array_to_sort = (int *)calloc(array_length, sizeof(int));

    for (int num_threads = 1; num_threads <= MAX_THREADS_NUMBER; num_threads++) {
        _copy_array(array_to_sort, array, array_length);

        double exec_time;
        if (num_threads == 1) {
            exec_time = shell_sort_linear(array_to_sort, array_length);
        } else {
            exec_time = shell_sort_n_threads(array_to_sort, array_length, num_threads);
        }
        if (check_result(array_to_sort, sorted_array, array_length)) {
            fprintf(stderr, "ERROR! array_type: %2d, threads_num: %2d\n", array_type, num_threads);
            _print_arrays(array_to_sort, sorted_array, array_length);
        }
        stat->avg_exec_time_array[num_threads - 1] += exec_time;
    }
    free(array_to_sort);
}

void _copy_array(int *dest, int *src, int array_length) {
    for (int i = 0; i < array_length; i++) {
            *(dest + i) = *(src + i);
    }
}

int check_result(int *array, int *sorted_array, int array_length) {
    int e_flag = 0;

    for (int i = 0; i < array_length; i++) {
        if (array[i] != sorted_array[i]) {
            e_flag = 1;
        }
    }

    return e_flag;
}

void generate_array(int *array, int *sorted_array, int array_length, int array_type) {

    switch (array_type) {
        case ORDERED:
            generate_sort_array(array, sorted_array, array_length, 100000);
            _copy_array(array, sorted_array, array_length);
            break;

        case REVERSE_ORDERED:
            generate_sort_array(array, sorted_array, array_length, 100000);
            qsort(array, array_length, sizeof(int), comp_rev);
            break;

        case RANDOM:
            generate_sort_array(array, sorted_array, array_length, 100000);
            break;

        case LOW_RANGE:
            generate_sort_array(array, sorted_array, array_length, 100);
            break;

        case FIRST_HALF_ORDERED:
            generate_sort_array(array, sorted_array, array_length, 100000);
            qsort(array, array_length / 2, sizeof(int), comp);
            break;

        case FIRST_HALF_REVERSE_ORDERED:
            generate_sort_array(array, sorted_array, array_length, 100000);
            qsort(array, array_length / 2, sizeof(int), comp_rev);
            break;

        case FIRST_QUATER_ORDERED:
            generate_sort_array(array, sorted_array, array_length, 100000);
            qsort(array, array_length / 4, sizeof(int), comp);
            break;

        case FIRST_QUATER_REVERSE_ORDERED:
            generate_sort_array(array, sorted_array, array_length, 100000);
            qsort(array, array_length / 4, sizeof(int), comp_rev);
            break;

        default:
            generate_sort_array(array, sorted_array, array_length, 100000);
            break;
    }
}

void generate_sort_array(int *array, int *sorted_array, int array_length, int range) {
    for (int i = 0; i < array_length; i++) {
        array[i] = rand() % range;
    }

    _copy_array(sorted_array, array, array_length);
    qsort(sorted_array, array_length, sizeof(int), comp);
}

int comp(const void *elem1, const void *elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int comp_rev(const void *elem1, const void *elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  -1;
    if (f < s) return 1;
    return 0;
}

void calculate_stats(stats *stat, int array_type, FILE *stat_fd) {
    fprintf(stat_fd, "\n\nAverage execution time for each amount of threads:\n");

    FILE *avg_fd = fopen(LOG_FILE_NAME[array_type], "w");
    FILE *speedup_fd = fopen(LOG_FILE_NAME[array_type + AMOUNT_OF_ARRAY_TYPES], "w");
    FILE *efficiency_fd = fopen(LOG_FILE_NAME[array_type + AMOUNT_OF_ARRAY_TYPES * 2], "w");

    for (int i = 0; i < MAX_THREADS_NUMBER; i++) {
        stat->avg_exec_time_array[i] /= RUNS_PER_ARRAY_TYPE;
    }

    for (int i = 0; i < MAX_THREADS_NUMBER; i++) {
        fprintf(stat_fd, "Average time for %2d threads: %f\n", i + 1, stat->avg_exec_time_array[i]);
        fprintf(avg_fd, "%d,%f\n", i + 1, stat->avg_exec_time_array[i]);
    }

    fprintf(stat_fd, "\n\nSpeedup:\n");
    double linear_time = stat->avg_exec_time_array[0];
    for (int i = 0; i < MAX_THREADS_NUMBER; i++) {
        stat->speedup_array[i] = linear_time / stat->avg_exec_time_array[i];
        fprintf(stat_fd, "Speedup for %2d threads: %f\n", i + 1, stat->speedup_array[i]);
        fprintf(speedup_fd, "%d,%f\n", i + 1, stat->speedup_array[i]);
    }

    fprintf(stat_fd, "\n\nEfficiency:\n");
    for (int i = 0; i < MAX_THREADS_NUMBER; i++) {
        stat->efficiency_array[i] = stat->speedup_array[i] / (i + 1);
        fprintf(stat_fd, "Efficiency for %2d threads: %f\n", i + 1, stat->efficiency_array[i]);
        fprintf(efficiency_fd, "%d,%f\n", i + 1, stat->efficiency_array[i]);
    }

    fclose(avg_fd);
    fclose(speedup_fd);
    fclose(efficiency_fd);
}

void _print_arrays(int *array, int *sorted_array, int array_length) {
    printf("\nArray:\n");
    for (int i = 0; i < array_length; i++) {
        printf("%d ", array[i]);
    }

    printf("\nSorted array:\n");
    for (int i = 0; i < array_length; i++) {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");
}