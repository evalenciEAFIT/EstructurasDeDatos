// ==========================================
// ESTRUCTURA DE DATOS: LISTA ENLAZADA
// ==========================================
// Explicación Detallada:
// Una lista enlazada permite almacenar datos de forma dinámica en la memoria.
// A diferencia de un arreglo estático, no necesitamos conocer la cantidad de elementos de antemano.
// Cada "Nodo" se aloja en memoria dinámica (usando malloc) y se enlaza con el siguiente
// mediante el puntero 'siguiente'.

#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del Nodo
struct Nodo {
    int dato;               // Almacena el valor numérico
    struct Nodo* siguiente; // Puntero al siguiente nodo en la cadena
};

// INSERCIÓN (al final)
// Proceso:
// 1. Asignamos memoria para el nuevo nodo con 'malloc'.
// 2. Inicializamos su 'dato' y hacemos que 'siguiente' apunte a NULL (ya que será el último).
// 3. Si la lista está vacía (*cabeza == NULL), el nuevo nodo será la cabeza.
// 4. Si ya tiene elementos, usamos un puntero auxiliar ('ultimo') para recorrer la lista
//    hasta llegar al final, y luego enlazamos el último nodo con el nuevo.
void insertar(struct Nodo** cabeza, int nuevo_dato) {
    // 1. Crear nuevo nodo
    struct Nodo* nuevo_nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct Nodo* ultimo = *cabeza; // Puntero auxiliar
    
    // 2. Inicializar valores
    nuevo_nodo->dato = nuevo_dato;
    nuevo_nodo->siguiente = NULL;
    
    // 3. Si está vacía, hacer del nuevo nodo la cabeza
    if (*cabeza == NULL) {
        *cabeza = nuevo_nodo;
        return;
    }
    
    // 4. Recorrer hasta el final y enlazar
    while (ultimo->siguiente != NULL) {
        ultimo = ultimo->siguiente;
    }
    ultimo->siguiente = nuevo_nodo;
}

// RECORRIDO
// Proceso:
// Empezamos desde el primer nodo, e imprimimos su valor.
// Luego avanzamos al nodo siguiente iterativamente hasta que el puntero sea NULL.
void recorrer(struct Nodo* nodo) {
    printf("Lista Enlazada: ");
    while (nodo != NULL) {
        printf("%d -> ", nodo->dato);
        nodo = nodo->siguiente;
    }
    printf("NULL\n");
}

// BÚSQUEDA
// Proceso:
// Compara secuencialmente el valor de cada nodo con el 'dato_buscado'.
// Devuelve 1 (Verdadero) si lo encuentra, o 0 (Falso) si llega al final.
int buscar(struct Nodo* nodo, int dato_buscado) {
    while (nodo != NULL) {
        if (nodo->dato == dato_buscado) return 1;
        nodo = nodo->siguiente;
    }
    return 0;
}

int main() {
    struct Nodo* cabeza = NULL; // La lista inicia vacía
    insertar(&cabeza, 10);
    insertar(&cabeza, 20);
    insertar(&cabeza, 30);
    recorrer(cabeza);
    printf("¿El 20 está en la lista?: %s\n", buscar(cabeza, 20) ? "Sí" : "No");
    return 0;
}