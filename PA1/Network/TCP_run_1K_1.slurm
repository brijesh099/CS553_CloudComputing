#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --output="TCP_1K_1.%j.%N.out"
#SBATCH --wait-all-nodes=1

srun ./TCP_run_1K_1.sh $SLURM_JOB_NODELIST