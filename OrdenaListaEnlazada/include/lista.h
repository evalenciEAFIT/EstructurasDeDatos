/**
 * Cabecera Principal del Proyecto (Header File)
 * Define las estructuras de datos fundamentales y expone todas las firmas 
 * y prototipos de funciones consumibles globalmente en toda la arquitectura del programa.
 */
#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

// Lista enlazada simple que aloja la entidad de negocio: Persona
typedef struct Persona {
    char nombre[32];      // Nombre completo en formato string corto
    int edad;             // Valor por el que se ordenan los algoritmos
    struct Persona* siguiente; // Puntero recursivo que une a la siguiente celda
} Persona;

// Operaciones Estructurales
Persona* crear_persona(const char* nombre, int edad);
void insertar_persona(Persona** cabeza, const char* nombre, int edad);
void liberar_lista(Persona* cabeza);
Persona* generar_datos(int num_elementos);
Persona* copiar_lista(Persona* cabeza);

// Operaciones Auxiliares y Visualizacion
double medir_tiempo(void (*funcion_ordenamiento)(Persona**), Persona** datos, const char* nombre_algoritmo);
void imprimir_primeros_n_elementos(Persona* cabeza, int n, const char* etiqueta);
void imprimir_ultimos_n_elementos(Persona* cabeza, int n, const char* etiqueta);

// Paradigmas de Ordenamiento
void ordenar_fuerza_bruta(Persona** ref_cabeza);
void ordenar_codicioso(Persona** ref_cabeza);
void ordenar_divide_y_venceras(Persona** ref_cabeza); // Merge Sort
void ordenar_quick_sort(Persona** ref_cabeza);         // Quick Sort
void ordenar_backtracking(Persona** ref_cabeza);      // Bogo Sort

#endif // LISTA_H
1