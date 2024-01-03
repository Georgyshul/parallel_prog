CC=gcc

SRC_LINEAR_DIR = linear
SRC_PARALLEL_DIR = parallel
SRC_ENTRY_DIR = .

SRC_LINEAR := $(shell find ${SRC_LINEAR_DIR} -name "*.c" | sed -e 's/\.\///')
SRC_PARALLEL := $(shell find ${SRC_PARALLEL_DIR} -name "*.c" | sed -e 's/\.\///')
SRC_ENTRY := $(shell find ${SRC_ENTRY_DIR} -name "*.c" | sed -e 's/\.\///')

BUILD_DIR = obj

OBJS_ENTRY := $(SRC_ENTRY:%.c=${BUILD_DIR}/%.o)
OBJS_LINEAR := $(SRC_LINEAR:%.c=${BUILD_DIR}/%.o)
OBJS_PARALLEL := $(SRC_PARALLEL:%.c=${BUILD_DIR}/%.o)

# CFLAGS=-Wall -Wextra -Werror -std=c11 -fopenmp
CFLAGS=-std=c11 -fopenmp
LDFLAGS=$(shell pkg-config --cflags)


all: experiment

experiment: $(OBJS_ENTRY) $(OBJS_LINEAR) $(OBJS_PARALLEL)
# experiment: $(OBJS_ENTRY) $(OBJS_PARALLEL)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o run.out
	@mkdir -p log
	./run.out
	./concat_csv.py

${BUILD_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf *.o *.out $(BUILD_DIR)

clean_logs:
	rm -f log/*.csv
	rm *.txt
	
codestyle:
	clang-format -i --style=google $(SRC_ENTRY_DIR)/*.c $(SRC_PARALLEL_DIR)/*.c
	clang-format -i --style=google $(SRC_ENTRY_DIR)/*.h $(SRC_PARALLEL_DIR)/*.h