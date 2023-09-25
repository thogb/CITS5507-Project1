#!/bin/bash

GCC_OPTIONS='-lomp -Xpreprocessor -fopenmp'

gcc simulation_sequential.c -o a.out
gcc $GCC_OPTIONS simulation_parallel.c -o b.out

FISH_AMOUNT=500000

./a.out $FISH_AMOUNT
export OMP_NUM_THREADS=2
./b.out $FISH_AMOUNT
export OMP_NUM_THREADS=4
./b.out $FISH_AMOUNT
export OMP_NUM_THREADS=8
./b.out $FISH_AMOUNT
export OMP_NUM_THREADS=16
./b.out $FISH_AMOUNT
export OMP_NUM_THREADS=32
./b.out $FISH_AMOUNT
export OMP_NUM_THREADS=64
./b.out $FISH_AMOUNT

