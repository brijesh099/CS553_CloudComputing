Name: Brijesh Mavani - A20406960
Course: Cloud Computing 
Assignment: PA-2B

In this programming assignment, we are implementing Hadoop and Spark sort application in a multi node environment.

A) Hadoop Sort

For this part Java was used as a programming language. For sorting using Hadoop, 3 class files were created. One for main function, second for mapper function and third for reducer function.

My code has been executed for 8GB, 20GB and 80GB files and results are provided. 

Assuming git is cloned or downloaded to the Linux test bed which also supports slurm based batch scheduling.  Assuming Hadoop and Spark classPath are already set. 

	Navigate to the folder cs553-pa2b.
	Java file name: HadoopSort.java
	Compile: Though make file has been created and provided, one can explicitly compile the code with command: javac -classpath $(HADOOP_CLASSPATH) HadoopSort.java
	Executing code: Slurm files are created for executing the code for sorting 8GB , 20GB and 80GB data files. Teravalidate will be executed after execution of java code to make sure output file is sorted correctly. Below are the slurm files:
	● hadoopsort8GB.slurm  -- for 8GB data file
	● hadoopsort20GB.slurm  -- for 20GB data file
	● hadoopsort80GB.slurm  -- for 80GB data file

	$sbatch hadoopsort8GB.slurm  -- for executing code for sorting 8GB data file
	$sbatch hadoopsort20GB.slurm  -- for executing code for sorting 20GB data file
	$sbatch hadoopsort80GB.slurm  -- for executing code for sorting 80GB data file
	
The result of slurm jobs will be stored in following log files: 
	● HadoopSort8GB.log  -- result of sorting 8GB data file
	● HadoopSort20GB.log  -- result of sorting 20GB data file
	● HadoopSort80GB.log  -- result of sorting 80GB data file


B) Spark Sort 

For this part also, Java was used as a programming language. For sorting using Spark only single class file was created. This class has a main method implemented. This class also extends the pairFunction class of Spark. The overrides methods for functions call has been written. sortByKey function has been used to sort the values based on key. After the sorting data will be written to output file. 

Assuming git is cloned or downloaded to the Linux test bed which also supports slurm based batch scheduling.  Assuming Hadoop and Spark classPath are already set. 

	Navigate to the folder cs553-pa2b.
	Java file name: SparkSort.java
	Compile: Though make file has been created and provided, one can explicitly compile the code with command: javac -classpath $(SPARK_CLASSPATH) SparkSort.java
	Executing code: Slurm files are created for executing the code for sorting 8GB , 20GB and 80GB data files. Teravalidate will be executed after execution of java code to make sure output file is sorted correctly. Below are the slurm files:
	● sparksort8GB.slurm  -- for 8GB data file
	● sparksort20GB.slurm  -- for 20GB data file
	● sparksort80GB.slurm  -- for 80GB data file

	$sbatch sparksort8GB.slurm  -- for executing code for sorting 8GB data file
	$sbatch sparksort20GB.slurm  -- for executing code for sorting 20GB data file
	$sbatch sparksort80GB.slurm  -- for executing code for sorting 80GB data file
	
The result of slurm jobs will be stored in following log files: 
	● SparkSort8GB.log  -- result of sorting 8GB data file
	● SparkSort20GB.log  -- result of sorting 20GB data file
	● SparkSort80GB.log  -- result of sorting 80GB data file
