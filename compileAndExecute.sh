#!/bin/bash
gcc -c scheduler.c -lrt
gcc -c hybchiveLog.c -lrt
gcc -c concatenate.c
gcc -c user.c
gcc -o user user.o scheduler.o hybchiveLog.o concatenate.o
./user
