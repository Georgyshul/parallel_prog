CC=gcc

OMP_DIR = ../../lab3/experiment
MPI_DIR = .

SRC_MPI := $(shell find $(MPI_DIR) -name "*.c" | sed -e 's/\.\///')

MPI_BUILD_DIR = $(MPI_DIR)/obj

OBJS_MPI := $(SRC_MPI:%.c=${MPI_BUILD_DIR}/%.o)

CFLAGS=-Wall -Wextra -Werror -std=c11 -fopenmp
LDFLAGS=$(shell pkg-config --cflags)

all: experiment_omp experiment_mpi calc_stats

experiment_omp:
	(cd $(OMP_DIR) && make)
	cp -r $(OMP_DIR)/log ./omp_log
	(cd $(OMP_DIR) && make clean)
	(cd $(OMP_DIR) && make clean_logs)

experiment_mpi: build_mpi
	@mkdir -p log
	for number in 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ; do \
		mpirun -np $$number ./run.out ; \
	done
	python3 concat_csv.py

build_mpi:
	mpicc -o run.out $(MPI_DIR)/entry.c

calc_stats:
	python3 calc_stats.py

${MPI_BUILD_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf *.o *.out $(MPI_BUILD_DIR) *.btr

clean_logs:
	rm -r log omp_log
