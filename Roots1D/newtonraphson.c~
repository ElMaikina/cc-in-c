#include <stdio.h>
#include <math.h>

// Definimos la funcion F(x)
double f(double x) {
    return x * x - 2; // Por ejemplo, queremos hallar la raíz de x² - 2 = 0 → √2
}

// Derivada de F(x)
double df(double x) {
    return 2 * x;
}

// Metodo de Newton-Raphson
double newton_raphson(double x0, double tol, int max_iter)
{
    // Copia el valor inicial por valor
    double x = x0;

    // Itera la funcion hasta llegar al maximo de iteraciones
    for (int i = 0; i < max_iter; i++) {
        double fx = f(x);
        double dfx = df(x);

	// Si la derivada es cero, el metodo no funciona	
        if (dfx == 0) {
            printf("Derivada cero.\n");
            return x;
        }

	// Iteracion de X_{i+1} = X_i - F(x) / F'(X)
        double x1 = x - fx / dfx;

	// Si esta por debajo de la tolerancia, alcanzamos la raiz
        if (fabs(x1 - x) < tol) {
            return x1;
        }

	// Vuelve a iterar si no estamos cerca
        x = x1;
    }

    // Si no alcanzamos una tolerancia aceptable, fallamos
    printf("No converge despues de %d iteraciones.\n", max_iter);
    return x;
}

// Ejecucion del Algoritmo:
// > gcc newtonraphson.c -o newtonraphson
// > /newtonraphson 
int main()
{
    // Condiciones iniciales
    double x0 = 1.0;     // Estimacion inicial
    double tol = 1e-6;   // Tolerancia
    int max_iter = 100;  // Numero maximo de iteraciones

    // Ejecucion de Newton Raphson
    double raiz = newton_raphson(x0, tol, max_iter);

    // Muestra condiciones y resultados
    printf("Valor inicial: %.6f\n", x0);
    printf("Tolerancia: %.6f\n", tol);
    printf("Iteraciones: %d\n", max_iter);
    printf("Raiz: %.6f\n", raiz);
    return 0;
}

