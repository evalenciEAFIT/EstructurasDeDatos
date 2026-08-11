/**
 * Algoritmo: Selection Sort (Enfoque Codicioso / Greedy)
 * Creador: Algoritmo tradicional de la historia de la computacion.
 * Intencion: En cada iteracion, tomar la "decision localmente optima" (codiciosa) 
 *            de buscar el elemento mas pequeno del arreglo restante y colocarlo en su
 *            posicion final. Complejidad O(N^2).
 */
#include <stddef.h>
#include <string.h>
#include "lista.h"

void sort_greedy(Persona** head_ref) {
    Persona* temp = *head_ref; // Nodo actual a posicionar
    
    // Iteramos por toda la lista buscando la posicion definitiva de cada elemento
    while (temp != NULL) {
        Persona* min = temp;       // Asumimos que el nodo actual es el minimo
        Persona* r = temp->next;   // Puntero para explorar el resto de la lista
        
        // Buscar linealmente el verdadero minimo en la lista restante
        while (r != NULL) {
            if (r->edad < min->edad) {
                min = r; // Actualizar el nuevo minimo encontrado
            }
            r = r->next;
        }
        
        // Si el minimo encontrado es diferente al actual, intercambiamos los valores
        if (min != temp) {
            char temp_name[32];
            int temp_edad = temp->edad;
            strcpy(temp_name, temp->nombre); // Respaldar actual
            
            temp->edad = min->edad;          // Asignar minimo al actual
            strcpy(temp->nombre, min->nombre);
            
            min->edad = temp_edad;           // Asignar respaldo al minimo
            strcpy(min->nombre, temp_name);
        }
        temp = temp->next; // Avanzar para fijar la posicion del siguiente elemento
    }
}
