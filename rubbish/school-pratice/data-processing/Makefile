# Makefile for AArch64 assembly program

# Variables
AS = aarch64-linux-gnu-as      # AArch64 assembler
CC = aarch64-linux-gnu-gcc     # AArch64 compiler/linker
ASFLAGS = -g                   # Assembler flags (e.g., debugging info)
CFLAGS =                        # Compiler/Linker flags
OBJ = arith1.o                 # Object file
TARGET = arith1                # Output executable
SRC = arith1.s                 # Assembly source file

# Default target
all: $(TARGET)

# Rule to build the executable using gcc for linking with libc
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lc

# Rule to assemble the source file
$(OBJ): $(SRC)
	$(AS) $(ASFLAGS) -o $@ $<

# Rebuild target: cleans and builds everything
rebuild: clean all

# Run the program after building
# run: $(TARGET)
# 	qemu-aarch64 ./$(TARGET)      # Use QEMU to run AArch64 binaries on non-AArch64 systems
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean rebuild run