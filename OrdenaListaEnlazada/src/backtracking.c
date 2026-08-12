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
bool esta_ordenado(Persona* cabeza) {
    if (cabeza == NULL) return true;
    Persona* actual = cabeza;
    while (actual->siguiente != NULL) {
        // Si encontramos un elemento mayor que su sucesor, la lista NO esta ordenada
        if (actual->edad > actual->siguiente->edad) return false;
        actual = actual->siguiente;
    }
    return true; // Todos los elementos respetaron el orden ascendente
}

// Intercambia la informacion contenida entre dos nodos Persona
void intercambiar_personas(Persona* a, Persona* b) {
    char nombre_temporal[32];
    int temp_edad = a->edad;
    strcpy(nombre_temporal, a->nombre);
    
    a->edad = b->edad;
    strcpy(a->nombre, b->nombre);
    
    b->edad = temp_edad;
    strcpy(b->nombre, nombre_temporal);
}

// Genera recursivamente permutaciones de la lista empleando retroceso (backtracking)
bool permutaciones_backtracking(Persona* cabeza, Persona* actual) {
    // Si llegamos al final de una permutacion, verificar si esta combinacion resulto ordenada
    if (actual == NULL) return esta_ordenado(cabeza); 
    
    Persona* temporal = actual;
    while (temporal != NULL) {
        // Tomar una decision (intercambio)
        intercambiar_personas(actual, temporal);
        
        // Explorar el sub-arbol derivado de esta decision
        if (permutaciones_backtracking(cabeza, actual->siguiente)) {
            return true; // Se hallo la permutacion perfecta, detener recursion
        }
        
        // Deshacer la decision (Backtrack) para probar la siguiente combinacion
        intercambiar_personas(actual, temporal);
        temporal = temporal->siguiente;
    }
    return false;
}

// Funcion principal de acceso al algoritmo
void ordenar_backtracking(Persona** ref_cabeza) {
    // Iniciar la exploracion en arbol desde la cabeza de la lista
    permutaciones_backtracking(*ref_cabeza, *ref_cabeza);
}
