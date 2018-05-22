/* Name: Brijesh Mavani
CWID: A20406960
University: Illinois Institute of Technology
Course: Cloud Computing
Assignment: 1  */

/* CPU Benchmarking*/

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

#define ITERATION 1000000
#define ITERATION1 100000


int numthreads;
pthread_barrier_t mybarrier;
// Comments are added for debugging purpose
void forloop()
{
    int i,j;
    //int a;
    for (i = 0; i <ITERATION/numthreads; i++) {
        for (j = 0; j <ITERATION1; j++) {
            // a=i%1;
            // Nothing to do
        }
    }
}


void * qops(void * arg)
{
    int i,j;
    //char a,b,c,d,e,p,q,r,s,t,x;
    char a,b,x;

    //a='a',b='b',c='c',d='d',e='e',p='p',q='q',r='r',s='s',t='t',x='x';
    a='a',b='b',x='x';
    //    int thread_id = *(int*)arg;
	//	printf("ID before barrier 1: %d\n",thread_id);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
	//	printf("ID after barrier 1: %d\n",thread_id);
    for (i = 0; i < ITERATION/numthreads; i++) {  // 4 operations

        for (j = 0; j <ITERATION1; j++) { // 3 operations
            a=x-a;
            b=(x-b)+b;
            a=x+a;
            /*d=x-d;  e=x-e; // 10 operations
            a=x+a;  b=x+b;  c=x+c;  d=x+d;  e=x+e; // 10 operations

            p=x-p;  q=x-q;  r=x-r;  s=x-s;  t=x-t; // 10 operations
            p=x+p;  q=x+q;  r=x+r;  s=x+s;  t=x+t; // 10 operations
            */
        }
    }
	//	printf("ID before barrier 2: %d\n",thread_id);
    pthread_barrier_wait(&mybarrier);  // Thread synchronization
	//	printf("ID after barrier 2: %d\n",thread_id);

	// total 47 opearations in one iteration.

    return NULL;

}

void * hops(void * arg)
{
    //short a,b,c,d,e,p,q,r,s,t,x;
    short a,b,x;
    int i,j;

    //a=1,b=2,c=3,d=4,e=5,p=1,q=2,r=3,s=4,t=5,x=2;
    a=1,b=2,x=2;
	//   int thread_id = *(int*)arg;
	//	printf("ID before barrier 1: %d\n",thread_id);
    pthread_barrier_wait(&mybarrier);// Thread synchronization
	//	printf("ID after barrier 1: %d\n",thread_id);

    for (i = 0; i < ITERATION/numthreads; i++) {  // 4 operations

        for (j = 0; j <ITERATION1; j++) {  // 3 operations
            a=a+x;
            b=(b+x)-x;
            a=a-x;
            /*
            c=c+x;  d=d+x;  e=e+x;    // 10 operations
            a=a-x;  b=b-x;  c=c-x;  d=d-x;  e=e-x;    // 10 operations

            p=p+x;  q=q+x;  r=r+x;  s=s+x;  t=t+x;    // 10 operations
            p=p-x;  q=q-x;  r=r-x;  s=s-x;  t=t-x;    // 10 operations
            */
        }
    }
	// total 47 opearations in one iteration.
	//	printf("ID before barrier 2: %d\n",thread_id);
    pthread_barrier_wait(&mybarrier);// Thread synchronization
	//	printf("ID after barrier 2: %d\n",thread_id);

    return NULL;
}

void * sops(void * arg)
{
    //int a,b,c,d,e,i,j,p,q,r,s,t,x;
    // a=1,b=2,c=3,d=4,e=5,p=1,q=2,r=3,s=4,t=5,x=2;

    int a,b,x,i,j;
    a=1,b=2,x=2;

	//   int thread_id = *(int*)arg;
	//	printf("ID before barrier 1: %d\n",thread_id);
    pthread_barrier_wait(&mybarrier);// Thread synchronization
	//	printf("ID after barrier 1: %d\n",thread_id);

    for (i = 0; i < ITERATION/numthreads; i++) {  // 4 operations

        for (j = 0; j <ITERATION1; j++) {  // 3 operations
            a=a+x;
            b=(b+x)-x;
            a=a-x;
            /*
            c=c+x;  d=d+x;  e=e+x;    // 10 operations
            a=a-x;  b=b-x;  c=c-x;  d=d-x;  e=e-x;    // 10 operations

            p=p+x;  q=q+x;  r=r+x;  s=s+x;  t=t+x;    // 10 operations
            p=p-x;  q=q-x;  r=r-x;  s=s-x;  t=t-x;    // 10 operations	  */
        }
    }
	// total 47 opearations in one iteration.
	//	printf("ID before barrier 2: %d\n",thread_id);
	pthread_barrier_wait(&mybarrier);// Thread synchronization
	//	printf("ID after barrier 2: %d\n",thread_id);


    return NULL;
}

