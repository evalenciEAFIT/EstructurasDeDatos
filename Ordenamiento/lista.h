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
    struct Persona* next; // Puntero recursivo que une a la siguiente celda
} Persona;

// Operaciones Estructurales
Persona* create_persona(const char* nombre, int edad);
void insert_persona(Persona** head, const char* nombre, int edad);
void free_list(Persona* head);
Persona* generate_data(int num_elements);
Persona* copy_list(Persona* head);

// Operaciones Auxiliares y Visualizacion
void measure_time(void (*sort_function)(Persona**), Persona** data, const char* name);
void print_first_n_elements(Persona* head, int n, const char* label);
void print_last_n_elements(Persona* head, int n, const char* label);

// Firmas de Paradigmas de Ordenamiento
void sort_brute_force(Persona** head_ref);
void sort_greedy(Persona** head_ref);
void sort_divide_and_conquer(Persona** headRef); // Merge Sort
void sort_quick_sort(Persona** headRef);         // Quick Sort
void sort_backtracking(Persona** head_ref);      // Bogo Sort

#endif // LISTA_H
