# Makefile for AArch64 assembly program

# Variables
AS = as                      # Assembler
LD = ld                      # Linker
ASFLAGS = -g                 # Assembler flags (e.g., debugging info)
LDFLAGS =                    # Linker flags
NAME = add
OBJ = $(NAME).o              # Object file
TARGET = $(NAME)             # Output executable
SRC = $(NAME).s              # Assembly source file

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Rule to assemble the source file
$(OBJ): $(SRC)
	$(AS) $(ASFLAGS) -o $@ $<

# Rebuild target: cleans and builds everything
rebuild: clean all

# Run the program after building
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f *.o $(TARGET)

test:
	make clean
	as add_fn.s -o add_fn_asm.o
	gcc -c add_fn.c -o add_fn_c.o
	gcc add_fn_c.o add_fn_asm.o -o add_fn
	./add_fn

test2:
	make clean
	as add_fn2.s -o add_fn2_asm.o
	gcc -c add_fn2.c -o add_fn2_c.o
	gcc add_fn2_c.o add_fn2_asm.o -o add_fn2
	./add_fn2

# Phony targets
.PHONY: all clean rebuild run