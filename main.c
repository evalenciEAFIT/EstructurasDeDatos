/**
 * Punto de Entrada Principal (Main)
 * Orquesta la interfaz interactiva de usuario en terminal (CLI) para 
 * generar las Personas, medir tiempos y comparar todos los algoritmos.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"

void mostrar_menu(int N) {
    printf("\n=========================================\n");
    printf("   MENU ORDENAMIENTO DE PERSONAS\n");
    printf("   Datos actuales en memoria: %d\n", N);
    printf("=========================================\n");
    printf("1. Generar N datos aleatorios\n");
    printf("2. Ver datos actuales\n");
    printf("3. Ejecutar tabla comparativa (Todos los algoritmos)\n");
    printf("4. Ejecutar un algoritmo especifico (y ver datos ordenados)\n");
    printf("5. Salir\n");
    printf("=========================================\n");
    printf("Opcion: ");
}

void mostrar_submenu() {
    printf("\n--- ALGORITMOS DISPONIBLES ---\n");
    printf("1. Fuerza Bruta (Bubble Sort)\n");
    printf("2. Algoritmo Codicioso (Selection Sort)\n");
    printf("3. Divide y Venceras (Merge Sort)\n");
    printf("4. Divide y Venceras (Quick Sort)\n");
    printf("5. Backtracking (Cuidado: N debe ser <= 6)\n");
    printf("Opcion: ");
}

void menu_visualizar_ordenados(Persona* head, int N) {
    printf("\nEl algoritmo ha finalizado y ha ordenado %d elementos.\n", N);
    printf("¿Desea explorar los datos ya ordenados?\n");
    printf("1. Ver los PRIMEROS K elementos (Menores edades)\n");
    printf("2. Ver los ULTIMOS K elementos (Mayores edades)\n");
    printf("0. Volver al menu principal\n");
    printf("Opcion: ");
    
    int opc_ver;
    if (scanf("%d", &opc_ver) == 1 && opc_ver != 0) {
        int k;
        printf("Cuantos elementos desea ver (K)? : ");
        if (scanf("%d", &k) == 1 && k > 0) {
            if (opc_ver == 1) {
                print_first_n_elements(head, k, "Primeros elementos");
            } else if (opc_ver == 2) {
                print_last_n_elements(head, k, "Ultimos elementos");
            }
        } else {
            while(getchar() != '\n');
        }
    } else {
        while(getchar() != '\n');
    }
}

int main() {
    srand(time(NULL));
    Persona* datos_maestros = NULL;
    int N = 0;
    int opcion = 0;

    while (opcion != 5) {
        mostrar_menu(N);
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        switch (opcion) {
            case 1:
                printf("Ingrese la cantidad N de datos a generar: ");
                if (scanf("%d", &N) == 1 && N > 0) {
                    if (datos_maestros != NULL) free_list(datos_maestros);
                    datos_maestros = generate_data(N);
                    printf("Se han generado %d registros aleatorios exitosamente.\n", N);
                } else {
                    printf("Numero invalido.\n");
                    while(getchar() != '\n');
                    N = 0;
                }
                break;

            case 2:
                if (datos_maestros == NULL) {
                    printf("No hay datos generados. Usa la opcion 1 primero.\n");
                } else {
                    printf("\nDatos en bruto (sin ordenar):\n");
                    print_first_n_elements(datos_maestros, 20, "Mostrando (hasta 20)");
                }
                break;

            case 3:
                if (datos_maestros == NULL) {
                    printf("No hay datos generados.\n");
                } else {
                    printf("\n=======================================================\n");
                    printf(" TABLA COMPARATIVA DE RENDIMIENTO (Datos ordenados: %d)\n", N);
                    printf("=======================================================\n");
                    
                    Persona* d1 = copy_list(datos_maestros);
                    measure_time(sort_brute_force, &d1, "Fuerza Bruta");
                    free_list(d1);

                    Persona* d2 = copy_list(datos_maestros);
                    measure_time(sort_greedy, &d2, "Algoritmo Codicioso");
                    free_list(d2);

                    Persona* d3 = copy_list(datos_maestros);
                    measure_time(sort_divide_and_conquer, &d3, "Divide y Venceras (Merge)");
                    free_list(d3);

                    Persona* d4 = copy_list(datos_maestros);
                    measure_time(sort_quick_sort, &d4, "Divide y Venceras (Quick)");
                    free_list(d4);

                    if (N <= 8) {
                        Persona* d5 = copy_list(datos_maestros);
                        measure_time(sort_backtracking, &d5, "Backtracking");
                        free_list(d5);
                    } else {
                        printf("Omitiendo Backtracking en la tabla por seguridad (N > 8).\n");
                    }
                    printf("=======================================================\n");
                }
                break;

            case 4:
                if (datos_maestros == NULL) {
                    printf("No hay datos generados.\n");
                } else {
                    mostrar_submenu();
                    int sub_opcion;
                    if (scanf("%d", &sub_opcion) == 1) {
                        Persona* d_test = copy_list(datos_maestros);
                        switch (sub_opcion) {
                            case 1:
                                measure_time(sort_brute_force, &d_test, "Fuerza Bruta");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            case 2:
                                measure_time(sort_greedy, &d_test, "Algoritmo Codicioso");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            case 3:
                                measure_time(sort_divide_and_conquer, &d_test, "Divide y Venceras (Merge)");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            case 4:
                                measure_time(sort_quick_sort, &d_test, "Divide y Venceras (Quick)");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            case 5:
                                if (N > 8) {
                                    printf("CUIDADO: N=%d es muy grande para Backtracking (sugerido <= 6). Se podria congelar.\n", N);
                                }
                                measure_time(sort_backtracking, &d_test, "Backtracking");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            default:
                                printf("Opcion invalida.\n");
                                break;
                        }
                        free_list(d_test);
                    } else {
                        while(getchar() != '\n');
                    }
                }
                break;

            case 5:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    }

    if (datos_maestros != NULL) free_list(datos_maestros);
    return 0;
}
