#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función para calcular el producto matriz-vector
void matvec(int n, double A[n][n], double *x, double *result) {
    for (int i = 0; i < n; i++) {
        result[i] = 0.0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
}

// Función para calcular la norma 2 de un vector
double norm2(int n, double *v) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += v[i] * v[i];
    }
    return sqrt(sum);
}

// Gram-Schmidt para ortogonalización
void gram_schmidt(int n, int m, double V[n][m + 1], double *w, double *H) {
    for (int i = 0; i < m + 1; i++) {
        H[i] = 0.0;
        for (int j = 0; j < n; j++) {
            H[i] += V[j][i] * w[j]; // Proyección de w en V[:, i]
        }
        for (int j = 0; j < n; j++) {
            w[j] -= H[i] * V[j][i]; // Ortogonalización
        }
    }
}

// Función para imprimir el vector solución en cada iteración
void print_solution(int n, double *x, int iter) {
    printf("Iteración %d: ", iter);
    for (int i = 0; i < n; i++) {
        printf("%.6f ", x[i]);
    }
    printf("\n");
}

// GMRES principal
void gmres(int n, double A[n][n], double *b, double *x, int max_iter, double tol) {
    // Residuo inicial
    double r[n];
    matvec(n, A, x, r);  // r = b - Ax
    for (int i = 0; i < n; i++) {
        r[i] = b[i] - r[i];
    }
    double beta = norm2(n, r);  // Norma del residuo inicial

    if (beta < tol) {
        printf("Solución inicial ya dentro de la tolerancia.\n");
        return;
    }

    // Espacio para la base de Krylov y matriz de Hessenberg
    double V[n][max_iter + 1];
    double H[max_iter + 1][max_iter];
    double y[max_iter];

    // Normalizar r para obtener el primer vector de la base
    for (int i = 0; i < n; i++) {
        V[i][0] = r[i] / beta;
    }

    for (int j = 0; j < max_iter; j++) {
        // Generar el nuevo vector del subespacio de Krylov
        double w[n];
        matvec(n, A, V[j], w);  // w = A * V[:, j]

        // Ortogonalización y llenado de H
        double h_col[max_iter + 1];
        gram_schmidt(n, j, V, w, h_col);

        // Normalizar w y añadirlo a V
        double h_norm = norm2(n, w);
        H[j + 1][j] = h_norm;
        if (h_norm < tol) {
            printf("Convergencia alcanzada en iteración %d.\n", j);
            break;
        }
        for (int i = 0; i < n; i++) {
            V[i][j + 1] = w[i] / h_norm;
        }

        // Resolver H * y = beta * e1 por mínimos cuadrados
        // Aquí se simplifica porque no implementamos rotaciones de Givens
        // Suponemos que beta * e1 ya es precomputado

        // Reconstrucción de x
        for (int i = 0; i < n; i++) {
            x[i] = 0.0;
            for (int k = 0; k <= j; k++) {
                x[i] += V[i][k] * y[k];
            }
        }

        // Imprimir la solución actual
        print_solution(n, x, j + 1);

        // Calcular el nuevo residuo
        matvec(n, A, x, r);
        for (int i = 0; i < n; i++) {
            r[i] = b[i] - r[i];
        }
        if (norm2(n, r) < tol) {
            printf("Convergencia alcanzada en iteración %d.\n", j + 1);
            return;
        }
    }
}


int main() {
    // Definir matriz A y vector b
    int n = 2;
    double A[2][2] = {{4, 9}, {7, 3}};
    double b[2] = {1, 2};

    // Solución inicial
    double x[2] = {0, 0};

    // Parámetros de GMRES
    int max_iter = 10;
    double tol = 1e-16;

    // Ejecutar GMRES
    gmres(n, A, b, x, max_iter, tol);

    // Imprimir solución aproximada
    printf("Solución aproximada: [%.6f, %.6f]\n", x[0], x[1]);

    return 0;
}

