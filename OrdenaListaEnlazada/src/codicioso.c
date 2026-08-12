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

void ordenar_codicioso(Persona** ref_cabeza) {
    Persona* temporal = *ref_cabeza; // Nodo actual a posicionar
    
    // Iteramos por toda la lista buscando la posicion definitiva de cada elemento
    while (temporal != NULL) {
        Persona* min = temporal;       // Asumimos que el nodo actual es el minimo
        Persona* r = temporal->siguiente;   // Puntero para explorar el resto de la lista
        
        // Buscar linealmente el verdadero minimo en la lista restante
        while (r != NULL) {
            if (r->edad < min->edad) {
                min = r; // Actualizar el nuevo minimo encontrado
            }
            r = r->siguiente;
        }
        
        // Si el minimo encontrado es diferente al actual, intercambiamos los valores
        if (min != temporal) {
            char nombre_temporal[32];
            int temp_edad = temporal->edad;
            strcpy(nombre_temporal, temporal->nombre); // Respaldar actual
            
            temporal->edad = min->edad;          // Asignar minimo al actual
            strcpy(temporal->nombre, min->nombre);
            
            min->edad = temp_edad;           // Asignar respaldo al minimo
            strcpy(min->nombre, nombre_temporal);
        }
        temporal = temporal->siguiente; // Avanzar para fijar la posicion del siguiente elemento
    }
}
