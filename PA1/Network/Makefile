CC=gcc
#CFLAGS=-g -Wall -O2 -lpthread

all:
	$(CC) -o MyNETBench-TCP MyNETBench-TCP.c -lpthread
	$(CC) -o MyNETBench-UDP MyNETBench-UDP.c -lpthread

clean:
	$(rm) *.o MyNETBench-TCP MyNETBench-UDP
