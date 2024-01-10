#include "entry.h"

#define MAX_FILE_NAME_LENGTH 50


static const char LOG_FILE_NAME[AMOUNT_OF_ARRAY_TYPES]
                                      [MAX_FILE_NAME_LENGTH] = {
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '0', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '1', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '2', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '3', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '4', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '5', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '6', '.', 'c', 's', 'v', '\0'},
                                          {'.', '/', 'l', 'o', 'g', '/', 's', 't', 'a', 't', '_', 'a', 'v', 'g', '_', '7', '.', 'c', 's', 'v', '\0'}};


int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    const int array_length = 100000;
    int m = array_length;

    int *array;
    int *sorted_array;

    double avg_exec_time_array[AMOUNT_OF_ARRAY_TYPES] = {0};

    int chunk_size;
    int *chunk;

    double start_time;
    double end_time;

    for (int array_type = 0; array_type < AMOUNT_OF_ARRAY_TYPES; array_type++) {
        for (int run = 0; run < RUNS_PER_ARRAY_TYPE; run++) {
            if (rank == 0) {
                chunk_size = array_length / size;
                int remainder = array_length % size;

                if (remainder != 0) {
                    chunk_size += 1;
                }

                array = (int *)calloc(chunk_size * size, sizeof(int));
                sorted_array = (int *)calloc(array_length, sizeof(int));

                generate_array(array, sorted_array, array_length, array_type);

                for (int i = array_length; i < size * chunk_size; i++) {
                    array[i] = -1;
                }

                start_time = MPI_Wtime();
            }

            MPI_Bcast(&chunk_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
            chunk = (int *)calloc(chunk_size, sizeof(int));
            MPI_Scatter(array, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

            shell_sort(chunk, chunk_size);

            int step = 1;
            while (step < size) {
                if (rank % (2 * step) == 0) {
                    if (rank + step < size) {
                        int sender = rank + step;
                        MPI_Recv(&m, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, &status);
                        int *other = (int *)calloc(m, sizeof(int));
                        MPI_Recv(other, m, MPI_INT, sender, 0, MPI_COMM_WORLD, &status);

                        chunk = merge(chunk, chunk_size, other, m);
                        chunk_size += m;
                    }
                } else {
                    int reciever = rank - step;
                    MPI_Send(&chunk_size, 1, MPI_INT, reciever, 0, MPI_COMM_WORLD);
                    MPI_Send(chunk, chunk_size, MPI_INT, reciever, 0, MPI_COMM_WORLD);
                    break;
                }
                step *= 2;
            }

            if(rank == 0) {
                end_time = MPI_Wtime();
                double exec_time = end_time - start_time;
                avg_exec_time_array[array_type] += exec_time;
            }

            if (rank == 0) {
                int start = 0;
                while (chunk[start] == -1) {
                    start++;
                }
                if (check_result(chunk + start, sorted_array, array_length)) {
                    fprintf(stderr, "ERROR! array_type: %2d\n", array_type);
                }
            }
        }
    }

    if (rank == 0) {
        for (int array_type = 0; array_type < AMOUNT_OF_ARRAY_TYPES; array_type++) {
            FILE *fd = fopen(LOG_FILE_NAME[array_type], "a");
            fprintf(fd, "%d,%f\n", size, avg_exec_time_array[array_type] /= RUNS_PER_ARRAY_TYPE);
            fclose(fd);
        }

        free(array);
        free(sorted_array);
    }

    free(chunk);

    MPI_Finalize();
    return 0;
}

void shell_sort(int *array, int array_length) {
    int s, i;

    for (s = array_length / 2; s > 0; s /= 2) {
        for (i = 0; i < s; i++) {
            for (int j = i + s; j < array_length; j += s) {
                int key = array[j];
                int k = j - s;
                while (k >= 0 && array[k] > key) {
                    array[k + s] = array[k];
                    k -= s;
                }
                array[k + s] = key;
            }
        }
    }
}

int *merge(int *array1, int len1, int *array2, int len2) {
    int i = 0;
    int j = 0;
    int k = 0;
    int *result = (int *)calloc(len1 + len2, sizeof(int));

    while (i < len1 && j < len2) {
        if (array1[i] < array2[j]) {
            result[k] = array1[i];
            i++;
            k++;
        } else {
            result[k] = array2[j];
            j++;
            k++;
        }
    }

    if (i == len1) {
        while (j < len2) {
            result[k] = array2[j];
            j++;
            k++;
        }
    } else {
        while (i < len1) {
            result[k] = array1[i];
            i++;
            k++;
        }
    }

    return result;
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