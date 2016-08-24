#! /bin/bash

CC=gcc 

mkdir -p out
cd out
$CC -c ../src/cckr-common.c -o cckr.o
$CC -c ../src/cckr-evaluate.c -o cckr-evaluate.o
$CC -c ../src/main.c -o main.o
$CC main.o cckr.o cckr-evaluate.o -o main
 
chmod 775 main
./main
