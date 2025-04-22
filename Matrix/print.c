#include <stdio.h>
#include <stdlib.h>

void imprimir_matriz(const char* archivo, int filas, int columnas) {
    // Abrir archivo en modo binario
    FILE* f = fopen(archivo, "rb");
    if (!f) {
        perror("No se pudo abrir el archivo");
        return;
    }

    // Reservar memoria para la matriz
    float* matriz = malloc(filas * columnas * sizeof(float));
    if (!matriz) {
        perror("No se pudo asignar memoria");
        fclose(f);
        return;
    }

    // Leer la matriz desde el archivo
    size_t elementos_leidos = fread(matriz, sizeof(float), filas * columnas, f);
    if (elementos_leidos != filas * columnas) {
        printf("Error leyendo el archivo\n");
        free(matriz);
        fclose(f);
        return;
    }

    fclose(f);

    // Mostrar la matriz
    printf("Matriz %dx%d leída desde el archivo:\n", filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%.3f ", matriz[i * columnas + j]);
        }
        printf("\n");
    }

    // Liberar la memoria reservada
    free(matriz);
}

int main() {
    int filas = 100;  // Número de filas de la matriz
    int columnas = 100;  // Número de columnas de la matriz
    const char* archivo = "matriz.bin";  // Nombre del archivo binario

    imprimir_matriz(archivo, filas, columnas);
    return 0;
}
