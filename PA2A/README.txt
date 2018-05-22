Name: Brijesh Mavani - A20406960
Course: Cloud Computing 
Assignment: PA-2A

A) External sort with shared memory: 

In this programming assignment, we are implementing external sort application in a single node shared memory environment using a multi-threaded approach.
As we are sorting large document specifically larger than memory, multi-threading approach is must to gain more throughput. The main issue with this type of sorting is requirement of read/write operations to file. To minimize this overhead, I am sorting the block of input file with merge sort and storing the sorted temporary files to disk. Once all records from input file has been read, sorted and stored into one of the temporary files, I am using k-way merging to generate final sorted output file. The input was generated with gensort program (http://www.ordinal.com/gensort.html). Each record is of 100 bytes with starting 10 bytes as key and remaining bytes as value. For this assignment code has been executed for 2GB and 20GB files and results are provided. 

Assuming git is cloned or downloaded to the Linux test bed which also supports slurm based batch scheduling. Another assumption is that input data file will be present in "/input" folder.
	Navigate to the folder PA2.
	Java file name: MySort.java
	Compile: Though make file has been created and provided, one can explicitly compile the code with command: javac Mysort.java
	Executing code: Slurm files are created for executing the code for sorting 2GB and 20GB data files. Valsort will be executed after execution of java code to make sure output file is sorted correctly. Below slurm files will be by default executed for threads =16. 
	● mysort2GB.slurm  -- for 2GB data file
	● mysort20GB.slurm  -- for 20GB data file

	$sbatch mysort2GB.slurm  -- for executing code for sorting 2GB data file
	$sbatch mysort20GB.slurm  -- for executing code for sorting 20GB data file
If you want to execute slurm job for different no of threads, then you can use following slurm files. 
•	mysort<load>_<number of threads>.slurm
where, load is 2GB or 20GB
number of threads: it can be 1, 2, 4, 8 or 16. 
Eg. Mysort2GB_8.slurm – This will submit slurm job for program execution with workload as 2GB and number of threads as 8.

Alternatively, you can execute it with command:
	java Mysort <inputfilename> <number of threads>
eg. java Mysort data-20GB.in 8 -- This will execute code for data file data-20GB.in in input folder with 8 threads. 

The result of slurm jobs will be stored in following log files: 
	● mysort2GB.log  -- result of sorting 2GB data file
	● mysort20GB.log  -- result of sorting 20GB data file

Log file will contain information about total read write operations, throughput as well result of valsort program. 
If you are running slurm job for different number of threads then output file will be in following format:
•	Mysort<workload>_<number of threads>.log
where, load is 2GB or 20GB
number of threads: it can be 1, 2, 4, 8 or 16. 
Eg. Mysort2GB_8.log – This will contain output of slurm job with for workload 2GB and number of threads 8.

B) Linux Sort 

To evaluate the performance of my program, I have executed the standard benchmark program called as Linux sort. This sorting program also executes on single shared memory node similar to my program. I have used multi-threading here as well to compare the performances of both programs.

Assuming Linux test bed available which also supports slurm based batch scheduling.
Executing code: Slurm files are created for executing the code for sorting 2GB and 20GB data files. Valsort will be executed after execution of linsort code to make sure output file is sorted correctly. 
	● linsort2GB.slurm  -- for 2GB data file
	● linsort20GB.slurm  -- for 20GB data file

	$sbatch linsort2GB.slurm  -- for executing code for sorting 2GB data file
	$sbatch linsort20GB.slurm  -- for executing code for sorting 20GB data file

Similar to Shared memory program slurm files for different number of threads are created. 
•	linsort<load>_<number of threads>.slurm
where, load is 2GB or 20GB
number of threads: it can be 1, 2, 4, 8 or 16. 
Eg. linsort2GB_8.slurm – This will submit slurm job for linsort program execution with workload as 2GB and number of threads as 8.

The result of slurm jobs will be stored in following log files: 
	● linsort2GB.log  -- result of sorting 2GB data file
	● linsort20GB.log -- result of sorting 20GB data file
If you are running slurm job for different number of threads, then output file will be in following format:
•	linsort<workload>_<number of threads>.log
where, load is 2GB or 20GB
number of threads: it can be 1, 2, 4, 8 or 16. 
Eg. linsort2GB_8.log – This will contain output of slurm job with for workload 2GB and number of threads 8.

I have also recorded the time taken by this program as well as valsort and stored them into output log files.
