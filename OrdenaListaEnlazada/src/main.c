/**
 * Punto de Entrada Principal (Main)
 * Orquesta la interfaz interactiva de usuario en terminal (CLI) para 
 * generar las Personas, medir tiempos y comparar todos los algoritmos.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BOLD    "\x1b[1m"

void pausar() {
    printf(ANSI_COLOR_CYAN "\nPresione ENTER para continuar..." ANSI_COLOR_RESET);
    while(getchar() != '\n'); // clear buffer just in case
    getchar(); // wait for enter
}

void dibujar_grafica(double tiempos[], const char* nombres[], int num_algoritmos) {
    printf(ANSI_COLOR_CYAN "\n╭──────────────────────────────────────────────────────────────╮\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "               GRAFICA DE RENDIMIENTO                         " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "├──────────────────────────────────────────────────────────────┤\n" ANSI_COLOR_RESET);
    
    double max_time = 0.000001;
    for (int i = 0; i < num_algoritmos; i++) {
        if (tiempos[i] > max_time) max_time = tiempos[i];
    }
    
    int max_bar_len = 38;
    for (int i = 0; i < num_algoritmos; i++) {
        int bar_len = (int)((tiempos[i] / max_time) * max_bar_len);
        if (bar_len < 1 && tiempos[i] >= 0) bar_len = 1;
        
        printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_RESET " %-12.12s ", nombres[i]);
        if (bar_len < 10) printf(ANSI_COLOR_GREEN);
        else if (bar_len < 25) printf(ANSI_COLOR_YELLOW);
        else printf(ANSI_COLOR_RED);
        
        for (int j = 0; j < bar_len; j++) printf("█");
        for (int j = bar_len; j < max_bar_len; j++) printf(" ");
        
        printf(ANSI_COLOR_RESET " %7.5fs " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET, tiempos[i]);
    }
    printf(ANSI_COLOR_CYAN "╰──────────────────────────────────────────────────────────────╯\n" ANSI_COLOR_RESET);
}

void mostrar_menu(int N) {
    printf(ANSI_COLOR_CYAN "\n╭──────────────────────────────────────────────────────────────╮\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "               MENU ORDENAMIENTO DE PERSONAS                  " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_GREEN "               Datos actuales en memoria: %-21d" ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET, N);
    printf(ANSI_COLOR_CYAN "├──────────────────────────────────────────────────────────────┤\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 1." ANSI_COLOR_RESET " Generar N datos aleatorios                                " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 2." ANSI_COLOR_RESET " Ver datos actuales                                        " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 3." ANSI_COLOR_RESET " Ejecutar tabla comparativa (Todos los algoritmos)         " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 4." ANSI_COLOR_RESET " Ejecutar un algoritmo especifico (y ver datos)            " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 5." ANSI_COLOR_RESET " Salir                                                     " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "╰──────────────────────────────────────────────────────────────╯\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "Opcion: " ANSI_COLOR_RESET);
}

void mostrar_submenu() {
    printf(ANSI_COLOR_CYAN "\n╭──────────────────────────────────────────────────────────────╮\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "               --- ALGORITMOS DISPONIBLES ---                 " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "├──────────────────────────────────────────────────────────────┤\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 1." ANSI_COLOR_RESET " Fuerza Bruta (Bubble Sort)                                " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 2." ANSI_COLOR_RESET " Algoritmo Codicioso (Selection Sort)                      " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 3." ANSI_COLOR_RESET " Divide y Venceras (Merge Sort)                            " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 4." ANSI_COLOR_RESET " Divide y Venceras (Quick Sort)                            " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD " 5." ANSI_COLOR_RESET " Backtracking (" ANSI_COLOR_RED "Cuidado: N debe ser <= 6" ANSI_COLOR_RESET ")                 " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "╰──────────────────────────────────────────────────────────────╯\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "Opcion: " ANSI_COLOR_RESET);
}

void menu_visualizar_ordenados(Persona* cabeza, int N) {
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
                imprimir_primeros_n_elementos(cabeza, k, "Primeros elementos");
            } else if (opc_ver == 2) {
                imprimir_ultimos_n_elementos(cabeza, k, "Ultimos elementos");
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
        system("clear");
        mostrar_menu(N);
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        switch (opcion) {
            case 1:
                printf("Ingrese la cantidad N de datos a generar: ");
                if (scanf("%d", &N) == 1 && N > 0) {
                    if (datos_maestros != NULL) liberar_lista(datos_maestros);
                    datos_maestros = generar_datos(N);
                    printf(ANSI_COLOR_GREEN "Se han generado %d registros aleatorios exitosamente.\n" ANSI_COLOR_RESET, N);
                } else {
                    printf(ANSI_COLOR_RED "Numero invalido.\n" ANSI_COLOR_RESET);
                    while(getchar() != '\n');
                    N = 0;
                }
                break;

            case 2:
                if (datos_maestros == NULL) {
                    printf("No hay datos generados. Usa la opcion 1 primero.\n");
                } else {
                    printf("\nDatos en bruto (sin ordenar):\n");
                    imprimir_primeros_n_elementos(datos_maestros, 20, "Mostrando (hasta 20)");
                }
                break;

            case 3:
                if (datos_maestros == NULL) {
                    printf(ANSI_COLOR_RED "No hay datos generados.\n" ANSI_COLOR_RESET);
                } else {
                    printf(ANSI_COLOR_CYAN "\n╭──────────────────────────────────────────────────────────────╮\n" ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_BOLD ANSI_COLOR_YELLOW " TABLA COMPARATIVA DE RENDIMIENTO (Datos ordenados: %-9d)" ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET, N);
                    printf(ANSI_COLOR_CYAN "├──────────────────────────────────────────────────────────────┤\n" ANSI_COLOR_RESET);
                    double tiempos[5] = {0};
                    const char* nombres[5] = {"F. Bruta", "Codicioso", "Merge Sort", "Quick Sort", "Backtrack"};
                    int num_algoritmos = 4;
                    
                    Persona* d1 = copiar_lista(datos_maestros);
                    tiempos[0] = medir_tiempo(ordenar_fuerza_bruta, &d1, "Fuerza Bruta");
                    liberar_lista(d1);

                    Persona* d2 = copiar_lista(datos_maestros);
                    tiempos[1] = medir_tiempo(ordenar_codicioso, &d2, "Algoritmo Codicioso");
                    liberar_lista(d2);

                    Persona* d3 = copiar_lista(datos_maestros);
                    tiempos[2] = medir_tiempo(ordenar_divide_y_venceras, &d3, "Divide y Venceras (Merge)");
                    liberar_lista(d3);

                    Persona* d4 = copiar_lista(datos_maestros);
                    tiempos[3] = medir_tiempo(ordenar_quick_sort, &d4, "Divide y Venceras (Quick)");
                    liberar_lista(d4);

                    if (N <= 8) {
                        Persona* d5 = copiar_lista(datos_maestros);
                        tiempos[4] = medir_tiempo(ordenar_backtracking, &d5, "Backtracking");
                        liberar_lista(d5);
                        num_algoritmos = 5;
                    } else {
                        printf(ANSI_COLOR_CYAN "│" ANSI_COLOR_RED " Omitiendo Backtracking en la tabla por seguridad (N > 8).  " ANSI_COLOR_CYAN "│\n" ANSI_COLOR_RESET);
                    }
                    printf(ANSI_COLOR_CYAN "╰──────────────────────────────────────────────────────────────╯\n" ANSI_COLOR_RESET);
                    
                    dibujar_grafica(tiempos, nombres, num_algoritmos);
                }
                break;

            case 4:
                if (datos_maestros == NULL) {
                    printf("No hay datos generados.\n");
                } else {
                    mostrar_submenu();
                    int sub_opcion;
                    if (scanf("%d", &sub_opcion) == 1) {
                        Persona* d_test = copiar_lista(datos_maestros);
                        switch (sub_opcion) {
                            case 1:
                                medir_tiempo(ordenar_fuerza_bruta, &d_test, "Fuerza Bruta");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            case 2:
                                medir_tiempo(ordenar_codicioso, &d_test, "Algoritmo Codicioso");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            case 3:
                                medir_tiempo(ordenar_divide_y_venceras, &d_test, "Divide y Venceras (Merge)");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            case 4:
                                medir_tiempo(ordenar_quick_sort, &d_test, "Divide y Venceras (Quick)");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            case 5:
                                if (N > 8) {
                                    printf("CUIDADO: N=%d es muy grande para Backtracking (sugerido <= 6). Se podria congelar.\n", N);
                                }
                                medir_tiempo(ordenar_backtracking, &d_test, "Backtracking");
                                menu_visualizar_ordenados(d_test, N);
                                break;
                            default:
                                printf("Opcion invalida.\n");
                                break;
                        }
                        liberar_lista(d_test);
                    } else {
                        while(getchar() != '\n');
                    }
                }
                break;

            case 5:
                printf(ANSI_COLOR_YELLOW "Saliendo del programa...\n" ANSI_COLOR_RESET);
                break;

            default:
                printf(ANSI_COLOR_RED "Opcion invalida. Intente de nuevo.\n" ANSI_COLOR_RESET);
                break;
        }
        if (opcion != 5) pausar();
    }

    if (datos_maestros != NULL) liberar_lista(datos_maestros);
    return 0;
}
