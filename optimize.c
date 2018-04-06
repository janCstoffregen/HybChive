//die performance files einlesen in einen array - done
//ich mache einfach einen pseudo - optimierungsalgorithmus und weise jeder variante die gleiche inputgroesse zu - done
//outputs sind die inputsgroessen, ueber shared memory. shared memory wird im scheduler erstellt und vom optimizer befuellt - done
//outputs werden vom scheduler anschließend ausgelesen. - done


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

main(int argc, char *argv[]){
	
	//n;
	int n=atoi(argv[1]);
	char *function = argv[2];
	
	//printf("\n 5.-1 Function arrived in optimize.c: %s \n",function);
	
    //printf("\n 5. Starting Optimizing procedure\n");
    FILE *pipe;
    
    printf("\n 6. Reading performance files\n");
    //printf("\n 6.1 Merging function name and variants to cd to directories like in scheduler\n");
    // later function - name as input of the optimize - program
    //char function[]="function";
    char pipecommand[2000] = "";
	char cd[]="cd ";
	strcat(pipecommand,cd);
	strcat(pipecommand,function);
	char savedir[]=" && ls -d */ | cut -f1 -d'/' > list.txt && cp list.txt 2.txt";	
	strcat(pipecommand,savedir);
	pipe=popen(pipecommand,"w");
	close(pipe);
    //printf("\n3. Read the list.txt file in an array\n");
    

    
	int numvariants=10;
	int characters=30;
	int i,j,k;
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
			printf("\ndistance: %d\n",distance);
		}
	}	
	numvariants=help;
	char newPipecommand[1000] = "";
	memset(newPipecommand,'\0',sizeof(newPipecommand));
	strcat(newPipecommand,"cd ");
	strcat(newPipecommand,function);
	strcat(newPipecommand," && rm list.txt && rm 2.txt");
	pipe=popen(newPipecommand,"w");
	close(pipe);
	char performancedata[]="performance.txt";
	int l;
	FILE *pipe2;
	int checkallperformance=0;
	memset(pipecommand,'\0',sizeof(pipecommand));
	
	float performancedatatable[numvariants][1000][2]; // derzeit angenommen: nicht mehr als 1000 performance.txt zeilen und nur 2 variablen.
	for (i=0;i<numvariants;i++){
		for (j=0;j<1000;j++){
			for(k=0;k<2;k++){
				performancedatatable[i][j][k]=-1;
			}
		}
	}
	int largestPossibleInput[numvariants];
	for(i=0;i<numvariants;i++){
		memset(pipecommand,'\0',sizeof(pipecommand));
		printf("\n a Check pipecommand, i=%d\n",i);
		for(j=0;j<40;j++){
			printf("%c",pipecommand[j]);
		}
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
		
		printf("\n 6.2 reading performance files for variant %d\n",i);
		//printf("\n Check pipecommand, i=%d\n",i);
		for(j=0;j<40;j++){
			printf("%c",pipecommand[j]);
		}
		int variables=2; 		//wird spaeter automatisch aus den files abgelesen
		
		//float performancedatatable[numvariants][variables];
		int ch, number_of_lines = 0;

		pipe=fopen(pipecommand,"r");
			//anzahl der Zeilen in dem Performance - File herausfinden
			do{
    			ch = fgetc(pipe);
    			if(ch == '\n')
    			number_of_lines++;
			} while (ch != EOF);

		

			// last line doesn't end with a new line!
			// but there has to be a line at least before the last line
			/*if(ch != '\n' && number_of_lines != 0){ 
    			number_of_lines++;
			}*/
		fclose(pipe);
		pipe=fopen(pipecommand,"r");
			float performancehelp[variables];
			//printf("\nnumber of lines with performance data in performance.txt = %d\n", number_of_lines);
			
			
			
			for(j=0;j<=number_of_lines;j++){
				fscanf(pipe,"%f %f", &performancehelp[0], &performancehelp[1]);
				//printf("\nPerformancehelp: %f, %f\n",performancehelp[0], performancehelp[1]);
				performancedatatable[i][j][0]=performancehelp[0];
				performancedatatable[i][j][1]=performancehelp[1];
			}
			
			largestPossibleInput[i]=performancedatatable[i][number_of_lines][0];
			
			//printf("\n 6.3 Largest possible input for variant %d: n= %d\n",i,largestPossibleInput[i]);
			
			
			
			//printf ("\n 6.3.1 Size of input data: n*n = %d\n",n);
			
			/*printf("\n 6.2.1 Check, if Performancedata arrived for variant %d\n",i);
			for(j=0;j<number_of_lines;j++){
				printf("%f  %f", performancedatatable[j][0], performancedatatable[j][1]);
				printf("\n");
			}*/
			
		
		fclose(pipe);

	}

	printf("\n 7. Run Optimizing Algorithm\n");
	//n spaeter als input, jetzt ersteinmal vorgegeben.
	
	int largestPossibleInputSum = 0;
	
	for (i=0;i<numvariants;i++){
		largestPossibleInputSum += largestPossibleInput[i] * largestPossibleInput[i];
	}
	
	printf("\n 7.0.1 Largest possible input for given problem and sum of devices: %d\n",largestPossibleInputSum);
	
	int splittable[numvariants];
	//int splithelp[numvariants];
	int total=0;
	
	int numberOfDevicesWhereStorageIsNotBigEnough = 0;
	
	int inputLeftToAssign = n;
	
	int checkSplitability[numvariants];
	
	int whichOptimisingAlgorithm = 0;
	
	for(i=0;i<numvariants;i++){
		checkSplitability[i]=0;
	}

	printf("next: it does not work if performance.txt already exists.");
	if(n>largestPossibleInputSum){
		printf("\n 7.0.2 Problem too big for given devices, no tiling possible yet. Will be implemented in the next step. Please abort program\n");
		exit(1);
	}
	else{
		printf("\n 7.0.3 Check, if data can be split evenly\n");

		for(i=0;i<numvariants;i++){
			if(n>largestPossibleInput[i]*largestPossibleInput[i]){
				printf("\n 7.0.4 Input too big for device %i\n",i);
				checkSplitability[i]=-1;
			}
			
		}

		for(i=0;i<numvariants;i++){
			if(checkSplitability[i]==-1){
				whichOptimisingAlgorithm=1;
			}			
		}

		if(whichOptimisingAlgorithm==0){
			printf("\n 7.0.5 Data evenly splitable\n");
			for(i=0;i<numvariants-1;i++){
				splittable[i]=n/numvariants;
				total+=n/numvariants;
			}
			splittable[numvariants-1]=n-total;
		}
		else{
			//printf("\n 7.0.6 Data not evenly splitable\n");
			//printf("\n 7.0.7 Assign small devices largest possible input and split the rest\n");
			for(i=0;i<numvariants;i++){
				if(checkSplitability[i]==-1){
                        splittable[i] = largestPossibleInput[i] * largestPossibleInput[i];
                        inputLeftToAssign = inputLeftToAssign - splittable[i]; 
                        if(inputLeftToAssign < 0){
                            splittable[i] += inputLeftToAssign;
                            i = numvariants;
                            inputLeftToAssign = 0;
                        }
                        else{
					   numberOfDevicesWhereStorageIsNotBigEnough += 1;
                        }
                }
			}
			for(i=0;i<numvariants;i++){
				if(checkSplitability[i]!=-1){
					splittable[i]=inputLeftToAssign/(numvariants-numberOfDevicesWhereStorageIsNotBigEnough);
				}
			}
		}
		
	
		for(i=0;i<numvariants;i++){
				//printf("\n 7.1 Aufteilung Devices %d: %d\n",i,splittable[i]);
		}


	}
	
	
	
	

	
	printf("\n 7.2 Create shared memory space for input.\n");
	  /*
    * We'll name our shared memory segment
    * "5678".
    */

 	int shmid;
    key_t key;
    int *shm, *s;
    key = 5678;
    int size=sizeof(int)*n;
 
    /*
    * Create the segment.
    */
    if ((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0) {
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
 
    /*
    * Now put some things into the memory for the
    * other process to read.
    */
    
	printf("\n 7.3 Put splittable in shared memory space\n");
	s=shm;
	
	int c;
	for(c=0;c<numvariants;c++){
		s[c]=splittable[c];
	}

    //show scheduler that optimizing procedure has finished
    pipe=popen("echo '' > wait.txt","w");
    close(pipe);
    
}