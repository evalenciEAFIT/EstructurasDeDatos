# Generación de Datos Masivos

Este módulo contiene herramientas para crear grandes volúmenes de datos simulados (dataset). El objetivo es utilizar estos datos masivos para someter a prueba de estrés (*stress testing*) y analizar el rendimiento de las diferentes **Estructuras de Datos** implementadas.

## 🚀 Uso del Generador

El módulo incluye un script en **Python** y un programa en **C**. Ambos generan de forma dinámica un archivo `dataset.csv` con las columnas: `ID`, `Nombre_Completo`, `Sexo`, `Edad`, `Peso_kg`, `Altura_cm`.

### Opción A: Usar Python
**Ejecución básica (10,000 registros):**
```bash
python3 generar_datos.py
```
**Ejecutar para "n" cantidad (ej. 5 millones):**
```bash
python3 generar_datos.py 5000000
```

### Opción B: Usar C (Máximo Rendimiento ⚡)
Al ser un lenguaje compilado, la ejecución en C realiza las millones de operaciones matemáticas de aleatoriedad y de escritura en disco en una fracción del tiempo de Python.
**1. Compilar el generador con nivel de optimización O3:**
```bash
gcc -Wall -O3 -o generar_datos_c generar_datos.c
```
**2. Ejecutar para "n" cantidad (ej. 5 millones):**
```bash
./generar_datos_c 5000000
```
*(Nota: El archivo `.csv` generado será exactamente el mismo que el de Python).*

---

## 🧠 Relación con las Estructuras de Datos

Cuando pasas de trabajar con 10 datos (como en los ejemplos básicos) a **5 millones de datos**, la elección de la estructura de datos es crítica para el rendimiento (complejidad temporal de la notación *Big O*):

### 1. Tabla Hash (Búsqueda por ID) `O(1)`
Si necesitas encontrar al paciente con `ID = 4500123`, usar una **Lista Enlazada** requeriría millones de saltos de memoria `O(n)`. Sin embargo, si cargas tu CSV a una **Tabla Hash**, usarás una función matemática para saltar instantáneamente a ese registro. El tiempo de búsqueda será casi de `O(1)`.

### 2. Árbol Binario de Búsqueda (Ordenamiento por Edad) `O(log n)`
Si quieres responder consultas como *"listar todas las personas entre 20 y 25 años"*, una Tabla Hash no te servirá porque no guarda el orden. Al cargar tus millones de registros en un **BST (Árbol Binario de Búsqueda)** indexado por `Edad`, el árbol descarta mitades enteras de datos en cada paso descendente, resolviendo consultas extremadamente rápido.

### 3. Listas Enlazadas `O(n)` y Pilas/Colas
Las listas enlazadas **no son eficientes para búsquedas masivas**. Sin embargo, son fundamentales como estructura secundaria. Por ejemplo:
- Si hay colisiones en la Tabla Hash, los datos se guardan en una **Lista Enlazada**.
- Si queremos procesar el dataset lote por lote a medida que entran los registros, podemos usar una **Cola (FIFO)**.

### 4. Grafos (Redes Sociales o de Contagio)
Imagina añadir una columna de `Amigo_ID` o `Contacto_Estrecho_ID` a este dataset. Ya no tendríamos registros aislados. Al cargarlos en un **Grafo**, cada persona se convierte en un *Vértice* y las interacciones en *Aristas*. Los Grafos nos permitirían responder a: *"¿Quién es el amigo del amigo de Juan?"* mediante algoritmos de recorrido como BFS.

---

> Siéntete libre de escribir scripts en `C` o `Python` que abran el `dataset.csv` e inserten todos sus datos utilizando las librerías construidas en `/source/`.
