/*
 * Multiplicación de matrices - Strassen: O(n^2.81)
 *
 * Idea: dividir cada matriz en 4 bloques (A11, A12, A21, A22).
 * El método clásico necesita 8 multiplicaciones de bloques.
 * Strassen usa solo 7 (M1..M7), a cambio de más sumas/restas:
 *
 *   M1 = (A11 + A22) * (B11 + B22)
 *   M2 = (A21 + A22) * B11
 *   M3 = A11 * (B12 - B22)
 *   M4 = A22 * (B21 - B11)
 *   M5 = (A11 + A12) * B22
 *   M6 = (A21 - A11) * (B11 + B12)
 *   M7 = (A12 - A22) * (B21 + B22)
 *
 *   C11 = M1 + M4 - M5 + M7
 *   C12 = M3 + M5
 *   C21 = M2 + M4
 *   C22 = M1 - M2 + M3 + M6
 *
 * Como T(n) = 7T(n/2) + O(n^2)  =>  O(n^log2(7)) = O(n^2.81)
 * Requisito: n debe ser potencia de 2 (1, 2, 4, 8, 16).
 */
#include <stdio.h>

#define MAX 16

typedef int Mat[MAX][MAX];

void sumar(int n, Mat A, Mat B, Mat R) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[i][j] = A[i][j] + B[i][j];
}

void restar(int n, Mat A, Mat B, Mat R) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            R[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, Mat A, Mat B, Mat C) {
    /* Caso base: matrices de 1x1 */
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int h = n / 2;  /* tamaño de cada bloque */
    Mat A11, A12, A21, A22, B11, B12, B21, B22;
    Mat M1, M2, M3, M4, M5, M6, M7, T1, T2;

    /* 1) DIVIDIR: copiamos los 4 bloques de A y de B */
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h; j++) {
            A11[i][j] = A[i][j];       A12[i][j] = A[i][j + h];
            A21[i][j] = A[i + h][j];   A22[i][j] = A[i + h][j + h];
            B11[i][j] = B[i][j];       B12[i][j] = B[i][j + h];
            B21[i][j] = B[i + h][j];   B22[i][j] = B[i + h][j + h];
        }
    }

    /* 2) CONQUISTAR: las 7 multiplicaciones recursivas */
    sumar(h, A11, A22, T1);  sumar(h, B11, B22, T2);  strassen(h, T1, T2, M1);
    sumar(h, A21, A22, T1);                           strassen(h, T1, B11, M2);
                             restar(h, B12, B22, T2); strassen(h, A11, T2, M3);
                             restar(h, B21, B11, T2); strassen(h, A22, T2, M4);
    sumar(h, A11, A12, T1);                           strassen(h, T1, B22, M5);
    restar(h, A21, A11, T1); sumar(h, B11, B12, T2);  strassen(h, T1, T2, M6);
    restar(h, A12, A22, T1); sumar(h, B21, B22, T2);  strassen(h, T1, T2, M7);

    /* 3) COMBINAR: armamos C a partir de M1..M7 */
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h; j++) {
            C[i][j]         = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];  /* C11 */
            C[i][j + h]     = M3[i][j] + M5[i][j];                        /* C12 */
            C[i + h][j]     = M2[i][j] + M4[i][j];                        /* C21 */
            C[i + h][j + h] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];  /* C22 */
        }
    }
}

void leer(int n, Mat M) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &M[i][j]);
}

void imprimir(int n, Mat M) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%5d ", M[i][j]);
        printf("\n");
    }
}

int main(void) {
    int n;
    Mat A, B, C;

    printf("Tamano n (potencia de 2, max %d): ", MAX);
    scanf("%d", &n);
    if (n < 1 || n > MAX || (n & (n - 1)) != 0) {
        printf("n debe ser potencia de 2 (1, 2, 4, 8, 16).\n");
        return 1;
    }
    printf("Matriz A (%d x %d):\n", n, n);
    leer(n, A);
    printf("Matriz B (%d x %d):\n", n, n);
    leer(n, B);

    strassen(n, A, B, C);
    printf("\nA x B (Strassen) =\n");
    imprimir(n, C);
    return 0;
}
