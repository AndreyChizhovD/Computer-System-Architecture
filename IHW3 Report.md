# Отчет по ИДЗ-3
# Чижов Андрей Дмитриевич БПИ218
# вариант 16
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
