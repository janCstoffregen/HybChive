#!/bin/bash
gcc -c scheduler.c -lrt
gcc -c hybchiveLog.c -lrt
gcc -c concatenate.c -lrt
gcc -c createSharedMemorySegmentsandKeys.c -lrt
gcc -c attachSharedMemorySegment.c -lrt
gcc -c user.c -lrt -lm
gcc -o user user.o scheduler.o hybchiveLog.o concatenate.o createSharedMemorySegmentsandKeys.o attachSharedMemorySegment.o -lrt -lm
./user
