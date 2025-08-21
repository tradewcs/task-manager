CC=gcc
CFLAGS=-Wall -Wextra -std=c11
SRC=src/main.c
OUT=taskman

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

