#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --output="TCP.%j.%N.out"
#SBATCH --wait-all-nodes=1

srun ./run.sh $SLURM_JOB_NODELIST