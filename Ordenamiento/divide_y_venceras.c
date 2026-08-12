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
Persona* sorted_merge(Persona* a, Persona* b) {
    if (a == NULL) return b; // Caso base 1
    if (b == NULL) return a; // Caso base 2
    
    Persona* result = NULL;
    
    // Comparar los nodos iniciales y anadir recursivamente el menor
    if (a->edad <= b->edad) {
        result = a;
        result->next = sorted_merge(a->next, b); // Continuar con la cola de 'a'
    } else {
        result = b;
        result->next = sorted_merge(a, b->next); // Continuar con la cola de 'b'
    }
    return result; // Retornar la nueva lista fusionada
}

// Divide una lista enlazada en dos mitades (front y back)
void front_back_split(Persona* source, Persona** frontRef, Persona** backRef) {
    Persona* fast = source->next; // Puntero rapido avanza de 2 en 2
    Persona* slow = source;       // Puntero lento avanza de 1 en 1
    
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    // Cuando el rapido llega al final, el lento esta justo en el medio
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL; // Cortar el enlace para separar ambas listas
}

// Funcion principal de Merge Sort
void sort_divide_and_conquer(Persona** headRef) {
    Persona* head = *headRef;
    if ((head == NULL) || (head->next == NULL)) return; // Caso base: tamano 0 o 1
    
    Persona *a, *b;
    front_back_split(head, &a, &b); // 1. DIVIDIR: separar en dos listas
    
    sort_divide_and_conquer(&a);    // 2. VENCER: ordenar recursivamente la lista A
    sort_divide_and_conquer(&b);    // 2. VENCER: ordenar recursivamente la lista B
    
    *headRef = sorted_merge(a, b);  // 3. COMBINAR: fusionar ambas listas ordenadas
}

// ------------------------- QUICK SORT ------------------------- //

// Retorna el ultimo nodo de la lista
Persona* get_tail(Persona* cur) {
    while (cur != NULL && cur->next != NULL) cur = cur->next;
    return cur;
}

// Particionar la lista usando el ultimo nodo como pivote
Persona* partition(Persona* head, Persona* end, Persona** newHead, Persona** newEnd) {
    Persona* pivot = end;   // El ultimo elemento es el pivote
    Persona* prev = NULL;
    Persona* cur = head;
    Persona* tail = pivot;
    
    while (cur != pivot) { // Recorrer hasta llegar al pivote
        if (cur->edad < pivot->edad) {
            if ((*newHead) == NULL) (*newHead) = cur; // Mantener la nueva cabeza
            prev = cur;
            cur = cur->next; // Elemento menor se queda en su lugar (izquierda)
        } else { // Si el elemento es mayor, se mueve a la derecha del pivote
            if (prev) prev->next = cur->next;
            Persona* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur; // Insertarlo al final
            tail = cur;
            cur = tmp;
        }
    }
    
    if ((*newHead) == NULL) (*newHead) = pivot; // Si todos fueron mayores
    (*newEnd) = tail;
    return pivot; // Retornar el pivote en su posicion final definitiva
}

// Logica recursiva principal de Quick Sort
Persona* quick_sort_recur(Persona* head, Persona* end) {
    if (!head || head == end) return head; // Caso base
    
    Persona *newHead = NULL, *newEnd = NULL;
    Persona* pivot = partition(head, end, &newHead, &newEnd); // Particionar lista
    
    // Si el pivote es el elemento mas pequeno, saltar recursion izquierda
    if (newHead != pivot) {
        Persona* tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next; // Buscar el penultimo
        tmp->next = NULL; // Cortar temporalmente
        
        // Ordenar recursivamente la mitad izquierda
        newHead = quick_sort_recur(newHead, tmp);
        
        // Reconectar
        tmp = get_tail(newHead);
        tmp->next = pivot;
    }
    
    // Ordenar recursivamente la mitad derecha
    pivot->next = quick_sort_recur(pivot->next, newEnd);
    return newHead;
}

void sort_quick_sort(Persona** headRef) {
    *headRef = quick_sort_recur(*headRef, get_tail(*headRef));
}
