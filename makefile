#
CC = gcc

main: main.o 
	$(CC) main.o -o main

main.o: main.c cckr.h
	$(CC) -c $(CFLAGS) main.c -o main.o

cckr.o: cckr.c cckr.h
	$(CC) -c $(CFLAGS) cckr.c -o cckr.o

cckr_eval.o: cckr-evaluate.c cckr-evaluate.h
	$(CC) -c

srcs = src/cckr.c src/cckr-evaluate.c src/main.c
objs = cckr.o cckr-evaluate.o main.o
gcc -c $(srcs)  -o $(objs)
gcc $(objs) -o cckr
