# Estructuras de Datos (C & Python)

Este repositorio contiene implementaciones didácticas de las principales **Estructuras de Datos** en los lenguajes **C** y **Python**. El propósito de este proyecto es servir como material de estudio y referencia. 

Todo el código fuente se encuentra organizado dentro de la carpeta `source/`.

---

## ⚙️ Compilación y Ejecución

Puedes ejecutar y compilar los archivos de forma individual o usar las herramientas de automatización incluidas.

### Opción 1: Usando `Makefile` para C (Recomendado)
El proyecto incluye un `Makefile` en la raíz. Para compilar **todos** los programas en C al mismo tiempo, simplemente ejecuta en la terminal:
```bash
make
```
Esto creará una carpeta llamada `bin/` con todos los ejecutables (`./bin/lista_enlazada`, `./bin/pila`, etc.), los cuales puedes ejecutar de forma manual:
```bash
./bin/lista_enlazada
```
Para limpiar los archivos binarios generados, usa:
```bash
make clean
```

### Opción 2: Ejecución individual manual
Si prefieres compilar un archivo C paso a paso sin usar el Makefile:
```bash
gcc -Wall -Wextra -o lista_enlazada source/c/lista_enlazada.c
./lista_enlazada
```
En **Python**, no requieres compilación previa. Ejecútalos directamente apuntando a la carpeta source:
```bash
python3 source/python/lista_enlazada.py
```

### Opción 3: Scripts automatizados de prueba
Si quieres compilar y correr absolutamente **todos** los ejemplos en secuencia para ver sus resultados en consola:
* **Para C:** ejecuta `./ejecutar_c.sh`
* **Para Python:** ejecuta `./ejecutar_py.sh`

---

## 📚 Índice de Estructuras

A continuación, se detalla cada estructura de datos implementada, incluyendo su comportamiento y enlaces directos al código fuente.

### 1. Lista Enlazada
Estructura lineal donde los elementos no están ubicados de manera contigua, sino que cada uno contiene una referencia (o puntero) al siguiente.
* 📄 **C:** [`source/c/lista_enlazada.c`](source/c/lista_enlazada.c)
* 🐍 **Python:** [`source/python/lista_enlazada.py`](source/python/lista_enlazada.py)

### 2. Pila (Stack)
Estructura que obedece al principio **LIFO (Last In, First Out)**. El último elemento en entrar es el primero en salir.
* 📄 **C:** [`source/c/pila.c`](source/c/pila.c)
* 🐍 **Python:** [`source/python/pila.py`](source/python/pila.py)

### 3. Cola (Queue)
Estructura que opera bajo el principio **FIFO (First In, First Out)**. El primer elemento en ingresar es el primero en ser procesado.
* 📄 **C:** [`source/c/cola.c`](source/c/cola.c)
* 🐍 **Python:** [`source/python/cola.py`](source/python/cola.py)

### 4. Árbol Binario de Búsqueda (BST)
Estructura jerárquica donde cada nodo tiene como máximo dos descendientes. El hijo izquierdo es siempre menor al padre y el derecho es mayor.
* 📄 **C:** [`source/c/arbol.c`](source/c/arbol.c)
* 🐍 **Python:** [`source/python/arbol.py`](source/python/arbol.py)

### 5. Tabla Hash
Estructura para búsqueda veloz que mapea claves a valores utilizando una función hash, resolviendo colisiones mediante encadenamiento.
* 📄 **C:** [`source/c/tabla_hash.c`](source/c/tabla_hash.c)
* 🐍 **Python:** [`source/python/tabla_hash.py`](source/python/tabla_hash.py)

### 6. Grafo
Estructura diseñada para modelar redes. Emplea distintos enfoques según el lenguaje:
* 📄 **C (Matriz de Adyacencia):** [`source/c/grafo.c`](source/c/grafo.c) - Utiliza una cuadrícula, ideal para consultar conectividad velozmente.
* 🐍 **Python (Lista de Adyacencia):** [`source/python/grafo.py`](source/python/grafo.py) - Emplea diccionarios, ideal para grafos grandes.

---

> Desarrollado como material de referencia. Siéntete libre de clonar y experimentar.
