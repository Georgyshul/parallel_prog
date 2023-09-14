#include "linear.h"

double run_linear_avg_time(int array_length, int experiments_number,
                           FILE *log_fd) {
  int *exp_array = (int *)calloc(array_length, sizeof(int));
  double avg_time = 0;

  fprintf(log_fd, "Linear program execution time:\n");
  for (int i = 0; i < experiments_number; i++) {
    srand(time(NULL));
    for (int j = 0; j < array_length; j++) {
      exp_array[j] = rand();
    }

    int max = exp_array[0];
    double start = omp_get_wtime();

    for (int j = 0; j < array_length; j++) {
      if (exp_array[j] > max) {
        max = exp_array[j];
      }
    }

    double end = omp_get_wtime();
    double exec_time = end - start;

    avg_time += exec_time;
    fprintf(log_fd, "%f\n", exec_time);
  }

  free(exp_array);
  avg_time /= experiments_number;

  return avg_time;
}

double run_linear_operations_count(int array_length, int experiments_number,
                                   FILE *log_fd) {
  int *exp_array = (int *)calloc(array_length, sizeof(int));
  int avg_oper_count = 0;

  fprintf(log_fd, "\nLinear program operations count:\n");
  for (int i = 0; i < experiments_number; i++) {
    srand(time(NULL));
    for (int j = 0; j < array_length; j++) {
      exp_array[j] = rand();
    }

    int max = exp_array[0];
    int oper_count = 0;

    for (int j = 0; j < array_length; j++) {
      if (exp_array[j] > max) {
        max = exp_array[j];
        oper_count++;
      }
      oper_count++;
    }

    avg_oper_count += oper_count;
    fprintf(log_fd, "%d\n", oper_count);
  }

  free(exp_array);
  avg_oper_count /= experiments_number;

  return avg_oper_count;
}