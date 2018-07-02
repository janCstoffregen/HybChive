#!/bin/bash
gcc -c scheduler.c
gcc -c hybchiveLog.c
gcc -c concatenate.c
gcc -c createSharedMemorySegmentsandKeys.c
gcc -c attachSharedMemorySegment.c
gcc -c user.c
gcc -o user user.o scheduler.o hybchiveLog.o concatenate.o createSharedMemorySegmentsandKeys.o attachSharedMemorySegment.o
./user
