#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"

int main() {
    srand(time(NULL));
    int N = 100000;
    
    printf("SIMULACION MASIVA: %d REGISTROS\n", N);
    printf("Ordenando lista de personas por edad...\n\n");

    Persona* data1 = generate_data(N);
    Persona* data2 = generate_data(N);
    Persona* data3 = generate_data(N);
    Persona* data4 = generate_data(N);

    printf("Iniciando pruebas (Fuerza bruta tomara varios segundos/minutos)...\n");

    measure_time(sort_brute_force, &data1, "Fuerza Bruta");
    measure_time(sort_greedy, &data2, "Algoritmo Codicioso");
    measure_time(sort_divide_and_conquer, &data3, "Divide y Venceras (Merge)");
    measure_time(sort_quick_sort, &data4, "Divide y Venceras (Quick)");
    
    free_list(data1); free_list(data2); free_list(data3); free_list(data4);
    return 0;
}
