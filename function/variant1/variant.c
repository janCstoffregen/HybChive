#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdarg.h>
#include "../../hybchive.h"

int main(
        int argc,
        char *argv[])
{


    /* Conversion string into int */
    int
            sharedMemoryKey,
            sharedMemorySize,
            variantId,
            numvariants,
            numberOfParameters,
            maxPossibleInputsForThisVariant = 10,
            problemSize;

    variantId = atoi(
            argv[ 1 ]
    );

    numberOfParameters = atoi(
            argv[ 2 ]
    );

    sharedMemoryKey = atoi(
            argv[ 3 ]
    );

    sharedMemorySize = atoi(
            argv[ 4 ]
    );

    printf("\nvariant %d | Hello, I have %d input(s):",
           variantId,
           numberOfParameters);

    printf("\nvariant %d | I will show you the first input, in a set you design you should know how many inputs you need.\n",
           variantId
    );

    double *inputArgumentOne;
    inputArgumentOne = attachSharedMemorySegment( sharedMemoryKey, sharedMemorySize, variantId );

    printf("\nvariant %d | to finalize: printf part of the input!\n",
           variantId
    );

    printf("variant %d | A[ 0 ]: %f\n",
           variantId,
           inputArgumentOne[ 0 ]
    );



//    ikey = atoi(argv[1]);
//    begin = atoi(argv[2]);
//    end = atoi(argv[3]);
//    n = atoi(argv[4]);
//    variantid = atoi(argv[5]);
//    numvariants = atoi(argv[6]);
// int ikey3 = atoi(argv[7]);

//    printf("\nvariant | 10.1 key: %d, begin: %d, end: %d, n: %d",ikey,begin,end,n);
//
//    //printf("\n 11. Attach shared memory space\n");
//    int shmid;
//    key_t key;
//    double *shm, *s;
//    int size=sizeof(double)*n;
//
//    key=ikey;
//
//    /*
//    * Locate the segment.
//    */
//    if ((shmid = shmget(key, size, 0666)) < 0) {
//        perror("shmget");
//        exit(1);
//    }
//
//    /*
//    * Now we attach the segment to our data space.
//    */
//    if ((shm = shmat(shmid, NULL, 0)) == (double *) -1) {
//        perror("shmat");
//        exit(1);
//    }
//
//    printf("\nvariant | 12. Check shared memory: %lf",shm[0]);
//
//    printf("\nvariant | 13. Begin of the algorithm");
//    //printf("\n Divide each member 100 times by 1.1\n");
//    int i,j;
//    for(i=0;i<10000;i++){
//        for(j=begin;j<end;j++){
//            shm[j]=shm[j]/1.1;
//        }
//    }
//
//    //printf("\n Sum up the entries of the vector\n");
//    double result=0;
//    for(j=begin;j<end;j++){
//        result+=shm[j];
//    }
//    printf("\nvariant | Result (begin: %d, end: %d) : %.5lf",begin,end,result);

//    printf("\nvariant | 15. Write result in shared memory");
//    int shmid2;
//    key_t key2;
//    double *shm2, *s2;
//    int size2=sizeof(double)*numvariants+1;
//
//    key2=ikey3;
//
//    /*
//    * Locate the segment.
//    */
//    if ((shmid2 = shmget(key2, size2, 0666)) < 0) {
//        perror("shmget");
//        exit(1);
//    }
//
//    /*
//    * Now we attach the segment to our data space.
//    */
//    if ((shm2 = shmat(shmid2, NULL, 0)) == (double *) -1) {
//        perror("shmat");
//        exit(1);
//    }

//    shm2[variantid+1]=result;
//    shm2[0]=shm2[0]+1;
//
//    printf("\nvariant | 13.1 End of the algorithm");

}
