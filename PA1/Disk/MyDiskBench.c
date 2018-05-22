/* Name: Brijesh Mavani
CWID: A20406960
University: Illinois Institute of Technology
Course: Cloud Computing
Assignment: 1  */

/* Disk Benchmarking*/
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
//Comments are added for debugging purpose

pthread_barrier_t mybarrier;
long int mem = 1024*1024*1024*10ul;	//Allocating 10GB of memory

//long int mem = 1024*1024;	//Allocating 1MB of memory
int bsize = 0;
int numthreads;
int Iterations;


typedef struct tinfo {
    int start; // starting location
    int end;   // end location
} tinfo;


void *createfile()
{
    int fp,writeop;
    //char write []= {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
    fp = open("/tmp/pa1Brijesh.dat", O_WRONLY | O_CREAT|O_TRUNC|O_APPEND,0666);
    if (fp < 0)
    {
        printf("Error in creating file.\n");
        exit(-1);
    }
    int i;
    for (i = 0; i < Iterations; i++)
    {
        char *buffer = (char*)malloc(sizeof(char) * bsize);
        if (i%2==0) {
            memset(buffer, 'b', bsize);
        }
        else {
            memset(buffer, 'B', bsize);
        }
        //lseek(fp,0,SEEK_CUR);

        writeop= write(fp, buffer, bsize); // File pointer will be set to current location. Hence, no need to move it or subsequent read 								like in random access.

        if (writeop < 0)  // check if write operation successful or not.
        {
            printf ("Error in writing to a file.\n");
            exit (-1);
        }
        //writecount+=writeop;
        free (buffer);  // free the memory
        //fsync (fp);
    }
    fsync (fp);
    if (close(fp)<0) // check if closing file operation successful or not.
    {
        printf ("Error in closing a file after read.\n");
        exit (-1);
    }
    printf("created the file ");
    return NULL;
}


//Function for reading from disk in sequential access
void *RS(void * arg)
{
    int i;
    int fp,readop;
    tinfo *ptinfo;
    ptinfo = (tinfo *)arg;
    int start = ptinfo->start;  // start memory location for thread
    int end = ptinfo->end;	   // end memory location for thread
    printf("\nstart : %d, end before: %d\n",start,end);
    long int readcount=0;
    //Read from disk in sequential access
    //long int offset=start*bsize;
    long int offset=start;
//	fp = open("/tmp/pa1Brijesh1.dat", O_RDONLY|O_DIRECT|O_SYNC, 0666);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    fp = open("/tmp/pa1Brijesh.dat", O_RDONLY|O_SYNC, 0666);
    if (fp < 0)
    {
        printf("Error in opening file.\n");
        exit(-1);
    }

    for (i = start; i <=end; i++)
    {
        char *buffer = (char*)malloc(sizeof(char) * bsize);
        //readop= read(fp, buffer, bsize); // File pointer will be set to current locaion. Hence, no need to move it or subsequent read 								like in random access.

        readop= pread(fp, buffer, bsize,offset); // File pointer will be set to current locaion. Hence, no need to move it or 									subsequent read like in random access.
//		printf("%s ",buffer);

        offset=offset+bsize;
        if (readop < 0)  // check if read operation successful or not.
        {
            printf ("Error in reading a file. at %d offset %ld\n",i,offset);
            exit (-1);
        }
        readcount+=readop;
        free (buffer);  // free the memory
        fsync (fp);
    }

    if (close(fp)<0) // check if closing file operation successful or not.
    {
        printf ("Error in closing a file after read.\n");
        exit (-1);
    }
    printf("read count: %ld\n",readcount);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    return NULL;
}

//Function for writing to disk in sequential access
void *WS(void * arg)
{
    int i;
    int fp,writeop;
//	int numop = (mem/bsize)/numthreads;
//	int numop = (mem/bsize);
    tinfo *ptinfo;
    ptinfo = (tinfo *)arg;
    int start = ptinfo->start;  // start memory location for thread
    int end = ptinfo->end;	   // end memory location for thread
    printf("\nstart : %d, end before: %d\n",start,end);

    long int writecount=0;
//	fp = creat("/tmp/pa1Brijesh1.dat", 0666);
    fp = open("/tmp/pa1Brijesh.dat", O_WRONLY | O_CREAT|O_TRUNC|O_APPEND,0666);

    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    //fp = open("/tmp/pa1Brijesh.dat", O_WRONLY | O_CREAT|O_APPEND,0666);
    if (fp < 0)
    {
        printf("Error in creating file.\n");
        exit(-1);
    }

    //Write to disk in sequential manner

    for (i = start; i <= end; i++)
    {
        char *buffer = (char*)malloc(sizeof(char) * bsize);
        if (i%2==0) {
            memset(buffer, 'b', bsize);
        }
        else {
            memset(buffer, 'B', bsize);
        }
        lseek(fp,0,SEEK_CUR);

        writeop= write(fp, buffer, bsize); // File pointer will be set to current locaion. Hence, no need to move it or subsequent read 								like in random access.

        if (writeop < 0)  // check if write operation successful or not.
        {
            printf ("Error in writing to a file.\n");
            exit (-1);
        }
        writecount+=writeop;
        free (buffer);  // free the memory
        fsync (fp);
    }

    if (close(fp)<0) // check if closing file operation successful or not.
    {
        printf ("Error in closing a file after read.\n");
        exit (-1);
    }
    printf("write count: %ld\n",writecount);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    return NULL;
}



