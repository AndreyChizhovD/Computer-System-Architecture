# Отчет по ИДЗ-1
# Чижов Андрей Дмитриевич БПИ218
# вариант 39

## 4
### Код на языке C
```c
#include <stdio.h>

static int A[1048576];
static int B[1048576];

int main(int argc, char** argv) {
    int n;
    int i;

    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &A[i]);
        
    }

    for (i = 0; i < n; ++i) {
    	B[i] = A[i] * A[i];
    }

    for (i = 0; i < n; ++i) {
    	printf("%d", B[i]);
    }

    return 0;
}
```

### Компиляция программы
```sh
gcc -masm=intel -S v39.c -o v39.s
```

### Программа на ассемблере
```assembly
    .file	"v39.c"
	.intel_syntax noprefix			# синтаксис в стиле Intel
	.text					# начало секции
	.local	A				# объявление символа A
	.comm	A,4194304,32			# неинициализированный массив А
	.local	B				# тоже самое с массивом В
	.comm	B,4194304,32			
	.section	.rodata			# переход в секцию  .rodata
.LC0:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	push	rbp				# rbp сохранен на стек
	.cfi_def_cfa_offset 16			
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6			# rbp := rsp
	sub	rsp, 32				# rsp -= 32
	mov	DWORD PTR -20[rbp], edi		# argc
	mov	QWORD PTR -32[rbp], rsi		# argv
	mov	rax, QWORD PTR fs:40		
	mov	QWORD PTR -8[rbp], rax		# n
	xor	eax, eax			
	lea	rax, -16[rbp] 			# rax(n) := &(-16 на стеке) 
	mov	rsi, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0				# счетчик в цикле
	call	__isoc99_scanf@PLT		# вызов scanf 
	mov	DWORD PTR -12[rbp], 0		
	jmp	.L2				# прыгаем по меткам в цикле
.L3:						
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, A[rip]
	add	rax, rdx
	mov	rsi, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	add	DWORD PTR -12[rbp], 1
.L2:
	mov	eax, DWORD PTR -16[rbp]
	cmp	DWORD PTR -12[rbp], eax
	jl	.L3
	mov	DWORD PTR -12[rbp], 0
	jmp	.L4
.L5:
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, A[rip]
	mov	edx, DWORD PTR [rdx+rax]
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	lea	rcx, 0[0+rax*4]
	lea	rax, A[rip]
	mov	eax, DWORD PTR [rcx+rax]
	imul	eax, edx
	mov	edx, DWORD PTR -12[rbp]
	movsx	rdx, edx
	lea	rcx, 0[0+rdx*4]
	lea	rdx, B[rip]
	mov	DWORD PTR [rcx+rdx], eax
	add	DWORD PTR -12[rbp], 1
.L4:
	mov	eax, DWORD PTR -16[rbp]
	cmp	DWORD PTR -12[rbp], eax
	jl	.L5
	mov	DWORD PTR -12[rbp], 0
	jmp	.L6
.L7:
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, B[rip]
	mov	eax, DWORD PTR [rdx+rax]
	mov	esi, eax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	add	DWORD PTR -12[rbp], 1
.L6:
	mov	eax, DWORD PTR -16[rbp]
	cmp	DWORD PTR -12[rbp], eax
	jl	.L7
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L9
	call	__stack_chk_fail@PLT
.L9:							# Выход из функции
	leave					
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
```

```sh
gcc ./v39.s -o ./v39.exe \
    ./v39.exe
***test***
```


### Компиляция программы с оптимизацией
```sh
gcc -masm=intel \
    -fno-asynchronous-unwind-tables \
    -fno-jump-tables \
    -fno-stack-protector \
    -fno-exceptions \
    ./v39.c \
    -S -o ./v39.s
```

### Тесты

| input  | output v39.c            | output v39.s           |
|-----------------|:---------------:|:---------------:|
| 0 | - | - |
| 5 [1 2 3 4 5]       | [1 4 9 16 25]     | [1 4 9 16 25]     |
| 4 [0 9 10 3]    | [0 81 100 9] | [0 81 100 9] |
| 5 [13 11 0 4 1]| [169 121 0 16 1]|[169 121 0 16 1]|

