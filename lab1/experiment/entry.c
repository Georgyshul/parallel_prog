#include "entry.h"

#include "linear/linear.h"
#include "parallel/parallel.h"

int main() {
  int array_length = 10000000;
  int max_threads_number = 20;
  int experiments_number = 50;

  FILE *log_fd = fopen("logs.txt", "w+");

  double avg_linear_time =
      run_linear_avg_time(array_length, experiments_number, log_fd);
  int avg_linear_operations =
      run_linear_operations_count(array_length, experiments_number, log_fd);
  double *avg_parallel_exec_time = 
      run_parallel_avg_time(array_length, experiments_number, max_threads_number, log_fd);

  return_stats(avg_linear_time, avg_linear_operations, avg_parallel_exec_time,
               max_threads_number, log_fd);

  free(avg_parallel_exec_time);
  fclose(log_fd);

  return 0;
}

void return_stats(double avg_linear_time, int avg_linear_operations,
                  double *avg_parallel_exec_time, int max_threads_number,
                  FILE *log_fd) {

  fprintf(log_fd, "\n----------------------------------------------------\n");
  fprintf(log_fd, "\nAverage linear time: %f\nAverage operations number: %d\n",
          avg_linear_time, avg_linear_operations);

  fprintf(log_fd, "\n\nAverage execution time for each amount of threads:\n");
  for (int i = 0; i < max_threads_number; i++) {
    fprintf(log_fd, "Average time for %2d threads: %f\n", i + 1,
            avg_parallel_exec_time[i]);
  }

  fprintf(log_fd, "\n\nSpeedup:\n");
  double *speedup_array = (double *)calloc(max_threads_number, sizeof(double));
  double linear_time = avg_parallel_exec_time[0];
  for (int i = 0; i < max_threads_number; i++) {
    speedup_array[i] = linear_time / avg_parallel_exec_time[i];
    fprintf(log_fd, "Speedup for %2d threads: %f\n", i + 1, speedup_array[i]);
  }

  fprintf(log_fd, "\n\nEfficiency:\n");
  double *efficiency_array =
      (double *)calloc(max_threads_number, sizeof(double));
  for (int i = 0; i < max_threads_number; i++) {
    efficiency_array[i] = speedup_array[i] / (i + 1);
    fprintf(log_fd, "Efficiency for %2d threads: %f\n", i + 1,
            efficiency_array[i]);
  }

  free(speedup_array);
  free(efficiency_array);
}
