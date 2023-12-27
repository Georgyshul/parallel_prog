#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_FILE_NAME_LENGTH 50
#define NUM_RUNS 50


static const char LOG_FILE_NAME[MAX_FILE_NAME_LENGTH] = {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', 'm', 'p', 'i', '.', 'c', 's', 'v', '\0'};


void generate_array(int *array, int array_length, int range);
double find_max_n_threads_mpi(int *array, int array_length, int *max);

int main(int argc, char *argv[]) {

    const int array_length = 10000000;
    const int range = 1000000;
    
    int *array = (int *)calloc(array_length, sizeof(int));

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int max;
    double total_time = 0.0;

    for (int i = 0; i < NUM_RUNS; i++) {
        if (rank == 0) {
            generate_array(array, array_length, range);
        }

        MPI_Bcast(array, array_length, MPI_INT, 0, MPI_COMM_WORLD);

        total_time += find_max_n_threads_mpi(array, array_length, &max);
    }

    if (rank == 0) {
        FILE *fd = fopen(LOG_FILE_NAME, "a");
        fprintf(fd, "%d,%f\n", size, total_time / NUM_RUNS);
        fclose(fd);
    }

    free(array);
    MPI_Finalize();

    return 0;
}

double find_max_n_threads_mpi(int *array, int array_length, int *max) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double localStart = MPI_Wtime();

    int local_max = array[0];
    int local_length = array_length / size;
    int remainder = array_length % size;

    int start = rank * local_length;
    int end = start + local_length;
    if (rank == size - 1) {
        end += remainder; // Adding the remainder to the last rank's portion
    }

    for (int j = start; j < end; j++) {
        if (array[j] > local_max) {
            local_max = array[j];
        }
    }

    MPI_Reduce(&local_max, max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    double localTime = MPI_Wtime() - localStart;

    double globalTime;
    MPI_Reduce(&localTime, &globalTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    return globalTime; // Time measurement is not implemented in this function
}

void generate_array(int *array, int array_length, int range) {
    for (int i = 0; i < array_length; i++) {
        array[i] = rand() % range;
    }

    array[rand() % array_length] = range + 1;
}
