Name: Brijesh Mavani
CWID: A20406960

CPU Benchmarking
This program calculates the Giga Char operations, Giga Short operations, Giga Integer operations and Giga Floating point operations.
The main aim is to utilize the complete CPU cycles by executing different arithmetic instructions. 
Utilizing the CPU’s Floating point unit (FPU) completely so that it gives us the maximum FLOPS.

DISK Benchmarking
The design includes implementation for 4 different block sizes i.e. 1KB,1MB, 10MB and 100MB each for Sequential and Random operations.
It implements 4 methods, sequential read & write and random read & write.
The sequential access is done using a file, and data is read from the file and written into it, in a sequential manner.
For random access, a random number is generated which lies within the file size, and is seeked to that location onto that file and read and write operations are performed.

MEMORY Benchmarking
For different block sizes i.e. 1B,1KB, 1MB and 10MB, sequential and random access to the memory is made.
The disk access are made using memcpy() function which is used to perform read and write operation onto the memory.

NETWORK Benchmarking
The benchmarking is done for both TCP as well as UDP protocol. The code is written to be executed on two different instances of cluster.
This code does the basic packets transmission from Client to Server and back again, while implementing this we find the RTT of the transmission.
The packets transmitted are of various sizes i.e. 1 Byte, 1KB and 32KB.
The TCP being reliable and connection oriented requires pre connection setup and accepting of connection between client and server.
On the other hand UDP being connection less, the packets are sent and received without and pre established connection.

How to run:

Considering the instance on which the program is going to be tested has the required compilers for C program.

CPU BENCHMARKING"

1. goto the folder named "Cpu"
2. Open the terminal for the instance you are running on
3. execute the script file named "run_dp.sh" as:
	srun run_dp.sh  -- for executing code for Double precision
	srun run_sp.sh  -- for executing code for Single precision
	srun run_qp.sh  -- for executing code for Quarter precision
	srun run_hp.sh  -- for executing code for Half precision
4. The desired output for GFLOPS will be displayed and output file will be created in output folder.

"DISK BENCHMARKING"

1. goto the folder named "Disk"
2. Open the terminal for the instance you are running on
3. execute the script file named run_wr_100M.sh as
srun run_wr_100M.sh for excuting code for random write with 100MB block size.
File format: run_<mode>_<blocksize>.sh where
mode == wr -- random write
ws -- sequential write
rr-- random read
rs -- sequential read 

blocksize == 100M -- 100 MB
10M -- 10MB
1M -- 1MB
1K -- 1KB 

4. The desired output for RANDOM and SEQUENTIAL Read & Write operations will be displayed and output file will be created in output folder.



"MEMORY BENCHMARKING"

1. goto the folder named "Memory"
2. Open the terminal for the instance you are running on
3. execute the script file named "run_rws_1M.sh" as
	srun run_rws_1M.sh
File format: run_<mode>_<blocksize>.sh where
mode == rws -- read write sequential
rwr -- read write random

blocksize == 10M -- 10 MB
1M -- 1MB
1K -- 1KB 	
1 -- 1B
	
	
4. The desired output for RANDOM ACCESS and SEQUENTIAL ACCESS for Memory will be displayed and output file will be created in output folder.



"NETWORK BENCHMARKING"

1. goto the folder named "Network"
2. Here we will require 2 instances to be opened
3. one of the instance will be acting as SERVER and another will be acting as CLIENT
4. Before execution, complie the code with $make all command.

5. execute the script file named "TCP_run_32K_8.sh" as
	sbatch TCP_run_32K_8.sh
	
File format: <Protocol>_run_<blocksize>_<numthreads>.sh where
protocol == TCP or UDP

blocksize == 32K -- 32KB
1K -- 1KB
1 -- 1B

numthreads -- 1,2,4,8

6. The desired output for TCP & UDP will be displayed on the Client Side terminal and output file will be created in output folder.

