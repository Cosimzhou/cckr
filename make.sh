#! /bin/bash

CC=gcc 

mkdir -p out
cd out
$CC -c ../src/cckr-tools.c -o cckr-tools.o
$CC -c ../src/cckr-const.c -o cckr-const.o
$CC -c ../src/cckr-common.c -o cckr.o
$CC -c ../src/cckr-evaluate.c -o cckr-evaluate.o
$CC -c ../src/main.c -o main.o
$CC main.o cckr.o cckr-evaluate.o cckr-const.o cckr-tools.o -o main
 
chmod 775 main
./main
