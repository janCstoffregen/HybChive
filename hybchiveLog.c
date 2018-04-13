#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void hybchiveLog(char *note) {
    struct  timespec currenttime;
    clock_gettime(CLOCK_REALTIME, &currenttime);
    double seconds = currenttime.tv_sec;
    double nanoseconds = currenttime.tv_nsec;
    FILE *pipe;
    pipe=fopen("hybchive.log","a");
    fprintf (pipe, "%f, %s\n", seconds + nanoseconds / 1000000000, note);
    close(pipe);
    printf("%f, %s\n", seconds + nanoseconds / 1000000000, note);
}
