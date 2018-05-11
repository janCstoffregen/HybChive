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
            problemSize,
            sharedMemoryCommuncation;

    variantId = atoi(
            argv[ 1 ]
    );

    numberOfParameters = atoi(
            argv[ 2 ]
    );

    sharedMemoryCommuncation = atoi(
            argv[ 3 ]
    );

    sharedMemoryKey = atoi(
            argv[ 4 ]
    );

    sharedMemorySize = atoi(
            argv[ 5 ]
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

    printf("variant %d | sharedMemoryCommuncationKey: %d\n",
           variantId,
           sharedMemoryCommuncation
    );

    // TODO: size of this as input for variants
    double *sharedMemoryCommunicationPointer;
    sharedMemoryCommunicationPointer = attachSharedMemorySegment(
            sharedMemoryCommuncation,
            8,
            variantId
    );

    sharedMemoryCommunicationPointer[ 0 ] += 1;

    printf("\nvariant %d | sharedMemoryCommuncationContent before finish: %f\n",
           variantId,
           sharedMemoryCommunicationPointer[ 0 ]
    );

    printf("\nvariant %d | next: fix key and size input for the other variants\n", variantId);

    return 0;
}
