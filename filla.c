#include <stdio.h>

extern int A[1048576];
extern int B[1048576];

void fillA(int size) {
	int i;
	FILE *input;
	
	input = fopen("input.txt", "r");
	int x;
	fscanf(input, "%d", &x);
	for (i = 0; i < size; ++i) {
		fscanf(input, "%d", &A[i]);
	}
}

