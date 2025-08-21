CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude
SRC=src/main.c src/process_list.c
OUT=taskman

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

