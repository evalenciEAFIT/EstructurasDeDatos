# Listas Enlazadas en C

Una **lista enlazada** es una estructura de datos lineal, similar a los arreglos, pero con la diferencia de que sus elementos no están almacenados en ubicaciones contiguas de memoria. En su lugar, cada elemento (llamado **nodo**) contiene la información (el dato) y un puntero (enlace) que indica la dirección de memoria del siguiente nodo en la secuencia.

## Ventajas sobre los arreglos:
1. **Tamaño dinámico:** Pueden crecer y reducirse durante la ejecución del programa según sea necesario.
2. **Inserciones y eliminaciones eficientes:** Es más rápido insertar o eliminar elementos en medio de la lista, ya que no se requiere desplazar los demás elementos (solo cambiar punteros).

## Desventajas:
1. **Acceso secuencial:** No se puede acceder aleatoriamente a los elementos (como en `arreglo[3]`). Se debe empezar desde el primer elemento y recorrer la lista.
2. **Memoria adicional:** Requieren más memoria debido al almacenamiento de los punteros junto con los datos.

---

## Estructura de un Nodo

En C, definimos un nodo usando una estructura (`struct`). Para una lista de números enteros, la estructura consta del dato (`int`) y un puntero a otro nodo.

```c
struct Nodo {
    int dato;              // El valor entero que almacena el nodo
    struct Nodo* siguiente; // Apuntador al siguiente nodo en la lista
};
```

---

## Operaciones Básicas

### 1. Insertar un Nodo
Para insertar un nodo al principio de la lista, primero creamos el nuevo nodo. Luego, hacemos que su puntero `siguiente` apunte al nodo que actualmente es la cabeza de la lista, y finalmente actualizamos la cabeza para que apunte al nuevo nodo.

```c
void insertarAlPrincipio(struct Nodo** cabeza_ref, int valor) {
    // 1. Crear nuevo nodo
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = valor;
    
    // 2. Apuntar el siguiente del nuevo nodo a la cabeza actual
    nuevoNodo->siguiente = *cabeza_ref;
    
    // 3. La nueva cabeza es el nuevo nodo
    *cabeza_ref = nuevoNodo;
}
```

### 2. Buscar un Nodo
Para buscar un valor, recorremos la lista desde la cabeza hasta el final (hasta que el puntero sea `NULL`). Si encontramos el valor, retornamos el puntero al nodo.

```c
struct Nodo* buscar(struct Nodo* cabeza, int valorBuscado) {
    struct Nodo* actual = cabeza;
    
    while (actual != NULL) {
        if (actual->dato == valorBuscado) {
            return actual; // Se encontró, retornamos el apuntador
        }
        actual = actual->siguiente; // Avanzamos
    }
    return NULL; // No se encontró
}
```

### 3. Modificar un Nodo
Para modificar, primero buscamos el nodo utilizando la función `buscar`. Si el nodo existe (no es `NULL`), simplemente le asignamos el nuevo valor a su campo `dato`.

```c
void modificar(struct Nodo* cabeza, int valorBuscado, int nuevoValor) {
    struct Nodo* nodoEncontrado = buscar(cabeza, valorBuscado);
    
    if (nodoEncontrado != NULL) {
        nodoEncontrado->dato = nuevoValor; // Modificamos el valor
    }
}
```

### 4. Eliminar un Nodo
Eliminar es la operación más compleja porque hay que considerar dos casos principales: si el nodo a eliminar es la cabeza de la lista, o si está en el medio/final. Debemos mantener una referencia al nodo *previo* para no perder el enlace de la lista.

```c
void eliminar(struct Nodo** cabeza_ref, int valorEliminar) {
    struct Nodo* temp = *cabeza_ref;
    struct Nodo* previo = NULL;
    
    // Caso 1: El nodo a eliminar es la cabeza
    if (temp != NULL && temp->dato == valorEliminar) {
        *cabeza_ref = temp->siguiente;
        free(temp);
        return;
    }
    
    // Caso 2: Buscar el nodo en el resto de la lista
    while (temp != NULL && temp->dato != valorEliminar) {
        previo = temp;
        temp = temp->siguiente;
    }
    
    // Si no se encontró el valor
    if (temp == NULL) return;
    
    // Desvincular el nodo de la lista y liberar memoria
    previo->siguiente = temp->siguiente;
    free(temp);
}
```
