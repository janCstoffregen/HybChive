#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

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
"  __global double* A_device, __global int* searchResult_device\n"	\
"	){int ii=get_global_id(0);int jj=get_global_id(1);\n" 			\
	"int n=126;\n"													\
	"if(A_device[ii*n+jj]==123){\n"									\
	"searchResult_device[0]=ii*n+jj;\n"								\
	"}\n"															\
	"\n"															\
"}\n";



int main(int argc, char *argv[]){
    printf("\n Execute Varianttest Tesla 1060\n");
    
    FILE *pipe;
    pipe=fopen("performance.txt","w");
    
    //Place the code to be tested here, measure the time for each constellatio of parameters and write it in the file "performance.txt".
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    int n;
    for (n=1;n<=126;n+=5){

        int device_chosen=1; //es geht nur 0 oder 1
        double *secondsarray, *nsecondsarray;
        double time;
        // marks the current time and saves it in an array
        void mytime(int timemark){
        struct 	timespec currenttime;
        //dynamic memory allocation
        if(timemark==1){	
            secondsarray=malloc(sizeof(double));
            nsecondsarray=malloc(sizeof(double));
        }
        else{	
            secondsarray=(double *)realloc(secondsarray,sizeof(double)*timemark);
            nsecondsarray=(double *)realloc(nsecondsarray,sizeof(double)*timemark);
        }
        clock_gettime(CLOCK_REALTIME, &currenttime);
        secondsarray[timemark-1]=currenttime.tv_sec;
        nsecondsarray[timemark-1]=currenttime.tv_nsec;
        }

        // gets the time difference of two times marked in the function mytime
        double timediff(int time2, int time1)
        {	if ((nsecondsarray[time2-1]-nsecondsarray[time1-1])<0) {
                time=secondsarray[time2-1]-secondsarray[time1-1];
                time=time+(1000000000+nsecondsarray[time2-1]-nsecondsarray[time1-1])/1000000000;
            } else {
                time=secondsarray[time2-1]-secondsarray[time1-1];
                time=time+(nsecondsarray[time2-1]-nsecondsarray[time1-1])/1000000000;
            }
            return time;
        }

        int i, j, err;
        //int n=126; // geht nur bis 126 Tesla 1060, geht nur bis 1024 Tesla C2060
        int tileX=126;
        int tileY=n/tileX;
        char* info;
        size_t infoSize;
        char buffer[10240];
        cl_uint platformCount;
        cl_platform_id *platforms;
        cl_platform_id platform;cl_device_id device_id[2];cl_context context;cl_command_queue commands;
        cl_program program;cl_kernel kernel;size_t local; size_t global;cl_event event;

        cl_mem A_device;
        cl_mem searchResult_device;
        
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
        printf("\nDEVICE_NAME = %s\n", buffer);

        // Create a compute context 
            //
            context = clCreateContext(0, 1, &device_id[device_chosen], NULL, NULL, &err);
            if (!context)
            {
                printf("Error: Failed to create a compute context!\n");
                return EXIT_FAILURE;
            }

        // Create a command commands
            //
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
            A_device = clCreateBuffer(context,  CL_MEM_READ_WRITE,  sizeof(double)*n*n, NULL, NULL);
            searchResult_device = clCreateBuffer(context,  CL_MEM_READ_WRITE,  sizeof(int)*5, NULL, NULL);

        // Generate Data
        //
        double A_host[n*n];
        int searchResult_host[5];
        searchResult_host[0] = -1;
        float temp=0.5;
        int count;
        int it;
        // Matrix Anlegen
        for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            A_host[i*n+j]=0;	
        }}
        A_host[23*n+34]=123;
        
        mytime(1);
        // Write our data set into the input array in device memory 
            //
            err = clEnqueueWriteBuffer(commands, A_device, CL_TRUE, 0, sizeof(double)*n*n, A_host, 0, NULL, NULL);
            if (err != CL_SUCCESS)
            {
                printf("Error: Failed to write to source (A_host) array!\n");
                exit(1);
            }
            err = clEnqueueWriteBuffer(commands, searchResult_device, CL_TRUE, 0, sizeof(int)*5, searchResult_host, 0, NULL, NULL);
            if (err != CL_SUCCESS)
            {
                printf("Error: Failed to write to source (searchResult_host) array!\n");
                exit(1);
            }
        
        // Set the arguments to our compute kernel
            //
        err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &A_device);
        err  = clSetKernelArg(kernel, 1, sizeof(cl_mem), &searchResult_device);	

        // Execute the kernel over the entire range of our 2d input data set
        size_t global_dimensions[] = {n,n};
        size_t local_dimensions[] = {1,n};
        
        //for(i=0;i<400;i++){
                err = clEnqueueNDRangeKernel(commands, kernel, 2, NULL, global_dimensions, local_dimensions, 0, NULL, NULL);
                if (err)
                {
                    printf("Error: Failed to execute kernel!\n");
                return EXIT_FAILURE;
                }
        //}

        clFinish(commands);

        // Read back the results from the device to verify the output
            //
        err = clEnqueueReadBuffer( commands, A_device, CL_TRUE, 0, sizeof(double) * n*n, A_host, 0, NULL, NULL );  
            if (err != CL_SUCCESS)
            {
                printf("Error: Failed to read output array! %d\n", err);
                exit(1);
        }
        err = clEnqueueReadBuffer( commands, searchResult_device, CL_TRUE, 0, sizeof(int)*5, searchResult_host, 0, NULL, NULL );  
            if (err != CL_SUCCESS)
            {
                printf("Error: Failed to read output array! %d\n", err);
                exit(1);
        }
        mytime(2);
        
        printf("\n---- Fastest code ----\n");
        printf("\nMatrix size: n = %d\n",n);
        printf("\nResult: Gefunden in: A[%d][%d]\n",searchResult_host[0]/n,searchResult_host[0] % n);
        printf("Time: %f sec\n",timediff(2,1));
        printf("\n");

        // Shutdown and cleanup
            //
            clReleaseMemObject(A_device);
            clReleaseMemObject(searchResult_device);

        free(platforms);



        //////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////
        if(searchResult_host[0]!=-1){
            fprintf (pipe, "%d %f \n", n, timediff(2,1));
        }        
    }
    close(pipe);
    pipe=popen("echo '' > wait.txt","w");
    close(pipe);
    
}