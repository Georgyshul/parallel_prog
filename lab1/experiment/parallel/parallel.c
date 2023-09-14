#include "parallel.h"

double *run_parallel_avg_time(int array_length, int experiments_number,
                              int max_threads_number, FILE *log_fd) {
  int *exp_array = (int *)calloc(array_length, sizeof(int));
  double *avg_time_for_threads =
      (double *)calloc(max_threads_number, sizeof(double));

  for (int i = 0; i < experiments_number; i++) {
    fprintf(log_fd, "\nRun n.%2d\n--------\n", i + 1);

    srand(time(NULL));
    for (int j = 0; j < array_length; j++) {
      exp_array[j] = rand();
    }

    for (int threads = 1; threads <= max_threads_number; threads++) {
      double exec_time = run_n_threads(exp_array, array_length, threads);
      avg_time_for_threads[threads - 1] += exec_time;
      fprintf(log_fd, "%-2d threads: %f\n", threads, exec_time);
    }
  }

  for (int i = 0; i < max_threads_number; i++) {
    avg_time_for_threads[i] /= experiments_number;
  }

  free(exp_array);

  return avg_time_for_threads;
}

double run_n_threads(int *exp_array, int array_length, int threads) {
  int max = exp_array[0];

  double start = omp_get_wtime();
#pragma omp parallel num_threads(threads) shared(exp_array, array_length) \
    reduction(max                                                         \
              : max) default(none)
  {
#pragma omp for
    for (int j = 0; j < array_length; j++) {
      if (exp_array[j] > max) {
        max = exp_array[j];
      }
    }
  }
  double end = omp_get_wtime();

  return end - start;
}