void * dops(void * arg)
{
    double i,j;
    //double a,b,c,d,e,p,q,r,s,t,x;
    //a=0.1,b=1.1,c=2.1,d=3.1,e=4.1,p=1.1,q=2.1,r=3.1,s=4.1,t=5.1,x=1.1;

    double a,b,x;
    a=0.1,b=1.1,x=1.1;

	//    int thread_id = *(int*)arg;
	//	printf("ID before barrier 1: %d\n",thread_id);
    pthread_barrier_wait(&mybarrier);// Thread synchronization
	//	printf("ID after barrier 1: %d\n",thread_id);


    for (i = 0; i < ITERATION/numthreads; i++) {  // 4 operations

        for (j = 0; j <ITERATION1; j++) {  // 3 operations
            a=a+x;
            b=(b+x)-x;
            a=a-x;

            /*c=c+x;  d=d+x;  e=e+x;    // 10 operations
            a=a-x;  b=b-x;  c=c-x;  d=d-x;  e=e-x;    // 10 operations

            p=p+x;  q=q+x;  r=r+x;  s=s+x;  t=t+x;    // 10 operations
            p=p-x;  q=q-x;  r=r-x;  s=s-x;  t=t-x;    // 10 operations */
        }
        //printf("%f,", i);
    }
	// total 47 opearations in one iteration.
	//	printf("ID before barrier 2: %d\n",thread_id);
    pthread_barrier_wait(&mybarrier);// Thread synchronization
	//	printf("ID after barrier 2: %d\n",thread_id);

    return NULL;
}



