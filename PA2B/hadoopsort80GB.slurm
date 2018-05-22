#!/bin/bash
#SBATCH --partition=compute
#SBATCH --output="HadoopSort80GB.log"

make
hadoop jar HadoopSort.jar HadoopSort -D mapred.map.tasks=4 -D mapred.reduce.tasks=4 -D mapreduce.map.output.compress="true" -D mapreduce.map.output.compress.codec="org.apache.hadoop.io.compress.SnappyCodec" /input/data-80GB /user/bmavani/output-hadoop
hadoop jar /opt/hadoop-2.9.0/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.9.0.jar teravalidate /user/bmavani/output-hadoop /user/bmavani/report-hadoop
hadoop fs -get /user/bmavani/report-hadoop/part-r-00000