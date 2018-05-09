#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int *createSharedMemorySegmentsandKeys( int size, char *type, ... ) {

    printf("\ncreateSharedMemorySegmentandKeys | Size: %d, Type: %s", size, type);

    int randomKey = rand(), i;
    key_t key = randomKey;
    printf("\ncreateSharedMemorySegmentandKeys | Randomly generated key: %d\n", randomKey);

    int *sharedMemoryKeyAndSize = {
            randomKey
    };

    int shmid;

    if ((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if( type == "double" ) {
        double *shm;
        shm = ( double * ) malloc( sizeof( double ) * size );
        if(shm == NULL)
        {
            printf("Error! memory not allocated.");
            exit(0);
        }

        printf("createSharedMemorySegmentandKeys | Create shared memory segment for a double hybchive specific argument");
        if ((shm = shmat(shmid, NULL, 0)) == (double *) -1) {
            perror("shmat");
            exit(1);
        }

        printf("\ncreateSharedMemorySegmentandKeys | Copy input to shared memory segment\n");
        va_list valist;
        va_start( valist, 1 );
        printf("\ncreateSharedMemorySegmentandKeys | here is the next bug \n");

        double *input;
        input = ( double * ) malloc( sizeof( double ) * size );

        memcpy(shm, input, size);

        free( input );
        va_end(valist);

    }

    return sharedMemoryKeyAndSize;




}