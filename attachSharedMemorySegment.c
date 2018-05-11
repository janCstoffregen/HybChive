#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


double *attachSharedMemorySegment( int key ) {

    printf( "attachSharedMemorySegment | for key: %d", key );
    double *output = { 0 };

    return output;
}