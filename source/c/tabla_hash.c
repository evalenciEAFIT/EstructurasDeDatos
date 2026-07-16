// ==========================================
// ESTRUCTURA DE DATOS: TABLA HASH 
// (Resolución de colisiones por encadenamiento)
// ==========================================
// Explicación Detallada:
// Implementamos una tabla hash donde la estructura principal es un arreglo de punteros
// a listas enlazadas ('cubetas').
// Cuando ocurre una colisión (dos claves terminan en el mismo índice), el nuevo elemento 
// simplemente se agrega como un nodo más en la lista enlazada de ese índice particular.

#include <stdio.h>
#include <stdlib.h>

#define TAMANO 5 // Un tamaño pequeño generará colisiones más fácil para demostración

// Estructura de Nodo para las Listas Enlazadas de cada cubeta
struct NodoHash {
    int clave;
    int valor;
    struct NodoHash* siguiente;
};

// Estructura principal
struct TablaHash {
    struct NodoHash* cubetas[TAMANO]; // Arreglo de punteros
};

// FUNCIÓN HASH
// Una función muy simple usando módulo para claves numéricas enteras.
int funcionHash(int clave) {
    return clave % TAMANO;
}

// INSERCIÓN
// Proceso:
// 1. Obtener índice con funcionHash.
// 2. Crear un nuevo nodo.
// 3. Insertar el nodo al *principio* de la lista enlazada correspondiente a ese índice.
void insertar(struct TablaHash* th, int clave, int valor) {
    int indice = funcionHash(clave);
    
    struct NodoHash* nuevo = (struct NodoHash*)malloc(sizeof(struct NodoHash));
    nuevo->clave = clave;
    nuevo->valor = valor;
    
    // Lo enlazamos apuntando al que actualmente sea la cabeza de esta cubeta
    nuevo->siguiente = th->cubetas[indice];
    
    // La nueva cabeza es el nodo insertado
    th->cubetas[indice] = nuevo;
}

// BÚSQUEDA
// Proceso:
// Calcula el índice, y recorre la lista enlazada solo de esa posición.
int buscar(struct TablaHash* th, int clave) {
    int indice = funcionHash(clave);
    struct NodoHash* actual = th->cubetas[indice];
    
    while (actual != NULL) {
        if (actual->clave == clave) return actual->valor;
        actual = actual->siguiente;
    }
    return -1; // -1 indicará 'no encontrado'
}

// RECORRIDO
// Visita cada índice del arreglo y recorre toda su lista enlazada.
void recorrer(struct TablaHash* th) {
    printf("Estado de la Tabla Hash:\n");
    for (int i = 0; i < TAMANO; i++) {
        printf(" Índice %d: ", i);
        struct NodoHash* actual = th->cubetas[i];
        while (actual != NULL) {
            printf("[%d -> %d] ", actual->clave, actual->valor);
            actual = actual->siguiente;
        }
        printf("(NULL)\n");
    }
}

int main() {
    struct TablaHash th;
    // Inicializar todos los punteros a NULL
    for (int i = 0; i < TAMANO; i++) th.cubetas[i] = NULL;
    
    insertar(&th, 10, 100); 
    insertar(&th, 15, 150); // 10 y 15 colisionan porque 10%5 = 0 y 15%5 = 0
    insertar(&th, 12, 120); // 12%5 = 2
    
    recorrer(&th);
    printf("\nBuscando clave 15: %d\n", buscar(&th, 15));
    return 0;
}