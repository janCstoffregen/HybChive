/*
gcc -c scheduler.c -lrt
gcc -c user.c
gcc -o user user.o scheduler.o
./user
*/

#include<stdlib.h>
#include<stdio.h>
#include"pps.h"

int main(){
    printf("\n 0. User executes function call\n");
    int n=1000000; // 1000000 is biggest possible input.
    double A[n];
    int i;
    for(i=0;i<n;i++){
        A[i]=1;
    }
    char algorithm[]="function";
    double result;
    printf("\n 0.1,5 vor der Schleife\n");
    for(n=800000;n<=900000;n=n+20000){
        printf("\n 0.2 fuehrt function aus mit n = %d\n",n);
        result=pps(A,n,algorithm);
    }
    
    printf("\n 0.3 Result in program of user: %lf\n",result);
    
    
}