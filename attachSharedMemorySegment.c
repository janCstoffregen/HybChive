#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


double *attachSharedMemorySegment( int key, int size, int variantId ) {

    printf( "attachSharedMemorySegment | ( variant %d ) | for key: %d and size: %d", variantId, key, size );

    int shmid;
    double *shm, *s;

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

    return shm;
}