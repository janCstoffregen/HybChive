// gcc sequentiell.c -o sequentiell -lrt
 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

double *secondsarray, *nsecondsarray;

// marks the current time and saves it in an array
void mytime(int timemark) {
    struct  timespec currenttime;
    //dynamic memory allocation
    if(timemark==1){
        secondsarray=malloc(sizeof(double));
        nsecondsarray=malloc(sizeof(double));
    }
    else{
        secondsarray=(double *)realloc(secondsarray,sizeof(double)*timemark);
        nsecondsarray=(double *)realloc(nsecondsarray,sizeof(double)*timemark);
    }
    clock_gettime(CLOCK_REALTIME, &currenttime);
    secondsarray[timemark-1]=currenttime.tv_sec;
    nsecondsarray[timemark-1]=currenttime.tv_nsec;
}

// gets the time difference of two times marked in the function mytime
double timediff(int time2, int time1)
{   double time;
    if ((nsecondsarray[time2-1]-nsecondsarray[time1-1])<0) {
        time = secondsarray[time2-1]-secondsarray[time1-1];
        time=time+(1000000000+nsecondsarray[time2-1]-nsecondsarray[time1-1])/1000000000;
    } else {
        time=secondsarray[time2-1]-secondsarray[time1-1];
        time=time+(nsecondsarray[time2-1]-nsecondsarray[time1-1])/1000000000;
    }
    return time;
}
 
int main(){
    printf("\n Executing real test procedure variant 1\n");

    int nfinal=900000;
    double A[nfinal];
    int i,j,n;
    FILE *pipe;
    pipe=fopen("performance.txt","w");
    for(n=0;n<=nfinal;n=n+100000){
            
        
        mytime(1);
        printf("\n Start calculating\n");
     
    

        for(i=0;i<n;i++){
            A[i]=1;
        }
         
        for(i=0;i<100000;i++){
            for(j=0;j<n;j++){
                A[j]=A[j]/1.1;
            }
        }
     
        double result=0;
        for(j=0;j<n;j++){
            result+=A[j];
        }
         
        //printf("\n Result: %lf\n",result);
        mytime(2);
     
        //printf("\n print in performance.txt\n");
        //printf("%d %f \n",n,timediff(2,1));
        fprintf (pipe, "%d %f \n", n, timediff(2,1));
    }
    close(pipe);
    pipe=popen("echo '' > wait.txt","w");
    close(pipe);
}
