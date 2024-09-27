# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Directories
SRC_DIR = src
TEST_DIR = tests

# Source files
SRC_FILES = $(SRC_DIR)/matrix_operations.c
OBJ_FILES = $(SRC_FILES:.c=.o)

# Test files
TEST_FILES = $(TEST_DIR)/matrix_operations_tests.c
TEST_OBJ_FILES = $(TEST_FILES:.c=.o)

# Executables
TEST_TARGET = matrix_operations_tests

# Default target
all: $(TEST_TARGET)

# Build the test executable
$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule to compile source files to object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/matrix_operations.h
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule to compile test files to object files
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c $(SRC_DIR)/matrix_operations.h
	$(CC) $(CFLAGS) -c $< -o $@

# Target to run the tests
run_matrix_operations_tests: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up
clean:
	rm -f $(OBJ_FILES) $(TEST_OBJ_FILES) $(TEST_TARGET)