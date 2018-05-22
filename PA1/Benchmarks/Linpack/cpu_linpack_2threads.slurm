#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=compute

cd ./l_mklb_p_2018.2.010/benchmarks_2018/linux/mkl/benchmarks/linpack
export OMP_NUM_THREADS=2
./runme_xeon64