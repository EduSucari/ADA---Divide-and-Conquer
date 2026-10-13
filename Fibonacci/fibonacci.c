#include <stdio.h>
#include "fibonacci.h"

int main(void) {
    int n;
    printf("Ingrese n (0 a 90): ");
    scanf("%d", &n);

    if (n < 0 || n > 90) {
        printf("n fuera de rango.\n");
        return 1;
    }

    printf("F(%d) secuencial  = %lld\n", n, fib_secuencial(n));
    printf("F(%d) logaritmico = %lld\n", n, fib_logaritmico(n));
    return 0;
}
