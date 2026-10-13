#ifndef FIBONACCI_H
#define FIBONACCI_H

/* Secuencial: O(n). Va guardando los dos últimos valores. */
static long long fib_secuencial(int n) {
    if (n == 0) return 0;
    long long anterior = 0, actual = 1;
    for (int i = 2; i <= n; i++) {
        long long siguiente = anterior + actual;
        anterior = actual;
        actual = siguiente;
    }
    return actual;
}

// ---- Logarítmico: O(log n) con matrices ----
typedef struct {
    long long a[2][2];
} MatrizFib;

static MatrizFib fib_multiplicar(MatrizFib A, MatrizFib B) {
    MatrizFib C;
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

static MatrizFib fib_potencia(MatrizFib M, int n) {
    if (n == 0) {
        MatrizFib I = {{{1, 0}, {0, 1}}};
        return I;
    }
    MatrizFib mitad = fib_potencia(M, n / 2);
    MatrizFib cuadrado = fib_multiplicar(mitad, mitad);
    if (n % 2 == 0) return cuadrado;
    return fib_multiplicar(cuadrado, M);
}

static long long fib_logaritmico(int n) {
    if (n == 0) return 0;
    MatrizFib base = {{{1, 1}, {1, 0}}};
    MatrizFib resultado = fib_potencia(base, n);
    return resultado.a[0][1];
}

#endif
