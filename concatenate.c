#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>

char *concatenate( int numberOfParameters, ... ) {

    printf("\n NumberOfParameters to Concatenate: %d\n ", numberOfParameters);

    va_list valist;
    va_start(valist, numberOfParameters);
    int j, i, size;
    char *inputString = "";

    char allInputStringsConcatenated[ 3000 ] = "";

    for( j = 0; j < numberOfParameters * 2; j += 2 ) {
        size = va_arg(valist, int );
        inputString = va_arg(valist, char *);
        //printf("\n Size of argument %d:, %d  \n", j, size);
        if ( inputString[ size - 1 ] == '\n') {
            printf("remove newline");
            inputString[ size - 1 ]  = '\0';
        }
        strcat( allInputStringsConcatenated, inputString);
    }
    va_end(valist);

    for( j = 0; j < sizeof( allInputStringsConcatenated ); j++ )
    {
        printf("%c", allInputStringsConcatenated[ j ] );
    }

    return allInputStringsConcatenated;
}