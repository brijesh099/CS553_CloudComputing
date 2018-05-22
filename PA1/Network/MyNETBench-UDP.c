/* Name: Brijesh Mavani
CWID: A20406960
University: Illinois Institute of Technology
Course: Cloud Computing
Assignment: 1  */

/* Network Benchmarking using UDP*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define ONEGB 1024*1024*1024
#define NUM_LOOPS 100
#define BUFF_SIZE 64
#define ERROR -1
#define PORT 9876

//Comments are added for debugging purpose

int Iterations,bufsize,numthreads;
long int mem = 1024*1024*1024;	//Allocating 1GB of memory
//long int mem = 1024*1024;	//Allocating 1MB of memory for testing
char buffer[ONEGB+1] = {0};
struct hostent *hp;
char output[100] = "./output/network-"; //network-UDP-1-1thread.out.dat
char mode[3];  // input operation mode.
char block[5];
typedef struct tinfo {
    int bsize; // buffer size
    int sockid;   // socket
    int tid; //Thread id
} tinfo;

typedef struct clientinfo {
    long int start; // starting location
    long int end;   // end location
    int tid; //Thread id
    int socketid;
    char ip[100];
} clientinfo;


void *UDP_Client_Data(void *arg)
{

    // char buffer[mem+1] = {0};
    int rc,i;
    int j,rep;
    clientinfo *pclieninfo;
    pclieninfo = (clientinfo *)arg;
    long int start = pclieninfo->start;
    long int end = pclieninfo->end;
    int tid = pclieninfo->tid;
    int sockfd = pclieninfo->socketid;
    printf("start is: %ld\n",start);
    printf("end is: %ld\n",end);
    printf("socketid:%d\n",sockfd);


    long int buffersize = bufsize;
    int threadblock= end-start;
    long int bytestosend=0;
    char *sbuffer = (char*) malloc(buffersize);
    char *rbuffer = (char*) malloc(buffersize);
    char c;
    long int sendcount=0,readcount=0,readvalue=0;
    memset(sbuffer, 'A',(bufsize));

    struct sockaddr_in addr_ser;
    char ip[100];

    addr_ser.sin_family = AF_INET;
    //addr_ser.sin_port = htons(PORT+tid);
    addr_ser.sin_port = htons(PORT);
    //int inet = inet_pton(AF_INET, tid, &addr_ser.sin_addr);
    struct sockaddr_in client_addr;
    int sockaddr_in_size = sizeof(struct sockaddr_in);
    struct in_addr **addr_list;
    addr_list = (struct in_addr **) hp->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        break;
    }


    int inet = inet_pton(AF_INET, ip, &addr_ser.sin_addr);

    //printf("client sending data with buffersize: %ld and bufsize:%d\n",buffersize,bufsize);
    rep=(bufsize==1)?1:100;
    printf("Rep:%d\n",rep);
    bytestosend= (end+1-start)*buffersize*100ul;
    printf("client Sock:%d\n",sockfd);
    for (i =0; i< rep; i++) {
        printf("in I for loop:%d\n",i);
        //printf("Bytes to send:%ld and (bytestosend-buffersize):%ld and sendcount:%ld\n",bytestosend,(bytestosend-buffersize),sendcount);
        for (j = start; j <=end; j++) {
            //printf("in J for loop");
            if (sendcount>=(bytestosend-buffersize))
            {
                memset(sbuffer, 'X',(bufsize));
                printf("client :%d sending last time!!\n",tid);
            }
            //rc = send(sockfd, sbuffer, buffersize, 0);
            //printf("msg sending");
            rc=sendto(sockfd, sbuffer, bufsize, 0, (struct sockaddr *)&addr_ser, sizeof(struct sockaddr));
            //printf("msg sent");
            if (rc < 0) {
                printf("Could not send package!\n");
            }
            sendcount+=buffersize;
            if (bufsize==1)
            {
                //	printf("waiting to receive");
                readvalue=recvfrom(sockfd,rbuffer,bufsize,0,(struct sockaddr *)&addr_ser, &sockaddr_in_size);
                //readvalue=recv(sockfd,rbuffer,bufsize,0);
                readcount+=readvalue;
            }
        }
        //	readvalue=recv(sockfd,rbuffer,bufsize,0);
        //	readcount+=readvalue;
        printf("client %d sent data for:%d times\n",tid,i);
    }
    printf("client receive count:%ld\n",readcount);
    printf("Client send count: %ld\n",sendcount);
    free (sbuffer);  // free the send buffer memory
    free (rbuffer);  // free the receive buffer memory
    //close(sockfd);
    return NULL;

}

// UDP Client
void *UDP_Client(void *arg) {
    int rc,i;
    struct sockaddr_in addr_ser;
    int sockfd = 0;
    long int readvalue=0,sendvalue=0;
//	struct in_addr **addr_list;
//	char ip[100];
    FILE *fp;


    double starttime,stoptime,exetime,bvalue,tvalue,efficiency,bput,blat,tput;
    struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */

    pthread_t clientthreads[numthreads];
    clientinfo pclieninfo[numthreads];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Could not create socket!\n");
        exit(-1);
    }
    memset(&addr_ser, 0, sizeof(addr_ser));

    /*addr_list = (struct in_addr **) hp->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        break;
    }*/
    //set server's address and port
    //printf("IP of the server:%s\n",ip);
    addr_ser.sin_family = AF_INET;
    //addr_ser.sin_port = htons(PORT+tid);
    addr_ser.sin_port = htons(PORT);
    /*int inet = inet_pton(AF_INET, ip, &addr_ser.sin_addr);
    if(inet<=0)
    {
        printf("\nAddress is invalid or the provided address is not supported.\n");
        exit(-1);
    }
    /*rc = connect(sockfd,  (struct sockaddr *)&addr_ser, sizeof(addr_ser));

    if (rc < 0) {
    	printf("Could not connect to server!\n");
    	exit(-1);
    }*/

    gettimeofday(&etstart, NULL);
    printf("Iterations:%d",Iterations);
    for (i=0;i<numthreads;i++)
    {
        pclieninfo[i].start= i*(Iterations/numthreads);
        pclieninfo[i].end=((i+1)*(Iterations/numthreads))-1;
        pclieninfo[i].tid=i+1;
        pclieninfo[i].socketid=sockfd;
        //pclieninfo[i].ip=ip;
        pthread_create( &clientthreads[i], NULL,  UDP_Client_Data , &pclieninfo[i]);
        printf("client created data thread:%d\n",i+1);
        //sleep(5);
    }
    printf("client created total data thread:%d\n",i);
    for (i=0;i<numthreads;i++)
    {
        pthread_join(clientthreads[i], NULL);
        printf("client joined data thread:%d\n",i+1);
    }

    gettimeofday(&etstop, NULL);

    // Calculate execution time in sec

    starttime= (double)etstart.tv_sec+(double)(etstart.tv_usec/1000000);
    stoptime= (double)etstop.tv_sec+(double)(etstop.tv_usec/1000000);
    printf("starttime: %lf s\n",starttime);
    printf("stoptime: %lf s\n",stoptime);
    exetime = (double)stoptime-(double)starttime;
    printf("exetime:%f",exetime);
    if (bufsize==1)
    {
        //latency Calculations;
        bput = ((exetime*1000)/(mem))*100ul;
        printf("Latency is: %lf ms\n",blat);
        tput=0.0007;
    }
    else {
        //throughput calculations;
        bput = ((mem*800ul)/exetime)/(1024*1024);
        printf("Throughput is: %lf Mbps\n",bput);
        tput=56000;
        //efficiency=(bput/tput)*100;
    }
    //write to file
    bvalue=bput;
    tvalue=tput;

    if (bufsize>1) {
        efficiency = ((double)bvalue/(double)tvalue)*100ul;
    }
    else {
        efficiency = ((double)bvalue/(double)tvalue);
    }
    printf("output in client:%s and mode is:%s",output,mode);
    fp = fopen(output, "a");

    if (fp == NULL)
    {
        printf("error in opening file");
        exit (-1);
    }
    else
    {
        fprintf(fp,"%s %d %s %10f %10f %10f\n",mode,numthreads,block,bvalue,tvalue,efficiency);
        //Protocol Concurrency BlockSize MyNETBenchValue TheoreticalValue MyNETBenchEfficiency
    }



    return NULL;
}

