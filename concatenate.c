#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>

char *concatenate( int numberOfParameters, ... ) {

    printf("\n NumberOfParameters to Concatenate: %d\n ", numberOfParameters);

    va_list valist;

    va_start(valist, numberOfParameters);
    int j, i;
    char *testVaList = "";
    for( j = 0; j < numberOfParameters; j++ ) {
        testVaList = va_arg(valist, char *);
        printf("\n Size of the valist: %d \n", sizeof( testVaList ));
        for(i=0;i< sizeof( testVaList ); i++ ) {
            printf("%c", testVaList[ i ] );
        }
        printf("\n");
    }
    va_end(valist);

    printf("end concatenate");

    while(fopen("wait.dummy","r")==NULL){
        //Wait, until test procedure is done with testing of the according variant
    }


    char *test = "test";
    return test;
}