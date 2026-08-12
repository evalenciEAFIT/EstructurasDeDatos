#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"

int main() {
    srand(time(NULL));
    int N = 100000;
    
    printf("SIMULACION MASIVA: %d REGISTROS\n", N);
    printf("Ordenando lista de personas por edad...\n\n");

    Persona* data1 = generar_datos(N);
    Persona* data2 = generar_datos(N);
    Persona* data3 = generar_datos(N);
    Persona* data4 = generar_datos(N);

    printf("Iniciando pruebas (Fuerza bruta tomara varios segundos/minutos)...\n");

    medir_tiempo(ordenar_fuerza_bruta, &data1, "Fuerza Bruta");
    medir_tiempo(ordenar_codicioso, &data2, "Algoritmo Codicioso");
    medir_tiempo(ordenar_divide_y_venceras, &data3, "Divide y Venceras (Merge)");
    medir_tiempo(ordenar_quick_sort, &data4, "Divide y Venceras (Quick)");
    
    liberar_lista(data1); liberar_lista(data2); liberar_lista(data3); liberar_lista(data4);
    return 0;
}
