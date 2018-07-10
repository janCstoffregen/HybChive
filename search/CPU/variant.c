#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <math.h>
#include "../../hybchive.h"




int main(int argc, char *argv[]){
	/* Conversion string into int */
	int		begin,
			end,
			ikey,
			ikey3,
			n,
			variantid,
			variantId,
			numberOfParameters,
			sharedMemoryCommuncation,
			sharedMemoryKey,
			sharedMemorySize,
			dataSliceForThisVariant,
			problemSize,
			numvariants;

	variantId = atoi(
            argv[ 1 ]
    );

    numberOfParameters = atoi(
            argv[ 2 ]
    );

    sharedMemoryCommuncation = atoi(
            argv[ 3 ]
    );

    numvariants = atoi(
            argv[ 4 ]
    );

    sharedMemoryKey = atoi(
            argv[ 5 ]
    );

    sharedMemorySize = atoi(
            argv[ 6 ]
    );

    dataSliceForThisVariant = atoi(
            argv[ 7 ]
    );

    printf("\nvariant %d | Hello, I have %d input(s).\n",
       variantId,
       numberOfParameters
       );

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

    printf("\nvariant %d | dataSlice %d\n",
           variantId,
           dataSliceForThisVariant
    );

    /**
     * The following statement is problem specific.
     * In a general way, the problem size has to be generated out of the shared memory size,
     * since the problem size is an implementation specific term.
     * */
    problemSize = sharedMemorySize / 8;

    printf("\nvariant %d | problem size %d\n",
           variantId,
           problemSize
    );

    /**
     * The following generation of the slice for this variant is HybChive - set specific /
     * optimisation - specific and has to be performed in every variant.
     * */

    printf("\nvariant %d | number of variants: %d\n",
           variantId,
           numvariants
    );

    begin = problemSize / numvariants * variantId;
    end = begin + dataSliceForThisVariant;

    printf("\nvariant %d | begin: %d, end: %d\n, ",
           variantId,
           begin,
           end
    );



    printf("\nvariant %d | Begin of the algorithm\n");

	printf("\nvariant %d | Search for zero - gravity spot in space\n");

	int i, j;
    for ( i = begin; i < end; i++ )
    {
	    printf(" i: %d, j: %d, input: %.54lf\n", i, j, inputArgumentOne[ i ]);
	    for (j = i; j < end; j++ )
	    {
		    inputArgumentOne[ i ] += inputArgumentOne[ j ] / ( j - i + 1 ) ;
 	    }
    }

    printf("\nvariant %d | End of the algorithm\n");


    sharedMemoryCommunicationPointer[ 0 ] += 1;

    printf("\nvariant %d | sharedMemoryCommuncationContent before finish: %f\n",
           variantId,
           sharedMemoryCommunicationPointer[ 0 ]
    );

    return 0;
}