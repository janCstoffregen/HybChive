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
char variantslist[20][40]={};
char variants[100]="";
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



void hybchive(
        char *hybChiveSetName,
        char *chosenVariants,
        char *optimize,
        int numberOfParameters,
        ...)
{

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
    // printf("\n3.0.1 Number of Variants: %d \n ", numvariants);
    for( i = 0; i < numvariants * characters; i++ )
    {
        fscanf(
                pipe,
                "%c",
                &variants[i]
        );
    }
	fclose(pipe);

	printf("\n3.1 show, that the devices - array got everything \n");
	printf("\n");
	for( i = 0; i < sizeof(variants); i++ )
    {
		printf(
                "%c",
                variants[ i ]
        );
	}


	printf("\n3.2 transfer devices to array - Something is going wrong here\n");

      i = 0;

	for( j = 0; j < 50; j++ )
    {
		if( variants[ j ] != '\n' )
        {
			variantslist[ i ][ j - distance ] = variants[ j ];
		} else {
			i = i + 1;
			distance = j + 1;
			help = help + 1;
			//printf("\ndistance: %d\n",distance);
		}
	}
	numvariants = help;
	printf("\n3.2.1 Numvariant: %d\n", numvariants);
	for( i = 0; i < numvariants; i++ )
    {
		for( j = 0; j < 30; j++ )
        {
				printf("%c",
                       variantslist[ i ][ j ]
                );
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
            , "w"
    );
	close( pipe );

	/*end part one*/

	printf("\n 3.2.1.1 nVariantslist: \n", numvariants);
	for( i = 0; i < numvariants; i++ )
    {
		for( j = 0; j < 30; j++ )
        {
				printf("%c",
                       variantslist[ i ][ j ]
                );
		}
		printf("\n");
	}

	/*begin part two*/


	for( i = 0; i < numvariants; i++)
    {

        memset(
                currentdir,
                '\0',
                sizeof(currentdir)
        );
		memset(
                pipecommand,
                '\0',
                sizeof(pipecommand)
        );
        memset(
                variants,
                '\0',
                sizeof(variants)
        );

		printf("\n 3.2.1.1 Check pipecommand - should be empty, i=%d\n",
               i
        );
		for( j = 0; j < 40; j++ )
        {
			printf("%c",
                   pipecommand[ j ]
            );
		}

		for( k = 0; k < 20; k++ )
        {
			if( variantslist[ i ][ k ] != '\0' )
            {
				variants[k]=variantslist[i][k];
			}
		}

		memset(
                currentdir,
                '\0',
                sizeof(currentdir)
        );
		strcat( currentdir, hybChiveSetName );
		strcat( currentdir, "/" );
        strcat( currentdir, variantslist[ i ] );
        printf("\nCurrentdir - here is the bug: \n");
        for( j = 0; j < 40; j++ )
        {
			printf("%c",
                   currentdir[ j ]
            );
		}



        if(
                fopen(
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
                , "r" )==NULL)
        {
            hybchiveLog( "scheduler | No performance data found for" );
			printf("\n ");
			for( j = 0; j < 30; j++ )
            {
				printf("%c",
                       variantslist[ i ][ j ]
                );
			}



			printf("\n");
			printf("\nscheduler | 4.3 Execute test \n");
			memset(
                    make,
                    '\0',
                    sizeof(make)
            );

			strcat(
                    make,
                    "cd "
            );
            int length = strlen( currentdir );
            if ( currentdir[ length - 1 ] == '\n' )
            {
                printf("remove newline");
                currentdir[ length - 1 ]  = '\0';
            }
            strcat( make, currentdir );

			strcat( make, " && make test && ./varianttest" );

			printf("\n 4.3.1 Check pipecommand - should be set name and variant name, i=%d\n",i);
			for( j = 0; j < 70; j++ )
            {
				printf("%c",
                       currentdir[ j ]
                );
			}
            printf("\nCurrentdir not working!");


			pipe=popen(
                    make,
                    "w"
            );
			close( pipe );
			memset(
                    Wait,
                   '\0',
                   sizeof(Wait)
            );
			strcat(
                    Wait,
                    currentdir
            );
			strcat( Wait, "/" );
			strcat( Wait, "Wait.txt" );
			while( fopen( Wait, "r" ) == NULL )
            {
				//Wait, until test procedure is done with testing of the according variant
			}
            hybchiveLog( "scheduler | End execute varianttest" );
			memset(
                    Wait,
                    '\0',
                    sizeof(Wait)
            );
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
    double *inputArgumentOne;
    double *argument;
    int sizeOfSharedMemorySegment[ 20 ] = { 0 };
	if( checkallperformance == numvariants ) {
        hybchiveLog( "scheduler | 4.4 All performance files found. Execute performance optimizing procedure" );

        /*
         * This function will create a shared memory segment for each HybChive specific argument
         * It returns a model where
         * int sharedMemoryKeys[ i ] is the shared memory key for the ith hybchive specific argument.
         * */

        va_list valist;
        va_start(valist, numberOfParameters);
        char *type="";
        int sharedMemoryKeyArray[ 20 ] = { 0 };
        int *sharedMemoryKey = { 0 };
        hybchiveLog( "scheduler | 4.5 Start copying HybChive - set specific parameters to shared memory segment" );
        for ( i = 0; i < numberOfParameters; i++) {
            sizeOfSharedMemorySegment[ i ] = va_arg(valist, int );
            type = va_arg(valist, char * );

            if( type == "double" ) {
                argument = va_arg(valist, double * );
                sharedMemoryKey = createSharedMemorySegmentsandKeys(
                        sizeOfSharedMemorySegment[ i ],
                        type,
                        argument );
                sharedMemoryKeyArray[ i ] = &sharedMemoryKey[ 0 ];

                // the following statement is only to check if the user gets the changes in the end!

                inputArgumentOne = attachSharedMemorySegment(
                        sharedMemoryKeyArray[ i ],
                        sizeOfSharedMemorySegment[ i ],
                        1234 );

            }
            // printf("key: %d, size: %d", sharedMemoryKeyArray[ i ], sizeOfSharedMemorySegment[ i ] );
        }
        va_end(valist);
        hybchiveLog( "scheduler | 4.5.1 End copying HybChive - set specific parameters to shared memory segment" );

        int n;
        if( numberOfParameters > 1 )
        {
            printf("\n scheduler | Please implement optimise procedure for more than one parameter and abort this program");
            while(fopen("Wait.dummy","r")==NULL){
                //Wait, until test procedure is done with testing of the according variant
            }
        } else {

            n = sizeOfSharedMemorySegment[ 0 ] / 8;
        }


        printf("\nscheduler | size of double: %d\n", n );

        char cn2[100];
		memset(cn2,'\0',sizeof(cn2));
		sprintf(cn2,"%d",n);

        char csize2[100];
        memset(
                csize2,
                '\0',
                sizeof( csize2 )
        );
        sprintf(
                csize2,
                "%d",
                sizeOfSharedMemorySegment[ 0 ]
        );



		pipe=popen(
                concatenate(
                        7,
                        sizeof( "gcc optimize.c -o optimize hybchiveLog.o -lrt && ./optimize" ),
                        "gcc optimize.c -o optimize hybchiveLog.o -lrt && ./optimize",
                        sizeof( " " ),
                        " ",
                        sizeof( cn2 ),
                        cn2,
                        sizeof( " " ),
                        " ",
                        sizeof( hybChiveSetName ),
                        hybChiveSetName,
                        sizeof( " " ),
                        " ",
                        sizeof( csize2 ),
                        csize2
                )
                ,"w");
		close( pipe );

		while( fopen( "Wait.txt", "r" ) == NULL )
        {
			//Wait, until test procedure is done with testing of the according variant
		}

		pipe = popen( "rm Wait.txt","w" );
		close( pipe );
        hybchiveLog( "scheduler | 7.4 Get the splitting information" );
		int shmid;
    	key_t key;
    	int *dataSplittingPattern, *s;
    	int size=sizeof( int ) * n;
	    key = 5678;

	    /*
	    * Locate the segment.
	    */
	    if ((shmid = shmget(key, numvariants, 0666)) < 0) {
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
		// printf("\nscheduler | 4.5 Optimizing Procedure has finished. Execute programs");
		int begin=0, end=0;



        // printf("\n 14. Create Shared memory for Variant communication segment\n");

        //The following type is double because I have not implemented shared memory segment for int yet.
        int *sharedCommunicationMemoryKey = {
                0
        };
        double communicationBetweenSchedulerAndVariants[
                1
        ];
        sharedCommunicationMemoryKey = createSharedMemorySegmentsandKeys(
                sizeof( communicationBetweenSchedulerAndVariants ),
                "double",
                communicationBetweenSchedulerAndVariants
        );

        double *sharedCommunication;
        sharedCommunication = attachSharedMemorySegment(
                &sharedCommunicationMemoryKey[ 0 ],
                sizeof( communicationBetweenSchedulerAndVariants ),
                1234
        );
        printf("\nscheduler | sharedCommunication[ 0 ]: %f ",
               sharedCommunication[ 0 ]
        );

        char cSharedMemoryForCommuncation[ 100 ] = "";
        memset(
                cSharedMemoryForCommuncation,
                '\0',
                sizeof(cSharedMemoryForCommuncation)
        );
        sprintf(
                cSharedMemoryForCommuncation,
                "%d",
                &sharedCommunicationMemoryKey[ 0 ]
        );
        printf("\n scheduler | sharedCommunicationKey: %c",
               cSharedMemoryForCommuncation[ 0 ]
        );




//        printf("\nscheduler | next: shared communcation key as input of variants\n");
//        while(fopen("Wait.dummy","r")==NULL) {
//            //Wait, until test procedure is done with testing of the according variant
//        }



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

			char ckey[100] = "";


			char cnumvariants[100] = "";


			sprintf(cnumvariants,"%d",numvariants);

			char make[1000]="";
            char *makeCommandWithoutInputs = malloc( sizeof(char) * ( 2000 ) );;
			memset(make,'\0',sizeof(make));

            char ci[100]="";
            sprintf(ci,"%d",i);

            char cNumberOfParameters[ 100 ] = "";
            sprintf(cNumberOfParameters, "%d", numberOfParameters);

            makeCommandWithoutInputs = concatenate(
                    13,
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
                    " ",
                    sizeof( cNumberOfParameters ),
                    cNumberOfParameters,
                    sizeof(" "),
                    " ",
                    sizeof( cSharedMemoryForCommuncation ),
                    cSharedMemoryForCommuncation,
                    sizeof(" "),
                    " ",
                    sizeof( cnumvariants ),
                    cnumvariants,
                    sizeof(" "),
                    " "

            );

            char *myDummy = malloc( sizeof(char) * ( 1000 ) );
            memset(myDummy,'\0',sizeof(myDummy));
            strcpy(myDummy, makeCommandWithoutInputs);

            // printf("\n-- Loop through Key, Size and data splitting pattern\n");

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
                        sharedMemoryKeyArray[ j ]
                );
                sprintf(
                        sizeOfSharedMemoryForCurrentParameter,
                        "%d",
                        sizeOfSharedMemorySegment[ j ]
                );

                makeDummy = concatenate(
                        5,
                        sizeof( keyOfSharedMemoryForCurrentParameter ),
                        keyOfSharedMemoryForCurrentParameter,
                        sizeof( " " ),
                        " ",
                        sizeof( sizeOfSharedMemoryForCurrentParameter ),
                        sizeOfSharedMemoryForCurrentParameter,
                        sizeof( " " ),
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

			char parameterList[100][100];


			va_end(valist);

            printf("\nscheduler | use concatenate to prepare shell command\n");

			pipe=popen(myDummy,"w");
			close(pipe);

		}
        hybchiveLog( "scheduler | 16.01 All variants started - adjust variant input" );
		printf("\nscheduler | 16. start sleeping\n");
		while(sharedCommunication[ 0 ] != numvariants )
        {
        	sleep(1);
		}
        hybchiveLog( "scheduler | 16.01 All variants ended" );
	}

    // Todo do this for every input variable
    hybchiveLog("scheduler | 17. copy shared memory segment back to input variable");
    printf("\nSize of argument: %d\n", sizeof(argument));
    printf("\nSize of inputArgumentOne: %d\n", sizeof(inputArgumentOne));
    printf("\nIndicated Size: %d\n", sizeof(argument));
    // memcpy(argument, inputArgumentOne, sizeOfSharedMemorySegment[ 0 ]);

	pipe=popen("chmod +x kill_ipcs.sh && ./kill_ipcs.sh","w");
	close(pipe);
}
