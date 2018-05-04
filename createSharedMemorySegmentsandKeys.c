#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int *createSharedMemorySegmentsandKeys( int size, char *type, ... ) {

    printf("createSharedMemorySegmentandKeys | Size: %d, Type: %s", size, type);

    srand( time( NULL ) );   // should only be called once
    int randomKey = rand(), i;
    key_t key = randomKey;
    printf("\ncreateSharedMemorySegmentandKeys | Randomly generated key: %d\n", randomKey);

    int *sharedMemoryKeyAndSize = {
            randomKey,
            size
    };

    int shmid;
    double *shm;

    if ((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if( type == "double" ) {
        double *shm;
        printf("createSharedMemorySegmentandKeys | Create shared memory segment for a double hybchive specific argument");
        if ((shm = shmat(shmid, NULL, 0)) == (double *) -1) {
            perror("shmat");
            exit(1);
        }

        printf("\ncreateSharedMemorySegmentandKeys | Copy input to shared memory segment\n");
        va_list valist;
        va_start( valist, 1 );
        memcpy(shm, va_arg(valist, double * ), size);
        va_end(valist);

        /*
        for ( i = 0; i < size; i++) {
            printf("%f", shm[i]);
        }*/

    }

    return sharedMemoryKeyAndSize;




}