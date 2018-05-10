#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "hybchive.h"
#include <stdarg.h>

int checkallperformance=0;
int numvariants=10;
int characters=30;
int i,j;
int k,l;
int help=0;
int distance=0;
double result=0;
char savedir[]=" && ls -d */ | cut -f1 -d'/' > list.txt && cp list.txt 2.txt";
char pipecommand[2000] = "";
char cd[]="cd ";
char list2[]="/2.txt";
char variantslist[20][30]={};
char list[]="/list.txt";
char performancedata[]="performance.txt";
char cd2[]="cd ";
char pipecommand2[2000] = "";
char removedir[]=" && rm list.txt && rm 2.txt";
char currentdir[1000]="";
char make[3000]="";
char execute[1000]="";
char Wait[1000]="";
char optimizeCommand[1000]="";

FILE *pipe;
FILE *pipe2;



void hybchive(char *hybChiveSetName, char *variants, char *optimize, int numberOfParameters, ...) {

    srand( time( NULL ) );   // should only be called once

    // start log
    hybchiveLog( "scheduler | start scheduler" );


    //printf("\n2.2 cd to folder and write directory listing to array\n");
	pipe=popen(
            concatenate(
                    3,
                    sizeof( cd ),
                    cd,
                    sizeof( hybChiveSetName ),
                    hybChiveSetName,
                    sizeof( savedir ),
                    savedir
            )
            ,"w");
	close(pipe);

	//printf("\n3. Read the list.txt file in an array\n");
	while(
            fopen(
            concatenate(
                    2,
                    sizeof( hybChiveSetName ),
                    hybChiveSetName,
                    sizeof( list2 ),
                    list2
            )
            ,"r")==NULL
            ){

    }


	pipe=fopen(
            concatenate(
                    2,
                    sizeof( hybChiveSetName ),
                    hybChiveSetName,
                    sizeof( list ),
                    list
            )
            ,"r");
    for( i = 0; i < numvariants * characters; i++ ) {
        fscanf(pipe,"%c",&variants[i]);
    }
	fclose(pipe);

	printf("\n3.1 show, that the devices - array got everything \n");
	printf("\n");
	for(i=0;i<30;i++){
		printf("%c",variants[i]);
	}


	//printf("\n3.2 transfer devices to array\n");

	i=0;

	for(j=0;j<50;j++){
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
	for(i=0;i<numvariants;i++) {
		for(j=0;j<30;j++){
				printf("%c",variantslist[i][j]);
		}
		printf("\n");
	}

    pipe=popen(
            concatenate(
                    3,
                    sizeof( cd2 ),
                    cd2,
                    sizeof( hybChiveSetName ),
                    hybChiveSetName,
                    sizeof( removedir ),
                    removedir
            )
            ,"w");
	close(pipe);

	/*end part one*/

	/*begin part two*/
	//printf("\n4. cd to every variant and check, if there is performance data\n");
	//printf("\n4.1 merge variant list and cd - command\n");


	for(i=0;i<numvariants;i++) {

        memset(currentdir,'\0',sizeof(currentdir));
		memset(pipecommand,'\0',sizeof(pipecommand));
        memset(variants,'\0',sizeof(variants));

		printf("\n a Check pipecommand - should be empty, i=%d\n",i);
		for(j=0;j<40;j++){
			printf("%c",pipecommand[j]);
		}

		for(k=0;k<20;k++){
			if(variantslist[i][k]!='\0'){
				variants[k]=variantslist[i][k];
			}
		}


		strcat(currentdir,hybChiveSetName);
		strcat(currentdir,"/");
        strcat(currentdir,variantslist[i]);



        if(fopen(
                concatenate(
                        5,
                        sizeof( hybChiveSetName ),
                        hybChiveSetName,
                        sizeof( "/" ),
                        "/",
                        sizeof( variantslist[i] ),
                        variantslist[i],
                        sizeof( "/" ),
                        "/",
                        sizeof( performancedata ),
                        performancedata
                )
                ,"r")==NULL){
            hybchiveLog( "scheduler | No performance data found for" );
			printf("\n ");
			for(j=0;j<40;j++){
				printf("%c",variantslist[i][j]);
			}



			printf("\n");
			printf("\nscheduler | 4.3 Execute test \n");
			memset(make,'\0',sizeof(make));

			strcat(make, "cd ");
            int length = strlen(currentdir);
            if (currentdir[length-1] == '\n') {
                //printf("remove newline");
                currentdir[length-1]  = '\0';
            }
            strcat(make, currentdir);

			strcat(make, " && make test && ./varianttest");

			printf("\n b Check pipecommand - should be set name and variant name, i=%d\n",i);
			for(j=0;j<70;j++) {
				printf("%c",currentdir[j]);
			}
            printf("\nCurrentdir not working!");


			pipe=popen(make,"w");
			close(pipe);
			memset(Wait,'\0',sizeof(Wait));
			strcat(Wait,currentdir);
			strcat(Wait,"/");
			strcat(Wait,"Wait.txt");
			while(fopen(Wait,"r")==NULL){
				//Wait, until test procedure is done with testing of the according variant
			}
            hybchiveLog( "scheduler | End execute varianttest" );
			memset(Wait,'\0',sizeof(Wait));
			strcat(Wait,"rm ");
			strcat(Wait,currentdir);
			strcat(Wait,"/");
			strcat(Wait,"Wait.txt");
			pipe=popen(Wait,"w");
			close(pipe);

		}
		if(pipe=fopen(
                concatenate(
                        5,
                        sizeof( hybChiveSetName ),
                        hybChiveSetName,
                        sizeof( "/" ),
                        "/",
                        sizeof( variantslist[i] ),
                        variantslist[i],
                        sizeof( "/" ),
                        "/",
                        sizeof( performancedata ),
                        performancedata
                )
                ,"r")){
			checkallperformance=checkallperformance+1;
			fclose(pipe);
//			printf("\nPerformance data found for ");
//			for(j=0;j<40;j++){
//				printf("%c",variantslist[i][j]);
//			}
//            printf("\n");
		}
		memset(pipecommand,'\0',sizeof(pipecommand));

	}

	if( checkallperformance == numvariants ) {
        hybchiveLog( "scheduler | 4.4 All performance files found. Execute performance optimizing procedure" );



        int n = 100;
		char cn2[100];
		memset(cn2,'\0',sizeof(cn2));
		sprintf(cn2,"%d",n);
		pipe=popen(
                concatenate(
                        5,
                        sizeof( "gcc optimize.c -o optimize hybchiveLog.o && ./optimize" ),
                        "gcc optimize.c -o optimize hybchiveLog.o && ./optimize",
                        sizeof( " " ),
                        " ",
                        sizeof( cn2 ),
                        cn2,
                        sizeof( " " ),
                        " ",
                        sizeof( hybChiveSetName ),
                        hybChiveSetName
                )
                ,"w");
		close(pipe);

		while(fopen("Wait.txt","r")==NULL){
			//Wait, until test procedure is done with testing of the according variant
		}

		pipe=popen("rm Wait.txt","w");
		close(pipe);
        hybchiveLog( "scheduler | 7.4 Get the splitting information" );
		int shmid;
    	key_t key;
    	int *dataSplittingPattern, *s;
    	int size=sizeof(int)*n;
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
	    if ((dataSplittingPattern = shmat(shmid, NULL, 0)) == (int *) -1) {
	    perror("shmat");
	    exit(1);
	    }
        hybchiveLog( "scheduler | 7.5 Splitting Data arrived in scheduler" );
	    for(i=0;i<numvariants;i++){
	    	printf("\nscheduler | 7.6 Device: %d, n = %d",i,dataSplittingPattern[i]);
	    }
		
		printf("\nscheduler | 4.5 Optimizing Procedure has finished. Execute programs");

		/*
		 * This function will create a shared memory segment for each HybChive specific argument
		 * It returns a model where
		 * int sharedMemoryKeys[ i ] is the shared memory key for the ith hybchive specific argument.
		 * */

		va_list valist;
        va_start(valist, numberOfParameters);
        char *type="";
        int sizeOfSharedMemorySegment[ 20 ] = { 0 };
        int sharedMemoryKeyArray[ 20 ] = { 0 };
		int *sharedMemoryKey = { 0 };
        for ( i = 0; i < numberOfParameters; i++) {
            sizeOfSharedMemorySegment[ i ] = va_arg(valist, int );
            type = va_arg(valist, char * );

            if( type == "double" ) {
                double *argument = va_arg(valist, double * );
				sharedMemoryKey = createSharedMemorySegmentsandKeys(
                        sizeOfSharedMemorySegment[ i ],
                        type,
                        argument );
                sharedMemoryKeyArray[ i ] = &sharedMemoryKey[ 0 ];
            }
            printf("key: %d, size: %d", sharedMemoryKeyArray[ i ], sizeOfSharedMemorySegment[ i ] );
        }
        va_end(valist);




		int begin=0, end=0;

        printf("\n 14. Create Shared memory for Variant communication segment\n");

        //The following type is double because I have not implemented shared memory segment for int yet.
        int *sharedCommunicationMemoryKey = { 0 };
        double *communicationBetweenSchedulerAndVariants = { 0 };
        sharedCommunicationMemoryKey = createSharedMemorySegmentsandKeys(
                sizeof( communicationBetweenSchedulerAndVariants ),
                "double",
                communicationBetweenSchedulerAndVariants
        );

		
		double *shm3, *s3;
		for( i=0; i<numvariants; i++ )
        {
			printf("\n 8.4 Calculate begin and end of each variant\n");
//			end=end-1;
//			begin=end+1;
//			end=end+1;
//			end=end+shm[i];
//			printf("\n 8.5 Execute variant %d\n",i);
//			printf("\n Begin: %d, end: %d\n",begin,end);

			char currentdir[1000]="";
			memset(currentdir,'\0',sizeof(currentdir));
			strcat(currentdir,hybChiveSetName);

			strcat(currentdir,"/");
			strcat(currentdir,variantslist[ i ]);
			
			printf("\nscheduler | 8.6 Converting inputs for programs into strings");
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


            printf(
                    "\nscheduler | Input for variants: ( for each input ) variant number: %d, key: %d, size: %d\n",
                    i,
                    sharedMemoryKeyArray[ 0 ],
                    sizeOfSharedMemorySegment[ 0 ]
            );


			int shmid3;
	    	key_t key3;
	    	
	    	s3=shm3;
	    	s3[0]=0;
			
			char make[1000]="";
            char *makeCommandWithoutInputs = malloc( sizeof(char) * ( 2000 ) );;
			memset(make,'\0',sizeof(make));

            makeCommandWithoutInputs = concatenate(
                    7,
                    sizeof( "cd " ),
                    "cd ",
                    sizeof( hybChiveSetName ),
                    hybChiveSetName,
                    sizeof( "/" ),
                    "/",
                    sizeof( variantslist[ i ] ),
                    variantslist[ i ],
                    sizeof( " && make final && ./variant" ),
                    " && make final && ./variant ",
                    sizeof( ci ),
                    ci,
                    sizeof(" "),
                    " "
            );

            char *myDummy = malloc( sizeof( myDummy ) );
            memset(myDummy,'\0',sizeof(myDummy));
            strcpy(myDummy, makeCommandWithoutInputs);

            printf("\n-- Loop through Key, Size and data splitting pattern\n");

            char *makeDummy = malloc( sizeof(char) * ( 500 ) );
            memset(makeDummy,'\0',sizeof(makeDummy));
            for( j = 0; j < numberOfParameters; j++ )
            {
                char keyOfSharedMemoryForCurrentParameter[ 100 ] = "";
                memset(keyOfSharedMemoryForCurrentParameter,'\0',sizeof(keyOfSharedMemoryForCurrentParameter));

                char sizeOfSharedMemoryForCurrentParameter[ 100 ] = "";
                memset(sizeOfSharedMemoryForCurrentParameter,'\0',sizeof(sizeOfSharedMemoryForCurrentParameter));

                char cDataSplittingPatternForChosenVariant[ 100 ] = "";
                memset(cDataSplittingPatternForChosenVariant,'\0',sizeof(cDataSplittingPatternForChosenVariant));

                sprintf(
                        cDataSplittingPatternForChosenVariant,
                        "%d",
                        dataSplittingPattern[ i ]
                );
                sprintf(
                        keyOfSharedMemoryForCurrentParameter,
                        "%d",
                        sharedMemoryKeyArray[ i ]
                );
                sprintf(
                        sizeOfSharedMemoryForCurrentParameter,
                        "%d",
                        sizeOfSharedMemorySegment[ i ]
                );

                makeDummy = concatenate(
                        5,
                        sizeof( keyOfSharedMemoryForCurrentParameter ),
                        keyOfSharedMemoryForCurrentParameter,
                        sizeof( "" ),
                        " ",
                        sizeof( sizeOfSharedMemoryForCurrentParameter ),
                        sizeOfSharedMemoryForCurrentParameter,
                        sizeof( "" ),
                        " ",
                        sizeof( cDataSplittingPatternForChosenVariant ),
                        cDataSplittingPatternForChosenVariant

                );

                strcat( myDummy, makeDummy );
            }

            printf("\n------\n");
            for( k = 0; k < 200; k++ )
            {
                printf("%c", myDummy[ k ] );
            }
            printf("\n------");



			printf("\n9.05 Attach parameters to the make command\n");

			char parameterList[100][100];


			va_end(valist);

            printf("\nscheduler | use concatenate to prepare shell command\n");

            for(j=0;j<120;j++){
                printf("%c",make[j]);
            }

			pipe=popen(myDummy,"w");
			close(pipe);

		}

		while(fopen("wait.dummy","r")==NULL){
			//Wait, until test procedure is done with testing of the according variant
		}
		
		//printf("\n 16. scheduler starts sleeping\n");
		while(s3[0]!=numvariants){
        	sleep(1);
		}
		//printf("\n 17. All variants are done\n");
		
		printf("\nscheduler | 18. Calculcating Result:");
		
		for(i=1;i<numvariants+1;i++){		//1, because 0 is for communication with scheduler
			result=result+s3[i];
		}
		printf("\nscheduler | 19. Result: %lf\n",result);
		
		
		
		
		
	}//end if(numvariants==all there)
	//printf("\nscheduler | 20. Remove all shared memory");
	pipe=popen("chmod +x kill_ipcs.sh && ./kill_ipcs.sh","w");
	close(pipe);

//

	
	//return result;
	

}
