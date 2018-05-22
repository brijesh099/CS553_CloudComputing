#!/bin/bash
#SBATCH --partition=compute
#SBATCH --output="HadoopSort20GB.log"

make
hadoop jar HadoopSort.jar HadoopSort -D mapred.reduce.tasks=1 /input/data-20GB /user/bmavani/output-hadoop
hadoop jar /opt/hadoop-2.9.0/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.9.0.jar teravalidate /user/bmavani/output-hadoop /user/bmavani/report-hadoop
hadoop fs -get /user/bmavani/report-hadoop/part-r-00000