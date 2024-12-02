PRG = verihush

CC = gcc

SRC = main.c
SRC_DIR = src

BIN_DIR = bin

DEBUG_DIR = debug

CFLAGS = -Wall -Werror -Wextra -Wpedantic -ggdb -O0 -std=gnu17

MEMCHECKFLAGS = -v\
								-s\
								--vgdb=full\
								--time-stamp=yes\
								--track-fds=all\
								--leak-check=full\
								--show-leak-kinds=all\
							 	--read-var-info=yes\
							 	--progress-interval=3600\
								--track-origins=yes\
								--keep-stacktraces=alloc-and-free\
								--xtree-memory=full\
								--xtree-memory-file=$(DEBUG_DIR)/memcheck/xtmemory.kcg

CALLGRINDFLAGS = -v\
								 -s\
								 --callgrind-out-file=$(DEBUG_DIR)/callgrind/callgrind.out\
								 --dump-instr=yes\
								 --collect-jumps=yes

MASSIFFLAGS = -v\
								 -s\
								 --massif-out-file=$(DEBUG_DIR)/callgrind/callgrind.out\

all: directories $(PRG) test

$(PRG):
	echo "Compiling ${PRG}"
	$(CC) $(CLFAGS) -o $(BIN_DIR)/$(PRG) $(SRC_DIR)/$(SRC)

test: test-memcheck test-callgrind test-massif

test-memcheck:
	valgrind --tool=memcheck $(MEMCHECKFLAGS) $(BIN_DIR)/$(PRG) -e hello
	valgrind --tool=memcheck $(MEMCHECKFLAGS) $(BIN_DIR)/$(PRG) -d khoor

test-callgrind:
	valgrind --tool=callgrind $(CALLGRINDFLAGS) $(BIN_DIR)/$(PRG) -e hello
	valgrind --tool=callgrind $(CALLGRINDFLAGS) $(BIN_DIR)/$(PRG) -d khoor

test-massif:
	valgrind --tool=massif $(MASSIFFLAGS) $(BIN_DIR)/$(PRG) -e hello
	valgrind --tool=massif $(MASSIFFLAGS) $(BIN_DIR)/$(PRG) -d khoor

directories:
	echo "Creating"
	mkdir -p $(BIN_DIR)
	mkdir -p $(DEBUG_DIR)/memcheck
	mkdir -p $(DEBUG_DIR)/callgrind
	mkdir -p $(DEBUG_DIR)/massif

clean:
	rm -rf $(BIN_DIR)/*

purge:
	rm -rf $(BIN_DIR)

