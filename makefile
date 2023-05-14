CC = gcc
CFLAGS = -Wall -Werror -g

# List all object files here
OBJ = main.o cd.o cdir.o exit.o fetch.o find.o ls.o mkdir.o rm.o rmdir.o touch.o

# The target executable
TARGET = main

# Compile everything
all: $(TARGET)

# Compile the main program
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each individual source file
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

