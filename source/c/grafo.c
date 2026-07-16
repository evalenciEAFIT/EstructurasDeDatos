// ==========================================
// ESTRUCTURA DE DATOS: GRAFO (Matriz de Adyacencia)
// ==========================================
// Explicación Detallada:
// Otra forma común de representar un grafo en programación es usando una matriz 2D (Matriz de Adyacencia).
// Las filas y columnas representan los vértices.
// Si hay una arista (conexión) entre el vértice 'i' y el vértice 'j', entonces matriz[i][j] = 1.
// Si no están conectados, es 0.
// Ventaja: Es extremadamente rápido (O(1)) verificar si dos nodos están conectados.
// Desventaja: Desperdicia memoria si hay muchas filas pero pocas conexiones reales (grafos dispersos).

#include <stdio.h>
#define VERTICES 4 // Grafo fijo de 4 nodos para el ejemplo: 0,1,2,3

// Inicializar Grafo
// Proceso: Rellena toda la matriz 2D con 0 indicando que no hay conexiones aún.
void inicializar(int grafo[VERTICES][VERTICES]) {
    for(int i = 0; i < VERTICES; i++) {
        for(int j = 0; j < VERTICES; j++) {
            grafo[i][j] = 0;
        }
    }
}

// INSERCIÓN (Agregar Arista)
// Proceso:
// Asignamos 1 en la intersección de u y v.
// Al ser un Grafo NO dirigido, la matriz es simétrica, por tanto también 
// asignamos 1 en la intersección de v y u.
void agregarArista(int grafo[VERTICES][VERTICES], int u, int v) {
    grafo[u][v] = 1;
    grafo[v][u] = 1; 
}

// RECORRIDO (Impresión de la Matriz)
// Proceso: Imprime la representación tabular visual de las conexiones del grafo.
void recorrer(int grafo[VERTICES][VERTICES]) {
    printf("Matriz de Adyacencia (Nodos 0 al %d):\n", VERTICES-1);
    for(int i = 0; i < VERTICES; i++) {
        printf("Nodo %d -> [ ", i);
        for(int j = 0; j < VERTICES; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("]\n");
    }
}

int main() {
    int grafo[VERTICES][VERTICES];
    inicializar(grafo);
    
    // Supongamos que 0=A, 1=B, 2=C, 3=D
    agregarArista(grafo, 0, 1); // Conecta 0 con 1
    agregarArista(grafo, 0, 2); // Conecta 0 con 2
    agregarArista(grafo, 1, 3); // Conecta 1 con 3
    
    recorrer(grafo);
    return 0;
}