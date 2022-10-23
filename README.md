# Отчет по ИДЗ-1
# Чижов Андрей Дмитриевич БПИ218
# вариант 39

## 4 балла
### Код на языке C
```c
#include "stdio.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *a;
    int i;
    int firstEvenNegativeIndex = -1;

    a = (int *)malloc((argc - 1) * sizeof(int));
    for (i = 0; i < argc - 1; i++) {
        a[i] = atoi(argv[i + 1]);
        if (a[i] < 0 && a[i] % 2 == 0 && firstEvenNegativeIndex == -1) {
            firstEvenNegativeIndex = i;
        }
    }

    if (firstEvenNegativeIndex == -1) {
        firstEvenNegativeIndex = argc - 2;
    }

    int *b;
    b = (int *)malloc((argc - 1) * sizeof(int));
    for (i = 0; i < argc - 1; i++) {
        b[i] = a[i] * a[firstEvenNegativeIndex];
    }

    printf("Output: ");
    for (i = 0; i < argc - 1; i++) {
        printf("%d ", b[i]);
    }
    printf("N\n");

    free(a);
    free(b);

    return 0;
}
```

### Компиляция программы без оптимизаций
```sh
gcc -O0 -Wall -masm=intel -S 29.c -o 29.s
```

### Компиляция программы с оптимизацией
```sh
gcc -O0 -Wall -masm=intel -S -fno-asynchronous-unwind-tables -fcf-protection=none 29.c -o 29c.s
```

### Тестовые прогоны

| Входные данные  | 29.s            | 29c.s           |
|-----------------|:---------------:|:---------------:|
| *пустой массив* | *пустой массив* | *пустой массив* |
| [1 2 3 4]       | [4 8 12 16]     | [4 8 12 16]     |
| [-2 1 2 3 4]    | [4 -2 -4 -6 -8] | [4 -2 -4 -6 -8] |
| [18 65 34 -8]| [-144 -520 -272 64]|[-144 -520 -272 64]|
