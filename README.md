# Estructuras de Datos (C & Python)

Este repositorio contiene implementaciones didácticas de las principales **Estructuras de Datos** en los lenguajes **C** y **Python**. El propósito de este proyecto es servir como material de estudio y referencia para comprender a profundidad cómo funciona cada estructura, sus procesos de inserción, búsqueda, eliminación y recorrido.

Cada archivo fuente cuenta con **comentarios exhaustivos y detallados** que explican paso a paso la lógica teórica detrás del código práctico.

---

## 🚀 Cómo ejecutar los programas

Se proporcionan scripts de automatización para facilitar la ejecución masiva de todos los ejemplos.

### Ejecución en C
Para compilar y ejecutar todas las implementaciones en C (hace uso automático del `Makefile`):
```bash
./ejecutar_c.sh
```

### Ejecución en Python
Para ejecutar en secuencia todos los scripts de Python:
```bash
./ejecutar_py.sh
```

---

## 📚 Índice de Estructuras

A continuación, se detalla cada estructura de datos implementada, incluyendo su comportamiento y enlaces directos al código fuente.

### 1. Lista Enlazada
Estructura lineal donde los elementos (nodos) no están ubicados de manera contigua en memoria, sino que cada uno contiene una referencia (o puntero) al siguiente. Ofrece un manejo de memoria sumamente dinámico e inserciones eficientes.
* 📄 **C:** [`lista_enlazada.c`](lista_enlazada.c)
* 🐍 **Python:** [`lista_enlazada.py`](lista_enlazada.py)

### 2. Pila (Stack)
Estructura abstracta que obedece al principio **LIFO (Last In, First Out)**. El último elemento en entrar ("apilar") es, obligatoriamente, el primero en salir ("desapilar").
* 📄 **C:** [`pila.c`](pila.c)
* 🐍 **Python:** [`pila.py`](pila.py)

### 3. Cola (Queue)
Estructura abstracta que opera bajo el principio **FIFO (First In, First Out)**. Similar a una fila en el supermercado, el primer elemento en ingresar (encolar) es el primero en ser procesado y eliminado (desencolar).
* 📄 **C:** [`cola.c`](cola.c)
* 🐍 **Python:** [`cola.py`](cola.py)

### 4. Árbol Binario de Búsqueda (BST)
Estructura jerárquica, no lineal, donde cada nodo puede tener como máximo dos descendientes (izquierdo y derecho). Sigue la regla en la que el hijo izquierdo siempre es menor que el padre, y el derecho mayor, lo que optimiza enormemente los algoritmos de búsqueda.
* 📄 **C:** [`arbol.c`](arbol.c)
* 🐍 **Python:** [`arbol.py`](arbol.py)

### 5. Tabla Hash
Estructura orientada a la búsqueda veloz que mapea *claves* a *valores*. Utiliza una "función hash" para ubicar un dato en un índice de memoria. Las colisiones en esta implementación son resueltas mediante *Encadenamiento* (listas enlazadas internas).
* 📄 **C:** [`tabla_hash.c`](tabla_hash.c)
* 🐍 **Python:** [`tabla_hash.py`](tabla_hash.py)

### 6. Grafo
Estructura poderosa diseñada para modelar redes y relaciones complejas. Formada por "Vértices" y "Aristas".
Para fines educativos, la implementación emplea distintos enfoques:
* 📄 **C (Matriz de Adyacencia):** [`grafo.c`](grafo.c) - Utiliza una cuadrícula (array 2D), ideal para consultar conectividad directa muy rápidamente.
* 🐍 **Python (Lista de Adyacencia):** [`grafo.py`](grafo.py) - Emplea diccionarios y listas para ahorrar espacio en memoria, ideal para grafos grandes y dispersos. Incluye algoritmo BFS (Búsqueda en Anchura).

---

> Desarrollado como material de referencia. Siéntete libre de clonar, experimentar y ejecutar para profundizar tus conocimientos en algoritmia clásica.
