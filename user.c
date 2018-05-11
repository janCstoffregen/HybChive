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
    int n=100;
    double A[ n * n ];
    double result=0;
    int i, j;
    for( i=0; i < n * n; i++ )
    {
        A[ i ] = 4;
    }

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

    printf("user | A[ 0 ]: %f\n",
           A[ 0 ]
    );

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
