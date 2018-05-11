void hybchive(
		char *function,
		char *variants,
		char *optimize,
		int numberOfParameters,
		...
);

void hybchiveLog(
		char *note
	);

char *concatenate(
		int numberOfParameters,
		...
);

int *createSharedMemorySegmentsandKeys(
        int size,
        char *type,
        ...
);

double *attachSharedMemorySegment(
        int key
);
