//gcc platforms.c -o platforms -I/usr/local/cuda-5.0/include -L/usr/lib/nvidia-current -lOpenCL -lrt

// Enable double precision

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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

int main() {

	
	int i, j, err;
	char* info;
	size_t infoSize;
	cl_uint platformCount;
	cl_platform_id *platforms;
	const char* attributeNames[5] = { "Name", "Vendor",
	"Version", "Profile", "Extensions" };
	const cl_platform_info attributeTypes[5] = { CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,
	CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE, CL_PLATFORM_EXTENSIONS };
	const int attributeCount = sizeof(attributeNames) / sizeof(char*);
	cl_platform_id platform;cl_device_id device_id;cl_context context;cl_command_queue commands;
	cl_program program;cl_kernel kernel;size_t local; size_t global;cl_event event;

	cl_mem A_device, B_device;

	// get platform count
	clGetPlatformIDs(5, NULL, &platformCount);

	// get all platforms
	platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
	clGetPlatformIDs(platformCount, platforms, NULL);
	
	
	// for each platform print all attributes
	for (i = 0; i < platformCount; i++) {

	printf(" %d. Platform n", i+1);

	for (j = 0; j < attributeCount; j++) {

	    // get platform attribute value size
	    clGetPlatformInfo(platforms[i], attributeTypes[j], 0, NULL, &infoSize);
	    info = (char*) malloc(infoSize);

	    // get platform attribute value
	    clGetPlatformInfo(platforms[i], attributeTypes[j], infoSize, info, NULL);

	    printf("\n  %d.%d %-11s: %s", i+1, j+1, attributeNames[j], info);
	    free(info);

	}

	printf("\n");

	}
	
	cl_uint platforms_n = 0;
	CL_CHECK(clGetPlatformIDs(100, platforms, &platforms_n));

	cl_device_id devices[100];
	cl_uint devices_n = 0;
	// CL_CHECK(clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, 100, devices, &devices_n));
	CL_CHECK(clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 100, devices, &devices_n));
	


	
	printf("=== %d OpenCL device(s) found on platform:\n", platforms_n);
	for (i=0; i<devices_n; i++)
	{
		char buffer[10240];
		cl_uint buf_uint;
		cl_ulong buf_ulong;
		printf("  -- %d --\n", i);
		CL_CHECK(clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(buffer), buffer, NULL));
		printf("  DEVICE_NAME = %s\n", buffer);
		CL_CHECK(clGetDeviceInfo(devices[i], CL_DEVICE_VENDOR, sizeof(buffer), buffer, NULL));
		printf("  DEVICE_VENDOR = %s\n", buffer);
		CL_CHECK(clGetDeviceInfo(devices[i], CL_DEVICE_VERSION, sizeof(buffer), buffer, NULL));
		printf("  DEVICE_VERSION = %s\n", buffer);
		CL_CHECK(clGetDeviceInfo(devices[i], CL_DRIVER_VERSION, sizeof(buffer), buffer, NULL));
		printf("  DRIVER_VERSION = %s\n", buffer);
		CL_CHECK(clGetDeviceInfo(devices[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(buf_uint), &buf_uint, NULL));
		printf("  DEVICE_MAX_COMPUTE_UNITS = %u\n", (unsigned int)buf_uint);
		CL_CHECK(clGetDeviceInfo(devices[i], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(buf_uint), &buf_uint, NULL));
		printf("  DEVICE_MAX_CLOCK_FREQUENCY = %u\n", (unsigned int)buf_uint);
		CL_CHECK(clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(buf_uint), &buf_uint, NULL));
		printf("  MAX_WORK_ITEM_DIMENSION = %llu\n", (unsigned long long)buf_ulong);
	}
	
	return 0;

}
