#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>

char *concatenate( int numberOfParameters, ... ) {

    printf("\n NumberOfParameters to Concatenate: %d\n ", numberOfParameters);

    va_list valist;
    va_start(valist, numberOfParameters);

    int j;

    for(j=0; j < numberOfParameters; j++ ) {

        printf("To concatenate: %s", va_arg(valist, int) );

    }

    printf("end concatenate");


    char *test = "test";
    return test;
}