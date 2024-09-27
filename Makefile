# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Directories
SRC_DIR = src
TEST_DIR = tests

# Source files
SRC_FILES = $(SRC_DIR)/matrix_operations.c $(SRC_DIR)/c_donut_operations.c $(SRC_DIR)/driver.c
OBJ_FILES = $(SRC_FILES:.c=.o)

# Test files
TEST_FILES = $(TEST_DIR)/matrix_operations_tests.c
TEST_OBJ_FILES = $(TEST_FILES:.c=.o)

# Executables
TARGET = matrix_operations
TEST_TARGET = matrix_operations_tests
DONUT_TARGET = donut_program  # Renaming for clarity

# Default target
all: $(TARGET) $(TEST_TARGET) $(DONUT_TARGET)

# Build the main matrix operations target
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Build the test executable
$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Build the donut application
$(DONUT_TARGET): $(OBJ_FILES)
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

# Run the donut executable
run: $(DONUT_TARGET)
	./$(DONUT_TARGET)

# Clean up
clean:
	rm -f $(OBJ_FILES) $(TEST_OBJ_FILES) $(TARGET) $(TEST_TARGET) $(DONUT_TARGET)