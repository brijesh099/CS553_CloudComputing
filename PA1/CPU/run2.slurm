#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

./MyCPUBench cpu_QP_2thread.dat

