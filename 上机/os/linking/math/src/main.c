#include <stdio.h>
#include "../include/test.h"

int main()
{
    int m, n;
    printf("Input two numbers: ");
    scanf("%d %d", &m, &n);
    printf("%d@%d=%d\n", m, n, add(m, n));

    return 0;
}

