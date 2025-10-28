#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct {
    long long total_nodes;
    long long promising_nodes;
    long long solution_nodes;
} BacktrackStats;

// Verifica si la colocación de una reina es válida
int promising(int col[], int n, int row) {
    for (int j = 0; j < row; j++) {
        if (col[j] == col[row] || abs(col[j] - col[row]) == abs(j - row)) {
            return 0;
        }
    }
    return 1;
}

// Algoritmo de backtracking con conteo de nodos
void backtracking(int col[], int n, int row, BacktrackStats *stats) {
    stats->total_nodes++;
    
    if (row == n) {
        stats->solution_nodes++;
        return;
    }
    
    for (int j = 1; j <= n; j++) {
        col[row] = j;
        if (promising(col, n, row)) {
            stats->promising_nodes++;
            backtracking(col, n, row + 1, stats);
        }
    }
}

BacktrackStats run_backtracking(int n) {
    BacktrackStats stats = {0, 0, 0};
    int *col = (int *)malloc(n * sizeof(int));
    if (col) {
        backtracking(col, n, 0, &stats);
        free(col);
    }
    return stats;
}

// Simulación Monte Carlo para estimar nodos de backtracking
long long monte_carlo_queens(int n) {
    int i = 0;
    long long m, mprod = 1, E = 1;
    int *col = (int *)calloc(n, sizeof(int));
    
    if (!col) return -1;
    
    while (i < n) {
        m = 0;
        int promising_children[n], count = 0;
        
        for (int j = 1; j <= n; j++) {
            col[i] = j;
            if (promising(col, n, i)) {
                m++;
                promising_children[count++] = j;
            }
        }
        
        if (m == 0) break;
        
        mprod *= m;
        E += mprod;
        
        if (count > 0) {
            col[i] = promising_children[rand() % count];
        }
        i++;
    }
    
    free(col);
    return E;
}

// Exhaustivo: C(n^2, n)
double exhaustive_calc(int n) {
    double result = 1.0, num = (double)(n * n);
    for (int i = 1; i <= n; i++) {
        result = result * num / i;
        num--;
    }
    return result;
}

// Factorial: n!
double factorial_calc(int n) {
    double result = 1.0;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Formatea números: notación científica para valores grandes
void format_value(double val, char *buffer, size_t size) {
    if (val >= 1e9) {
        snprintf(buffer, size, "%.2e", val);
    } else {
        long long num = (long long)val;
        char temp[64];
        int len = snprintf(temp, sizeof(temp), "%lld", num);
        int pos = 0;
        
        for (int i = 0; i < len; i++) {
            if (i > 0 && (len - i) % 3 == 0 && pos < size - 1) {
                buffer[pos++] = ',';
            }
            if (pos < size - 1) {
                buffer[pos++] = temp[i];
            }
        }
        buffer[pos] = '\0';
    }
}

int main() {
    const int max_backtrack_n = 15;
    const int mc_runs = 1000;
    
    printf("=================================================================================================================================================\n");
    printf("%-10s %-22s %-22s %-22s %-22s %-22s %-22s\n", 
           "Reinas", "Nodos Exhaustivo", "Nodos Factorial", "Nodos Backtracking", "Nodos Promising", "Nodos Solucion", "Montecarlo");
    printf("=================================================================================================================================================\n");
    
    srand(time(NULL));
    
    for (int n = 4; n <= 100; n++) {
        char ex_str[64], fact_str[64], bt_str[64], prom_str[64], sol_str[64], mc_str[64];
        
        format_value(exhaustive_calc(n), ex_str, sizeof(ex_str));
        format_value(factorial_calc(n), fact_str, sizeof(fact_str));
        
        if (n <= max_backtrack_n) {
            BacktrackStats stats = run_backtracking(n);
            format_value((double)stats.total_nodes, bt_str, sizeof(bt_str));
            format_value((double)stats.promising_nodes, prom_str, sizeof(prom_str));
            format_value((double)stats.solution_nodes, sol_str, sizeof(sol_str));
        } else {
            strcpy(bt_str, "---");
            strcpy(prom_str, "---");
            strcpy(sol_str, "---");
        }
        
        long long mc_sum = 0;
        for (int run = 0; run < mc_runs; run++) {
            long long result = monte_carlo_queens(n);
            if (result > 0 && mc_sum < LLONG_MAX - result) {
                mc_sum += result;
            }
        }
        format_value((double)mc_sum / mc_runs, mc_str, sizeof(mc_str));
        
        printf("%-10d %-22s %-22s %-22s %-22s %-22s %-22s\n",
               n, ex_str, fact_str, bt_str, prom_str, sol_str, mc_str);
        
        if (n % 10 == 0) fflush(stdout);
    }
    
    printf("=================================================================================================================================================\n");
    return 0;
}
