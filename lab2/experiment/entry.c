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
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '0', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '1', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '2', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '3', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '4', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '5', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 's', 'p', 'u', '_', '6', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '0', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '1', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '2', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '3', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '4', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '5', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'e', 'f', 'f', '_', '6', '.', 'c', 's', 'v', '\0'}};


int main() {
    const int array_length = 10000000;
    const int target = 16;

    FILE *log_fd = fopen("logs.txt", "w+");
    FILE *stat_fd = fopen("stat.txt", "w+");
    int *array = (int*)calloc(array_length, sizeof(int));

    for (int array_type = 0; array_type < AMOUNT_OF_ARRAY_TYPES; array_type++) {
        stats stat = {{0}, {0}, {0}};
        fprintf(log_fd, "Array type %d\n------------\n", array_type);
        for (int i = 0; i < RUNS_PER_ARRAY_TYPE; i++) {
            generate_array(&array, array_length, target, array_type);
            fprintf(log_fd, "RUN n.%d\n", i+1);
            make_experiment(array, target, array_length, array_type, log_fd, &stat);
        }
        fprintf(stat_fd, "Array type %d\n------------\n", array_type);
        calculate_stats(&stat, array_type, stat_fd);
    }

    free(array);
    fclose(log_fd);
    fclose(stat_fd);

    return 0;
}

void make_experiment(int *array, int target, int array_length, int array_type, FILE *log_fd, stats *stat) {
    for (int num_threads = 1; num_threads <= MAX_THREADS_NUMBER; num_threads++) {
        int idx = -1;
        double exec_time = find_occurance_n_threads(array, target, array_length, num_threads, &idx);
        check_result(array, target, idx, array_type, log_fd);
        fprintf(log_fd, "%-2d threads: %f\n", num_threads, exec_time);

        stat->avg_exec_time_array[num_threads - 1] += exec_time;
    }
}

void check_result(int *array, int target, int idx, int array_type, FILE *log_fd) {
    if (array_type == ELEMENT_NOT_EXIST) {
        if (idx != -1) {
            fprintf(log_fd, "ERROR: INCORRECT RESULT\n");
        }
    } else if (array[idx] != target) {
        fprintf(log_fd, "ERROR: INCORRECT RESULT\n");
    }
}

void generate_array(int **array, int array_length, int target, int array_type) {
    srand(time(NULL));

    switch (array_type) {
        case ELEMENT_IS_FIRST:
            generate_element_is_first(array, target, array_length);
            break;

        case ELEMENT_IN_BEGINNING:
            generate_element_in_beginning(array, target, array_length);
            break;

        case ELEMENT_IN_END:
            generate_element_in_end(array, target, array_length);
            break;
        
        case ELEMENT_IS_LAST:
            generate_element_is_last(array, target, array_length);
            break;  
        
        case ELEMENT_IN_MIDDLE:
            generate_element_in_middle(array, target, array_length);
            break;
        
        case ELEMENT_NOT_EXIST:
            generate_element_not_exist(array, target, array_length);
            break;
        
        case ELEMENT_EVERYWHERE:
            generate_element_everywhere(array, target, array_length);
            break;
    }   
}   

void generate_element_is_first(int **array, int target, int array_length) {
    generate_rand_array_without_target(array, target, array_length);

    (*array)[0] = target;
}

void generate_element_in_beginning(int **array, int target, int array_length) {
    generate_rand_array_without_target(array, target, array_length);

    int position = rand() % (array_length / (MAX_THREADS_NUMBER * 10));
    (*array)[position] = target;
}

void generate_element_in_end(int **array, int target, int array_length) {
    generate_rand_array_without_target(array, target, array_length);

    int position = rand() % (array_length / (MAX_THREADS_NUMBER * 10));
    (*array)[array_length - position] = target;
}

void generate_element_is_last(int **array, int target, int array_length) {
    generate_rand_array_without_target(array, target, array_length);

    (*array)[array_length - 1] = target;
}

void generate_element_in_middle(int **array, int target, int array_length) {
    generate_rand_array_without_target(array, target, array_length);

    int position = array_length / 2 + rand() % (array_length / MAX_THREADS_NUMBER);
    (*array)[position] = target;
}

void generate_element_not_exist(int **array, int target, int array_length) {
    generate_rand_array_without_target(array, target, array_length);
}

void generate_element_everywhere(int **array, int target, int array_length) {
    for (int i = 0; i < array_length; i++) {
        (*array)[i] = target;
    } 
}

void generate_rand_array_without_target(int **array, int target, int array_length) {
    for (int j = 0; j < array_length; j++) {
      int element = rand();
      if (element == target) { element = target + 10; }
      (*array)[j] = element;
    }
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