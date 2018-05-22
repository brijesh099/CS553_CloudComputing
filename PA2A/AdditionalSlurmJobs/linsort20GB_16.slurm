#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=compute
#SBATCH --output="linsort20GB_16.log"

time LC_ALL=C /usr/bin/sort --parallel=16 -o "/tmp/linsort20GB.out" "/input/data-20GB.in"
time /usr/bin/valsort "/tmp/linsort20GB.out"
