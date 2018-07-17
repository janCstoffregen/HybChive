#
#Compiles and executes the different programs
#


test:	varianttest.c 
	gcc varianttest.c -o varianttest -I/usr/local/cuda-5.0/include -L/usr/lib/nvidia-current -lOpenCL -lrt -lm

final: variant.c
	gcc variant.c -o variant -I/usr/local/cuda-5.0/include -L/usr/lib/nvidia-current -lOpenCL -lrt -lm ../../attachSharedMemorySegment.o