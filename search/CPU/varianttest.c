#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>




int main(int argc, char *argv[]){

    //printf("\nExecute varianttest.\n");
    FILE *pipe;
    pipe=fopen("performance.txt","w");
    
    //Place the code to be tested here, measure the time for 
    //each constellatio of parameters and write 
    //it in the file "performance.txt".
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    int n;
    for (n=1;n<=1100;n+=50){
        //printf("%d",n);
        
        double *secondsarray, *nsecondsarray;
        double time;
        // marks the current time and saves it in an array
        void mytime(int timemark){
        struct 	timespec currenttime;
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
        {	if ((nsecondsarray[time2-1]-nsecondsarray[time1-1])<0) {
                time=secondsarray[time2-1]-secondsarray[time1-1];
                time=time+(1000000000+nsecondsarray[time2-1]-nsecondsarray[time1-1])/1000000000;
            } else {
                time=secondsarray[time2-1]-secondsarray[time1-1];
                time=time+(nsecondsarray[time2-1]-nsecondsarray[time1-1])/1000000000;
            }
            return time;
        }
        
        int i, j, err;
 
        
        //Input data
        double A[n*n];
        for(i=0;i<n*n;i++){
            A[i]=0;
        }
        A[(n-1)*n+(n-1)]=1234;
        
        mytime(1);
        
        
        //Hide test result in input data
        

        //Main search procedure:
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if (A[i*n+j]==1234){
                    //printf("\nData found in A[%d][%d]\n",i,j);
                    i=n;
                    j=n;
                }
            }
        }
      
        //end of your algorithm
        mytime(2);

        
        //////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////
        fprintf (pipe, "%d %f \n", n, timediff(2,1));
       
    }
    close(pipe);
    
    //printf("\nWait a little bit.\n");
    //unsigned int retTime = time(0) + 3;
    //while (time(0) < retTime);
    
    pipe=popen("echo '' > wait.txt","w");
    close(pipe);
    
}