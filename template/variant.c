#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <math.h>




int main(int argc, char *argv[]){
    
	printf("\n 10 Check, if input has arrived\n");
	
	/* Conversion string into int */
	int begin,end,ikey,n,variantid,numvariants;
    ikey = atoi(argv[1]);
    begin = atoi(argv[2]);
    end = atoi(argv[3]);
    n = atoi(argv[4]);

    n = (double) n;
    n=sqrt(n);
    n = (int) n;

    variantid = atoi(argv[5]);
    numvariants = atoi(argv[6]);
    int ikey3 = atoi(argv[7]);
    double parameterOne[1];
    parameterOne[0] = atof(argv[8]);
    
    printf("\n 10.1 key: %d, begin: %d, end: %d, n: %d, parameterOne: %d\n",ikey,begin,end,n,parameterOne[0]);

    printf("\n 11. Attach shared memory space\n");
    int shmid;
    key_t key;
    double *A_host, *s;
    int size=sizeof(double)*n;
    
    key=ikey;

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
    if ((A_host = shmat(shmid, NULL, 0)) == (double *) -1) {
    perror("shmat");
    exit(1);
    }
    
    printf("\n 12. Check shared memory: %lf\n",A_host[0]);
    
    printf("\n 13. Begin of the algorithm\n");
    double result=0; //dummy result, this double variable needs to be used for the ouput.

    
    int searchResult_host[1];
    
    int i, j;
    searchResult_host[0]=-1;
    //Put your algorithm here!!
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if ( A_host[i*n+j] == parameterOne[0]){
                    printf("\nData found in A[%d][%d]\n",i,j);
                    searchResult_host[0] = i*n+j;
                    i=n;
                    j=n;
                }
            }
        }
    
    
    //End of your algorithm!!

    if(searchResult_host[0]!=-1){
        result  = searchResult_host[0] + begin;
    }
    printf("\n Result (begin: %d, end: %d) : %.5lf\n",begin,end,result);

    printf("\n 15. Write result in shared memory\n");
    int shmid2;
    key_t key2;
    double *shm2, *s2;
    int size2=sizeof(double)*numvariants+1;
    
    key2=ikey3; //spaeter als input, hab ich gerade keine lust zu

    /*
    * Locate the segment.
    */
    if ((shmid2 = shmget(key2, size2, 0666)) < 0) {
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
    
    shm2[variantid+1]=result;
    shm2[0]=shm2[0]+1;

    printf("\n 13.1 End of the algorithm\n");

    
    
    
}