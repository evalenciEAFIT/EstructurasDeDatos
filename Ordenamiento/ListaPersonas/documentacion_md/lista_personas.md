# Listas Enlazadas con Estructuras Complejas en C

En aplicaciones reales, una lista enlazada rara vez almacena solo un número simple. Lo más común es que cada nodo almacene un "registro" o estructura de datos completa.

En este documento explicamos cómo adaptar una lista enlazada para que almacene una estructura con `nombre`, `peso` y `talla`.

## La Estructura de Datos

Primero, definimos una estructura que representará la información que queremos almacenar. Luego, el nodo de la lista contendrá una instancia de esta estructura en lugar de un tipo primitivo como `int`.

```c
// La información del registro
struct Persona {
    char nombre[50];
    float peso;
    float talla;
};

// El Nodo de la lista enlazada
struct Nodo {
    struct Persona dato;    // El dato ahora es la estructura completa
    struct Nodo* siguiente; // Puntero al siguiente elemento
};
```

---

## Operaciones con Estructuras

Al manejar estructuras, hay pequeños cambios en cómo comparamos o asignamos los datos, especialmente con las cadenas de texto (como el nombre).

### 1. Insertar
Para insertar, la función ahora recibe un parámetro de tipo `struct Persona`.

```c
void insertarAlPrincipio(struct Nodo** cabeza_ref, struct Persona nuevaPersona) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    nuevoNodo->dato = nuevaPersona; // Se copia la estructura completa
    nuevoNodo->siguiente = *cabeza_ref;
    *cabeza_ref = nuevoNodo;
}
```

### 2. Buscar (por Nombre)
Para buscar, ya no podemos usar el operador `==` para comparar cadenas de texto. Debemos usar la función `strcmp` de la librería `<string.h>`. Esta función devuelve `0` si ambas cadenas son idénticas.

```c
struct Nodo* buscar(struct Nodo* cabeza, char* nombreBuscado) {
    struct Nodo* actual = cabeza;
    
    while (actual != NULL) {
        // Se utiliza strcmp para comparar el campo 'nombre'
        if (strcmp(actual->dato.nombre, nombreBuscado) == 0) {
            return actual; // Retorna el nodo si coincide
        }
        actual = actual->siguiente;
    }
    return NULL;
}
```

### 3. Modificar
Para modificar, primero utilizamos la función `buscar`. Si encontramos el nodo, accedemos a sus campos utilizando el operador flecha `->` seguido del operador punto `.` para acceder a la estructura interna.

```c
void modificar(struct Nodo* cabeza, char* nombreBuscado, float nuevoPeso, float nuevaTalla) {
    struct Nodo* nodoEncontrado = buscar(cabeza, nombreBuscado);
    
    if (nodoEncontrado != NULL) {
        // Se actualizan los campos específicos
        nodoEncontrado->dato.peso = nuevoPeso;
        nodoEncontrado->dato.talla = nuevaTalla;
    }
}
```

### 4. Eliminar
El proceso de eliminación de los enlaces es idéntico al de una lista de enteros. La única diferencia es cómo identificamos el nodo a eliminar (usando `strcmp` para comparar el nombre).

```c
void eliminar(struct Nodo** cabeza_ref, char* nombreEliminar) {
    struct Nodo* temp = *cabeza_ref;
    struct Nodo* previo = NULL;
    
    // Si es la cabeza
    if (temp != NULL && strcmp(temp->dato.nombre, nombreEliminar) == 0) {
        *cabeza_ref = temp->siguiente;
        free(temp);
        return;
    }
    
    // Buscar en el resto de la lista
    while (temp != NULL && strcmp(temp->dato.nombre, nombreEliminar) != 0) {
        previo = temp;
        temp = temp->siguiente;
    }
    
    // Si no se encuentra o la lista termina
    if (temp == NULL) return;
    
    // Desenlazar y liberar
    previo->siguiente = temp->siguiente;
    free(temp);
}
```
