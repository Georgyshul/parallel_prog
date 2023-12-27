CC=gcc

OMP_DIR = ./omp/
MPI_DIR = ./mpi/

SRC_OMP := $(shell find $(OMP_DIR) -name "*.c" | sed -e 's/\.\///')
SRC_MPI := $(shell find $(MPI_DIR) -name "*.c" | sed -e 's/\.\///')

OMP_BUILD_DIR = obj
MPI_BUILD_DIR = $(MPI_DIR)/obj

OBJS_OMP := $(SRC_OMP:%.c=${OMP_BUILD_DIR}/%.o)
OBJS_MPI := $(SRC_MPI:%.c=${MPI_BUILD_DIR}/%.o)

CFLAGS=-Wall -Wextra -Werror -std=c11 -fopenmp
LDFLAGS=$(shell pkg-config --cflags)

all: experiment_omp experiment_mpi calc_stats

experiment_omp: $(OBJS_OMP)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o run.out
	@mkdir -p log
	./run.out

experiment_mpi: build_mpi
	for number in 1 2 3 4 5 6 7 8 9 10 ; do \
		mpirun -np $$number ./run.out ; \
	done

build_mpi:
	mpicc -o run.out $(MPI_DIR)/entry.c

calc_stats:
	python3 calc_stats.py

${OMP_BUILD_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

${MPI_BUILD_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf *.o *.out $(OMP_BUILD_DIR)
	rm -rf *.o *.out $(MPI_BUILD_DIR)

clean_logs:
	rm -f log/*.csv
