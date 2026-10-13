# Códigos Divide y Conquista
 
Tarea del curso de Análisis de Algoritmos. Implementaciones en **C** de problemas clásicos resueltos con la técnica *divide y conquista*, comparando la versión simple contra la optimizada.
 
## Estructura
 
| Archivo | Contenido | Complejidad |
|---|---|---|
| `potencia.c` | Potencia de un número (secuencial y logarítmica) | O(n) vs O(log n) |
| `potencia_matriz.c` | Potencia de una matriz 2x2 | O(log n) |
| `fibonacci.h` | Funciones de Fibonacci (compartidas) | — |
| `fibonacci.c` | Fibonacci secuencial y logarítmico | O(n) vs O(log n) |
| `fibonacci_pruebas.c` | Pruebas: valores conocidos y comparación de ambos métodos | — |
| `matrices_cubica.c` | Multiplicación de matrices clásica | O(n³) |
| `matrices_strassen.c` | Multiplicación de matrices con Strassen | O(n^2.81) |
 
## Compilar y ejecutar
 
Requiere `gcc`.
 
```bash
gcc -o potencia potencia.c
./potencia
 
gcc -o potencia_matriz potencia_matriz.c
./potencia_matriz
 
gcc -o fibonacci fibonacci.c
./fibonacci
 
gcc -o fibonacci_pruebas fibonacci_pruebas.c
./fibonacci_pruebas
 
gcc -o matrices_cubica matrices_cubica.c
./matrices_cubica
 
gcc -o matrices_strassen matrices_strassen.c
./matrices_strassen
```
 
En Windows (MinGW) los ejecutables se llaman `nombre.exe`.
 
## Ideas principales
 
### Potencia logarítmica
En lugar de multiplicar la base `n` veces, se usa:
 
- `x^n = (x^(n/2))²` si `n` es par
- `x^n = (x^(n/2))² · x` si `n` es impar
El problema se reduce a la mitad en cada paso, por eso es O(log n).
 
### Potencia de matriz 2x2
Es la misma idea, pero la multiplicación es entre matrices 2x2.
 
### Fibonacci logarítmico
Se cumple que:
 
```
| 1 1 |^n   | F(n+1)  F(n)   |
| 1 0 |   = | F(n)    F(n-1) |
```
 
Entonces F(n) se obtiene elevando la matriz `[[1,1],[1,0]]` a la `n` con la potencia logarítmica. Funciona hasta `F(90)` usando `long long`.
 
### Multiplicación de matrices
- **Cúbica:** tres bucles anidados, O(n³).
- **Strassen:** divide cada matriz en 4 bloques y usa **7** multiplicaciones recursivas en vez de 8, dando T(n) = 7T(n/2) + O(n²) → O(n^log₂7) ≈ O(n^2.81). La matriz debe ser de tamaño potencia de 2 (máximo 16 en este código).
## Ejemplo de entrada (Strassen / cúbica, n = 2)
 
```
2
1 2
3 4
5 6
7 8
```
 
Salida esperada:
 
```
   19    22
   43    50
```

