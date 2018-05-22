/* Name: Brijesh Mavani
CWID: A20406960
University: Illinois Institute of Technology
Course: Cloud Computing
Assignment: 1  */

/* RAM Benchmarking*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

//Comments are added for debugging purpose
long int mem = 1024*1024*1024;	//Allocating 1GB of memory
int bsize = 0;
int numthreads;
int Iterations;
pthread_barrier_t mybarrier;

typedef struct tinfo {
    int start; // starting location
    int end;   // end location
} tinfo;


void * RWS(void * arg)
{
    printf("value of Iterations: %d",Iterations);
    int i=0,j;
    long int offset;
    tinfo *ptinfo;
    ptinfo = (tinfo *)arg;
    int start = ptinfo->start;  // start memory location for thread
    int end = ptinfo->end;	   // end memory location for thread
    printf("start : %d, end before: %d\n",start,end);
    int rep;
    //end = (bsize==1)?(end/10):end;  // 100 million operations when block size is 1.
    //start = (bsize==1&&numthreads>1)?(start/10):start;  // 100 million operations when block size is 1.
    printf("end after: %d\n",end);

    rep = (bsize==1)?1:100;  // 100 million operations when block size is 1.
    printf("rep : %d\n",rep);
    long int threadblock = end-start;
    //printf("before barrier");
    printf("threadblock: %ld\n",threadblock);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    //printf("before mem allocation\n");
    //printf("threadblock: %ld\n",threadblock);
    char *block1 = (char*)malloc(((threadblock+1)*bsize)*sizeof(char));
    //printf("after mem allocation block1\n");
    char *block2 = (char*)malloc(((threadblock+1)*bsize)*sizeof(char));

    //printf("after mem allocation block2\n");
    memset(block1,'b',((threadblock+1)*bsize)*sizeof(char));

    //printf("mem set");
    for (i=0;i<rep;i++) {
        offset=0;
		//printf("I");
        for (j=start;j<=end;j++) {
            memcpy(block2+offset,block1+offset,bsize);
            offset = offset+bsize;
        }
		//		printf("J finished");
    }
    free(block1);
    free(block2);

    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    pthread_exit(NULL);

    return NULL;
}

void * RWR(void * arg)
{

    printf("value of Iterations: %d",Iterations);
    int i=0, offset,j;
    srand((unsigned)time(NULL));

    tinfo *ptinfo;
    ptinfo = (tinfo *)arg;
    int start = ptinfo->start;
    int end = ptinfo->end;
    int rep;
    printf("start : %d, end before: %d\n",start,end);

//	end = (bsize==1)?(end/10):end;
    rep = (bsize==1)?1:100;  // 100 million operations when block size is 1.
    printf("rep : %d\n",rep);
    printf("end after: %d\n",end);
    long int threadblock = end-start;
    printf("threadblock: %ld\n",threadblock);

    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    //printf("after barrier\n");
    char *block1 = (char*)malloc(((threadblock+1)*bsize)*sizeof(char));
    //      printf("allocated block1\n");

    char *block2 = (char*)malloc(((threadblock+1)*bsize)*sizeof(char));
    //printf("allocated block2\n");
    memset(block1,'b',((threadblock+1)*bsize)*sizeof(char));
    //printf("mem set\n");

    for (i=0;i<rep;i++) {
        offset=0;
        for (j=start;j<=end;j++) {
            //offset = rand()%(start-end)+(start);
            offset = rand()%(start-end);
            memcpy(block2+offset,block1+offset,bsize);  // block2+(offset*bsize)
        }
    }
    free(block1);
    free(block2);

    pthread_barrier_wait(&mybarrier);  // Thread synchronization


    pthread_exit(NULL);

    return NULL;
}


int main(int argc, char const * argv[])
{
    FILE *fp;
    char buffer[20];
    char input[3];  // input operation mode.
    char output[100] = "./output/memory-"; //memory-RWR-1-1thread.out
    char mode[3];  // input operation mode.
    int i;
    double executionTime,exestart,exestop,bvalue,tvalue,tput,bput,efficiency;
    struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */
    double clockcycle = 0.4;
    double cl = 15;
    double truelatency =0.01406;  // (1/((RAMspeed/2)/1000) x CL)/1000 = True Latency in microseconds
    double truethroughput = 63.568354; // (Clock frequency) * (lines per clock) * (Memory Bus Width) * (Number of Interfaces) = ((2133000000*2*64*2)/8)/(1024*1024*1024) GBPS
    char block[5];

    if (argc != 2)
    {
        printf("usage: %s <file name>\n", argv[0]);
        return -1;
    }

    printf("argv[0]: %s\n",argv[1]);
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("error in opening file\n");
        return -1;
    }
    else
    {
        fscanf(fp, "%s", mode);
        strncpy(input, mode, 3);

        printf("Input: %s", input);
        if (strncmp(input,"RWS",3)==0) {
            strcat(output,"RWS-");
            //strncpy(mode, "RWS", 3);
        }
        else if (strncmp(input,"RWR",3)==0) {
            strcat(output,"RWR-");
            //strncpy(mode, "RWR", 3);
        }

        fscanf(fp, "%s", buffer);
        printf("2nd line : %s\n", buffer );
        bsize = atoi(buffer);
        strcat(output,buffer);
        fscanf(fp, "%s", buffer);
        printf("3rd line : %s\n", buffer );
        numthreads = atoi(buffer);
        strcat(output,"-");
        strcat(output,buffer);
        strcat(output,"thread.out.dat");
    }
    fclose(fp);
    printf("output: %s",output);

    if (bsize==1) {
        strncpy(block, "1B", 2);
    }
    if (bsize>1 && bsize <= 1000)
    {
        bsize = 1024;
        strncpy(block, "1KB", 3);
    }
    else if (bsize>1000 && bsize <= 1000000)
    {
        bsize = 1024*1024;
        strncpy(block, "1MB", 3);
    }
    else if (bsize>1000000 && bsize <= 10000000)
    {
        bsize = 1024*1024*10;
        strncpy(block, "10MB", 4);
    }
    Iterations = mem/bsize;

    //parameter structure passed in pthread
    pthread_t thread[numthreads];
    tinfo t[numthreads];
    pthread_barrier_init(&mybarrier, NULL, numthreads + 1);
    Iterations = (bsize==1)?(100000000):Iterations;

	//Call respective function to perform RWR and RWS operations

    if (strncmp(input,"RWS",3)==0) {

		//	gettimeofday(&etstart, NULL);
        for (i = 0; i < numthreads; i++) {
            t[i].start = i*(Iterations/numthreads);
            t[i].end = (i+1)*(Iterations/numthreads)-1;
            pthread_create(&thread[i], NULL, RWS, &t[i]);
        }

        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstart, NULL);
        printf("started time");
        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstop, NULL);
        printf("ended time");


        for (i = 0; i < numthreads; i++) {
            pthread_join(thread[i], NULL);
        }
		// gettimeofday(&etstop, NULL);

        // Calculate execution time in sec

        exestart= (double)etstart.tv_sec+(double)(etstart.tv_usec/1000000);
        exestop= (double)etstop.tv_sec+(double)(etstop.tv_usec/1000000);
        printf("exestart: %lf s\n",exestart);
        printf("exestop: %lf s\n",exestop);
        executionTime = (double)exestop-(double)exestart;

        if (bsize==1) {
            printf("Latency time: %lf\n",executionTime);
            bput = (executionTime*1000000)/(mem/10);
            //tvalue = (double)(clockcycle/1000) * cl;*/
            printf("True Latency is: %0.12lfms\n",truelatency);
            //printf("Latency is: %0.12lfs\n",tput);
            tvalue = truelatency;
        }
        else {
            printf("Execution Time Throughput: %10fs\n", executionTime);
            bput = ((mem * 100ul )/executionTime)/(1024*1024*1024);

			//  printf("Throughput: %10fs\n", tput);
            printf("Throughput is: %lf GBPS\n",bput);
            tvalue=truethroughput;
            printf("bsize: %d",bsize);

        }
    }

    else if (strncmp(input,"RWR",3)==0) {

        for (i = 0; i < numthreads; i++) {
            t[i].start = i*(Iterations/numthreads);
            t[i].end = (i+1)*(Iterations/numthreads)-1;
            pthread_create(&thread[i], NULL, RWR, &t[i]);
        }
        printf("after thread create");
        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstart, NULL);
        printf("started time");
        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstop, NULL);
        printf("ended time");



        for (i = 0; i < numthreads; i++) {
            pthread_join(thread[i], NULL);
        }
        // gettimeofday(&etstop, NULL);

        // Calculate execution time in sec

        exestart= (double)etstart.tv_sec+(double)(etstart.tv_usec/1000000);
        exestop= (double)etstop.tv_sec+(double)(etstop.tv_usec/1000000);
        printf("exestart: %lf s\n",exestart);
        printf("exestop: %lf s\n",exestop);
        executionTime = (double)exestop-(double)exestart;

        if (bsize==1) {
            printf("Execution Time latency: %10fs", executionTime);
            bput = (executionTime*1000000)/(mem/10);
            tvalue=truelatency;
            printf("Latency is: %0.12lfms\n",bput);
        }
        else {
            printf("Execution Time Throughput: %10fs\n", executionTime);
			//		printf("numthreads: %d, Iterations: %d, Bsize: %d, execution time: %lf\n",numthreads, Iterations,bsize,executionTime);

            /*		long double num = (double)(numthreads * Iterations * bsize *100ul )/(double)executionTime;
            		double deno = (double)(1024*1024*1024);
            		double div = num/deno;
            		printf("num long..: %Lf\n", num);
            		printf("deno: %lf\n",deno);
            		printf("div: %lf\n",div);*/
            bput = ((mem * 100ul )/executionTime)/(1024*1024*1024);
            tvalue=truethroughput;
//		    printf("Throughput: %10fs\n", tput);
            printf("Throughput is: %lf GBPS\n",bput);
            printf("bsize: %d",bsize);

        }
    }

    bvalue= bput;
	//tvalue = tput;
    if (bsize>1) {
        efficiency = ((double)bvalue/(double)tvalue)*100ul;
    }
    else {
        efficiency = ((double)bvalue/(double)tvalue);
    }

    printf("output: %s\n",output);

    fp = fopen(output, "a");

    if (fp == NULL)
    {
        printf("error in opening file");
        return -1;
    }
    else
    {
        fprintf(fp,"%s %d %s %10f %10f %10f\n",mode,numthreads,block,bvalue,tvalue,efficiency);
        //Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency
    }

    return 0;
}
