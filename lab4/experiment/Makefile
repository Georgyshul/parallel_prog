CC=gcc

SRC_LINEAR_DIR = linear
SRC_PARALLEL_DIR = parallel
# SRC_ENTRY_DIR = .

MONITORING_DIR = omp_setup
MONITORING_SRC = monitoring.c

LOCKS_DIR = locks
LOCKS_SRC = locking.c

SRC_LINEAR := $(shell find ${SRC_LINEAR_DIR} -name "*.c" | sed -e 's/\.\///')
SRC_PARALLEL := $(shell find ${SRC_PARALLEL_DIR} -name "*.c" | sed -e 's/\.\///')
# SRC_ENTRY := $(shell find ${SRC_ENTRY_DIR} -name "*.c" | sed -e 's/\.\///')
SRC_ENTRY := entry.c

BUILD_DIR = obj

OBJS_ENTRY := $(SRC_ENTRY:%.c=${BUILD_DIR}/%.o)
OBJS_LINEAR := $(SRC_LINEAR:%.c=${BUILD_DIR}/%.o)
OBJS_PARALLEL := $(SRC_PARALLEL:%.c=${BUILD_DIR}/%.o)

CFLAGS=-Wall -Wextra -Werror -std=c11 -fopenmp
# CFLAGS=-std=c11 -fopenmp
LDFLAGS=$(shell pkg-config --cflags)

ccred=$(echo -e "\033[0;31m")
ccyellow=$(echo -e "\033[0;33m")
ccend=$(echo -e "\033[0m")


all: setup with_locks without_locks experiment

# experiment: $(OBJS_ENTRY) $(OBJS_LINEAR) $(OBJS_PARALLEL)
experiment: $(OBJS_ENTRY) $(OBJS_PARALLEL) $(OBJS_LINEAR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o run.out
	@mkdir -p log
	./run.out
	python3 calc_stats.py

${BUILD_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf *.o *.out $(BUILD_DIR)

clean_logs:
	rm -f log/*.csv

setup:
	@echo "\e[0;33m\n\n--------------------Started omp_setup section--------------------\e[0m"
	@$(CC) $(CFLAGS) ${MONITORING_DIR}/${MONITORING_SRC} -o setup.out
	@./setup.out

with_locks:
	@echo "\e[0;33m\n\n--------------------Started with_locks section--------------------\e[0m"
	@$(CC) $(CFLAGS) -DWITH_LOCK ${LOCKS_DIR}/${LOCKS_SRC} -o with_lock.out
	@./with_lock.out

without_locks:
	@echo "\e[0;33m\n\n--------------------Started without_locks section--------------------\e[0m"
	@$(CC) $(CFLAGS) ${LOCKS_DIR}/${LOCKS_SRC} -o without_lock.out
	@./without_lock.out

codestyle:
	clang-format -i --style=google $(SRC_ENTRY_DIR)/*.c $(SRC_PARALLEL_DIR)/*.c
	clang-format -i --style=google $(SRC_ENTRY_DIR)/*.h $(SRC_PARALLEL_DIR)/*.h