void *RR(void * arg)
{
    int i;
    int fp,offset,seek,readop;
    //int numop = (mem/bsize);
    srand((unsigned)time(NULL));
    tinfo *ptinfo;
    ptinfo = (tinfo *)arg;
    int start = ptinfo->start;  // start memory location for thread
    int end = ptinfo->end;	   // end memory location for thread
    printf("\nstart : %d, end before: %d\n",start,end);

    long int readcount=0;
//	fp = open("/tmp/pa1Brijesh1.dat", O_RDONLY|O_DIRECT | O_SYNC, 0666);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    fp = open("/tmp/pa1Brijesh.dat", O_RDONLY| O_SYNC, 0666);

    if (fp < 0)
    {
        printf("Error in opening file.\n");
        exit(-1);
    }

    // Read from disk in random manner
	// printf("numop: %d\n",numop);
    for (i = start; i <=end; i++)
    {
        offset = (rand()%(start-end))+start;
        char *buffer = (char*)malloc(sizeof(char) * bsize);

        // position the File Pointer to random blocks away
        seek = lseek(fp, offset, SEEK_SET);
        if (seek < 0)
        {
            printf ("Error in seek operation of random read.\n");
            exit (-1);
        }
        readop= read(fp, buffer, bsize);
        if (readop < 0)  // check if read operation successful or not.
        {
            printf ("Error in writing to a file.\n");
            exit (-1);
        }

        readcount+=readop;
        free (buffer);  // free the memory
        fsync (fp);
    }

    if (close(fp)<0) // check if closing file operation successful or not.
    {
        printf ("Error in closing a file after read.\n");
        exit (-1);
    }
    printf("readcount: %ld\n",readcount);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    return NULL;
}


void *WR(void * arg)
{
    int i;
    int fp,offset,seek,writeop;
    int numop = (mem/bsize);
    srand((unsigned)time(NULL));
    //fp = creat("/tmp/pa1Brijesh.dat", 0666);

    tinfo *ptinfo;
    ptinfo = (tinfo *)arg;
    int start = ptinfo->start;  // start memory location for thread
    int end = ptinfo->end;	   // end memory location for thread
    printf("\nstart : %d, end before: %d\n",start,end);
    long int writecount=0;
    fp = open("/tmp/pa1Brijesh.dat", O_WRONLY | O_CREAT|O_TRUNC|O_APPEND,0666);

    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    //fp = creat("/tmp/pa1Brijesh.dat", 0666);
    if (fp < 0)
    {
        printf("Error in creating file.\n");
        exit(-1);
    }

    //Write to disk in Random manner
    printf("numop: %d\n",numop);
    for (i = start; i <=end; i++)
    {
		offset = (rand()%(start-end))+start;
        char *buffer = (char*)malloc(sizeof(char) * bsize);

        // position the File Pointer to random blocks away
        seek = lseek(fp, offset, SEEK_SET);
        if (seek < 0)
        {
            printf ("Error in seek operation of random write.\n");
            exit (-1);
        }
        if (i%2==0) {
            memset(buffer, 'b', bsize);
        }
        else {
            memset(buffer, 'B', bsize);
        }
        writeop= write(fp, buffer, bsize);

        if (writeop < 0)  // check if write operation successful or not.
        {
            printf("I: %d",i);
            printf ("Error in writing to a file.\n");
            exit (-1);
        }
        writecount+=writeop;

        free (buffer);  // free the memory
        fsync (fp);
    }

    if (close(fp)<0) // check if closing file operation successful or not.
    {
        printf ("Error in closing a file after read.\n");
        exit (-1);
    }
    printf("write count: %ld\n",writecount);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
    return NULL;
}

