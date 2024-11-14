# Makefile for compiling AArch64 programs with variable assembly source

# Variables
CC = aarch64-linux-gnu-gcc       # AArch64 compiler/linker
AS = aarch64-linux-gnu-as        # AArch64 assembler
CFLAGS = -g                      # Compiler flags for debugging info
ASFLAGS = -g                     # Assembler flags for debugging info
CSRC = main.c                    # C source file
ASRC = $(src)                    # Assembly source file passed from command line
OBJ = main.o $(ASRC:.s=.o)       # Object files to generate based on ASRC
TARGET = $(ASRC:.s=)             # Output executable named after the assembly file

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile the C source file
main.o: $(CSRC)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to assemble the assembly source file
%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

# Rebuild target: cleans and builds everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f *.o
	find . -type f -executable -delete

# Phony targets
.PHONY: all clean rebuild run
