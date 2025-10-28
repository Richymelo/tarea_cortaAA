# Tarea Corta - Análisis de Algoritmos N-Reinas

## Descripción

Este proyecto implementa una comparación de diferentes algoritmos para resolver el problema de las N-Reinas:
- Algoritmo exhaustivo
- Algoritmo factorial
- Algoritmo de backtracking (con conteo de nodos)
- Simulación de Monte Carlo para estimar nodos de backtracking

## Compilación

```bash
gcc -Wall -std=c11 -O2 -o nqueens main.c -lm
```

## Ejecución

```bash
./nqueens
```

## Salida

El programa genera una tabla con 7 columnas:
1. **N**: Número de reinas (de 4 a 100)
2. **Exhaustive**: Nodos visitados por algoritmo exhaustivo (fórmula: C(n², n))
3. **Factorial**: Nodos visitados por algoritmo factorial (fórmula: n!)
4. **Backtracking**: Nodos totales visitados por backtracking
5. **Promising**: Nodos prometedores en backtracking
6. **Solutions**: Cantidad de soluciones encontradas
7. **Monte Carlo**: Estimado de nodos usando simulación Monte Carlo

**Nota**: Las columnas 4, 5 y 6 solo muestran valores para N ≤ 15, después muestran "---" debido a la complejidad computacional.

## Características

- Implementación de backtracking con conteo de nodos, nodos prometedores y soluciones
- Simulación de Monte Carlo según pseudocódigo proporcionado
- Tabla formateada profesionalmente
- Fórmulas exactas para algoritmos exhaustivo y factorial
- Manejo de números grandes con formato con comas

## Algoritmos

### Backtracking
Explora el espacio de soluciones colocando reinas una por una, verificando que no se ataquen entre sí. Cuenta todos los nodos visitados, los nodos prometedores y las soluciones completas.

### Monte Carlo
Utiliza una simulación estocástica para estimar la cantidad de nodos que visitaría el algoritmo de backtracking sin ejecutarlo completamente. Realiza múltiples corridas y promedia los resultados para mayor precisión.
