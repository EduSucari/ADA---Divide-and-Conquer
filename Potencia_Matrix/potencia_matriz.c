#include <stdio.h>

typedef struct {
    long long a[2][2];
} Matriz;

/* Multiplica dos matrices 2x2: C = A * B */
Matriz multiplicar(Matriz A, Matriz B) {
    Matriz C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C.a[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                C.a[i][j] += A.a[i][k] * B.a[k][j];
            }
        }
    }
    return C;
}

/* M^n en O(log n) */
Matriz potencia_matriz(Matriz M, int n) {
    if (n == 0) {               /* caso base: matriz identidad */
        Matriz I = {{{1, 0}, {0, 1}}};
        return I;
    }
    Matriz mitad = potencia_matriz(M, n / 2);    /* dividir */
    Matriz cuadrado = multiplicar(mitad, mitad); /* combinar */
    if (n % 2 == 0) {
        return cuadrado;
    } else {
        return multiplicar(cuadrado, M);
    }
}

void imprimir(Matriz M) {
    for (int i = 0; i < 2; i++) {
        printf("| %lld  %lld |\n", M.a[i][0], M.a[i][1]);
    }
}

int main(void) {
    Matriz M;
    int n;

    printf("Ingrese la matriz 2x2 (a b c d): ");
    scanf("%lld %lld %lld %lld", &M.a[0][0], &M.a[0][1], &M.a[1][0], &M.a[1][1]);
    printf("Ingrese el exponente (entero >= 0): ");
    scanf("%d", &n);

    printf("\nResultado de M^%d:\n", n);
    imprimir(potencia_matriz(M, n));
    return 0;
}
