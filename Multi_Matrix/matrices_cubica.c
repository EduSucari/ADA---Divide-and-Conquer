#include <stdio.h>

#define MAX 16

void multiplicar_cubica(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void leer(int n, int M[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &M[i][j]);
}

void imprimir(int n, int M[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%5d ", M[i][j]);
        printf("\n");
    }
}

int main(void) {
    int n, A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    printf("Tamano n de las matrices (max %d): ", MAX);
    scanf("%d", &n);
    printf("Matriz A (%d x %d):\n", n, n);
    leer(n, A);
    printf("Matriz B (%d x %d):\n", n, n);
    leer(n, B);

    multiplicar_cubica(n, A, B, C);
    printf("\nA x B =\n");
    imprimir(n, C);
    return 0;
}
