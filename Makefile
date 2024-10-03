# Makefile for AArch64 Assembly project

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Output executable name
TARGET = $(BIN_DIR)/program

# Compiler and flags
AS = as
LD = ld
ASFLAGS = -g            # -g for debugging support
LDFLAGS =               # Flags for the linker

# List of source files (.s files in src directory)
SRCS = $(wildcard $(SRC_DIR)/*.s)

# Object files (same names as source files, but in the obj directory)
# OBJS = $(SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)
OBJS = $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(SRCS))

# Default target: build the program
all: dir $(TARGET)

dir:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)

# Create bin directory if it doesn't exist
# $(BIN_DIR):
# 	@mkdir -p $(BIN_DIR)

# Create obj directory if it doesn't exist
# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)


# Rule to build the target executable
$(TARGET): $(OBJS) | $(BIN_DIR)
# @echo "Linking..."
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)
# @echo "Build complete."

# Rule to assemble .s files into .o object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s | $(OBJ_DIR)
# @echo "Assembling $<..."
	$(AS) $(ASFLAGS) -o $@ $<

# Clean build files
clean:
# @echo "Cleaning up..."
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

run: 
	./$(TARGET)

rebuild: clean all

# Phony targets (to avoid conflicts with files named 'clean', etc.)
.PHONY: all clean
