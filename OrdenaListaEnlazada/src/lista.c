/**
 * Implementacion de Estructura de Datos Base
 * Contiene todas las operaciones CRUD y utilidades matematicas/impresion para
 * soportar la lista enlazada simple de Personas.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"

// Inicializa en memoria heap un nodo Persona completamente nuevo
Persona* crear_persona(const char* nombre, int edad) {
    Persona* nuevo_nodo = (Persona*)malloc(sizeof(Persona)); // Asignar memoria RAM
    strncpy(nuevo_nodo->nombre, nombre, 31); // Copiar nombre de forma segura
    nuevo_nodo->nombre[31] = '\0';           // Asegurar termino de cadena
    nuevo_nodo->edad = edad;                 // Guardar propiedad edad
    nuevo_nodo->siguiente = NULL;                 // Aislado por defecto
    return nuevo_nodo;
}

// Anade una nueva Persona a la cabeza (inicio) de la lista enlazada (O(1))
void insertar_persona(Persona** cabeza, const char* nombre, int edad) {
    Persona* nuevo_nodo = crear_persona(nombre, edad);
    nuevo_nodo->siguiente = *cabeza; // El nuevo nodo apunta al antiguo inicio
    *cabeza = nuevo_nodo;       // El nuevo nodo se convierte en el nuevo inicio
}

// Libera toda la memoria RAM ocupada por la lista iterativamente
void liberar_lista(Persona* cabeza) {
    Persona* actual = cabeza;
    while (actual != NULL) {
        Persona* temporal = actual;
        actual = actual->siguiente;
        free(temporal); // Retornar la memoria del nodo al Sistema Operativo
    }
}

// Genera un arreglo de N datos ficticios realistas para realizar pruebas de carga
Persona* generar_datos(int num_elementos) {
    Persona* cabeza = NULL;
    char nombre_temporal[64];
    
    // Arrays estaticos de nombres tipicos en espanol
    const char* nombres[] = {"Juan", "Maria", "Carlos", "Ana", "Luis", "Laura", "Pedro", "Sofia", "Diego", "Carmen"};
    const char* apellidos[] = {"Garcia", "Martinez", "Lopez", "Sanchez", "Perez", "Gomez", "Martin", "Jimenez", "Ruiz", "Hernandez"};

    for (int i = 0; i < num_elementos; i++) {
        // Armar aleatoriamente Nombre + Apellido
        sprintf(nombre_temporal, "%s %s", nombres[rand() % 10], apellidos[rand() % 10]);
        // Restringir la edad para que sea estrictamente mayor a 18 y menor a 100 [19, 99]
        int random_edad = 19 + (rand() % 81);
        insertar_persona(&cabeza, nombre_temporal, random_edad);
    }
    return cabeza;
}

// Crea una copia exacta (Deep Copy) de la lista enlazada para pruebas aisladas
Persona* copiar_lista(Persona* cabeza) {
    if (cabeza == NULL) return NULL; // Si es nulo no hay que copiar
    
    Persona* nueva_cabeza = crear_persona(cabeza->nombre, cabeza->edad);
    Persona* actual_orig = cabeza->siguiente;
    Persona* actual_nuevo = nueva_cabeza;
    
    // Recorremos secuencialmente clonando las celdas
    while(actual_orig != NULL) {
        actual_nuevo->siguiente = crear_persona(actual_orig->nombre, actual_orig->edad);
        actual_nuevo = actual_nuevo->siguiente;
        actual_orig = actual_orig->siguiente;
    }
    return nueva_cabeza;
}

// Mide estadisticamente cuanto tarda un algoritmo al inyectarse por puntero
double medir_tiempo(void (*funcion_ordenamiento)(Persona**), Persona** datos, const char* nombre_algoritmo) {
    // Mostrar indicador de carga antes de bloquear el hilo
    printf("\x1b[36m│\x1b[32m Tiempo de \x1b[1m%-30s\x1b[0m\x1b[32m : \x1b[33m%-18s\x1b[36m│\x1b[0m", nombre_algoritmo, "Ordenando...");
    fflush(stdout);

    clock_t inicio = clock(); // Registrar instante de inicio
    funcion_ordenamiento(datos);     // Ejecutar la rutina de ordenamiento externa
    clock_t fin = clock();   // Registrar instante final
    
    // Calcular e imprimir en consola el lapso transcurrido sobrescribiendo la linea actual
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("\r\x1b[36m│\x1b[32m Tiempo de \x1b[1m%-30s\x1b[0m\x1b[32m : \x1b[33m%8.6f\x1b[32m segundos \x1b[36m│\x1b[0m\n", nombre_algoritmo, tiempo);
    return tiempo;
}

// Visualiza los primeros 'n' elementos desde la cabeza
void imprimir_primeros_n_elementos(Persona* cabeza, int n, const char* etiqueta) {
    printf("%s: [", etiqueta);
    Persona* actual = cabeza;
    int contador = 0;
    while (actual != NULL && contador < n) {
        printf("%s(%d)", actual->nombre, actual->edad);
        actual = actual->siguiente;
        if (actual != NULL && contador < n - 1) printf(", ");
        contador++;
    }
    if (actual != NULL) printf(", ...");
    printf("]\n");
}

// Localiza el final de la lista y muestra solo los ultimos 'n' elementos
void imprimir_ultimos_n_elementos(Persona* cabeza, int n, const char* etiqueta) {
    int total = 0;
    Persona* actual = cabeza;
    
    // Calcular el tamano total de la lista (O(N))
    while(actual != NULL) { total++; actual = actual->siguiente; }
    
    int indice_inicio = total - n; // Definir a partir de donde imprimir
    if (indice_inicio < 0) indice_inicio = 0;

    printf("%s: [", etiqueta);
    if (indice_inicio > 0) printf("..., ");
    
    actual = cabeza;
    int contador = 0;
    while (actual != NULL) {
        if (contador >= indice_inicio) {
            printf("%s(%d)", actual->nombre, actual->edad); // Imprimir los datos
            if (actual->siguiente != NULL) printf(", ");
        }
        actual = actual->siguiente;
        contador++;
    }
    printf("]\n");
}
