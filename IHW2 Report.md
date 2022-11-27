# Отчет по ИДЗ-2
# Чижов Андрей Дмитриевич БПИ218
# вариант 4

## 6
### Код на языке C
```c
#include <stdio.h>

static char str[100];
static char substr[100];

void getSubstring(int size, int n) {
	int k = 0, i = 0;
	for (i = 0; i < size - 1; ++i) {
		if (str[i] > str[i + 1]) {
			for (k = 0; k < n; ++k) {
				if (i + k + 1 >= size) {
					break;
				}
				if (str[i + k] > str[i + k + 1]) {
					substr[k] = str[i + k];
					substr[k + 1] = str[i + k + 1];
				} else {
					k = 0;
					break;
				}
			}
		} else {
			k = 0;
		}
	}
}

int main(int argc, char** argv) {
	FILE *input;
	FILE *output;
	int N;

        input = fopen("input.txt", "r");
	fscanf(input, "%d", &N);
	while (fgets(str, sizeof(str), input)) {}
	fclose(input);
	
	getSubstring(sizeof(str), N);
	
	output = fopen("output.txt", "w");
	fprintf(output, "%s", substr);
	
	fclose(output);
    return 0;
}
```

### Компиляция программы
```sh
gcc -masm=intel -S v4.c -o v4.s
```

