/**
 * Implementacion de Estructura de Datos Base
 * Contiene todas las operaciones CRUD y utilidades matematicas/impresion para
 * soportar la lista enlazada simple de Personas.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"

// Inicializa en memoria heap un nodo Persona completamente nuevo
Persona* create_persona(const char* nombre, int edad) {
    Persona* new_node = (Persona*)malloc(sizeof(Persona)); // Asignar memoria RAM
    strncpy(new_node->nombre, nombre, 31); // Copiar nombre de forma segura
    new_node->nombre[31] = '\0';           // Asegurar termino de cadena
    new_node->edad = edad;                 // Guardar propiedad edad
    new_node->next = NULL;                 // Aislado por defecto
    return new_node;
}

// Anade una nueva Persona a la cabeza (inicio) de la lista enlazada (O(1))
void insert_persona(Persona** head, const char* nombre, int edad) {
    Persona* new_node = create_persona(nombre, edad);
    new_node->next = *head; // El nuevo nodo apunta al antiguo inicio
    *head = new_node;       // El nuevo nodo se convierte en el nuevo inicio
}

// Libera toda la memoria RAM ocupada por la lista iterativamente
void free_list(Persona* head) {
    Persona* curr = head;
    while (curr != NULL) {
        Persona* temp = curr;
        curr = curr->next;
        free(temp); // Retornar la memoria del nodo al Sistema Operativo
    }
}

// Genera un arreglo de N datos ficticios realistas para realizar pruebas de carga
Persona* generate_data(int num_elements) {
    Persona* head = NULL;
    char temp_name[64];
    
    // Arrays estaticos de nombres tipicos en espanol
    const char* nombres[] = {"Juan", "Maria", "Carlos", "Ana", "Luis", "Laura", "Pedro", "Sofia", "Diego", "Carmen"};
    const char* apellidos[] = {"Garcia", "Martinez", "Lopez", "Sanchez", "Perez", "Gomez", "Martin", "Jimenez", "Ruiz", "Hernandez"};

    for (int i = 0; i < num_elements; i++) {
        // Armar aleatoriamente Nombre + Apellido
        sprintf(temp_name, "%s %s", nombres[rand() % 10], apellidos[rand() % 10]);
        // Restringir la edad para que sea estrictamente mayor a 18 y menor a 100 [19, 99]
        int random_edad = 19 + (rand() % 81);
        insert_persona(&head, temp_name, random_edad);
    }
    return head;
}

// Crea una copia exacta (Deep Copy) de la lista enlazada para pruebas aisladas
Persona* copy_list(Persona* head) {
    if (head == NULL) return NULL; // Si es nulo no hay que copiar
    
    Persona* new_head = create_persona(head->nombre, head->edad);
    Persona* curr_orig = head->next;
    Persona* curr_new = new_head;
    
    // Recorremos secuencialmente clonando las celdas
    while(curr_orig != NULL) {
        curr_new->next = create_persona(curr_orig->nombre, curr_orig->edad);
        curr_new = curr_new->next;
        curr_orig = curr_orig->next;
    }
    return new_head;
}

// Mide estadisticamente cuanto tarda un algoritmo al inyectarse por puntero
void measure_time(void (*sort_function)(Persona**), Persona** data, const char* name) {
    clock_t start = clock(); // Registrar instante de inicio
    sort_function(data);     // Ejecutar la rutina de ordenamiento externa
    clock_t end = clock();   // Registrar instante final
    
    // Calcular e imprimir en consola el lapso transcurrido
    printf("Tiempo de %-30s : %f segundos\n", name, (double)(end - start) / CLOCKS_PER_SEC);
}

// Visualiza los primeros 'n' elementos desde la cabeza
void print_first_n_elements(Persona* head, int n, const char* label) {
    printf("%s: [", label);
    Persona* curr = head;
    int count = 0;
    while (curr != NULL && count < n) {
        printf("%s(%d)", curr->nombre, curr->edad);
        curr = curr->next;
        if (curr != NULL && count < n - 1) printf(", ");
        count++;
    }
    if (curr != NULL) printf(", ...");
    printf("]\n");
}

// Localiza el final de la lista y muestra solo los ultimos 'n' elementos
void print_last_n_elements(Persona* head, int n, const char* label) {
    int total = 0;
    Persona* curr = head;
    
    // Calcular el tamano total de la lista (O(N))
    while(curr != NULL) { total++; curr = curr->next; }
    
    int start_index = total - n; // Definir a partir de donde imprimir
    if (start_index < 0) start_index = 0;

    printf("%s: [", label);
    if (start_index > 0) printf("..., ");
    
    curr = head;
    int count = 0;
    while (curr != NULL) {
        if (count >= start_index) {
            printf("%s(%d)", curr->nombre, curr->edad); // Imprimir los datos
            if (curr->next != NULL) printf(", ");
        }
        curr = curr->next;
        count++;
    }
    printf("]\n");
}
