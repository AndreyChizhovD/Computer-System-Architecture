extern int A[1048576];
extern int B[1048576];

void fillB(int size) {
	int i;
	
	for (i = 0; i < size; ++i) {
		B[i] = A[i] * A[i];
	}
}