## 5
### Код на языке C
```c
#include <stdio.h>

static int A[1048576];
static int B[1048576];

void printArray(int size, int array[]) {
    int j;
    for (j = 0; j < size; ++j) {
    	printf("%d", array[j]);
    }
}

int main(int argc, char** argv) {
    int n;
    int i;

    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &A[i]);
        
    }

    for (i = 0; i < n; ++i) {
    	B[i] = A[i] * A[i];
    }
    
    printArray(n, B);

    return 0;
}
```
### Ассемблер
```assembly
printArray:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	DWORD PTR -20[rbp], edi			# сохраняем аргументы на стек
	mov	QWORD PTR -32[rbp], rsi			 
	mov	DWORD PTR -4[rbp], 0			# в цикле j присваивается 0
	jmp	.L2					# проверка условия цикла
.L3:
	mov	eax, DWORD PTR -4[rbp]			# счетчик в rax
	cdqe						# sign-extend
	lea	rdx, 0[0+rax*4]				# rcx := 4 * rax
	mov	rax, QWORD PTR -32[rbp]			# rax := array[j]
	add	rax, rdx
	mov	eax, DWORD PTR [rax]
	mov	esi, eax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT				# вызов printf("%d", array[j]);
	add	DWORD PTR -4[rbp], 1			# ++счетчик
.L2:
	mov	eax, DWORD PTR -4[rbp]			# загружаем j из стека в eax
	cmp	eax, DWORD PTR -20[rbp]			# сравниваем с size
	jl	.L3					# true => идем дальше по итерациям
	nop
	nop
	leave
	ret
	.size	printArray, .-printArray
	.globl	main
	.type	main, @function
```
```assembly
# main..
.L7:
	mov	eax, DWORD PTR -16[rbp]
	cmp	DWORD PTR -12[rbp], eax
	jl	.L8
	mov	eax, DWORD PTR -16[rbp]		# eax := rbp[-32] загрузка из стека в аргументы
	lea	rdx, B[rip]			# rdx := rip[B]
	mov	rsi, rdx			# rsi := rdx	
	mov	edi, eax			# edi := eax
	call	printArray			# вызов printArray
# main..
```
### Полная декомпозиция в 7.
## 6
```assembly
	.file	"v39.c"
	.intel_syntax noprefix
	.text
	.local	A
	.comm	A,4194304,32
	.local	B
	.comm	B,4194304,32
	.section	.rodata
.LC0:
	.string	"%d"
	.text
	.globl	printArray
	.type	printArray, @function
printArray:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	DWORD PTR -20[rbp], edi			# сохраняем аргументы на стек
	mov	QWORD PTR -32[rbp], rsi			# 
	mov	DWORD PTR -4[rbp], 0			# в цикле j присваивается 0
	jmp	.L2					# проверка условия цикла
.L3:
	mov	eax, DWORD PTR -4[rbp]			# счетчик в rax
	cdqe						# sign-extend
	lea	rdx, 0[0+rax*4]				# rcx := 4 * rax
	mov	rax, QWORD PTR -32[rbp]			# rax := array[j]
	add	rax, rdx
	mov	eax, DWORD PTR [rax]
	mov	esi, eax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT				# вызов printf("%d", array[j]);
	add	DWORD PTR -4[rbp], 1			# ++счетчик
.L2:
	mov	eax, DWORD PTR -4[rbp]			# загружаем j из стека в eax
	cmp	eax, DWORD PTR -20[rbp]			# сравниваем с size
	jl	.L3					# true => идем дальше по итерациям
	nop
	nop
	leave
	ret
	.size	printArray, .-printArray
	.globl	main
	.type	main, @function
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	DWORD PTR -20[rbp], edi
	mov	QWORD PTR -32[rbp], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	lea	rax, -16[rbp]
	mov	rsi, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	mov	DWORD PTR -12[rbp], 0
	jmp	.L5
.L6:
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, A[rip]
	add	rax, rdx
	mov	rsi, rax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_scanf@PLT
	add	DWORD PTR -12[rbp], 1
.L5:
	mov	eax, DWORD PTR -16[rbp]
	cmp	DWORD PTR -12[rbp], eax
	jl	.L6
	mov	DWORD PTR -12[rbp], 0
	jmp	.L7
.L8:
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, A[rip]
	mov	edx, DWORD PTR [rdx+rax]
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	lea	rcx, 0[0+rax*4]
	lea	rax, A[rip]
	mov	eax, DWORD PTR [rcx+rax]
	imul	eax, edx
	mov	edx, DWORD PTR -12[rbp]
	movsx	rdx, edx
	lea	rcx, 0[0+rdx*4]
	lea	rdx, B[rip]
	mov	DWORD PTR [rcx+rdx], eax
	add	DWORD PTR -12[rbp], 1
.L7:
	mov	eax, DWORD PTR -16[rbp]
	cmp	DWORD PTR -12[rbp], eax
	jl	.L8
	mov	eax, DWORD PTR -16[rbp]		# eax := rbp[-32] загрузка из стека в аргументы
	lea	rdx, B[rip]			# rdx := rip[B]
	mov	rsi, rdx			# rsi := rdx	
	mov	edi, eax			# edi := eax
	call	printArray			# вызов printArray
	mov	eax, 0				# 
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L10
	call	__stack_chk_fail@PLT
.L10:
	leave
	ret
```

### тесты (same input)
| output v39.s(old)  | output v39.c            | output v39.s           |
|-----------------|:---------------:|:---------------:|
| - | - | - |
| [1 4 9 16 25]       | [1 4 9 16 25]     | [1 4 9 16 25]     |
| [0 81 100 9]     | [0 81 100 9] | [0 81 100 9] |
| [169 121 0 16 1]| [169 121 0 16 1]|[169 121 0 16 1]|

