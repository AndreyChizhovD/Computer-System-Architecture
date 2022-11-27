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
### Ассемблер
### main.s
```assembly
	.file	"main.c"
	.intel_syntax noprefix				# intel syntax
	.text						# начало секции
	.section	.rodata				# переход в секцию .rodata
.LC1:
	.string	"r"
.LC2:
	.string	"input.txt"
.LC3:
	.string	"%lf"
.LC4:
	.string	"w"
.LC5:
	.string	"output.txt"
	.text
	.globl	main
	.type	main, @function
main:
	push	rbp					# rbp сохранен на стек
	mov	rbp, rsp				# rbp := rsp		
	sub	rsp, 64					# rsp -= 64
	mov	DWORD PTR -52[rbp], edi			# argc
	mov	QWORD PTR -64[rbp], rsi			# argv
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax			# -> далее все объявленные в мейне переменные input,
	xor	eax, eax				# output, eps, x, sum
	movsd	xmm0, QWORD PTR .LC0[rip]
	movsd	QWORD PTR -40[rbp], xmm0
	lea	rax, .LC1[rip]
	mov	rsi, rax
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	fopen@PLT				# вызов fopen
	mov	QWORD PTR -32[rbp], rax
	lea	rdx, -48[rbp]
	mov	rax, QWORD PTR -32[rbp]
	lea	rcx, .LC3[rip]
	mov	rsi, rcx
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_fscanf@PLT			# вызов fscanf
	mov	rax, QWORD PTR -32[rbp]
	mov	rdi, rax
	call	fclose@PLT
	mov	rax, QWORD PTR -48[rbp]
	movsd	xmm0, QWORD PTR -40[rbp]
	movapd	xmm1, xmm0
	movq	xmm0, rax
	call	taylorSeries@PLT			# вызов taylorSeries(x, eps)
	movq	rax, xmm0
	mov	QWORD PTR -24[rbp], rax
	lea	rax, .LC4[rip]
	mov	rsi, rax
	lea	rax, .LC5[rip]
	mov	rdi, rax
	call	fopen@PLT				# открыли файл на чтение
	mov	QWORD PTR -16[rbp], rax
	mov	rdx, QWORD PTR -24[rbp]
	mov	rax, QWORD PTR -16[rbp]
	movq	xmm0, rdx
	lea	rdx, .LC3[rip]
	mov	rsi, rdx
	mov	rdi, rax
	mov	eax, 1
	call	fprintf@PLT				# запись в файл
	mov	rax, QWORD PTR -16[rbp]
	mov	rdi, rax
	call	fclose@PLT
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L3					# секция .L3
	call	__stack_chk_fail@PLT
.L3:
	leave						# выход
	ret
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	-755914244
	.long	1061184077
```
### taylorSeries.s
```assembly
	.file	"taylorSeries.c"
	.intel_syntax noprefix
	.text
	.globl	taylorSeries
	.type	taylorSeries, @function
taylorSeries:
	push	rbp
	mov	rbp, rsp
	movsd	QWORD PTR -40[rbp], xmm0			# сохраняем аргументы на стек 
	movsd	QWORD PTR -48[rbp], xmm1
	mov	DWORD PTR -20[rbp], 1				
	movsd	xmm0, QWORD PTR .LC0[rip]
	movsd	QWORD PTR -16[rbp], xmm0
	movsd	xmm0, QWORD PTR .LC0[rip]
	movsd	QWORD PTR -8[rbp], xmm0
.L2:
	movsd	xmm0, QWORD PTR -40[rbp]
	movq	xmm1, QWORD PTR .LC1[rip]
	xorpd	xmm0, xmm1
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, DWORD PTR -20[rbp]
	divsd	xmm0, xmm1
	movsd	xmm1, QWORD PTR -8[rbp]
	mulsd	xmm0, xmm1
	movsd	QWORD PTR -8[rbp], xmm0
	movsd	xmm0, QWORD PTR -16[rbp]
	addsd	xmm0, QWORD PTR -8[rbp]
	movsd	QWORD PTR -16[rbp], xmm0
	add	DWORD PTR -20[rbp], 1				# прибавляем единичку в факториал
	movsd	xmm0, QWORD PTR -8[rbp]
	movq	xmm1, QWORD PTR .LC2[rip]
	andpd	xmm0, xmm1
	comisd	xmm0, QWORD PTR -48[rbp]
	jnb	.L2						# true => прыгаем в начало секции do-while
	movsd	xmm0, QWORD PTR -16[rbp]
	movq	rax, xmm0
	movq	xmm0, rax
	pop	rbp
	ret
	.size	taylorSeries, .-taylorSeries
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 16
.LC1:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.align 16
.LC2:
	.long	-1
	.long	2147483647
	.long	0
	.long	0
```
