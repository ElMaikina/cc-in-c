#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Genera una Matriz en formato binario para 
// cargarse por los otros algoritmos en C
void generar_matriz(const char* nombre_archivo, int filas, int columnas)
{
    // Revisa si se puede escribir el archivo
    FILE* archivo = fopen(nombre_archivo, "wb");
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return;
    }

    // Reserva memoria para la matriz (contigua en memoria)
    float* matriz = malloc(filas * columnas * sizeof(float));
    if (!matriz) {
        perror("No se pudo asignar memoria");
        fclose(archivo);
        return;
    }

    // Iniciar generador de números aleatorios
    srand((unsigned int)time(NULL));

    // Llenar la matriz con valores aleatorios entre 0 y 1
    for (int i = 0; i < filas * columnas; i++) {
        matriz[i] = (float)rand();
    }

    // Escribir datos al archivo
    fwrite(matriz, sizeof(float), filas * columnas, archivo);
    fclose(archivo);

    // Muestra por pantalla que pudo crear la Matriz
    printf("Matriz (%dx%d) guardada en '%s'\n", filas, columnas, nombre_archivo);

    // Libera la memoria pedida
    free(matriz);
}

// Ejecucion del Algoritmo:
// > gcc generate.c -o generate
// > ./generate 
int main(int argc, char* argv[]) {
    int filas = 100;
    int columnas = 100;
    generar_matriz("matriz.bin", filas, columnas);
    return 0;
}
