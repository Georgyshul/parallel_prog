#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void shellSort(int *array, int array_length, int rank, int size) {
    int s, i;

    for (s = array_length / 2; s > 0; s /= 2) {
        MPI_Status status;

        // int *num_iterations = (int *)calloc(size, sizeof(int));
        // for (int i = 0; i < size; i++) {
        //     num_iterations[i] = s / size;
        // }

        // int remainder = s % size;

        // while (remainder > 0) {
        //     num_iterations[remainder] += 1;
        //     remainder--;
        // }

        // int *starts = (int *)calloc(size, sizeof(int));
        // for (int i = 1; i < size; i++) {
        //     starts[i] += num_iterations[i - 1];
        //     starts[i] += starts[i - 1];
        // }

        // int start_end_step[3] = {starts[rank], starts[rank] + num_iterations[rank], s};

        // int start = start_end_step[0];
        // int end = start_end_step[1];
        // int step = start_end_step[2];

        for (i = start; i < end; i++) {
            for (int j = i + step; j < array_length; j += step) {
                int key = array[j];
                int k = j - step;
                while (k >= 0 && array[k] > key) {
                    array[k + step] = array[k];
                    k -= step;
                }
                array[k + step] = key;
            }
        }

        if (rank != 0) {
            MPI_Send(array, array_length, MPI_INT, 0, rank, MPI_COMM_WORLD);
            MPI_Send(start_end_step, 3, MPI_INT, 0, 2 * rank, MPI_COMM_WORLD);
        } else {
            for (int i = 1; i < size; i++) {
                int *tmp_array = (int*)calloc(array_length, sizeof(int));
                MPI_Recv(tmp_array, array_length, MPI_INT, i, i, MPI_COMM_WORLD, &status);
                MPI_Recv(start_end_step, 3, MPI_INT, i, 2 * i, MPI_COMM_WORLD, &status);

                for (int j = start_end_step[0]; j < start_end_step[1]; j++) {
                    for (int k = j; k < array_length; k += s) {
                        array[k] = tmp_array[k];
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    int rank, size;
    int array_size = 100000;
    int *array = (int*)malloc(array_size * sizeof(int));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < array_size; i++) {
            array[i] = rand() % 100;
        }
    }
    MPI_Bcast(array, array_size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    shellSort(array, array_size, rank, size);

    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();

    MPI_Finalize();

    if (rank == 0) {
        // for (int i = 0; i < array_size; i++) {
        //     printf("%d ", array[i]);
        // }
        printf("\n%f\n", end_time - start_time);
    }

    return 0;
}
