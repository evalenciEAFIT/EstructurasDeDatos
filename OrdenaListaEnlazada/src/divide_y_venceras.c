/**
 * Algoritmos: Merge Sort y Quick Sort (Paradigma de Divide y Venceras)
 * Creadores: 
 *   - Merge Sort: John von Neumann (1945)
 *   - Quick Sort: Tony Hoare (1959)
 * Intencion: Dividir el problema en sub-problemas mas pequenos hasta llegar a casos base
 *            triviales (listas de tamano 1), y luego combinar (Merge) o particionar (Quick)
 *            obteniendo una complejidad altamente eficiente O(N log N).
 */
#include <stddef.h>
#include "lista.h"

// ------------------------- MERGE SORT ------------------------- //

// Mezcla (merge) de dos listas enlazadas que ya estan ordenadas
Persona* fusion_ordenada(Persona* a, Persona* b) {
    if (a == NULL) return b; // Caso base 1
    if (b == NULL) return a; // Caso base 2
    
    Persona* result = NULL;
    
    // Comparar los nodos iniciales y anadir recursivamente el menor
    if (a->edad <= b->edad) {
        result = a;
        result->siguiente = fusion_ordenada(a->siguiente, b); // Continuar con la cola de 'a'
    } else {
        result = b;
        result->siguiente = fusion_ordenada(a, b->siguiente); // Continuar con la cola de 'b'
    }
    return result; // Retornar la nueva lista fusionada
}

// Divide una lista enlazada en dos mitades (front y back)
void dividir_frente_atras(Persona* origen, Persona** ref_frente, Persona** ref_atras) {
    Persona* rapido = origen->siguiente; // Puntero rapido avanza de 2 en 2
    Persona* lento = origen;       // Puntero lento avanza de 1 en 1
    
    while (rapido != NULL) {
        rapido = rapido->siguiente;
        if (rapido != NULL) {
            lento = lento->siguiente;
            rapido = rapido->siguiente;
        }
    }
    // Cuando el rapido llega al final, el lento esta justo en el medio
    *ref_frente = origen;
    *ref_atras = lento->siguiente;
    lento->siguiente = NULL; // Cortar el enlace para separar ambas listas
}

// Funcion principal de Merge Sort
void ordenar_divide_y_venceras(Persona** ref_cabeza) {
    Persona* cabeza = *ref_cabeza;
    if ((cabeza == NULL) || (cabeza->siguiente == NULL)) return; // Caso base: tamano 0 o 1
    
    Persona *a, *b;
    dividir_frente_atras(cabeza, &a, &b); // 1. DIVIDIR: separar en dos listas
    
    ordenar_divide_y_venceras(&a);    // 2. VENCER: ordenar recursivamente la lista A
    ordenar_divide_y_venceras(&b);    // 2. VENCER: ordenar recursivamente la lista B
    
    *ref_cabeza = fusion_ordenada(a, b);  // 3. COMBINAR: fusionar ambas listas ordenadas
}

// ------------------------- QUICK SORT ------------------------- //

// Retorna el ultimo nodo de la lista
Persona* obtener_cola(Persona* cur) {
    while (cur != NULL && cur->siguiente != NULL) cur = cur->siguiente;
    return cur;
}

// Particionar la lista usando el ultimo nodo como pivote
Persona* particion(Persona* cabeza, Persona* fin, Persona** nueva_cabeza, Persona** nuevo_fin) {
    Persona* pivote = fin;   // El ultimo elemento es el pivote
    Persona* anterior = NULL;
    Persona* cur = cabeza;
    Persona* cola = pivote;
    
    while (cur != pivote) { // Recorrer hasta llegar al pivote
        if (cur->edad < pivote->edad) {
            if ((*nueva_cabeza) == NULL) (*nueva_cabeza) = cur; // Mantener la nueva cabeza
            anterior = cur;
            cur = cur->siguiente; // Elemento menor se queda en su lugar (izquierda)
        } else { // Si el elemento es mayor, se mueve a la derecha del pivote
            if (anterior) anterior->siguiente = cur->siguiente;
            Persona* tmp = cur->siguiente;
            cur->siguiente = NULL;
            cola->siguiente = cur; // Insertarlo al final
            cola = cur;
            cur = tmp;
        }
    }
    
    if ((*nueva_cabeza) == NULL) (*nueva_cabeza) = pivote; // Si todos fueron mayores
    (*nuevo_fin) = cola;
    return pivote; // Retornar el pivote en su posicion final definitiva
}

// Logica recursiva principal de Quick Sort
Persona* quick_sort_recursivo(Persona* cabeza, Persona* fin) {
    if (!cabeza || cabeza == fin) return cabeza; // Caso base
    
    Persona *nueva_cabeza = NULL, *nuevo_fin = NULL;
    Persona* pivote = particion(cabeza, fin, &nueva_cabeza, &nuevo_fin); // Particionar lista
    
    // Si el pivote es el elemento mas pequeno, saltar recursion izquierda
    if (nueva_cabeza != pivote) {
        Persona* tmp = nueva_cabeza;
        while (tmp->siguiente != pivote) tmp = tmp->siguiente; // Buscar el penultimo
        tmp->siguiente = NULL; // Cortar temporalmente
        
        // Ordenar recursivamente la mitad izquierda
        nueva_cabeza = quick_sort_recursivo(nueva_cabeza, tmp);
        
        // Reconectar
        tmp = obtener_cola(nueva_cabeza);
        tmp->siguiente = pivote;
    }
    
    // Ordenar recursivamente la mitad derecha
    pivote->siguiente = quick_sort_recursivo(pivote->siguiente, nuevo_fin);
    return nueva_cabeza;
}

void ordenar_quick_sort(Persona** ref_cabeza) {
    *ref_cabeza = quick_sort_recursivo(*ref_cabeza, obtener_cola(*ref_cabeza));
}
