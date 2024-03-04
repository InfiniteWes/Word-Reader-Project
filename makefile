# Define compiler
CC=gcc

# Define any compile-time flags
CFLAGS=-Wall -g

# Define the target executable
TARGET=word_reader

# 'all' target specifies what to build when you run just 'make'
all: $(TARGET)

# Rule for building the target executable
$(TARGET): word_reader.o
	$(CC) $(CFLAGS) word_reader.o -o $(TARGET)

# Rule for compiling the source file
word_reader.o: word_reader.c
	$(CC) $(CFLAGS) -c word_reader.c

# 'clean' target for removing compiled files
clean:
	rm -f $(TARGET) *.o

# Prevent make from doing something with a file named 'all' or 'clean'
.PHONY: all clean
