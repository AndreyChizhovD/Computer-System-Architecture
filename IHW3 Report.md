# Отчет по ИДЗ-3
# Чижов Андрей Дмитриевич БПИ218
# вариант 16
```
Разработать программу, вычисляющую с помощью степенного ряда с точностью не хуже 0,05% значение e^(-x)
для заданного параметра x.
```
## 7
### Код на языке C
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv)
{
    int n;
    double x;
    double eps;
    double sum;
    double cur;

    scanf("%lf", &x);
    eps = 0.0005;
    
    sum = 1;
    cur = 1;
    n = 1;
    do {
        cur *= (-1.0) * x / n;
        sum += cur;
        ++n;
    } while (fabs(cur) >= eps);
    
    printf("%lf", sum);
    return 0;
}
```
### Компиляция программы с оптимизацией
```sh
gcc -masm=intel \
    -fno-asynchronous-unwind-tables \
    -fno-jump-tables \
    -fno-stack-protector \
    -fno-exceptions \
    ./v16.c \
    -S -o ./v16.s
```
### Получившаяся программа на ассемблере
```assembly
	.file	"v16.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"%lf"
	.text
	.globl	main
	.type	main, @function
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 64
	mov	DWORD PTR -52[rbp], edi
	mov	QWORD PTR -64[rbp], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	lea	rax, -40[rbp]
	mov	rsi, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	movsd	xmm0, QWORD PTR .LC1[rip]
	movsd	QWORD PTR -16[rbp], xmm0
	movsd	xmm0, QWORD PTR .LC2[rip]
	movsd	QWORD PTR -32[rbp], xmm0
	movsd	xmm0, QWORD PTR .LC2[rip]
	movsd	QWORD PTR -24[rbp], xmm0
	mov	DWORD PTR -44[rbp], 1
.L2:
	movsd	xmm0, QWORD PTR -40[rbp]
	movq	xmm1, QWORD PTR .LC3[rip]
	xorpd	xmm0, xmm1
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, DWORD PTR -44[rbp]
	divsd	xmm0, xmm1
	movsd	xmm1, QWORD PTR -24[rbp]
	mulsd	xmm0, xmm1
	movsd	QWORD PTR -24[rbp], xmm0
	movsd	xmm0, QWORD PTR -32[rbp]
	addsd	xmm0, QWORD PTR -24[rbp]
	movsd	QWORD PTR -32[rbp], xmm0
	add	DWORD PTR -44[rbp], 1
	movsd	xmm0, QWORD PTR -24[rbp]
	movq	xmm1, QWORD PTR .LC4[rip]
	andpd	xmm0, xmm1
	comisd	xmm0, QWORD PTR -16[rbp]
	jnb	.L2
	mov	rax, QWORD PTR -32[rbp]
	movq	xmm0, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 1
	call	printf@PLT
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	leave
	ret
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	-755914244
	.long	1061184077
	.align 8
.LC2:
	.long	0
	.long	1072693248
	.align 16
.LC3:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.align 16
.LC4:
	.long	-1
	.long	2147483647
	.long	0
	.long	0
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
```
### Разделим на 2 единицы компиляции.
### C
### main.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern double taylorSeries(double x, double eps);

int main(int argc, char** argv)
{
    FILE *input;
    FILE *output;
    double eps;
    double x;
    double sum;

    eps = 0.0005;
    input = fopen("input.txt", "r");
    fscanf(input, "%lf", &x);
    fclose(input);
    
    sum = taylorSeries(x, eps);
    
    output = fopen("output.txt", "w");
    fprintf(output, "%lf", sum);
    fclose(output);

    return 0;
}
```
### taylorSeries.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double taylorSeries(double x, double eps) {
    int n;
    double sum;
    double cur;
    
    n = 1;
    sum = 1;
    cur = 1;
    do {
        cur *= (-1.0) * x / n;
        sum += cur;
        ++n;
    } while (fabs(cur) >= eps);
    
    return sum;
}
```
```sh
gcc ./main.c -c -o main.o
gcc ./taylorSeries.c -c -o taylorSeries.o

gcc ./taylorSeries.o ./main.o ./a.out
```
### tests
|input.txt  | output.txt     | WolframAlpha         |
|-----------|:--------------:|:--------------------:|
| 1.345     | 0.260575       | 0.260540...          |
|      5    |      0.006706  |      0.006737...   |
|    4.327  |   0.013171    | 	0.0132071...	 |
| 	-2.2    | 	9.024981	|	9.02501...	|
