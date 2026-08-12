# Arquitectura y Comparación de Paradigmas Algorítmicos en Ordenamiento

Este proyecto en C explora y contrasta de forma práctica los principales paradigmas de diseño de algoritmos de la ciencia de la computación. Todo esto se aplica sobre un problema central: **Ordenar una lista enlazada simple de estructuras `Persona` (Nombre y Edad) con base en su edad.**

## Paradigmas de Diseño Evaluados

En el ámbito del diseño de algoritmos, existen múltiples enfoques para atacar el mismo problema. A continuación, exploramos conceptualmente cada uno de ellos, su implementación en este proyecto y su pertinencia en la vida real.

---

### 1. Fuerza Bruta (Bubble Sort)

La **fuerza bruta** es el enfoque más directo e ingenuo. No intenta ser inteligente ni optimizar el uso de recursos; simplemente ataca el problema probando todas las posibilidades sistemáticamente hasta que la condición se cumple.

* **Enfoque en el código ([`src/fuerza_bruta.c`](src/fuerza_bruta.c)):** Implementado mediante el clásico *Bubble Sort*. El algoritmo recorre repetidamente toda la lista, comparando pares de personas adyacentes y permutándolas si están en el orden incorrecto. Continúa haciendo pasadas iterativas hasta que recorre la lista completa sin realizar ningún intercambio.
* **Análisis de Complejidad:**
  * **Tiempo:** $\mathcal{O}(N^2)$. Al no recordar casi nada de las pasadas anteriores (salvo el límite de los ya ordenados), compara redundante e ineficientemente miles de veces los mismos nodos.
  * **Espacio:** $\mathcal{O}(1)$. Trabaja directamente sobre la estructura de la lista (In-Place).
* **Uso en Producción:** **Totalmente desaconsejado.** Su uso real se restringe estrictamente a la academia como herramienta pedagógica o en conjuntos de datos microscópicos (menos de 50 elementos) donde la sobrecarga de un algoritmo complejo no vale la pena.

---

### 2. Algoritmo Codicioso / Greedy (Selection Sort)

Un algoritmo **codicioso (greedy)** toma, en cada paso, la decisión que parece ser la óptima en ese momento inmediato, con la esperanza de que estas decisiones "locales" conduzcan a una solución "global" óptima. No retrocede ni reconsidera sus decisiones.

* **Enfoque en el código ([`src/codicioso.c`](src/codicioso.c)):** Implementado mediante *Selection Sort*. El algoritmo se para en una posición de la lista y se vuelve "codicioso": escanea todo lo que queda de la lista buscando al elemento más pequeño absoluto y lo intercambia para colocarlo en la posición actual. Asume que colocar el mínimo local en su sitio definitivo es la mejor decisión sin importar el resto.
* **Análisis de Complejidad:**
  * **Tiempo:** $\mathcal{O}(N^2)$. Aunque es codicioso, debe explorar secuencialmente todo el resto de la lista no ordenada por cada nodo, forzando un ciclo anidado.
  * **Espacio:** $\mathcal{O}(1)$. No requiere estructuras de memoria adicionales.
* **Uso en Producción:** **Muy situacional.** Aunque sigue siendo lento, realiza drásticamente menos operaciones de *intercambio* (escritura en memoria) que la fuerza bruta. Es útil en sistemas embebidos (microcontroladores) donde escribir en memoria flash tiene un costo eléctrico o de desgaste alto.

---

### 3. Divide y Vencerás (Merge Sort y Quick Sort)

**Divide y Vencerás** (Divide and Conquer) es la piedra angular del alto rendimiento. Su filosofía dicta que un problema masivo es inmanejable, por lo que debe romperse por la mitad de forma recursiva hasta llegar a "casos base" (sub-problemas tan diminutos que se resuelven trivialmente). Luego, las sub-soluciones se combinan para armar la solución final.

* **Enfoque en el código ([`src/divide_y_venceras.c`](src/divide_y_venceras.c)):** Implementado usando los dos titanes históricos:
  * **Merge Sort (John von Neumann, 1945):** Parte la lista enlazada físicamente a la mitad hasta tener personas aisladas. Luego, las "fusiona" (merge) de vuelta pero cruzando los punteros para que queden ordenadas.
  * **Quick Sort (Tony Hoare, 1959):** Elige una persona al azar (Pivote). Tira a los menores a la izquierda y a los mayores a la derecha. Luego repite recursivamente el proceso en ambos lados.
