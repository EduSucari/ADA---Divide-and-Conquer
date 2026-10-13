/*
 * Potencia de un número: base^exp
 *  - Secuencial:  O(n)      -> multiplica la base n veces
 *  - Logarítmico: O(log n)  -> divide y conquista (exponenciación rápida)
 */
#include <stdio.h>

/* Secuencial: base * base * base ... (exp veces) */
long long potencia_secuencial(long long base, int exp) {
    long long resultado = 1;
    for (int i = 0; i < exp; i++) {
        resultado = resultado * base;
    }
    return resultado;
}

/*
 * Logarítmico: usamos la idea
 *   base^exp = (base^(exp/2))^2          si exp es par
 *   base^exp = (base^(exp/2))^2 * base   si exp es impar
 * Así el problema se reduce a la mitad en cada paso.
 */
long long potencia_logaritmica(long long base, int exp) {
    if (exp == 0) {            /* caso base */
        return 1;
    }
    long long mitad = potencia_logaritmica(base, exp / 2);  /* dividir */
    if (exp % 2 == 0) {
        return mitad * mitad;          /* combinar (par) */
    } else {
        return mitad * mitad * base;   /* combinar (impar) */
    }
}

int main(void) {
    long long base;
    int exp;

    printf("Ingrese la base: ");
    scanf("%lld", &base);
    printf("Ingrese el exponente (entero >= 0): ");
    scanf("%d", &exp);

    printf("\n%lld^%d (secuencial)  = %lld\n", base, exp, potencia_secuencial(base, exp));
    printf("%lld^%d (logaritmico) = %lld\n", base, exp, potencia_logaritmica(base, exp));
    return 0;
}
