#include <stdio.h>

extern int A[1048576];
extern int B[1048576];

void printArray(int size) {
	int i;
	FILE *output;
	
	output = fopen("output.txt", "w");
	for (i = 0; i < size; ++i) {
		fprintf(output, "%d", B[i]);
	}
}

