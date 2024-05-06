CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3 -fopenmp
LDFLAGS = -lm -fopenmp

TARGET = simpson.exe
SRC = simpson.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(TARGET) $(OBJ)