## 7
### main.c
```c
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
```
### filla.c
```c
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

```
### fillb.c
```c
extern int A[1048576];
extern int B[1048576];

void fillB(int size) {
	int i;
	
	for (i = 0; i < size; ++i) {
		B[i] = A[i] * A[i];
	}
}

```
### print.c
```c
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

```
```sh
gcc ./main.c -c -o main.o
gcc ./print.c -c -o print.o
gcc ./fillb.c -c -o fillb.o
gcc ./filla.c -c -o filla.o
gcc ./filla.o ./fillb.o ./print.o main.o
./a.out
```
### main.s

```assembly
	.file	"main.c"
	.intel_syntax noprefix
	.text
	.globl	A
	.bss
	.align 32
	.type	A, @object
	.size	A, 4194304
A:
	.zero	4194304
	.globl	B
	.align 32
	.type	B, @object
	.size	B, 4194304
B:
	.zero	4194304
	.section	.rodata
.LC0:
	.string	"r"
.LC1:
	.string	"input.txt"
.LC2:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	DWORD PTR -36[rbp], edi
	mov	QWORD PTR -48[rbp], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	lea	rax, .LC0[rip]
	mov	rsi, rax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	fopen@PLT
	mov	QWORD PTR -16[rbp], rax
	lea	rdx, -20[rbp]
	mov	rax, QWORD PTR -16[rbp]
	lea	rcx, .LC2[rip]
	mov	rsi, rcx
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_fscanf@PLT
	mov	eax, DWORD PTR -20[rbp]
	mov	edi, eax
	call	fillA@PLT
	mov	eax, DWORD PTR -20[rbp]
	mov	edi, eax
	call	fillB@PLT
	mov	eax, DWORD PTR -20[rbp]
	mov	edi, eax
	call	printArray@PLT
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
```
### filla.s
```assembly
	.file	"filla.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"r"
.LC1:
	.string	"input.txt"
.LC2:
	.string	"%d"
	.text
	.globl	fillA
	.type	fillA, @function
fillA:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	DWORD PTR -36[rbp], edi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	lea	rax, .LC0[rip]
	mov	rsi, rax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	fopen@PLT
	mov	QWORD PTR -16[rbp], rax
	lea	rdx, -24[rbp]
	mov	rax, QWORD PTR -16[rbp]
	lea	rcx, .LC2[rip]
	mov	rsi, rcx
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_fscanf@PLT
	mov	DWORD PTR -20[rbp], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR -20[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, A[rip]
	add	rdx, rax
	mov	rax, QWORD PTR -16[rbp]
	lea	rcx, .LC2[rip]
	mov	rsi, rcx
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_fscanf@PLT
	add	DWORD PTR -20[rbp], 1
.L2:
	mov	eax, DWORD PTR -20[rbp]
	cmp	eax, DWORD PTR -36[rbp]
	jl	.L3
	nop
	mov	rax, QWORD PTR -8[rbp]
	sub	rax, QWORD PTR fs:40
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	leave
	ret
	.size	fillA, .-fillA
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
```
### fillb.s
```assembly
	.file	"fillb.c"
	.intel_syntax noprefix
	.text
	.globl	fillB
	.type	fillB, @function
fillB:
	push	rbp
	mov	rbp, rsp
	mov	DWORD PTR -20[rbp], edi
	mov	DWORD PTR -4[rbp], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, A[rip]
	mov	edx, DWORD PTR [rdx+rax]
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rcx, 0[0+rax*4]
	lea	rax, A[rip]
	mov	eax, DWORD PTR [rcx+rax]
	imul	eax, edx
	mov	edx, DWORD PTR -4[rbp]
	movsx	rdx, edx
	lea	rcx, 0[0+rdx*4]
	lea	rdx, B[rip]
	mov	DWORD PTR [rcx+rdx], eax
	add	DWORD PTR -4[rbp], 1
.L2:
	mov	eax, DWORD PTR -4[rbp]
	cmp	eax, DWORD PTR -20[rbp]
	jl	.L3
	nop
	nop
	pop	rbp
	ret
	.size	fillB, .-fillB
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
```
### print.s
```assembly
	.file	"print.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"w"
.LC1:
	.string	"output.txt"
.LC2:
	.string	"%d"
	.text
	.globl	printArray
	.type	printArray, @function
printArray:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	DWORD PTR -20[rbp], edi
	lea	rax, .LC0[rip]
	mov	rsi, rax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	fopen@PLT
	mov	QWORD PTR -8[rbp], rax
	mov	DWORD PTR -12[rbp], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR -12[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, B[rip]
	mov	edx, DWORD PTR [rdx+rax]
	mov	rax, QWORD PTR -8[rbp]
	lea	rcx, .LC2[rip]
	mov	rsi, rcx
	mov	rdi, rax
	mov	eax, 0
	call	fprintf@PLT
	add	DWORD PTR -12[rbp], 1
.L2:
	mov	eax, DWORD PTR -12[rbp]
	cmp	eax, DWORD PTR -20[rbp]
	jl	.L3
	nop
	nop
	leave
	ret
	.size	printArray, .-printArray
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
```
### input.txt
```
5
0
3
3
12
10
```
### output.txt
```
0 9 9 144 100
```
