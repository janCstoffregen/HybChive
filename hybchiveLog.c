#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void hybchiveLog(char *note) {
    struct  timespec currenttime;
    clock_gettime(CLOCK_REALTIME, &currenttime);
    double seconds = currenttime.tv_sec;
    double nanoseconds = currenttime.tv_nsec;
    printf("%s, %f", note, seconds + nanoseconds / 1000000000);
}