void *UDP_server_Data(void *arg)
{
    struct tinfo *ptinfo = (struct tinfo *)arg;
    char c;
    int svalue = 0,i=0,j=0;
    long int sendcount=0,readcount=0,counter=0;
    char *sebuffer = (char*) malloc(bufsize);
    char *rebuffer = (char*) malloc(bufsize);
    printf("server data thread\n");
    memset(sebuffer, 'B',(bufsize));
    long int tblock=(mem/numthreads);
    long int totalblock = tblock*100;
    printf("Tblock: %ld\n",tblock);
    printf("TotalBlock: %ld\n",totalblock);
    printf("server buffer:%d\n",bufsize);
    struct sockaddr_in client_addr;
    int sockaddr_in_size = sizeof(struct sockaddr_in);
    printf("server sock:%d\n",ptinfo -> sockid);

    char z='X';
    int y=0;
    while (y==0)
    {
        //printf("in while loop\n");
        svalue=recvfrom(ptinfo -> sockid,rebuffer,bufsize, 0,(struct sockaddr *)&client_addr, &sockaddr_in_size);
        //printf("after receive\n");
        readcount+=svalue;
        //send(ptinfo -> sockid,sebuffer,svalue,0);
        //send(ptinfo -> sockid,sebuffer,svalue,MSG_NOSIGNAL);

        if (bufsize==1)
        {
            sendto(ptinfo -> sockid,sebuffer, bufsize, 0, (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
            //printf("after send\n");
            sendcount+=svalue;
        }
        counter++;
        if (rebuffer[0]==z)
        {
            counter++;
            if (counter>10000000)
            {
                printf("Exiting server\n");
                y=1;//exit while loop
            }
        }

        /*
        //printf("in while loop\n");
        svalue=recv(ptinfo -> sockid,rebuffer,bufsize,0);
        readcount+=svalue;
        //send(ptinfo -> sockid,sebuffer,svalue,0);
        if(bufsize==1)
        {
        	send(ptinfo -> sockid,sebuffer,svalue,MSG_NOSIGNAL);
        }
        sendcount+=svalue;
        counter++;
        if(rebuffer[0]==z)
        {
        	counter++;
        	if(counter>totalblock)
        	{
        		printf("Exiting server\n");
        		y=1;//exit while loop
        	}
        }*/
    }
    printf("server receive count:%ld\n",readcount);
    printf("server send count:%ld\n",sendcount);
    printf("server freed sbuf\n");
    free(sebuffer);
    printf("server freed rbuf\n");
    free(rebuffer);
    exit (-1);
    // close(ptinfo -> sockid);
    /*free(sebuffer);
    printf("server freed sbuf");
    free(rebuffer);
    printf("server freed rbuf");*/

    return NULL;
}

// UDP Server
void *UDP_Server() {
    printf("udp server");

    int sockfd, clientfd, rc,i;
    struct sockaddr_in ser_addr,client_addr;
    //char *sbuffer;
    //char *rbuffer;
    socklen_t addrlen;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Could not create socket!\n");
        exit(-1);
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    //set server address and port


    //printf("UDP server thread memset.\n");
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ser_addr.sin_port = htons(PORT);
    /*for(i=0;i<numthreads;i++){
    	ser_addr.sin_port = htons(PORT+i+1);
    }*/
    if (bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0) {
        printf("Could not bind socket!");
        close(sockfd);
        exit(-1);
    }
    /*int L = listen(sockfd, numthreads);
    	printf("listen value:%d\n",L);
    if(L<0){
    	printf("Could not listen to socket!");
    	close(sockfd);
    	exit(-1);
    }

    addrlen = sizeof(ser_addr);	*/

    pthread_t serverthreads[numthreads];
    // connect with a client
    for (i=0;i<numthreads;i++)
    {
        /*clientfd = accept(sockfd, (struct sockaddr *)&ser_addr, &addrlen);
        if (clientfd < 0) {
        	printf("Could not accept client!\n");
        	close(sockfd);
        	exit(-1);
        }*/
        struct tinfo *ptinfo = (struct tinfo *)malloc(sizeof(struct tinfo));
        ptinfo[i].bsize = bufsize;
        ptinfo[i].sockid = sockfd;
        ptinfo[i].tid=i+1;
        printf("server created data thread:%d\n",i+1);
        pthread_create(&serverthreads[i],NULL,UDP_server_Data,&ptinfo[i]);
        printf("server data thread returned:%d\n",i);
        pthread_join(serverthreads[i], NULL);
    }
    printf("server created total data thread:%d\n",i);
    /*for(i=0;i<numthreads;i++){
    	pthread_join(serverthreads[i], NULL);
    	printf("server joined data thread:%d\n",i+1);
    }*/
    printf("server joined total data thread:%d\n",i);

    close(clientfd);
    close(sockfd);
}

int main(int argc, char *argv[]) {

    FILE *fp;
    char buffer1[20];
    char input[3];  // input operation mode.
    //char output[100] = "./output/network-"; //network-UDP-1-1thread.out.dat
    //char mode[3];  // input operation mode.
    int i,repeat,bsize;
    double executionTime,exestart,exestop,latencystart,latencystop,latencyTime,bvalue,tvalue,tput,efficiency;
    struct timeval etstart, etstop,latstart,latstop;  /* Elapsed times using gettimeofday() */


    if (argc < 2)
    {
        printf("usage: %s <file name>\n", argv[0]);
        return -1;
    }

    printf("argv[0]: %s\n",argv[1]);
    if (argc==3)
    {
        printf("hostname:");
        hp = gethostbyname(argv[2]);
        printf("hostname:");
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("error in opening file");
        return -1;
    }
    else
    {
        fscanf(fp, "%s", buffer1);
        strncpy(mode, buffer1, 3);

        printf("Mode: %s", mode);
        if (strncmp(buffer1,"UDP",3)==0) {
            strcat(output,"UDP-");
        }
        else {
            printf("Invalid protocol.");
            return -1;
        }
        fscanf(fp, "%s", buffer1);
        printf("2nd line : %s\n", buffer1 );
        bufsize = atoi(buffer1);
        strcat(output,buffer1);
        fscanf(fp, "%s", buffer1);
        printf("3rd line : %s\n", buffer1 );
        numthreads = atoi(buffer1);
        strcat(output,"-");
        strcat(output,buffer1);
        strcat(output,"thread.out.dat");
    }
    fclose(fp);
    printf("output: %s",output);

    pthread_t ithread[1];
    if (bufsize==1)
    {
        bufsize = 1;
        strncpy(block, "1B", 2);
    }
    else if (bufsize>1 && bufsize <= 1000)
    {
        bufsize = 1024;
        strncpy(block, "1KB", 3);
    }
    else if (bufsize>1000 && bufsize <= 32000)
    {
        bufsize = 1024*32;
        strncpy(block, "32KB", 4);
    }

    Iterations = mem/bufsize;
    //parameter structure passed in pthread
    tinfo t;
    t.bsize = bufsize;
    Iterations = (bsize==1)?(100000000):Iterations;
//Call respective function to perform RWR and RWS operations

    //gettimeofday(&etstart, NULL);
    i =0;

    // while(i<2)
    //{
    if (argc==2) {
        printf("creating server parent thread.\n");
        pthread_create(&ithread[0], NULL, UDP_Server,NULL); //Server parent thread

    }
    else if (argc==3) {
        sleep(10);
        printf("creating client parent thread.\n");
        pthread_create(&ithread[0], NULL, UDP_Client,NULL); //Client parent thread
    }
    // sleep for 10 sec before creating client parent thread
    //i++;
    // }
    //i=0;
    //while(i<2)
    //{
    if (argc==2) {
        printf("joining server parent thread.\n");
        pthread_join(ithread[0], NULL); //Server parent thread
        printf("server parent thread joined.\n");
    }
    else if (argc==3) {
        printf("joining client parent thread.\n");
        pthread_join(ithread[0], NULL); //Client parent thread
        printf("client parent thread joined.\n");
    }
    //i++;
    // }
    return 0;

}