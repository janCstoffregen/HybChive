#!/bin/bash
gcc -c scheduler.c -lrt
gcc -c log.c -lrt
gcc -c user.c
gcc -o user user.o scheduler.o log.o -lrt
./user
