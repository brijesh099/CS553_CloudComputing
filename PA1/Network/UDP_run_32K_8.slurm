#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --output="UDP_32_8.%j.%N.out"
#SBATCH --wait-all-nodes=1

srun ./UDP_run_32K_8.sh $SLURM_JOB_NODELIST