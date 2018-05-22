#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=compute
#SBATCH --output="mysort2GB_16.log"

make
java MySort data-2GB.in 16
echo 'Starting Valsort execution:'
srun /usr/bin/valsort "/tmp/outputBrijesh.dat"