* **Análisis de Complejidad:**
  * **Tiempo:** $\mathcal{O}(N \log N)$. El proceso logarítmico (cortar por la mitad) reduce exponencialmente la cantidad de comparaciones necesarias.
  * **Espacio:** $\mathcal{O}(\log N)$ debido a las llamadas en la pila de recursión (Stack Frame). Para listas enlazadas en C, Merge Sort no requiere arreglos auxiliares $O(N)$, haciéndolo excepcionalmente eficiente.
* **Uso en Producción:** **Es el estándar de la industria (Industry Standard).** Lenguajes como Java, Python y C++ utilizan variantes de este paradigma bajo el capó en sus funciones nativas (como `Timsort` o `Introsort`). Es la única forma viable de ordenar millones de registros (bases de datos, Big Data).

---

### 4. Backtracking (Bogo Sort estructurado)

El **Backtracking** (Retroceso) es una técnica de búsqueda en árboles que explora un camino para resolver un problema, y si descubre que ese camino es un callejón sin salida, "retrocede" sobre sus pasos para intentar un camino alternativo.

* **Enfoque en el código ([`src/backtracking.c`](src/backtracking.c)):** Adaptado como un modelo de demostración matemático. El programa explora el inmenso árbol de todas las *permutaciones posibles* de la lista. Intercambia valores, avanza, si no está ordenada deshace el intercambio (Backtrack) y prueba con el siguiente. Sigue iterando a ciegas hasta que, por coincidencia, el árbol choca con la combinación perfectamente ordenada.
* **Análisis de Complejidad:**
  * **Tiempo:** $\mathcal{O}(N!)$ (Factorial).
  * **Espacio:** $\mathcal{O}(N)$ (Profundidad máxima del árbol de recursión).
* **Uso en Producción:** **Jamás.** Es un anti-patrón. Matemáticamente, ordenar apenas $15$ personas requeriría $1.3 \times 10^{12}$ (un billón) de comprobaciones. Sirve exclusivamente en la teoría de la computación para demostrar comportamientos intratables (NP-Hard / Factoriales).

---

### Mención Honorífica: Programación Dinámica

La **Programación Dinámica (PD)** consiste en resolver problemas superpuestos dividiéndolos, pero con la característica clave de guardar (cachear/memorizar) los resultados de cálculos pesados para jamás repetirlos.
*¿Por qué no está presente como un algoritmo individual aquí?* Porque en una lista enlazada simple que solo se ordena por un entero (`edad`), **no existe** ningún cálculo pesado que valga la pena memorizar. La PD brilla en el ordenamiento únicamente cuando la condición de orden (peso) deriva de una operación computacionalmente masiva (ej. ordenar bases de datos por distancia geográfica heurística calculada en tiempo real).

---

## Comparativa Resumida en la Ejecución (Benchmarks)

Al generar `100,000` registros aleatorios con nuestra herramienta de simulación, la abismal diferencia matemática de las notaciones "Big O" ( $\mathcal{O}$ ) se materializa en tiempos reales de procesador:

| Paradigma                    | Algoritmo            | N = 100,000 (Tiempos aprox) | ¿Escalabilidad Real?                 |
| :--------------------------- | :------------------- | :-------------------------- | :------------------------------------ |
| **Divide y Vencerás** | Merge Sort           | `0.03 segundos`           | **Óptima** (Escala a millones) |
| **Divide y Vencerás** | Quick Sort           | `0.30 segundos`           | Excelente                             |
| **Codicioso**          | Selection Sort       | `10.27 segundos`          | Colapsa a gran escala                 |
| **Fuerza Bruta**       | Bubble Sort          | `38.91 segundos`          | Totalmente inviable                   |
| **Backtracking**       | Árbol Permutacional | `> 1,000,000 de años`    | Intratable (Limitado a N=6)           |

---


## Guía de Uso del Menú Interactivo (CLI)

Hemos construido una aplicación de consola en C automatizada con `Makefile` para facilitar la experimentación sin alterar el código fuente.

1. **Compilación en Linux:**
   Simplemente abre tu terminal en este directorio y teclea:
   ```bash
   make
   ```
2. **Lanzamiento:**
   Esto te generará un binario interactivo. Ejecútalo así:
   ```bash
   ./bin/comparacion
   ```
3. **Flujo de la Aplicación:**
   * Primero, ingresa la opción `1` para generar `N` datos sintéticos en memoria viva. (Se te preguntará la cantidad).
   * Luego, puedes oprimir `3` para que el sistema cree copias profundas de la memoria y ejecute una carrera de rendimiento con todos los algoritmos al mismo tiempo.
   * Si usas la opción `4`, podrás enfocarte en ver paso a paso cómo un solo algoritmo hace su magia, dándote la opción de imprimir a las primeras (o últimas) personas de la lista para verificar empíricamente su correcto ordenamiento.
