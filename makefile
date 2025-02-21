# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c11

# Executable name
TARGET = game

# Source files
SRCS = dungeonGame.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule: Build the executable
all: $(TARGET)

# Linking step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# PHONY targets to avoid conflicts with files named "clean" or "all"
.PHONY: all clean run
