/**
 * Algoritmo: Bubble Sort (Fuerza Bruta)
 * Creador: Algoritmo clasico, popularizado en las decadas de 1950 y 1960. 
 * Intencion: Ordenar la lista adyacentemente comparando pares sucesivos, empujando
 *            el valor mas grande hacia el final iterativamente. Es ineficiente 
 *            (O(N^2)) pero muy simple de entender y programar.
 */
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "lista.h"

void sort_brute_force(Persona** head_ref) {
    if (*head_ref == NULL) return; // Si la lista esta vacia, no hay nada que ordenar
    
    bool swapped;
    Persona* ptr1;
    Persona* lptr = NULL; // Marca el limite final de la lista ya ordenada

    do {
        swapped = false; // Bandera para saber si se hizo algun intercambio en esta pasada
        ptr1 = *head_ref; // Empezamos desde la cabeza de la lista

        while (ptr1->next != lptr) { // Recorremos hasta el elemento ya ordenado
            if (ptr1->edad > ptr1->next->edad) { // Comparar edades adyacentes
                // Intercambiar datos entre nodos sin romper los punteros
                char temp_name[32];
                int temp_edad = ptr1->edad;
                strcpy(temp_name, ptr1->nombre); // Respaldar nodo 1
                
                ptr1->edad = ptr1->next->edad;   // Mover nodo 2 al nodo 1
                strcpy(ptr1->nombre, ptr1->next->nombre);
                
                ptr1->next->edad = temp_edad;    // Asignar respaldo al nodo 2
                strcpy(ptr1->next->nombre, temp_name);
                
                swapped = true; // Hubo al menos un intercambio
            }
            ptr1 = ptr1->next; // Avanzar al siguiente nodo
        }
        lptr = ptr1; // El ultimo elemento comparado ya es el mayor, no se vuelve a tocar
    } while (swapped); // Repetir hasta que no haya intercambios
}
