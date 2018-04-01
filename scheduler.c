//part one  - This program reads the structure of the folders and writes it in an array - done
//Afterwards, it checks in each folder, if there is performance data - done
//if there is performance data, it compiles and runs the program (here comes the performance -  optimizing later) - done
//if there is no performance data, it runs the test program and then runs the program (here comes the performance - optimizing later) - done

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "hybchive.h"
#include <stdarg.h>

double hybchive(double *A, int n, char *function, int numberOfParameters,...){
	
	printf("\n 0.1 Scheduler is executed through user \n");
    //printf("\n 0.2 Data arrived in scheduler:\n");
    //printf("\n 0.2.1 First entry of A: %lf\n",A[0]);
    //printf("\n 0.2.2 Name of the algorithm:\n");
	double result=0;
	int sizefunction=sizeof(function);
    //printf("%s",function);
    //printf("\n");
    
    //printf("\n 0.2.3 n: %d\n",n);
	
	
	double *secondsarray, *nsecondsarray;
    double time;
    // marks the current time and saves it in an array
    void mytime(int timemark){
    struct  timespec currenttime;
    //dynamic memory allocation
    if(timemark==1){    
        secondsarray=malloc(sizeof(double));
        nsecondsarray=malloc(sizeof(double));
    }
    else{   
        secondsarray=(double *)realloc(secondsarray,sizeof(double)*timemark);
        nsecondsarray=(double *)realloc(nsecondsarray,sizeof(double)*timemark);
    }
    clock_gettime(CLOCK_REALTIME, &currenttime);
    secondsarray[timemark-1]=currenttime.tv_sec;
    nsecondsarray[timemark-1]=currenttime.tv_nsec;
    }
 
    // gets the time difference of two times marked in the function mytime
    double timediff(int time2, int time1)
    {   if ((nsecondsarray[time2-1]-nsecondsarray[time1-1])<0) {
            time=secondsarray[time2-1]-secondsarray[time1-1];
            time=time+(1000000000+nsecondsarray[time2-1]-nsecondsarray[time1-1])/1000000000;
        } else {
            time=secondsarray[time2-1]-secondsarray[time1-1];
            time=time+(nsecondsarray[time2-1]-nsecondsarray[time1-1])/1000000000;
        }
        return time;
    }
	
	mytime(1);
	
	/* begin part one*/
	//printf("\n1. A function called function is being executed from the user\n");
	//char function[] = "function";

	//printf("\n2. cd to the folder called function and then list the variants\n");
	FILE *pipe;
	char pipecommand[2000] = "";
	char cd[]="cd ";
	//printf("\n2.1 concatenate the two strings: %s\n",pipecommand);
	strcat(pipecommand,cd);
	strcat(pipecommand,function);
	char savedir[]=" && ls -d */ | cut -f1 -d'/' > list.txt && cp list.txt 2.txt";	
	strcat(pipecommand,savedir);

	//printf("\n2.2 cd to folder and write directory listing to array\n");	
	pipe=popen(pipecommand,"w");
	close(pipe);

	//printf("\n3. Read the list.txt file in an array\n");
	int numvariants=10;
	int characters=30;
	int i,j;
	char variants[100]="";
	char list2[]="/2.txt";
	memset(pipecommand,'\0',sizeof(pipecommand));
	strcat(pipecommand,function);
	strcat(pipecommand,list2);
	while(fopen(pipecommand,"r")==NULL){
						}
	char list[]="/list.txt";
	memset(pipecommand,'\0',sizeof(pipecommand));
	strcat(pipecommand,function);
	strcat(pipecommand,list);
	pipe=fopen(pipecommand,"r");
		for(i=0;i<numvariants*characters;i++){
			fscanf(pipe,"%c",&variants[i]);
		}
	fclose(pipe);

	//printf("\n3.1 show, that the devices - array got everything \n");
	//printf("\n");
	//for(i=0;i<30;i++){
	//	printf("%c",variants[i]);
	//}		
	//printf("\n3.2 transfer devices to array\n");
	char variantslist[20][30]={};
	i=0;
	int help=0;
	int distance=0;
	for(j=0;j<50;j++){						//Bei Cloud9 darf hier die obergrenze der Iterationen nicht zu hoch sein
		if(variants[j]!='\n'){
			variantslist[i][j-distance]=variants[j];
		}
		else{
			i=i+1;
			distance=j+1;
			help=help+1;
			//printf("\ndistance: %d\n",distance);
		}
	}	
	numvariants=help;
	/*for(i=0;i<numvariants;i++){
		for(j=0;j<30;j++){
				printf("%c",variantslist[i][j]);
		}
		printf("end of line\n");
	}*/
	
	//printf("\nprint help value  %d\n",help);

	//printf("\n3.3 rm list.txt\n");
	char cd2[]="cd ";
	char pipecommand2[2000] = "";
	strcat(pipecommand2,cd2);
	strcat(pipecommand2,function);
	char removedir[]=" && rm list.txt && rm 2.txt";
	strcat(pipecommand2,removedir);
	pipe=popen(pipecommand2,"w");
	close(pipe);

	/*end part one*/

	/*begin part two*/
	//printf("\n4. cd to every variant and check, if there is performance data\n");
	//printf("\n4.1 merge variant list and cd - command\n");
	char performancedata[]="performance.txt";
	int k,l;
	FILE *pipe2;
	int checkallperformance=0;
	memset(pipecommand,'\0',sizeof(pipecommand));
	for(i=0;i<numvariants;i++){
		//printf("\n a Check pipecommand, i=%d\n",i);
		/*for(j=0;j<40;j++){
			printf("%c",pipecommand[j]);
		}*/
		memset(variants,'\0',sizeof(variants));
		for(k=0;k<20;k++){
			if(variantslist[i][k]!='\0'){
				variants[k]=variantslist[i][k];
			}
		}
		char currentdir[1000]="";
		memset(currentdir,'\0',sizeof(currentdir));
		strcat(pipecommand,function);
		strcat(currentdir,function);
		strcat(pipecommand,"/");
		strcat(currentdir,"/");
		strcat(pipecommand,variants);
		strcat(currentdir,variants);
		strcat(pipecommand,"/");
		char make[1000]="";
		char execute[1000]="";
		char wait[1000]="";
		strcat(pipecommand,performancedata);
		//printf("\n b Check pipecommand, i=%d\n",i);
		/*for(j=0;j<40;j++){
			printf("%c",pipecommand[j]);
		}*/
		//printf("\n");

		//printf("\n 4.2 Check, if performance data exists.\n");
		
		if(fopen(pipecommand,"r")==NULL){
			//printf("\nNo performance data found for ");
			for(j=0;j<40;j++){
				//printf("%c",pipecommand[j]);
			}
			//printf("\n");
			//printf("\n 4.3 Execute test \n");
			
			memset(make,'\0',sizeof(make));
			
			strcat(make, "cd ");
			strcat(make,currentdir);
			//printf("\n Execute varianttest \n");
			strcat(make," && make test && ./varianttest");
			pipe=popen(make,"w");
			close(pipe);
			memset(wait,'\0',sizeof(wait));
			strcat(wait,currentdir);
			strcat(wait,"/");
			strcat(wait,"wait.txt");
			while(fopen(wait,"r")==NULL){
				//wait, until test procedure is done with testing of the according variant
			}
			//printf("\n End execute varianttest \n");
			memset(wait,'\0',sizeof(wait));
			strcat(wait,"rm ");
			strcat(wait,currentdir);
			strcat(wait,"/");
			strcat(wait,"wait.txt");
			pipe=popen(wait,"w");
			close(pipe);
			
		}
		if(pipe=fopen(pipecommand,"r")){
			checkallperformance=checkallperformance+1;
			fclose(pipe);
			//printf("\nPerformance data found for ");
			for(j=0;j<40;j++){
				//printf("%c",pipecommand[j]);
			}
		}
		memset(pipecommand,'\0',sizeof(pipecommand));

	}

	if(checkallperformance==numvariants){
		//printf("\n 4.4 All performance files found. \nExecute performance optimizing procedure\n");	
		char optimize [100]="";
		memset(optimize,'\0',sizeof(optimize));
		char cn2[100];
		memset(cn2,'\0',sizeof(cn2));
		sprintf(cn2,"%d",n);
		strcat(optimize,"gcc optimize.c -o optimize && ./optimize");
		strcat(optimize," ");
		strcat(optimize,cn2);
		strcat(optimize," ");
		strcat(optimize,function);
		pipe=popen(optimize,"w");
		close(pipe);
		while(fopen("wait.txt","r")==NULL){
			//wait, until test procedure is done with testing of the according variant
		}
		pipe=popen("rm wait.txt","w");
		close(pipe);
		
		//printf("\n7.4 Get the splitting information\n");
		int shmid;
    	key_t key;
    	int *shm, *s;
    	//int n=899999;
    	int size=sizeof(int)*n;
	    /*
	    * We need to get the segment named
	    * "5678", created by the server.
	    */
	    key = 5678;
	 
	    /*
	    * Locate the segment.
	    */
	    if ((shmid = shmget(key, size, 0666)) < 0) {
	    perror("shmget");
	    exit(1);
	    }
	 
	    /*
	    * Now we attach the segment to our data space.
	    */
	    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
	    perror("shmat");
	    exit(1);
	    }
	    
	    //printf("\n 7.5 Splitting Data arrived in scheduler\n");
	    for(i=0;i<numvariants;i++){
	    	//printf("\n (in scheduler) Device: %d, n = %d\n",i,shm[i]);
	    }
		
		//printf("\n 4.5 Optimizing Procedure has finished. Execute programs\n");
		
		//printf("\n 8. Create data for programs (later as user - input)\n");
		/*double A[n];
		for(i=0;i<n;i++){
			A[i]=1;
		}*/
		
		//printf("\n 8.1 Create shared memory for variants\n");
		int shmid2;
    	key_t key2;
    	double *shm2, *s2;
    	key2 = 1111;
    	int size2=sizeof(double)*n;
    	
    	/*
    	* Create the segment.
    	*/
    	if ((shmid2 = shmget(key2, size2, IPC_CREAT | 0666)) < 0) {
    	perror("shmget");
    	exit(1);
    	}
 
    	/*
    	* Now we attach the segment to our data space.
    	*/
    	if ((shm2 = shmat(shmid2, NULL, 0)) == (double *) -1) {
    	perror("shmat");
    	exit(1);
    	}
 
	    /*
	    * Now put some things into the memory for the
	    * other process to read.
	    */
	    
		//printf("\n 8.2 Put data in shared memory space\n");
        mytime(7);
		s2=shm2;
		for(i=0;i<n;i++){
			s2[i]=A[i];
		}
        mytime(8);
		//printf("\n 8.3 Test Data in shared memory: %lf\n",s2[0]);
		
		int begin=0, end=0;
		
		double *shm3, *s3;
		for(i=0;i<numvariants;i++){
			//printf("\n 8.4 Calculate begin and end of each variant\n");
			end=end-1;
			begin=end+1;
			end=end+1;
			end=end+shm[i];
			//printf("\n 8.5 Execute variant %d\n",i);
			//printf("\n Begin: %d, end: %d\n",begin,end);
			memset(variants,'\0',sizeof(variants));
			for(k=0;k<20;k++){
				if(variantslist[i][k]!='\0'){
					variants[k]=variantslist[i][k];
				}
			}
			char currentdir[1000]="";
			memset(currentdir,'\0',sizeof(currentdir));
			strcat(currentdir,function);
			strcat(currentdir,"/");
			strcat(currentdir,variants);
			
			//printf("\n 8.6 Converting inputs for programs into strings\n");
			char cbegin[100]; 
			char cend[100];
			char ckey[100];
			char cn[100];
			char ci[100];
			char cnumvariants[100];
			sprintf(cbegin,"%d",begin);
			sprintf(cend,"%d",end);
			sprintf(cn,"%d",n);
			sprintf(ci,"%d",i);
			sprintf(cnumvariants,"%d",numvariants);

			//printf("\n 8.6.1 Check, if it works: %s, %s\n",cbegin,cend);
			
			//printf("\n 8.6.2 Convert key_t in char\n");
			sprintf(ckey,"%d",key2);
			//printf("\n 8.6.2 Check, if it works: %s\n",ckey);
			
			/*printf("\n 4.5.1 Print current directory\n");
			for(j=0;j<40;j++){
				printf("%c",currentdir[j]);
			}
			printf("\n");*/
			
			//printf("\n 14. Create Shared memory for result\n");
			int shmid3;
	    	key_t key3;
	    	
	    	key3 = 2222;
	    	char ckey3[100];
	    	sprintf(ckey3,"%d",key3);
	    	int size3=sizeof(double)*(numvariants+1);	//the first entry is used by the variants to show that the variants are done.
	    	/*
	    	* Create the segment.
	    	*/
	    	if ((shmid3 = shmget(key3, size3, IPC_CREAT | 0666)) < 0) {
	    	perror("shmget");
	    	exit(1);
	    	}
	 
	    	/*
	    	* Now we attach the segment to our data space.
	    	*/
	    	if ((shm3 = shmat(shmid3, NULL, 0)) == (double *) -1) {
	    	perror("shmat");
	    	exit(1);
	    	}
	    	
	    	s3=shm3;
	    	s3[0]=0;
			
			char make[1000]="";
			memset(make,'\0',sizeof(make));
			strcat(make,"cd ");
			strcat(make,currentdir);
			strcat(make," && make final && ./variant");
			//printf("\n 9 Concatenate inputs - key, begin, end\n");
			strcat(make," ");
			strcat(make,ckey);
			strcat(make," ");
			strcat(make,cbegin);
			strcat(make," ");
			strcat(make,cend);
			strcat(make," ");
			strcat(make,cn);
			strcat(make," ");
			strcat(make,ci);
			strcat(make," ");
			strcat(make,cnumvariants);
			strcat(make," ");
			strcat(make,ckey3);
			
			//printf("\n9.05 Attach parameters to the make command\n");
			
			//printf("\n9.05.02 Show number of Parameters:\n");
			
			va_list valist;
			va_start(valist, numberOfParameters);
			
			int parameters;
			char parameterList[100][100];

			for(j=0;j<=numberOfParameters;j++){
				parameters = va_arg(valist, int);
				
				memset(parameterList[j],'\0',sizeof(parameterList));
				sprintf(parameterList[j],"%d",parameters);
				//printf("\n Parameter number %d %s \n",j,parameterList[j]);
				
				strcat(make," ");
				strcat(make,parameterList[j]);
			}
			
			
			va_end(valist);
			
			
			//printf("\n 9.1 Print make and execute command\n");
			for(j=0;j<120;j++){
				printf("%c",make[j]);
			}
			//printf("\n");

			pipe=popen(make,"w");
			close(pipe);
		}
		
		//printf("\n 16. scheduler starts sleeping\n");
        mytime(2);
		while(s3[0]!=numvariants){
        	sleep(1);
		}
        mytime(3);
		//printf("\n 17. All variants are done\n");
		
		//printf("\n 18. Calculcating Result:\n");
		
		for(i=1;i<numvariants+1;i++){		//1, because 0 is for communication with scheduler
			result=result+s3[i];
		}
		//printf("\n 19. Result: %lf\n",result);
		
		
		
		
		
	}//end if(numvariants==all there)
	//printf("\n 20. Remove all shared memory\n");
	pipe=popen("chmod +x kill_ipcs.sh && ./kill_ipcs.sh","w");
	close(pipe);
	
	mytime(4);
	
	printf("Time for %d variants copying data: %f sec\n",numvariants,timediff(8,7));
	
	pipe=fopen("performancev1.txt","a");
		fprintf(pipe,"%lf \n",timediff(4,1));
	fclose(pipe);
	
	return result;
	

}