int main(int argc, char const * argv[])
{
    FILE *fp;
    char buffer[20];
    char input[3];  // input operation mode.
    char output[100] = "./output/disk-"; //disk-RR-1-1thread.out.dat
    char mode[3];  // input operation mode.
    int i;
    double RRTime,RSTime,WSTime,WRTime,RSstart,RSstop,RRstart,RRstop,WSstart,WSstop,WRstart,WRstop,bvalue,tvalue,efficiency;
    struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */
    char block[10];
    double biops,tiops,iopsefficiency,blat,bput,tlat,tblocks;
    double tput= 600;
    if (argc != 2)
    {
        printf("usage: %s <file name>\n", argv[0]);
        return -1;
    }

    printf("argv[0]: %s\n",argv[1]);
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("error in opening file");
        return -1;
    }
    else
    {
        fscanf(fp, "%s", mode);
        strncpy(input, mode, 3);

        printf("Input: %s", input);
        if (strncmp(input,"RR",2)==0) {
            strcat(output,"RR-");
            //strncpy(mode, "RR",2);
        }
        else if (strncmp(input,"RS",2)==0) {
            strcat(output,"RS-");
            //strncpy(mode, "RS", 2);
        }
        else if (strncmp(input,"WS",2)==0) {
            strcat(output,"WS-");
            //strncpy(mode, "WS", 2);
        }
        else if (strncmp(input,"WR",2)==0) {
            strcat(output,"WR-");
            //strncpy(mode, "WR", 2);
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

    pthread_t thread[numthreads];
    if (bsize==1)
    {
        bsize=1024;
        mem = 1024*1024*1024;
        strncpy(block, "1KB", 3);
    }

    else if (bsize>1 && bsize <= 1000)
    {
        bsize = 1024*1024;
        strncpy(block, "1MB", 3);
    }
    else if (bsize>1000 && bsize <= 10000)
    {
        bsize = 1024*1024*10;
        strncpy(block, "10MB", 4);
    }
    else if (bsize>10000 && bsize <= 100000)
    {
        bsize = 1024*1024*100;
        strncpy(block, "100MB", 5);
    }

    Iterations = mem/bsize;
    tblocks=(double)mem/(double)bsize;
    tinfo t[numthreads];
    pthread_barrier_init(&mybarrier, NULL, numthreads + 1);
	//Call respective function to perform RWR and RWS operations

    if (strncmp(input,"RS",2)==0) {

        // create threads to perform Read sequential access.
        createfile();

		//	gettimeofday(&etstart, NULL);
        for (i = 0; i < numthreads; i++) {
            t[i].start = i*(Iterations/numthreads);
            t[i].end = (i+1)*(Iterations/numthreads)-1;
            pthread_create(&thread[i], NULL, RS, &t[i]);
            printf("Created thread : %d", i+1);
        }


        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstart, NULL);
        printf("started time");
        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstop, NULL);
        printf("ended time");

        for (i = 0; i < numthreads; i++) {
            pthread_join(thread[i], NULL);
            printf("joined thread : %d", i+1);
        }
		// gettimeofday(&etstop, NULL);

        // Calculate execution time in sec

        RSstart= (double)etstart.tv_sec+(double)(etstart.tv_usec/1000000);
        RSstop= (double)etstop.tv_sec+(double)(etstop.tv_usec/1000000);
        printf("RSstart: %lf s\n",RSstart);
        printf("RSstop: %lf s\n",RSstop);
        RSTime = (double)RSstop-(double)RSstart;

        printf("Execution Time Read Sequential: %10f ms", RSTime);
        bput = ((mem)/RSTime)/(1024*1024);
        printf("Throughput is: %lf MBPS\n",bput);
        printf("bsize: %d",bsize);
    }

    else if (strncmp(input,"WS",2)==0) {

        // create threads to perform write sequential access.

		//	gettimeofday(&etstart, NULL);
        for (i = 0; i < numthreads; i++) {
            t[i].start = i*(Iterations/numthreads);
            t[i].end = (i+1)*(Iterations/numthreads)-1;
            pthread_create(&thread[i], NULL, WS, &t[i]);
            printf("created thread : %d", i+1);
        }


        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstart, NULL);
        printf("started time");
        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstop, NULL);
        printf("ended time");


        for (i = 0; i < numthreads; i++) {
            pthread_join(thread[i], NULL);
            printf("joined thread : %d", i+1);
        }
		// gettimeofday(&etstop, NULL);

        // Calculate execution time in sec

        WSstart= (double)etstart.tv_sec+(double)(etstart.tv_usec/1000000);
        WSstop= (double)etstop.tv_sec+(double)(etstop.tv_usec/1000000);
        printf("WSstart: %lf s\n",WSstart);
        printf("WSstop: %lf s\n",WSstop);
        WSTime = (double)WSstop-(double)WSstart;

        printf("Execution Time Read Sequential: %10f ms", WSTime);
        bput =((mem)/WSTime)/(1024*1024);
        printf("Throughput is: %lf MBPS\n",bput);
        printf("bsize: %d",bsize);
    }

    else if (strncmp(input,"RR",2)==0) {

        // create threads to perform Read random access.
        createfile();
		//	gettimeofday(&etstart, NULL);
        for (i = 0; i < numthreads; i++) {
            t[i].start = i*(Iterations/numthreads);
            t[i].end = (i+1)*(Iterations/numthreads)-1;
            pthread_create(&thread[i], NULL, RR, &t[i]);
            printf("created thread : %d", i+1);
        }

        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstart, NULL);
        printf("started time");
        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstop, NULL);
        printf("ended time");

        for (i = 0; i < numthreads; i++) {
            pthread_join(thread[i], NULL);
            printf("joined thread : %d", i+1);
        }
		// gettimeofday(&etstop, NULL);

        // Calculate execution time in sec

        RRstart= (double)etstart.tv_sec+(double)(etstart.tv_usec/1000000);
        RRstop= (double)etstop.tv_sec+(double)(etstop.tv_usec/1000000);
        printf("RRstart: %lf s\n",RRstart);
        printf("RRstop: %lf s\n",RRstop);
        RRTime = (double)RRstop-(double)RRstart;

        printf("Execution Time Read Random: %10f ms", RRTime);
        if (bsize==1024) {
            blat = (RRTime*1000)/(mem);
            //biops = ((mem)/RRTime)/(1000000000);
            biops = ((tblocks)/RRTime);
            printf("Latancy is: %lf ms\n",blat);
            printf("IOPS is: %lf ops\n",biops);
            tiops= 78.988941;
            tlat=4.16;
        }
        else {
            bput = ((mem)/RRTime)/(1024*1024);
            printf("Throughput is: %lf MBPS\n",bput);
            printf("bsize: %d",bsize);
        }
    }

    else if (strncmp(input,"WR",2)==0) {

        // create threads to perform Write random access.

		//	gettimeofday(&etstart, NULL);
        for (i = 0; i < numthreads; i++) {
            t[i].start = i*(Iterations/numthreads);
            t[i].end = (i+1)*(Iterations/numthreads)-1;
            pthread_create(&thread[i], NULL, WR, &t[i]);
            printf("created thread : %d", i+1);
        }


        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstart, NULL);
        printf("started time");
        pthread_barrier_wait(&mybarrier);  // Thread synchronization
        gettimeofday(&etstop, NULL);
        printf("ended time");


        for (i = 0; i < numthreads; i++) {
            pthread_join(thread[i], NULL);
            printf("joined thread : %d", i+1);
        }
		// gettimeofday(&etstop, NULL);

        // Calculate execution time in sec

        WRstart= (double)etstart.tv_sec+(double)(etstart.tv_usec/1000000);
        WRstop= (double)etstop.tv_sec+(double)(etstop.tv_usec/1000000);
        printf("WRstart: %lf s\n",WRstart);
        printf("WRstop: %lf s\n",WRstop);
        WRTime = (double)WRstop-(double)WRstart;

        printf("Execution Time write random: %10f ms", WRTime);

        if (bsize==1024) {
            blat = (WRTime*1000)/(mem);
            //biops = ((mem)/WRTime)/(1000000000);
            biops = ((tblocks)/WRTime);
            printf("Latancy is: %lf ms\n",blat);
            printf("IOPS is: %lf ops\n",biops);
            tiops= 73.206442;
            tlat=4.16;
        }
        else {
            bput = ((mem)/WRTime)/(1024*1024);
            printf("Throughput is: %lf MBPS\n",bput);
            printf("bsize: %d",bsize);
        }

    }

    if (bsize==1024)
    {
        bvalue=blat;
        tvalue=tlat;
        biops=biops;
        tiops=tiops;
        efficiency = ((double)bvalue/(double)tvalue);
        iopsefficiency = ((double)biops/(double)tiops);
    }
    else
    {
        bvalue=bput;
        tvalue=tput;
        efficiency = ((double)bvalue/(double)tvalue)*100ul;
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
        if (bsize>1024)
        {
            fprintf(fp,"%s %d %s %10f %10f %10f\n",mode,numthreads,block,bvalue,tvalue,efficiency);
            //Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency
        }
        else
        {
            fprintf(fp,"%s %d %s %10f %10f %10f %10f %10f %10f\n",mode,numthreads,block,bvalue,tvalue,efficiency,biops,tiops,iopsefficiency);
            //Workload Concurrency BlockSize Latency Theoreticallatency MyRAMBenchlatencyEfficiency IOPS TheoreticalIOPS IOPSefficiency
        }
    }

    return 0;
}
