CC = gcc
CFLAGS = -Wall -Wextra -O3

TARGET = cracker

SRCS = main.c \
	src/oracle.c \
	src/bruteForce.c \
	src/divideAndConquer.c \
	src/dpMemoization.c \
	src/geneticAlgorithm.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) src/*.o *.o

.PHONY: all clean

