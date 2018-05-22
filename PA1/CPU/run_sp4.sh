#!/bin/bash

echo "Hello, $USER."
make all

#gcc -o MyCPUBench.exe MyCPUBench.c -lpthread
for j in `seq 1 3`;
	do
	for i =`9`;
        do
			sbatch run$i.slurm
        done
	done

