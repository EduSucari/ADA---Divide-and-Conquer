#include <stdio.h>
#include "fibonacci.h"

int main(void) {
    int errores = 0;

    /* Prueba 1: valores conocidos */
    int  entradas[]  = {0, 1, 2, 5, 10, 20, 50};
    long long esperados[] = {0, 1, 1, 5, 55, 6765, 12586269025LL};
    int total = sizeof(entradas) / sizeof(entradas[0]);

    printf("--- Prueba 1: valores conocidos ---\n");
    for (int i = 0; i < total; i++) {
        long long s = fib_secuencial(entradas[i]);
        long long l = fib_logaritmico(entradas[i]);
        int ok = (s == esperados[i] && l == esperados[i]);
        printf("F(%2d): esperado=%lld  sec=%lld  log=%lld  -> %s\n",
               entradas[i], esperados[i], s, l, ok ? "OK" : "ERROR");
        if (!ok) errores++;
    }

    /* Prueba 2: ambos métodos coinciden */
    printf("\n--- Prueba 2: secuencial vs logaritmico (n = 0..90) ---\n");
    for (int n = 0; n <= 90; n++) {
        if (fib_secuencial(n) != fib_logaritmico(n)) {
            printf("Diferencia en n=%d\n", n);
            errores++;
        }
    }
    if (errores == 0) printf("Todos coinciden.\n");

    printf("\nResultado final: %s\n", errores == 0 ? "TODAS LAS PRUEBAS PASARON" : "HAY ERRORES");
    return errores;
}
