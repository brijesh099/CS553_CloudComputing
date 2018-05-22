#!/bin/bash
#SBATCH --partition=compute
#SBATCH --output="SparkSort80GB.log"

make
spark-submit --class SparkSort --master yarn --deploy-mode client --driver-memory 2g --executor-memory 4g --executor-cores 4 --num-executors 4 SparkSort.jar /input/data-80GB /user/bmavani/output-spark
hadoop jar /opt/hadoop-2.9.0/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.9.0.jar teravalidate /user/bmavani/output-spark /user/bmavani/report-spark
hadoop fs -get /user/bmavani/report-spark/part-r-00000
