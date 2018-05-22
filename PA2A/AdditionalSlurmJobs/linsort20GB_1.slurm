#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=compute
#SBATCH --output="linsort20GB_1.log"

time LC_ALL=C /usr/bin/sort -o "/tmp/linsort20GB.out" "/input/data-20GB.in"
time /usr/bin/valsort "/tmp/linsort20GB.out"