int main(int argc, char const * argv[])
{
    FILE *fp;
    char buffer[20];
    char input[2];  // input operation mode.
    char output[100] = "./output/cpu_";
    char mode[2];  // input operation mode.
    int i;
    double executionTime, ops,ForTime,exestart,exestop,fstart,fstop,tops,efficiency;
    struct timeval etstart, etstop,forstart,forstop;  /* Elapsed times using gettimeofday() */
    unsigned long totalops = ITERATION ;
    double socket =2;
    double corepersocket = 1;
    double cyclepersecond = 2.30;  // Hyperion has 2.30GHz
    double flops = 1;


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
        fscanf(fp, "%s", buffer);
        strncpy(input, buffer, 2);

        printf("Input: %s", input);

        fscanf(fp, "%s", buffer);
        printf("2nd line : %s\n", buffer );
        numthreads = atoi(buffer);
    }
    fclose(fp);

    pthread_t thread[numthreads];
	//	int  id[numthreads];

    pthread_barrier_init(&mybarrier, NULL, numthreads + 1);

	//Call respective function to perform quarter precision, half precision, single precision and double precision operations

    if (strncmp(input,"QP",2)==0) {

        // Time calculation for FOR loops

        gettimeofday(&forstart, NULL);
        for (i = 0; i < numthreads; i++) {
            forloop();
        }

        gettimeofday(&forstop, NULL);

        fstart=(double)forstart.tv_sec+(double)(forstart.tv_usec/1000000);
        fstop=(double)forstop.tv_sec+(double)(forstop.tv_usec/1000000);
        ForTime=(double)fstop-(double)fstart;
        printf("For loop Time: %lfs", ForTime);


        // create threads to perform 1e12 operation on char data type.

        for (i = 0; i < numthreads; i++) {
		//	id[i]=i+1;
		//	pthread_create(&thread[i], NULL, qops, &id[i]);
            pthread_create(&thread[i], NULL, qops, NULL);
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

        printf("Execution Time: %10fs", executionTime);
        executionTime= abs((double)ForTime-(double)executionTime);
        printf("Actual Execution Time: %lfs", executionTime);

        // Calculate total number of operations.
        totalops = (10ul*ITERATION1*ITERATION)+(4ul*ITERATION);

        printf("Totalops: %lf\n",(double)totalops);

        //Operations per second equals to total number of operations divided by total execution time

        ops = (((double)totalops)/((double)executionTime))/1000000000;
        flops = 128;
        tops = (double)socket*corepersocket*cyclepersecond*flops;
        efficiency = (double)ops/(double)tops*100ul;

        printf("Executed qp\n");
        printf("Total threads: %d , executed in %lfs and the Giga Ops/sec are %lf\n", numthreads, executionTime, ops);
        strcat(output,"QP_");
        strcat(output,buffer);
        strcat(output,"thread.out.dat");
        strncpy(mode, "QP", 2);

        printf("output: %s\n",output);

    }

    else if (strncmp(input,"HP",2)==0) {

        // Time calculation for FOR loops

        gettimeofday(&forstart, NULL);
        for (i = 0; i < numthreads; i++) {
            forloop();
        }
        gettimeofday(&forstop, NULL);

        fstart=(double)forstart.tv_sec+(double)(forstart.tv_usec/1000000);
        fstop=(double)forstop.tv_sec+(double)(forstop.tv_usec/1000000);
        ForTime=(double)fstop-(double)fstart;
        printf("For loop Time: %lfs", ForTime);


        // create threads to perform 1e12 operation on char data type.
        //gettimeofday(&etstart, NULL);

        for (i = 0; i < numthreads; i++) {
		//	id[i]=i+1;
		//	pthread_create(&thread[i], NULL, hops, &id[i]);
            pthread_create(&thread[i], NULL, hops, NULL);
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
        //gettimeofday(&etstop, NULL);
        // Calculate execution time in sec

        exestart= (double)etstart.tv_sec+(double)(etstart.tv_usec/1000000);
        exestop= (double)etstop.tv_sec+(double)(etstop.tv_usec/1000000);
        printf("exestart: %lf s\n",exestart);
        printf("exestop: %lf s\n",exestop);
        executionTime = (double)exestop-(double)exestart;

        printf("Execution Time: %10fs", executionTime);
        executionTime= abs((double)ForTime-(double)executionTime);
        printf("Actual Execution Time: %lfs", executionTime);

        // Calculate total number of operations.
        totalops = (10ul*ITERATION1*ITERATION)+(4ul*ITERATION);

        printf("Totalops: %lf\n",(double)totalops);

        //Operations per second equals to total number of operations divided by total execution time

        ops = (((double)totalops)/((double)executionTime))/1000000000;
        flops = 64;
        tops = (double)socket*corepersocket*cyclepersecond*flops;
        efficiency = (double)ops/(double)tops*100ul;

        printf("Executed hp\n");
        printf("Total threads: %d , executed in %lfs and the Giga Ops/sec are %lf\n", numthreads, executionTime, ops);
        strcat(output,"HP_");
        strcat(output,buffer);
        strcat(output,"thread.out.dat");
        strncpy(mode, "HP", 2);

        printf("output: %s\n",output);
    }


    else if (strncmp(input,"SP",2)==0) {
        printf("Executing sp\n");
        //gettimeofday(&etstart, NULL);
        for (i = 0; i < numthreads; i++) {
		//	id[i]=i+1;
		//  pthread_create(&thread[i], NULL, sops, &id[i]);
            pthread_create(&thread[i], NULL, sops, NULL);
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

        printf("Execution Time: %10fs", executionTime);
        printf("Actual Execution Time: %lfs", executionTime);

        // Calculate total number of operations.
        totalops = (10ul*ITERATION1*ITERATION)+(4ul*ITERATION);

        printf("Totalops: %lf\n",(double)totalops);

        //Operations per second equals to total number of operations divided by total execution time

        ops = (((double)totalops)/((double)executionTime))/1000000000;
        flops = 32;
        tops = (double)socket*corepersocket*cyclepersecond*flops;
        efficiency = (double)ops/(double)tops*100ul;

        printf("Executed sp\n");
        printf("Total threads: %d , executed in %lfs and the Giga Ops/sec are %lf\n", numthreads, executionTime, ops);
        strcat(output,"SP_");
        strcat(output,buffer);
        strcat(output,"thread.out.dat");
        strncpy(mode, "SP", 2);
        printf("output: %s\n",output);
    }


    else if (strncmp(input,"DP",2)==0) {

        //gettimeofday(&etstart, NULL);
        for (i = 0; i < numthreads; i++) {
		//	id[i]=i+1;
		//	pthread_create(&thread[i], NULL, dops, &id[i]);
            pthread_create(&thread[i], NULL, dops, NULL);
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

        printf("Execution Time: %10fs", executionTime);
        printf("Actual Execution Time: %lfs", executionTime);

        // Calculate total number of operations.
        totalops = (10ul*ITERATION1*ITERATION)+(4ul*ITERATION);

        printf("Totalops: %lf\n",(double)totalops);

        //Operations per second equals to total number of operations divided by total execution time

        ops = (((double)totalops)/((double)executionTime))/1000000000;
        flops = 16;
        tops = (double)socket*corepersocket*cyclepersecond*flops;
        efficiency = (double)ops/(double)tops*100ul;

        printf("Executed dp\n");
        printf("Total threads: %d , executed in %lfs and the Giga Ops/sec are %lf\n", numthreads, executionTime, ops);

        strcat(output,"DP_");
        strcat(output,buffer);
        strcat(output,"thread.out.dat");
        strncpy(mode, "DP", 2);


        printf("output: %s\n",output);
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
        fprintf(fp,"%s %d %10f %10f %10f \n",mode,numthreads,ops,tops,efficiency);
        //Workload Concurrency MyCPUBenchValue TheoreticalValue Efficiency
    }

    return 0;
}
