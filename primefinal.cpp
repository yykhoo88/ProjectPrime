#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//defining constants
#define TOTALMEM 60000000
#define SIZEOFVBR 4294967296
#define PRIMEINFILE 10000

//declaring functions
unsigned long readtext(unsigned long *primenum); //reading numbers from text to mem
unsigned long checkprime(unsigned long num,unsigned long *primenum,unsigned long sizelast); //checking primility given number, list of primes, size of primes
void pif(unsigned long prime,unsigned long sizelast);//print in file

void main()
{
	unsigned long sizelast,flag,i=0,testnumber;//size of last done iteration,flag whethere it's a prime, counter
	unsigned long noptd;//Number Of Prime To Do
	unsigned long *primenum;//pointer to malloc, primenum=list of primes in ram
	clock_t startClock;
	double timeTaken;	
	primenum=(unsigned long*)malloc(TOTALMEM*4); //allocate appropriate memory
	sizelast=readtext(primenum);	//reading numbers,sizelast = size of array so far
	
	//edit to make it run itself
	//printf("Please insert the number of itteration to do: ");//asking for itterations
	//scanf("%u",&noptd);
	noptd=TOTALMEM-sizelast-1;
	startClock = clock();
	testnumber=primenum[sizelast-1];

	//looping for primes
	while((i<noptd) && (testnumber<SIZEOFVBR) && (i<TOTALMEM)){
			testnumber+=2;
			flag=checkprime(testnumber,primenum,sizelast);
			if(flag==0){
					i++;
					printf("%-10uth number: %u\n",sizelast+1,testnumber);
					primenum[sizelast]=testnumber;
					pif(testnumber,sizelast);
					sizelast++;
			}
	}
	timeTaken = ((double)(clock() - startClock) / (double)CLOCKS_PER_SEC);
	printf("The program took %.3fs\n", timeTaken);
}

unsigned long readtext(unsigned long *primenum)
{
	unsigned long i=0; //total number of elements
	int filenum=0,j=0;//file number, local counter
	char path[30];//path to file
	FILE *fp;
	do{
		//opening the correct file, starting from prime0.dat
		sprintf(path,"b:\\primes%d.dat",filenum);
		fp=fopen(path,"r");
		//checking null pointer
		if(fp==NULL){
			printf("error opening file %s. quitting\n",path);
			exit(1);
		}
		//reading into file
		while(j<PRIMEINFILE){
			//if encounter EOF before file ends, return
			if((fscanf(fp,"%u",primenum++))==EOF){
				fclose(fp);
				return (i);
			}
			i++;
			j++;
		}
		fclose(fp);
		filenum++;
		j=0;
	} while(1);
}

unsigned long checkprime(unsigned long num,unsigned long *primenum,unsigned long sizelast)
{
	unsigned long i,a;
	int flag=0;
	a=(unsigned long)sqrt((double)sizelast);
	for(i=0;i<a;i++){
		if(num%primenum[i]==0){
			flag=1;
			break;
		}
	}
	return(flag);
}


void pif(unsigned long prime,unsigned long sizelast)
{
	FILE *fp;
	char path[30];//path to file
	sprintf(path,"b:\\primes%d.dat",(sizelast)/PRIMEINFILE);
	fp=fopen(path,"a+");
	if(fp==NULL){
		printf("error opening file. quitting");
		exit(1);
	}
	fprintf(fp,"\n%u",prime);
	fclose(fp);
}
