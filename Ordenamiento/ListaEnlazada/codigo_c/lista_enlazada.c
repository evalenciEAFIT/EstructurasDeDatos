#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo para la lista enlazada
struct Nodo {
    int dato;              // El valor entero que almacena el nodo
    struct Nodo* siguiente; // Apuntador al siguiente nodo en la lista
};

// Función para crear un nuevo nodo
// Recibe el valor entero que almacenará el nodo
struct Nodo* crearNodo(int valor) {
    // Se reserva memoria dinámica para el nuevo nodo usando malloc
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    // Si malloc falla (devuelve NULL), significa que no hay memoria disponible
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(1); // Se termina la ejecución del programa con código de error
    }
    
    // Se asigna el valor al campo 'dato' del nuevo nodo
    nuevoNodo->dato = valor;
    // Como el nodo se insertará al final o es nuevo, su apuntador 'siguiente' es NULL
    nuevoNodo->siguiente = NULL;
    
    // Se retorna el apuntador al nodo recién creado
    return nuevoNodo;
}

// Función para insertar un nodo al principio de la lista
// Recibe un apuntador al apuntador de la cabeza (para poder modificar la cabeza real) y el valor
void insertarAlPrincipio(struct Nodo** cabeza_ref, int valor) {
    // Se crea el nuevo nodo llamando a la función crearNodo
    struct Nodo* nuevoNodo = crearNodo(valor);
    
    // El 'siguiente' del nuevo nodo apuntará al nodo que actualmente es la cabeza
    nuevoNodo->siguiente = *cabeza_ref;
    
    // Ahora la nueva cabeza de la lista será el nuevo nodo
    *cabeza_ref = nuevoNodo;
    
    printf("Nodo con valor %d insertado en la lista.\n", valor);
}

// Función para buscar un nodo por su valor
// Retorna un apuntador al nodo si lo encuentra, o NULL si no lo encuentra
struct Nodo* buscar(struct Nodo* cabeza, int valorBuscado) {
    // Se usa un apuntador temporal 'actual' para recorrer la lista, empezando por la cabeza
    struct Nodo* actual = cabeza;
    
    // Mientras no lleguemos al final de la lista (actual no sea NULL)
    while (actual != NULL) {
        // Si el dato del nodo actual coincide con el valor buscado
        if (actual->dato == valorBuscado) {
            return actual; // Retornamos el apuntador a este nodo
        }
        // Si no es el valor, avanzamos al siguiente nodo de la lista
        actual = actual->siguiente;
    }
    
    // Si el bucle termina y no se encontró el valor, se retorna NULL
    return NULL;
}

// Función para modificar el valor de un nodo existente
// Recibe la cabeza de la lista, el valor a buscar y el nuevo valor
void modificar(struct Nodo* cabeza, int valorBuscado, int nuevoValor) {
    // Reutilizamos la función 'buscar' para encontrar el nodo a modificar
    struct Nodo* nodoEncontrado = buscar(cabeza, valorBuscado);
    
    // Si la función buscar no retornó NULL, significa que el nodo existe
    if (nodoEncontrado != NULL) {
        // Se actualiza el campo 'dato' del nodo encontrado con el nuevo valor
        nodoEncontrado->dato = nuevoValor;
        printf("Valor %d modificado por %d con exito.\n", valorBuscado, nuevoValor);
    } else {
        // Si retornó NULL, el nodo no existe en la lista
        printf("Error: No se encontro un nodo con el valor %d para modificar.\n", valorBuscado);
    }
}

// Función para eliminar un nodo dado su valor
// Recibe el apuntador al apuntador de la cabeza y el valor a eliminar
void eliminar(struct Nodo** cabeza_ref, int valorEliminar) {
    // Apuntador 'temp' para recorrer la lista, inicializado en la cabeza
    struct Nodo* temp = *cabeza_ref;
    // Apuntador 'previo' para mantener la referencia al nodo anterior a 'temp'
    struct Nodo* previo = NULL;
    
    // Caso 1: El nodo a eliminar es la cabeza de la lista
    if (temp != NULL && temp->dato == valorEliminar) {
        // La nueva cabeza será el siguiente nodo del actual
        *cabeza_ref = temp->siguiente;
        // Se libera la memoria del nodo eliminado
        free(temp);
        printf("Nodo con valor %d eliminado (era la cabeza).\n", valorEliminar);
        return; // Terminamos la función
    }
    
    // Caso 2: El nodo a eliminar está en medio o al final
    // Recorremos la lista buscando el valor, llevando registro del nodo anterior
    while (temp != NULL && temp->dato != valorEliminar) {
        previo = temp;          // El nodo actual se convierte en el previo
        temp = temp->siguiente; // Avanzamos al siguiente nodo
    }
    
    // Si 'temp' llegó a NULL, significa que recorrimos toda la lista y no encontramos el valor
    if (temp == NULL) {
        printf("Error: No se encontro el nodo con valor %d para eliminar.\n", valorEliminar);
        return;
    }
    
    // Si se encontró, el 'siguiente' del nodo previo ahora apuntará al 'siguiente' del nodo a eliminar
    // Desvinculando así el nodo 'temp' de la lista
    previo->siguiente = temp->siguiente;
    
    // Se libera la memoria ocupada por el nodo 'temp'
    free(temp);
    printf("Nodo con valor %d eliminado de la lista.\n", valorEliminar);
}

// Función auxiliar para imprimir la lista (útil para verificar el funcionamiento)
void imprimirLista(struct Nodo* nodo) {
    printf("Estado de la lista: ");
    // Recorremos la lista hasta el final
    while (nodo != NULL) {
        // Imprimimos el dato del nodo actual
        printf("%d -> ", nodo->dato);
        // Avanzamos al siguiente nodo
        nodo = nodo->siguiente;
    }
    // Indicamos el final de la lista con NULL
    printf("NULL\n");
}

int main() {
    // Inicializamos la lista vacía (la cabeza apunta a NULL)
    struct Nodo* cabeza = NULL;
    
    printf("--- Iniciando operaciones de la Lista Enlazada ---\n\n");
    
    // Probando la inserción
    insertarAlPrincipio(&cabeza, 10);
    insertarAlPrincipio(&cabeza, 20);
    insertarAlPrincipio(&cabeza, 30);
    insertarAlPrincipio(&cabeza, 40);
    imprimirLista(cabeza);
    printf("\n");
    
    // Probando la búsqueda
    int valorBuscar = 20;
    struct Nodo* resultadoBusqueda = buscar(cabeza, valorBuscar);
    if (resultadoBusqueda != NULL) {
        printf("Busqueda: Se encontro el nodo. Su direccion de memoria es %p y su valor es %d.\n", (void*)resultadoBusqueda, resultadoBusqueda->dato);
    } else {
        printf("Busqueda: Nodo con valor %d no encontrado.\n", valorBuscar);
    }
    printf("\n");
    
    // Probando la modificación
    modificar(cabeza, 30, 35);
    imprimirLista(cabeza);
    printf("\n");
    
    // Probando la eliminación
    eliminar(&cabeza, 40); // Eliminar la cabeza
    imprimirLista(cabeza);
    eliminar(&cabeza, 10); // Eliminar un nodo del final o medio
    imprimirLista(cabeza);
    eliminar(&cabeza, 100); // Intentar eliminar un nodo inexistente
    printf("\n");
    
    return 0;
}
