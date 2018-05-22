HADOOP_CLASSPATH = /opt/hadoop-2.9.0/etc/hadoop:/opt/hadoop-2.9.0/share/hadoop/common/lib/*:/opt/hadoop-2.9.0/share/hadoop/common/*:/opt/hadoop-2.9.0/share/hadoop/hdfs:/opt/hadoop-2.9.0/share/hadoop/hdfs/lib/*:/opt/hadoop-2.9.0/share/hadoop/hdfs/*:/opt/hadoop-2.9.0/share/hadoop/yarn:/opt/hadoop-2.9.0/share/hadoop/yarn/lib/*:/opt/hadoop-2.9.0/share/hadoop/yarn/*:/opt/hadoop-2.9.0/share/hadoop/mapreduce/lib/*:/opt/hadoop-2.9.0/share/hadoop/mapreduce/*:/opt/hadoop-2.9.0/contrib/capacity-scheduler/*.jar

SPARK_CLASSPATH = /opt/spark-2.3.0-bin-hadoop2.7/jars/spark-core_2.11-2.3.0.jar:/opt/spark-2.3.0-bin-hadoop2.7/jars/spark-sql_2.11-2.3.0.jar:/opt/spark-2.3.0-bin-hadoop2.7/jars/scala-compiler-2.11.8.jar:/opt/spark-2.3.0-bin-hadoop2.7/jars/scala-library-2.11.8.jar
exec:run

run:all
		
		javac -classpath $(HADOOP_CLASSPATH) HadoopSort.java
		jar cvf HadoopSort.jar *.class
		
		javac -classpath $(SPARK_CLASSPATH) SparkSort.java
		jar cvf SparkSort.jar SparkSort.class

all:
		$(RM) *.class
		$(RM) *.jar

.PHONY: exec run