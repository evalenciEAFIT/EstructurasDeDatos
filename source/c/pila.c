// ==========================================
// ESTRUCTURA DE DATOS: PILA (STACK)
// ==========================================
// Explicación Detallada:
// Esta implementación en C utiliza un arreglo estático para simular la pila.
// Se mantiene un entero 'tope' que actúa como índice apuntando siempre al elemento
// que está en la cima de la pila. 
// LIFO: El último en entrar es el primero en salir.

#include <stdio.h>
#include <stdlib.h>
#define MAX 100 // Capacidad máxima de la pila estática

struct Pila {
    int tope;       // Índice del elemento más alto en la pila
    int arr[MAX];   // Arreglo donde se guardan los datos
};

// INSERCIÓN (Apilar / Push)
// Proceso:
// 1. Verificamos que el arreglo no esté lleno (tope >= MAX - 1).
// 2. Si hay espacio, incrementamos el índice 'tope' y colocamos el nuevo dato en esa posición.
void apilar(struct Pila* p, int dato) {
    if (p->tope >= MAX - 1) {
        printf("Error: La Pila está llena (Overflow)\n");
        return;
    }
    p->tope++;                // Mover el tope hacia arriba
    p->arr[p->tope] = dato;   // Insertar
    printf("Apilado en la cima: %d\n", dato);
}

// ELIMINACIÓN (Desapilar / Pop)
// Proceso:
// 1. Verificamos si la pila está vacía revisando si el tope es menor a 0.
// 2. Si no está vacía, extraemos el valor que está en el 'tope' y lo decrementamos, 
//    "borrando" lógicamente el elemento de la pila.
int desapilar(struct Pila* p) {
    if (p->tope < 0) {
        printf("Error: La Pila está vacía (Underflow)\n");
        return -1;
    }
    int dato_extraido = p->arr[p->tope];
    p->tope--; // Bajar el tope
    return dato_extraido;
}

// RECORRIDO
// Proceso: Iteramos sobre el arreglo en reversa, desde el 'tope' hasta el índice 0,
// para mostrar primero el elemento más reciente.
void recorrer(struct Pila* p) {
    printf("Pila actual (cima a base): ");
    for (int i = p->tope; i >= 0; i--) {
        printf("%d ", p->arr[i]);
    }
    printf("\n");
}

int main() {
    struct Pila p;
    p.tope = -1; // Al iniciar, el tope es -1 indicando que está vacía.
    apilar(&p, 1);
    apilar(&p, 2);
    apilar(&p, 3);
    recorrer(&p);
    printf("Elemento desapilado: %d\n", desapilar(&p));
    recorrer(&p);
    return 0;
}