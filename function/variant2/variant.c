#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]){
	printf("\nExecuting variant 2\n");
	
		printf("\n 10 Check, if input has arrived\n");
	
	/* Conversion string into int */
	int begin,end,ikey,n,variantid,numvariants;
    ikey = atoi(argv[1]);
    begin = atoi(argv[2]);
    end = atoi(argv[3]);
    n = atoi(argv[4]);
    variantid = atoi(argv[5]);
    numvariants = atoi(argv[6]);
    int ikey3 = atoi(argv[7]);
    
    printf("\n 10.1 key: %d, begin: %d, end: %d, n: %d\n",ikey,begin,end,n);
    
    printf("\n 11. Attach shared memory space\n");
    int shmid;
    key_t key;
    double *shm, *s;
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
    if ((shm = shmat(shmid, NULL, 0)) == (double *) -1) {
    perror("shmat");
    exit(1);
    }
    
    printf("\n 12. Check shared memory: %lf\n",shm[0]);
    
    printf("\n 13. Begin of the algorithm\n");
        //printf("\n Divide each member 100 times by 1.1\n");
    int i,j;
    for(i=0;i<10000;i++){
        for(j=begin;j<end;j++){
            shm[j]=shm[j]/1.1;
        }
    }
     
    //printf("\n Sum up the entries of the vector\n");
    double result=0;
    for(j=begin;j<end;j++){
        result+=shm[j];
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
