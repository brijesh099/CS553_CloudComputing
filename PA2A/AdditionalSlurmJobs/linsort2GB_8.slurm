#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=compute
#SBATCH --output="linsort2GB_8.log"

time LC_ALL=C /usr/bin/sort --parallel=8 -o "/tmp/linsort2GB.out" "/input/data-2GB.in"
time /usr/bin/valsort "/tmp/linsort2GB.out"
