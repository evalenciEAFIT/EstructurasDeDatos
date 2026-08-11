#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Librería crucial para manejar la función clock() y medir rendimiento

/*
 * CONCEPTO: RENDIMIENTO (TIEMPO) Y CONSUMO (MEMORIA)
 * En Ciencias de la Computación (EDA - Estructuras de Datos y Algoritmos),
 * no solo importa que el código "funcione", sino evaluar su complejidad 
 * algorítmica (Big O) en relación a los recursos físicos del sistema operativo:
 * 1. CPU (Medido en ticks de reloj / Segundos).
 * 2. RAM (Medido en Bytes asignados dinámicamente).
 */

struct Persona {
    char nombre[50];
    float peso;
    float talla;
};

struct Nodo {
    struct Persona dato;
    struct Nodo* siguiente;
};

// GLOBAL: Acumulador de bytes solicitados a la memoria RAM.
// size_t es el tipo de dato ideal para representar tamaños de bytes.
size_t memoriaTotalAsignada = 0;

struct Nodo* crearNodo(struct Persona nuevaPersona) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: Memoria RAM llena.\n");
        exit(1);
    }
    
    // CONCEPTO: RASTREO DE MEMORIA
    // sizeof(struct Nodo) calcula automáticamente cuántos bytes pesa el bloque.
    // Sumamos esos bytes a nuestra cuenta total.
    memoriaTotalAsignada += sizeof(struct Nodo);
    
    nuevoNodo->dato = nuevaPersona;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void insertarAlPrincipio(struct Nodo** cabeza_ref, struct Persona nuevaPersona) {
    struct Nodo* nuevoNodo = crearNodo(nuevaPersona);
    nuevoNodo->siguiente = *cabeza_ref;
    *cabeza_ref = nuevoNodo;
}

struct Nodo* buscar(struct Nodo* cabeza, char* nombreBuscado) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        if (strcmp(actual->dato.nombre, nombreBuscado) == 0) {
            return actual;
        }
        actual = actual->siguiente; // Iteración lineal O(n)
    }
    return NULL;
}

void modificar(struct Nodo* cabeza, char* nombreBuscado, float nuevoPeso, float nuevaTalla) {
    struct Nodo* nodo = buscar(cabeza, nombreBuscado);
    if (nodo != NULL) {
        nodo->dato.peso = nuevoPeso;
        nodo->dato.talla = nuevaTalla;
    }
}

void eliminar(struct Nodo** cabeza_ref, char* nombreEliminar) {
    struct Nodo* temp = *cabeza_ref;
    struct Nodo* previo = NULL;
    
    if (temp != NULL && strcmp(temp->dato.nombre, nombreEliminar) == 0) {
        *cabeza_ref = temp->siguiente;
        
        // CONCEPTO: LIBERACIÓN DE RECURSOS
        // Al matar el nodo, devolvemos sus bytes de memoria. Restamos del contador.
        free(temp);
        memoriaTotalAsignada -= sizeof(struct Nodo);
        return;
    }
    
    while (temp != NULL && strcmp(temp->dato.nombre, nombreEliminar) != 0) {
        previo = temp;
        temp = temp->siguiente;
    }
    
    if (temp == NULL) return;
    
    previo->siguiente = temp->siguiente;
    free(temp);
    
    // Restamos también aquí al liberar un nodo que estaba en medio o al final.
    memoriaTotalAsignada -= sizeof(struct Nodo); 
}

int main() {
    struct Nodo* cabeza = NULL;
    
    // Variables para medir el tiempo
    clock_t inicio, fin; 
    double tiempo_usado;
    
    printf("--- MEDICION EXPERIMENTAL BIG O EN C ---\n\n");
    
    // EXPERIMENTO 1: INSERCIÓN CONSTANTE O(1)
    // Vamos a forzar a la computadora a asignar 100,000 nodos.
    inicio = clock(); // Disparamos el cronómetro del procesador
    for (int i = 0; i < 100000; i++) {
        struct Persona p;
        // sprintf sirve para imprimir una variable DENTRO de un string (cadena).
        // Así logramos nombres automáticos: Persona_0, Persona_1...
        sprintf(p.nombre, "Persona_%d", i);
        p.peso = 70.0;
        p.talla = 1.75;
        insertarAlPrincipio(&cabeza, p); 
    }
    fin = clock(); // Detenemos cronómetro
    
    // Calculamos segundos dividiendo la diferencia de ticks entre los Ticks por Segundo.
    tiempo_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
    
    printf("[!] 100,000 Nodos Insertados.\n");
    printf("    -> Tiempo CPU: %f segundos.\n", tiempo_usado);
    // Imprimimos el acumulado de bytes convertido a KiloBytes (dividido por 1024).
    printf("    -> RAM Asignada: %zu Bytes (~%zu KB)\n\n", memoriaTotalAsignada, memoriaTotalAsignada / 1024);
    
    
    // EXPERIMENTO 2: BÚSQUEDA LINEAL O(n) EN EL PEOR CASO
    // Como insertamos todo al principio, "Persona_0" fue el primero en entrar,
    // así que fue empujado hasta el ÚLTIMO LUGAR de la lista.
    // Obligaremos a la función a recorrer los 100,000 elementos para encontrarlo.
    inicio = clock();
    struct Nodo* res = buscar(cabeza, "Persona_0"); 
    fin = clock();
    tiempo_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
    
    printf("[!] Busqueda del peor caso (Elemento hasta el final).\n");
    if(res) printf("    -> Encontrado: %s\n", res->dato.nombre);
    printf("    -> Tiempo CPU: %f segundos.\n\n", tiempo_usado);


    // EXPERIMENTO 3: ELIMINACIÓN
    // Eliminaremos el último nodo. Al hacer 'free()', nuestra variable global de memoria debe bajar.
    inicio = clock();
    eliminar(&cabeza, "Persona_0");
    fin = clock();
    tiempo_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
    
    printf("[!] Eliminacion del ultimo elemento.\n");
    printf("    -> Tiempo CPU: %f segundos.\n", tiempo_usado);
    printf("    -> RAM Asignada AHORA: %zu Bytes (~%zu KB) (Notese la reduccion)\n", memoriaTotalAsignada, memoriaTotalAsignada / 1024);

    return 0;
}
