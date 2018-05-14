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

    printf("\n Create input data\n");
    int n=4;
    double A[ n * n ];
    double result=0;
    int i, j;
    for( i=0; i < n * n; i++ )
    {
        A[ i ] = 4;
    }

    printf("user | A[ 0 ]: %f\n",
           A[ 0 ]
    );


    char set[]="hybChiveC_SetTemplate";
    char variants[]="all";
    char optimize[]="performance";
    int numberOfParameters = 1;



    hybchiveLog( "user | execute HybChive Function" );

    hybchive(
        set,
        variants,
        optimize,
        numberOfParameters,
        sizeof( A ),
        "double",
        A
    );

    hybchiveLog( "\nuser | end HybChive Function - order timemarks yourself\n" );

    printf("\nuser | matrix after hybchive function call\n");

    for( i = 0; i < 4; i++ )
    {
        for( j = 0; j < 4; j++ )
        {
            printf("%lf ", A[ i * n + j ]);
        }
        printf("\n");
    }


}
