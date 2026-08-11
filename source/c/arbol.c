// ==========================================
// ESTRUCTURA DE DATOS: ÁRBOL BINARIO DE BÚSQUEDA
// ==========================================
// Explicación Detallada:
// En C, usamos punteros para enlazar los nodos, parecido a la lista enlazada,
// pero con dos ramas. El nodo raíz es nuestro punto de entrada al árbol.
// La regla es: hijos izquierdos < padre < hijos derechos.

#include <stdio.h>
#include <stdlib.h>

// Definición de Nodo
struct Nodo {
    int dato;
    struct Nodo *izq, *der;
};

// CREAR NODO
// Función auxiliar que pide memoria y setea valores por defecto para los hijos (NULL).
struct Nodo* crearNodo(int dato) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo->dato = dato;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

// INSERCIÓN
// Proceso (Recursivo):
// Recibe un nodo raíz local. Si está vacío, ahí inserta el nuevo nodo y lo devuelve.
// Si el dato es menor, llama recursivamente a 'insertar' en la rama izquierda.
// Si es mayor, lo hace en la rama derecha.
struct Nodo* insertar(struct Nodo* nodo, int dato) {
    if (nodo == NULL) return crearNodo(dato); // Espacio libre encontrado
    
    if (dato < nodo->dato)
        nodo->izq = insertar(nodo->izq, dato); // Bajar por izquierda
    else if (dato > nodo->dato)
        nodo->der = insertar(nodo->der, dato); // Bajar por derecha
        
    return nodo;
}

// RECORRIDO (Inorden)
// Proceso: 
// 1. Recorrer rama izquierda
// 2. Visitar el nodo
// 3. Recorrer rama derecha
// Esto garantiza imprimir los valores ordenados ascendentemente.
void inorden(struct Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izq);
        printf("%d ", raiz->dato);
        inorden(raiz->der);
    }
}

// BÚSQUEDA
// Proceso recursivo similar a la inserción, navegando según si el dato 
// es menor (izquierda) o mayor (derecha) al valor del nodo actual.
int buscar(struct Nodo* raiz, int dato) {
    if (raiz == NULL) return 0; // Falso, llegó al final y no lo encontró
    if (raiz->dato == dato) return 1; // Verdadero, hallado
    
    if (dato < raiz->dato)
        return buscar(raiz->izq, dato); // Buscar a la izquierda
    else
        return buscar(raiz->der, dato); // Buscar a la derecha
}

int main() {
    struct Nodo* raiz = NULL;
    // La primera inserción inicializa la raíz
    raiz = insertar(raiz, 50);
    insertar(raiz, 30);
    insertar(raiz, 70);
    insertar(raiz, 20);
    insertar(raiz, 40);
    
    printf("Recorrido inorden (ordenado): ");
    inorden(raiz);
    
    printf("\n¿El 40 está en el árbol?: %s\n", buscar(raiz, 40) ? "Sí" : "No");
    return 0;
}