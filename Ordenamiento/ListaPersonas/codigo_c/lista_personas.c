#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * CONCEPTO: LISTAS ENLAZADAS CON ESTRUCTURAS COMPLEJAS
 * A diferencia de los tipos primitivos (int, float), en el mundo real
 * las listas enlazadas manejan "registros" (estructuras) que agrupan
 * varios atributos.
 * 
 * Además, trabajar con cadenas de texto (arreglos de char) en C
 * requiere herramientas especiales de <string.h> como strcmp() para
 * comparar y strcpy() para copiar, ya que no se pueden usar los
 * operadores normales (== o =).
 */

// 1. EL "REGISTRO" O DATO
// Esta estructura representa la información útil que queremos almacenar.
struct Persona {
    char nombre[50]; // Arreglo de caracteres para el nombre
    float peso;      // Atributo flotante
    float talla;     // Atributo flotante
};

// 2. LA ESTRUCTURA DEL NODO
// El nodo es el "contenedor" que nos permite enlazar los datos.
struct Nodo {
    struct Persona dato;    // Aquí incrustamos el registro completo. 
                            // Podríamos también usar un apuntador (struct Persona* dato),
                            // pero copiar la estructura es más sencillo para empezar.
    struct Nodo* siguiente; // El cordón umbilical que une este nodo con el que sigue.
};

// Función para inicializar un nodo en la memoria RAM
struct Nodo* crearNodo(struct Persona nuevaPersona) {
    // CONCEPTO: Asignación Dinámica
    // malloc reserva los bytes exactos que pesa "struct Nodo" en el Heap (memoria libre).
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    // Si malloc retorna NULL, el sistema operativo nos denegó la memoria (RAM llena).
    if (nuevoNodo == NULL) {
        printf("Error: Memoria insuficiente.\n");
        exit(1);
    }
    
    // Al usar '=', en C, se copia el contenido completo de la estructura 'nuevaPersona' 
    // hacia el campo 'dato' del nuevo nodo byte por byte.
    nuevoNodo->dato = nuevaPersona;
    
    // Al ser un nodo recién nacido, no tiene a nadie después de él todavía.
    nuevoNodo->siguiente = NULL;
    
    return nuevoNodo;
}

// OPERACIÓN: INSERTAR AL PRINCIPIO
void insertarAlPrincipio(struct Nodo** cabeza_ref, struct Persona nuevaPersona) {
    // 1. Fabricamos el nodo
    struct Nodo* nuevoNodo = crearNodo(nuevaPersona);
    
    // 2. Conectamos el nuevo nodo a la lista existente
    // El 'siguiente' de nuestro nuevo nodo apuntará a donde apunta actualmente la cabeza.
    nuevoNodo->siguiente = *cabeza_ref;
    
    // 3. Movemos la cabeza
    // Ahora, oficialmente, la cabeza de nuestra fila es este nuevo nodo.
    *cabeza_ref = nuevoNodo;
    
    printf("Registro insertado: %s\n", nuevaPersona.nombre);
}

// OPERACIÓN: BUSCAR
// Retorna la dirección de memoria (apuntador) del nodo si lo encuentra.
struct Nodo* buscar(struct Nodo* cabeza, char* nombreBuscado) {
    // CONCEPTO: Recorrido
    // Usamos 'actual' como nuestro "dedo índice" para ir señalando nodo por nodo
    // sin modificar o perder la variable 'cabeza' original.
    struct Nodo* actual = cabeza;
    
    // Mientras no caigamos al vacío (NULL) al final de la lista...
    while (actual != NULL) {
        // CONCEPTO: strcmp (String Compare)
        // strcmp devuelve 0 si ambas cadenas son exactamente idénticas letra por letra.
        // Accedemos a actual->dato.nombre:
        // 'actual->' entra al nodo, '.dato' entra a la estructura, '.nombre' entra al atributo.
        if (strcmp(actual->dato.nombre, nombreBuscado) == 0) {
            return actual; // ¡Premio! Devolvemos el apuntador a este contenedor.
        }
        
        // Si no es el que buscamos, avanzamos un paso en la lista.
        actual = actual->siguiente;
    }
    
    // Si el while termina, recorrimos toda la lista y no hubo coincidencias.
    return NULL; 
}

