#
#Compiles and executes the different programs
#


test:	varianttest.c 
	gcc -c varianttest.c -lrt
	gcc -o varianttest varianttest.o

final: variant.c
	gcc variant.c -o variant ../../attachSharedMemorySegment.o