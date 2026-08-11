/**
 * Algoritmo: Bogo Sort (Permutaciones via Backtracking)
 * Creador: H. Muller (Aprox. 1956, concepto de ordenamiento destructivo / al azar)
 * Intencion: Demostrar un paradigma exhaustivo explorando permutaciones posibles hasta 
 *            toparse accidentalmente con el arreglo ordenado. Tiene complejidad factorial
 *            O(N!), volviendose inutil y perjudicial a partir de N=10.
 */
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"

// Verifica linealmente si toda la lista enlazada ya se encuentra ordenada
bool is_sorted(Persona* head) {
    if (head == NULL) return true;
    Persona* curr = head;
    while (curr->next != NULL) {
        // Si encontramos un elemento mayor que su sucesor, la lista NO esta ordenada
        if (curr->edad > curr->next->edad) return false;
        curr = curr->next;
    }
    return true; // Todos los elementos respetaron el orden ascendente
}

// Intercambia la informacion contenida entre dos nodos Persona
void swap_personas(Persona* a, Persona* b) {
    char temp_name[32];
    int temp_edad = a->edad;
    strcpy(temp_name, a->nombre);
    
    a->edad = b->edad;
    strcpy(a->nombre, b->nombre);
    
    b->edad = temp_edad;
    strcpy(b->nombre, temp_name);
}

// Genera recursivamente permutaciones de la lista empleando retroceso (backtracking)
bool backtrack_permutations(Persona* head, Persona* current) {
    // Si llegamos al final de una permutacion, verificar si esta combinacion resulto ordenada
    if (current == NULL) return is_sorted(head); 
    
    Persona* temp = current;
    while (temp != NULL) {
        // Tomar una decision (intercambio)
        swap_personas(current, temp);
        
        // Explorar el sub-arbol derivado de esta decision
        if (backtrack_permutations(head, current->next)) {
            return true; // Se hallo la permutacion perfecta, detener recursion
        }
        
        // Deshacer la decision (Backtrack) para probar la siguiente combinacion
        swap_personas(current, temp);
        temp = temp->next;
    }
    return false;
}

// Funcion principal de acceso al algoritmo
void sort_backtracking(Persona** head_ref) {
    // Iniciar la exploracion en arbol desde la cabeza de la lista
    backtrack_permutations(*head_ref, *head_ref);
}
