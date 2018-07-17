#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <math.h>
#include "../../hybchive.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
#define CL_CHECK(_expr)                                                         \
   do {                                                                         \
     cl_int _err = _expr;                                                       \
     if (_err == CL_SUCCESS)                                                    \
       break;                                                                   \
     fprintf(stderr, "OpenCL Error: '%s' returned %d!\n", #_expr, (int)_err);   \
     abort();                                                                   \
   } while (0)

const char *KernelSource =
"\n" 																\
"\n"																\
"\n"																\
"#if defined(cl_khr_fp64)\n"
    "#  pragma OPENCL EXTENSION cl_khr_fp64: enable\n"
    "#elif defined(cl_amd_fp64)\n"
    "#  pragma OPENCL EXTENSION cl_amd_fp64: enable\n"
    "#else\n"
    "#  error double precision is not supported\n"
    "#endif\n"
"\n"																									\
"\n"																									\
"__kernel void algorithm(\n" 																			\
"  __global double* A_device, __global int* problemSize_device\n"	\
"	){int ii=get_global_id(0); int i = 0; \n" 									\
		"  for(i = 0; i < 100000000; i ++) { A_device[ ii ] += 1; }   \n"
"}\n";







int main(int argc, char *argv[]){
	/* Conversion string into int */
	int		begin,
			end,
			ikey,
			ikey3,
			n,
			variantid,
			variantId,
			numberOfParameters,
			sharedMemoryCommuncation,
			sharedMemoryKey,
			sharedMemorySize,
			dataSliceForThisVariant,
			problemSize,
			numvariants;

	variantId = atoi(
            argv[ 1 ]
    );

    numberOfParameters = atoi(
            argv[ 2 ]
    );

    sharedMemoryCommuncation = atoi(
            argv[ 3 ]
    );

    numvariants = atoi(
            argv[ 4 ]
    );

    sharedMemoryKey = atoi(
            argv[ 5 ]
    );

    sharedMemorySize = atoi(
            argv[ 6 ]
    );

    dataSliceForThisVariant = atoi(
            argv[ 7 ]
    );

    printf("\nvariant %d | Hello, I have %d input(s).\n",
       variantId,
       numberOfParameters
       );

	printf("\nvariant %d | I will show you the first input, in a set you design you should know how many inputs you need.\n",
		variantId
	);

    double *inputArgumentOne;
    inputArgumentOne = attachSharedMemorySegment( sharedMemoryKey, sharedMemorySize, variantId );

    printf("\nvariant %d | to finalize: printf part of the input!\n",
           variantId
    );

    printf("variant %d | A[ 0 ]: %f\n",
           variantId,
           inputArgumentOne[ 0 ]
    );


    printf("variant %d | sharedMemoryCommuncationKey: %d\n",
           variantId,
           sharedMemoryCommuncation
    );

   // TODO: size of this as input for variants
    double *sharedMemoryCommunicationPointer;
    sharedMemoryCommunicationPointer = attachSharedMemorySegment(
            sharedMemoryCommuncation,
            8,
            variantId
    );

    printf("\nvariant %d | dataSlice %d\n",
           variantId,
           dataSliceForThisVariant
    );

    /**
     * The following statement is problem specific.
     * In a general way, the problem size has to be generated out of the shared memory size,
     * since the problem size is an implementation specific term.
     * */
    problemSize = sharedMemorySize / 8;

    printf("\nvariant %d | problem size %d\n",
           variantId,
           problemSize
    );

    /**
     * The following generation of the slice for this variant is HybChive - set specific /
     * optimisation - specific and has to be performed in every variant.
     * */

    printf("\nvariant %d | number of variants: %d\n",
           variantId,
           numvariants
    );

    begin = problemSize / numvariants * variantId;
    end = begin + dataSliceForThisVariant;

    printf("\nvariant %d | begin: %d, end: %d\n, ",
           variantId,
           begin,
           end
    );



    printf("\nvariant %d | Begin of the algorithm\n", variantId);
    int searchForInt_Host[1];
    double result=0; //dummy result, this double variable needs to be used for the ouput.

        int device_chosen = 1;
        int i, j, err;
        char* info;
        size_t infoSize;
        char buffer[10240];
        cl_uint platformCount;
        cl_platform_id *platforms;
        cl_platform_id platform;cl_device_id device_id[2];cl_context context;cl_command_queue commands;
        cl_program program;cl_kernel kernel;size_t local; size_t global;cl_event event;
        cl_mem A_device;
        cl_mem problemSize_device;
        // get first available platform
            //
            clGetPlatformIDs(1, &platform, NULL);

        // Connect to a compute device
            //
            err = clGetDeviceIDs(platform,CL_DEVICE_TYPE_GPU, 2, device_id, NULL);
            if (err != CL_SUCCESS)
            {
                printf("Error: Failed to create a device group!\n");
                return EXIT_FAILURE;
            }
        CL_CHECK(clGetDeviceInfo(device_id[device_chosen], CL_DEVICE_NAME, sizeof(buffer), buffer, NULL));
        //printf"\nDEVICE_NAME = %s\n", buffer);

            printf("\nvariant %d | Create Context\n", variantId);
            context = clCreateContext(0, 1, &device_id[device_chosen], NULL, NULL, &err);
            if (!context)
            {
                printf("Error: Failed to create a compute context!\n");
                return EXIT_FAILURE;
            }

        // Create a command commands
            //
            printf("\nvariant %d | Create Command Commands\n", variantId);
            commands = clCreateCommandQueue(context, device_id[device_chosen], 0, &err);
            if (!commands)
            {
                printf("Error: Failed to create a command commands!\n");
                return EXIT_FAILURE;
            }
        // Create the compute program from the source buffer
            //
            program = clCreateProgramWithSource(context, 1, (const char **) & KernelSource, NULL, &err);
            if (!program)
            {
                printf("Error: Failed to create compute program!\n");
                return EXIT_FAILURE;
            }

        // Build the program executable
        //
        err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

        // Create the compute kernel in the program we wish to run
        //
        kernel = clCreateKernel(program, "algorithm", &err);
        if (!kernel || err != CL_SUCCESS)
        {
            printf("Error: Failed to create compute kernel!\n");
            exit(1);
        }

        // Create the input and output arrays in device memory for our calculation
        //
            A_device = clCreateBuffer(context,  CL_MEM_READ_WRITE,  sizeof(double)*(problemSize-begin), NULL, NULL);
            problemSize_device = clCreateBuffer(context,  CL_MEM_READ_WRITE,  sizeof(int)*1, NULL, NULL);
        // Generate Data
        //
        int searchResult_host[5];
        searchResult_host[0] = -1;
        float temp=0.5;
        int count;
        int it;
        int problemSize_host[ 1 ];
        problemSize_host[ 0 ] = problemSize;

        double *pointer;
        pointer = inputArgumentOne + begin;

        // Write our data set into the input array in device memory 
            //
            err = clEnqueueWriteBuffer(commands, A_device, CL_TRUE, 0, sizeof(double)*(end-begin), pointer, 0, NULL, NULL);
            if (err != CL_SUCCESS)
            {
                printf("Error: Failed to write to source (inputArgumentOne) array!\n");
                exit(1);
            }
            err = clEnqueueWriteBuffer(commands, problemSize_device, CL_TRUE, 0, sizeof(int)*1, problemSize_host, 0, NULL, NULL);
            if (err != CL_SUCCESS)
            {
                printf("Error: Failed to write to source (searchForInt_host) array!\n");
                exit(1);
            }


        // Set the arguments to our compute kernel
            //
        err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &A_device);
        err  = clSetKernelArg(kernel, 1, sizeof(cl_mem), &problemSize_device);
        int difference = end-begin;
        double globalN = (double) difference;

        size_t global_dimensions[] = {globalN};
        size_t local_dimensions[] = {1};

        err = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, global_dimensions, local_dimensions, 0, NULL, NULL);
        if (err)
        {
            printf("Tesla C2050 Error: Failed to execute kernel!\n");
			return EXIT_FAILURE;
        }

        clFinish(commands);
         double resultTest[ end - begin ];
         err = clEnqueueReadBuffer(
         							commands,
         							A_device,
         							CL_TRUE,
         							0,
         							sizeof( double  ) * ( end - begin ),
         							resultTest,
         							0,
         							NULL,
         							NULL
         							);
         if (err != CL_SUCCESS)
         {
             printf("Error: Failed to read output array! %d\n", err);
             //exit(1);
    	 }
    	 if (err == CL_INVALID_VALUE)
         {
             printf("Error: region being read specified by (offset, cb) is out of bounds or if ptr is a NULL value\n");
             //exit(1);
    	 }
    	 if (err == CL_INVALID_MEM_OBJECT)
         {
             printf("Error: CL_INVALID_MEM_OBJECT\n");
             //exit(1);
    	 }
    	 if (err == CL_OUT_OF_RESOURCES)
         {
             printf("Tesla C1060 CL_OUT_OF_RESOURCES\n");
             //exit(1);
    	 }
    	 if (err == CL_OUT_OF_HOST_MEMORY)
         {
             printf("CL_OUT_OF_HOST_MEMORY\n");
             //exit(1);
    	 }

        clReleaseMemObject(A_device);

    printf("\nvariant %d | End of the algorithm Tesla C1060\n", variantId);


    sharedMemoryCommunicationPointer[ 0 ] += 1;

    printf("\nvariant %d | sharedMemoryCommuncationContent before finish: %f\n",
           variantId,
           sharedMemoryCommunicationPointer[ 0 ]
    );

    return 0;

}