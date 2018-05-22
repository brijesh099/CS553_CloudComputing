#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=compute
#SBATCH --output="mysort20GB_16.log"

make
#java MySort data-20GB.in 8
java -Xms64m -Xmx2g MySort data-20GB.in 16
echo 'Starting Valsort execution:'
/usr/bin/valsort "/tmp/outputBrijesh.dat" 