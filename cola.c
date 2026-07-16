// ==========================================
// ESTRUCTURA DE DATOS: COLA (QUEUE)
// ==========================================
// Explicación Detallada:
// Implementación estática de una Cola circular con arreglos en C.
// Se usan dos índices:
// - frente: apunta al primer elemento que debe ser extraído (desencolado).
// - final: apunta al último espacio ocupado donde se insertó un dato.
// FIFO: Primero en entrar, primero en salir.

#include <stdio.h>
#define MAX 100 // Límite estático

struct Cola {
    int frente, final;
    int arr[MAX];
};

// INSERCIÓN (Encolar)
// Proceso:
// 1. Verificar si la cola está llena.
// 2. Si es el primer elemento, inicializamos el frente en 0.
// 3. Incrementamos el índice 'final' y guardamos ahí el dato.
void encolar(struct Cola* c, int dato) {
    if (c->final == MAX - 1) {
        printf("Error: Cola llena\n");
        return;
    }
    if (c->frente == -1) c->frente = 0; // Configurar frente la primera vez
    
    c->final++; // Avanzamos el puntero final
    c->arr[c->final] = dato;
    printf("Encolado al final: %d\n", dato);
}

// ELIMINACIÓN (Desencolar)
// Proceso:
// 1. Verificamos si la cola está vacía (frente es -1, o frente superó al final).
// 2. Extraemos el valor del 'frente' y luego incrementamos el frente,
//    lo que lógicamente elimina el dato.
int desencolar(struct Cola* c) {
    if (c->frente == -1 || c->frente > c->final) {
        printf("Error: Cola vacía\n");
        return -1;
    }
    int extraido = c->arr[c->frente];
    c->frente++; // Avanzamos el frente al siguiente en la fila
    return extraido;
}

// RECORRIDO
// Proceso: Iterar desde el índice 'frente' hasta el índice 'final' para ver a los formados.
void recorrer(struct Cola* c) {
    if (c->frente == -1 || c->frente > c->final) {
        printf("La cola está vacía\n");
        return;
    }
    printf("Cola actual (frente a final): ");
    for (int i = c->frente; i <= c->final; i++) {
        printf("%d ", c->arr[i]);
    }
    printf("\n");
}

int main() {
    struct Cola c;
    c.frente = -1; 
    c.final = -1;
    encolar(&c, 10);
    encolar(&c, 20);
    encolar(&c, 30);
    recorrer(&c);
    printf("Desencolado: %d\n", desencolar(&c));
    recorrer(&c);
    return 0;
}