/*
gcc -c scheduler.c -lrt
gcc -c user.c
gcc -o user user.o scheduler.o -lrt
./user
*/

#include<stdlib.h>
#include<stdio.h>
#include"hybchive.h"

int main(){
    
    //create input data
    int n=100; // 1000000 is biggest possible input.
    double A[n*n];
    double result=0;
    int i;
    printf("\n Create input data\n");
    for(i=0;i<n*n;i++){
        A[i]=0;
    } 
    A[9*n+9]=1234;
    
    //define HybChive parameters:
    //1. Define name of the HybChive routine that you want to call
    char set[]="function";
    char variants[]="all";
    char optimize[]="performance";
    //2. define number of parameters AFTER the "numberOfParameters-1" input paramter 
    //of the Hybchive routine:
    int numberOfParameters = 1;
    //3. Parameter for the search algorithm: Define the entry that you'd like to search for:
    int parameterOne=1234;

    //4. Execute the hybchive routine:

    if(fopen("hybchive.log","r")!=NULL){

        FILE *pipe;
        pipe=popen("rm hybchive.log","w");
        close(pipe);

        while(fopen(hybchive.log,"r")!=NULL){
            //wait, until log file has been removed
        }

    }



    hybchiveLog( "user | execute HybChive Function" );

    hybchive(
	set,
	variants,
	optimize,
	numberOfParameters-1,
	n*n,
	A,
	parameterOne);

    hybchiveLog( "user | end HybChive Function" );
    

    printf("\nuser | 0.3 Result in program of user: Found in A[%d][%d]\n",((int) result)/n,((int)result) % n);

    printf("\n next: order hybchive log");


}
