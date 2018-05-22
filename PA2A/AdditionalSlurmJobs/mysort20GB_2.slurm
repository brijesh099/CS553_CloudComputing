#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=compute
#SBATCH --output="mysort20GB_2.log"

make
#java MySort data-20GB.in 8
java -Xms64m -Xmx2g MySort data-20GB.in 2
echo 'Starting Valsort execution:'
/usr/bin/valsort "/tmp/outputBrijesh.dat" 