CC = gcc
CFLAGS = -fopenmp -O3 -std=c99
LDFLAGS = -lgomp -llapack -lblas -lm 

all: rev

rev: clean
	$(CC) $(CFLAGS) rev.c -o ./bin/rev $(LDFLAGS) 


clean:
	rm -f ./bin/*
