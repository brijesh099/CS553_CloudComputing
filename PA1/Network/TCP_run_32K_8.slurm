#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --output="TCP_32_8.%j.%N.out"
#SBATCH --wait-all-nodes=1

srun ./TCP_run_32K_8.sh $SLURM_JOB_NODELIST