// OPERACIÓN: MODIFICAR
void modificar(struct Nodo* cabeza, char* nombreBuscado, float nuevoPeso, float nuevaTalla) {
    // Nos apoyamos en la función de búsqueda para que haga el trabajo pesado
    struct Nodo* nodoEncontrado = buscar(cabeza, nombreBuscado);
    
    // Si la búsqueda no retornó vacío...
    if (nodoEncontrado != NULL) {
        // ...pisamos los valores antiguos con los nuevos.
        nodoEncontrado->dato.peso = nuevoPeso;
        nodoEncontrado->dato.talla = nuevaTalla;
        printf("Modificacion exitosa para: %s\n", nombreBuscado);
    } else {
        printf("Fallo modificacion: %s no existe en la lista.\n", nombreBuscado);
    }
}

// OPERACIÓN: ELIMINAR
void eliminar(struct Nodo** cabeza_ref, char* nombreEliminar) {
    struct Nodo* temp = *cabeza_ref; // Iterador principal
    struct Nodo* previo = NULL;      // Para no perder el hilo al desatar un nudo
    
    // CASO A: ¿Y si el que queremos eliminar es el mismísimo primer elemento?
    // Verificamos que la lista no esté vacía y que la cabeza coincida.
    if (temp != NULL && strcmp(temp->dato.nombre, nombreEliminar) == 0) {
        // La nueva cabeza será el segundo elemento
        *cabeza_ref = temp->siguiente;
        
        // CONCEPTO: free()
        // Le devolvemos el espacio del nodo viejo al sistema operativo.
        // Si no hacemos esto, causamos un "Memory Leak" (Fuga de memoria).
        free(temp);
        printf("Eliminado (era la cabeza): %s\n", nombreEliminar);
        return; // Terminamos, misión cumplida.
    }
    
    // CASO B: Está perdido en medio del mar de nodos
    while (temp != NULL && strcmp(temp->dato.nombre, nombreEliminar) != 0) {
        // Antes de avanzar 'temp', guardamos su posición en 'previo'
        previo = temp;
        // Ahora sí, 'temp' avanza al siguiente
        temp = temp->siguiente;
    }
    
    // Si temp llegó a NULL, no existía en toda la lista.
    if (temp == NULL) {
        printf("Fallo eliminacion: %s no existe.\n", nombreEliminar);
        return;
    }
    
    // CONCEPTO: Desvincular
    // El nodo 'previo' (el que está justo antes del que vamos a matar) 
    // ahora apuntará al nodo que está *después* del que vamos a matar.
    // Esto literalmente saca a 'temp' de la cadena.
    previo->siguiente = temp->siguiente;
    
    // Eliminamos la evidencia liberando la memoria
    free(temp);
    printf("Eliminado de la lista: %s\n", nombreEliminar);
}

// Función para imprimir
void imprimirLista(struct Nodo* nodo) {
    printf("\n[ Estado Actual de la Lista ]\n");
    if (nodo == NULL) {
        printf("(Vacia)\n");
        return;
    }
    // Recorremos e imprimimos
    while (nodo != NULL) {
        printf(" -> %s (%.1f kg, %.2f m)\n", 
               nodo->dato.nombre, nodo->dato.peso, nodo->dato.talla);
        nodo = nodo->siguiente;
    }
    printf("\n");
}

int main() {
    struct Nodo* cabeza = NULL; // Lista vacía
    
    // Preparamos los registros estructurados
    struct Persona p1 = {"Juan Perez", 75.5, 1.75};
    struct Persona p2 = {"Ana Gomez", 62.0, 1.68};
    struct Persona p3 = {"Carlos Ruiz", 80.2, 1.80};
    
    // Realizamos las inserciones
    insertarAlPrincipio(&cabeza, p1);
    insertarAlPrincipio(&cabeza, p2);
    insertarAlPrincipio(&cabeza, p3);
    
    imprimirLista(cabeza);
    
    // Probamos operaciones que dependen del nombre (cadenas de texto)
    modificar(cabeza, "Ana Gomez", 60.0, 1.68);
    eliminar(&cabeza, "Juan Perez");
    
    imprimirLista(cabeza);
    
    return 0;
}
