#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <math.h>

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
"\n"																\
"\n"																\
"__kernel void algorithm(\n" 										\
"  __global double* A_device, __global int* searchResult_device, __global int* searchForInt_device\n"	\
"	){int ii=get_global_id(0);int jj=get_global_id(1);\n" 			\
	"int n=1001;\n"													\
	"if(A_device[ii*n+jj]==searchForInt_device[0]){\n"									\
	"searchResult_device[0]=ii*n+jj;\n"								\
	"}\n"															\
	"\n"															\
"}\n";



int main(int argc, char *argv[]){
    //printf"\n Execute Variant Tesla C1060\n");
    
	//printf"\n 10 Check, if input has arrived\n");
	
	/* Conversion string into int */
	int begin,end,ikey,n,variantid,numvariants;
    ikey = atoi(argv[1]);
    begin = atoi(argv[2]);
    end = atoi(argv[3]);
    n = atoi(argv[4]);

    n = (double) n;
    n=sqrt(n);
    n = (int) n;

    variantid = atoi(argv[5]);
    numvariants = atoi(argv[6]);
    int ikey3 = atoi(argv[7]);
    int searchForInt_Host[1];
    searchForInt_Host[0] = atoi(argv[8]);
    
    //printf"\n 10.1 key: %d, begin: %d, end: %d, n: %d\n",ikey,begin,end,n);

    //printf"\n 11. Attach shared memory space\n");
    int shmid;
    key_t key;
    double *A_host, *s;
    int size=sizeof(double)*n;
    
    key=ikey;

    /*
    * Locate the segment.
    */
    if ((shmid = shmget(key, size, 0666)) < 0) {
    perror("shmget");
    exit(1);
    }
 
    /*
    * Now we attach the segment to our data space.
    */
    if ((A_host = shmat(shmid, NULL, 0)) == (double *) -1) {
    perror("shmat");
    exit(1);
    }
    
    //printf"\n 12. Check shared memory: %lf\n",A_host[0]);
    
    //printf"\n 13. Begin of the algorithm\n");
    double result=0; //dummy result, this double variable needs to be used for the ouput.

    //Put your algorithm here!!
    
        int device_chosen = 0;
        int i, j, err;
        //int n=126; // geht nur bis 126 Tesla 1060, geht nur bis 1024 Tesla C2060
        char* info;
        size_t infoSize;
        char buffer[10240];
        cl_uint platformCount;
        cl_platform_id *platforms;
        cl_platform_id platform;cl_device_id device_id[2];cl_context context;cl_command_queue commands;
        cl_program program;cl_kernel kernel;size_t local; size_t global;cl_event event;
        cl_mem A_device;
        cl_mem searchResult_device;
        cl_mem searchForInt_device;
        
        // get first available platform
            //
            clGetPlatformIDs(1, &platform, NULL);

        // Connect to a compute device
            //
            err = clGetDeviceIDs(platform,CL_DEVICE_TYPE_GPU, 2, device_id, NULL);
            if (err != CL_SUCCESS)
            {
                //printf"Error: Failed to create a device group!\n");
                return EXIT_FAILURE;
            }

        CL_CHECK(clGetDeviceInfo(device_id[device_chosen], CL_DEVICE_NAME, sizeof(buffer), buffer, NULL));
        //printf"\nDEVICE_NAME = %s\n", buffer);

        // Create a compute context 
            //
            context = clCreateContext(0, 1, &device_id[device_chosen], NULL, NULL, &err);
            if (!context)
            {
                //printf"Error: Failed to create a compute context!\n");
                return EXIT_FAILURE;
            }

        // Create a command commands
            //
            commands = clCreateCommandQueue(context, device_id[device_chosen], 0, &err);
            if (!commands)
            {
                //printf"Error: Failed to create a command commands!\n");
                return EXIT_FAILURE;
            }
        
        // Create the compute program from the source buffer
            //
            program = clCreateProgramWithSource(context, 1, (const char **) & KernelSource, NULL, &err);
            if (!program)
            {
                //printf"Error: Failed to create compute program!\n");
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
            //printf"Error: Failed to create compute kernel!\n");
            exit(1);
        }

        // Create the input and output arrays in device memory for our calculation
        //
            A_device = clCreateBuffer(context,  CL_MEM_READ_WRITE,  sizeof(double)*(end-begin), NULL, NULL);
            searchResult_device = clCreateBuffer(context,  CL_MEM_READ_WRITE,  sizeof(int)*5, NULL, NULL);
            searchForInt_device = clCreateBuffer(context,  CL_MEM_READ_WRITE,  sizeof(int)*1, NULL, NULL);


        // Generate Data
        //
        //double A_host[n*n];
        int searchResult_host[5];
        searchResult_host[0] = -1;
        float temp=0.5;
        int count;
        int it;
        

        double *pointer;
        pointer = A_host + begin;
        //for(i=0;i<begin;i++){
        //    A_host++;
        //}
            

        // Write our data set into the input array in device memory 
            //
            err = clEnqueueWriteBuffer(commands, A_device, CL_TRUE, 0, sizeof(double)*(end-begin), pointer, 0, NULL, NULL);
            if (err != CL_SUCCESS)
            {
                //printf"Error: Failed to write to source (A_host) array!\n");
                exit(1);
            }
            err = clEnqueueWriteBuffer(commands, searchResult_device, CL_TRUE, 0, sizeof(int)*5, searchResult_host, 0, NULL, NULL);
            if (err != CL_SUCCESS)
            {
                //printf"Error: Failed to write to source (searchResult_host) array!\n");
                exit(1);
            }
            err = clEnqueueWriteBuffer(commands, searchForInt_device, CL_TRUE, 0, sizeof(int)*1, searchForInt_Host, 0, NULL, NULL);
            if (err != CL_SUCCESS)
            {
                //printf"Error: Failed to write to source (searchForInt_host) array!\n");
                exit(1);
            }
        
        // Set the arguments to our compute kernel
            //
        err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &A_device);
        err  = clSetKernelArg(kernel, 1, sizeof(cl_mem), &searchResult_device);	
        err  = clSetKernelArg(kernel, 2, sizeof(cl_mem), &searchForInt_device);

        // Execute the kernel over the entire range of our 2d input data set
        int difference = end-begin;
        double globalN = (double) difference;
        globalN = sqrt(globalN);
        globalN = (int) globalN;
        globalN += 1;

        size_t global_dimensions[] = {globalN,globalN};
        size_t local_dimensions[] = {1,globalN};
        
        //for(i=0;i<400;i++){
                err = clEnqueueNDRangeKernel(commands, kernel, 2, NULL, global_dimensions, local_dimensions, 0, NULL, NULL);
                if (err)
                {
                    //printf"Tesla C2050 Error: Failed to execute kernel!\n");
                return EXIT_FAILURE;
                }
        //}

        clFinish(commands);

        // Read back the results from the device to verify the output
            //
        //err = clEnqueueReadBuffer( commands, A_device, CL_TRUE, 0, sizeof(double) * (end-begin), pointer, 0, NULL, NULL );  
        //    if (err != CL_SUCCESS)
        //    {
        //        //printf"Error: Failed to read output array! %d\n", err);
        //        exit(1);
        //}
        err = clEnqueueReadBuffer( commands, searchResult_device, CL_TRUE, 0, sizeof(int)*5, searchResult_host, 0, NULL, NULL );  
            if (err != CL_SUCCESS)
            {
                //printf"Error: Failed to read output array! %d\n", err);
                //exit(1);
        }
        
        //printf"\n---- Fastest code ----\n");
        //printf"\nMatrix size: n = %d\n",n);
        //printf"\nResult: Gefunden in: A[%d][%d]\n",searchResult_host[0]/n,searchResult_host[0] % n);
        ////printf"Time: %f sec\n",timediff(2,1));
        //printf"\n");

        // Shutdown and cleanup
            //
            clReleaseMemObject(A_device);
            clReleaseMemObject(searchResult_device);

        //free(platforms);
    
    
    //End of your algorithm!!
    if(searchResult_host[0]!=-1){
        result = searchResult_host[0] + begin;
    }
    //printf"\n Result (begin: %d, end: %d) : %.5lf\n",begin,end,result);

    //printf"\n 15. Write result in shared memory\n");
    int shmid2;
    key_t key2;
    double *shm2, *s2;
    int size2=sizeof(double)*numvariants+1;
    
    key2=ikey3; //spaeter als input, hab ich gerade keine lust zu

    /*
    * Locate the segment.
    */
    if ((shmid2 = shmget(key2, size2, 0666)) < 0) {
    perror("shmget");
    exit(1);
    }
 
    /*
    * Now we attach the segment to our data space.
    */
    if ((shm2 = shmat(shmid2, NULL, 0)) == (double *) -1) {
    perror("shmat");
    exit(1);
    }
    
    shm2[variantid+1]=result;
    shm2[0]=shm2[0]+1;

    //printf"\n 13.1 End of the algorithm\n");

    
    
    
}