### Программа на ассемблере
```assembly
    	.file	"v4.c"
	.intel_syntax noprefix		# синтаксис в стиле интел
	.text				# начало секции
	.local	str			# объявление символа
	.comm	str,100,32		# неинициализированный массив
	.local	substr
	.comm	substr,100,32
	.section	.rodata		# переход в секцию
.LC0:
	.string	"%d, %d \n"
	.text
	.globl	getSubstring
	.type	getSubstring, @function
getSubstring:
	push	rbp			
	mov	rbp, rsp		
	sub	rsp, 32			
	mov	DWORD PTR -20[rbp], edi # сохраняем аргументы на стек
	mov	DWORD PTR -24[rbp], esi 
	mov	DWORD PTR -8[rbp], 0    
	mov	DWORD PTR -4[rbp], 0
	mov	DWORD PTR -4[rbp], 0	# в цикле присваиваем 0
	jmp	.L2			# прыгаем по меткам в цикле проверяя условие
.L11:
	mov	eax, DWORD PTR -4[rbp]  # счетчик в rax
	cdqe				# sign-extend
	lea	rdx, str[rip]
	movzx	edx, BYTE PTR [rax+rdx]
	mov	eax, DWORD PTR -4[rbp]
	add	eax, 1
	cdqe
	lea	rcx, str[rip]
	movzx	eax, BYTE PTR [rax+rcx]
	cmp	dl, al
	jle	.L3
	mov	DWORD PTR -8[rbp], 0
	jmp	.L4
.L9:
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	eax, edx
	add	eax, 1
	cmp	DWORD PTR -20[rbp], eax
	jle	.L13
	mov	edx, DWORD PTR -8[rbp]
	mov	eax, DWORD PTR -4[rbp]
	mov	esi, eax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	eax, edx
	cdqe
	lea	rdx, str[rip]
	movzx	edx, BYTE PTR [rax+rdx]
	mov	ecx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	eax, ecx
	add	eax, 1
	cdqe
	lea	rcx, str[rip]
	movzx	eax, BYTE PTR [rax+rcx]
	cmp	dl, al
	jle	.L7
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	eax, edx
	cdqe
	lea	rdx, str[rip]
	movzx	edx, BYTE PTR [rax+rdx]
	mov	eax, DWORD PTR -8[rbp]
	cdqe
	lea	rcx, substr[rip]
	mov	BYTE PTR [rax+rcx], dl
	mov	edx, DWORD PTR -4[rbp]
	mov	eax, DWORD PTR -8[rbp]
	add	eax, edx
	lea	edx, 1[rax]
	mov	eax, DWORD PTR -8[rbp]
	lea	ecx, 1[rax]
	movsx	rax, edx
	lea	rdx, str[rip]
	movzx	edx, BYTE PTR [rax+rdx]
	movsx	rax, ecx
	lea	rcx, substr[rip]
	mov	BYTE PTR [rax+rcx], dl
	jmp	.L12
.L7:
	mov	DWORD PTR -8[rbp], 0
	jmp	.L10
.L12:
	add	DWORD PTR -8[rbp], 1
.L4:
	mov	eax, DWORD PTR -8[rbp]
	cmp	eax, DWORD PTR -24[rbp]
	jl	.L9
	jmp	.L10
.L3:
	mov	DWORD PTR -8[rbp], 0
	jmp	.L10
.L13:
	nop
.L10:
	add	DWORD PTR -4[rbp], 1
.L2:
	mov	eax, DWORD PTR -20[rbp]
	sub	eax, 1
	cmp	DWORD PTR -4[rbp], eax
	jl	.L11
	nop
	nop
	leave
	ret
	.size	getSubstring, .-getSubstring
	.section	.rodata
.LC1:
	.string	"r"
.LC2:
	.string	"input.txt"
.LC3:
	.string	"%d"
.LC4:
	.string	"w"
.LC5:
	.string	"output.txt"
.LC6:
	.text
	.globl	main
	.type	main, @function
main:
	push	rbp				# rbp сохранен на стек
	mov	rbp, rsp			# rbp:=rsp
	sub	rsp, 48				# rbp -= 48
	mov	DWORD PTR -36[rbp], edi		# argc
	mov	QWORD PTR -48[rbp], rsi		# argv
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax		# N
	xor	eax, eax
	lea	rax, .LC1[rip]
	mov	rsi, rax
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	fopen@PLT
	mov	QWORD PTR -24[rbp], rax
	lea	rdx, -28[rbp]
	mov	rax, QWORD PTR -24[rbp]
	lea	rcx, .LC3[rip]
	mov	rsi, rcx
	mov	rdi, rax
	mov	eax, 0
	call	__isoc99_fscanf@PLT		# чтение из файла 
	nop
.L15:
	mov	rax, QWORD PTR -24[rbp]
	mov	rdx, rax
	mov	esi, 100
	lea	rax, str[rip]
	mov	rdi, rax
	call	fgets@PLT
	test	rax, rax
	jne	.L15
	mov	rax, QWORD PTR -24[rbp]
	mov	rdi, rax
	call	fclose@PLT
	mov	eax, DWORD PTR -28[rbp]
	mov	esi, eax
	mov	edi, 100
	call	getSubstring
	lea	rax, .LC4[rip]
	mov	rsi, rax
	lea	rax, .LC5[rip]
	mov	rdi, rax
	call	fopen@PLT
	mov	QWORD PTR -16[rbp], rax
	movzx	eax, BYTE PTR substr[rip+2]
	movsx	ecx, al
	movzx	eax, BYTE PTR substr[rip+1]
	movsx	edx, al
	movzx	eax, BYTE PTR substr[rip]
	movsx	eax, al
	mov	esi, eax
	lea	rax, .LC6[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR -16[rbp]
	mov	rsi, rax
	lea	rax, substr[rip]
	mov	rdi, rax
	call	fputs@PLT
	mov	rax, QWORD PTR -16[rbp]
	mov	rdi, rax
	call	fclose@PLT
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L17
	call	__stack_chk_fail@PLT
.L17:
	leave
	ret
```

```sh
gcc ./v4.s -o ./v4.exe \
    ./v4.exe
```


### Компиляция программы с оптимизацией
```sh
gcc -masm=intel \
    -fno-asynchronous-unwind-tables \
    -fno-jump-tables \
    -fno-stack-protector \
    -fno-exceptions \
    ./v4.c \
    -S -o ./v4.s
```

### input.txt
```
3
Never gonna give you up, 
Never gonna let you down, 
Never gonna run around and desert you
--------------------------------------
2
Yeah buddy! Light weight baby
--------------------------------------
4
abcdefghijklmnop
```
### output.txt
```
ert
-----
by
-----
mnop
```
