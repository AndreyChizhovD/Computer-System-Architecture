#include <stdio.h>

int A[1048576];
int B[1048576];

extern void printArray(int size);
extern void fillB(int size);
extern void fillA(int size);

int main(int argc, char** argv) {
    int n;
    FILE *input;

    input = fopen("input.txt", "r");
    fscanf(input, "%d", &n);
    
    fillA(n);
    fillB(n);
    printArray(n);

    return 0;
}
