#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=compute
#SBATCH --output="mysort2GB_4.log"

make
java MySort data-2GB.in 4
echo 'Starting Valsort execution:'
srun /usr/bin/valsort "/tmp/outputBrijesh.dat"