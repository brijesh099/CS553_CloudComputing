#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

./MyCPUBench cpu_QP_4thread.dat

