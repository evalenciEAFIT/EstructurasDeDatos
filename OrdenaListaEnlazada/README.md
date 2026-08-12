# Arquitectura y Comparación de Paradigmas Algorítmicos en Ordenamiento

Este proyecto en C explora y contrasta de forma práctica los principales paradigmas de diseño de algoritmos de la ciencia de la computación. Todo esto se aplica sobre un problema central: **Ordenar una lista enlazada simple de estructuras `Persona` (Nombre y Edad) con base en su edad.**

## Paradigmas de Diseño Evaluados

En el ámbito del diseño de algoritmos, existen múltiples enfoques para atacar el mismo problema. A continuación, exploramos conceptualmente cada uno de ellos, su implementación en este proyecto y su pertinencia en la vida real.

---

### 1. Fuerza Bruta (Bubble Sort)

La **fuerza bruta** es el paradigma algorítmico más rudimentario. Se basa en una enumeración exhaustiva y evaluación iterativa sin aprovechar las propiedades estructurales del problema. Su lógica dicta probar todas las combinaciones o recorrer repetidamente la estructura de datos hasta alcanzar el estado deseado.

* **Enfoque en el código ([`src/fuerza_bruta.c`](src/fuerza_bruta.c)):** Implementado mediante *Bubble Sort*. El algoritmo recorre sistemáticamente toda la lista comparando adyacencias, arrastrando iterativamente los valores más altos hacia la cola de la estructura. 
* **Ventajas:** Fácil de razonar e implementar. No requiere memoria adicional (In-Place).
* **Desventajas:** Extremadamente ineficiente. Realiza comparaciones e intercambios redundantes por diseño.

---

### 2. Algoritmos Codiciosos / Greedy (Selection Sort)

El paradigma **codicioso (greedy)** toma decisiones sub-óptimas localmente en cada paso de su ejecución, esperando heurísticamente que la acumulación de decisiones localmente óptimas devenga en un resultado global óptimo. Nunca reconsidera una decisión pasada ni proyecta a futuro; actúa exclusivamente sobre la información actual.

* **Enfoque en el código ([`src/codicioso.c`](src/codicioso.c)):** Implementado mediante *Selection Sort*. Desde una posición fija, explora vorazmente el resto de la lista no procesada en busca del mínimo absoluto actual. Al hallarlo, lo intercambia a su lugar definitivo de un solo movimiento.
* **Ventajas:** Lógica intuitiva y control preciso sobre el número de operaciones de escritura (intercambios minimizados).
* **Desventajas:** Su voracidad local le impide ignorar grandes volúmenes de datos descartables, obligándolo a leer iterativamente el conjunto completo en cada paso.

---

### 3. Divide y Vencerás (Merge Sort y Quick Sort)

El enfoque **Divide y Vencerás (Divide and Conquer)** es la base computacional de la algoritmia moderna. Establece que los problemas masivos son matemáticamente inabordables como un todo. Su estrategia se divide en tres fases: **Dividir** el problema a la mitad recursivamente, **Conquistar** solucionando los micro-problemas base de manera trivial y **Combinar** las micro-soluciones para escalar nuevamente al problema completo.

* **Enfoque en el código ([`src/divide_y_venceras.c`](src/divide_y_venceras.c)):** Se incluyen dos exponentes históricos:
  * **Merge Sort (1945):** Fisión simétrica de la lista en sublistas individuales y subsecuente fusión ordenada (merge). Destaca por su estabilidad predictiva inquebrantable.
  * **Quick Sort (1959):** Partición asimétrica dictada por un *Pivote*. Clasifica menores a babor, mayores a estribor y se llama recursivamente. Extremadamente veloz gracias al cacheo interno del procesador.
* **Ventajas:** Optimización exponencial (logarítmica) del tiempo de procesamiento que domina masivos flujos de información en producción.
* **Desventajas:** Dependencia estructural de llamadas recursivas en el *Stack Frame* y posible consumo adicional de memoria temporal.

---

### 4. Backtracking (Bogo Sort estructurado)

El **Backtracking (Vuelta atrás)** es una técnica iterativa de búsqueda en profundidad aplicada sobre árboles de decisiones lógicas. Al encontrarse en una encrucijada, toma una rama; si descubre que dicha rama entra en conflicto o es un "callejón sin salida", retrocede cronológicamente (deshace los cambios) e intenta la siguiente alternativa de forma metódica.

* **Enfoque en el código ([`src/backtracking.c`](src/backtracking.c)):** Aunque el Backtracking no está diseñado para ordenar, lo hemos forzado construyendo el árbol de **todas las permutaciones posibles** de la lista. Intercambia iterativamente cada nodo generando ramas combinatorias y, al evaluar que la estructura no queda en ascenso, retrocede.
* **Ventajas:** Garantiza matemáticamente hallar todas y cada una de las soluciones posibles de un sistema de condiciones complejas.
* **Desventajas:** Su crecimiento exponencial y factorial ($\mathcal{O}(N!)$) colapsa irremediablemente el hardware ante un número minúsculo de entradas.

---

## Tabla de Comparación: Casos de Uso y Rendimiento de Ordenamiento

A continuación, una comparativa estructural detallando en qué tipo de problemas computacionales destacan históricamente estos paradigmas y cuál es su rendimiento matemático teórico aplicado al **ordenamiento estricto de datos** (que es el enfoque central de este proyecto).

| Paradigma | Casos de Uso Ideales (Naturaleza del problema) | Tiempo Promedio (Ordenamiento) | Rendimiento Real al Ordenar Datos |
| :--- | :--- | :---: | :--- |
| **Divide y Vencerás** | Manejo de Bases de Datos, *Big Data*, algoritmos geométricos, transformadas de Fourier (FFT). | $\mathcal{O}(N \log N)$ | **Estándar de Producción (Óptimo).** Es el motor interno en Python, C++ y Java (`sort()`). Capaz de procesar millones de registros instantáneamente. |
| **Codicioso (Greedy)** | Compresión (Huffman), enrutamiento de redes (Dijkstra), MST (Kruskal), memorias flash (solo lectura/baja escritura). | $\mathcal{O}(N^2)$ | **Ineficiente para masividad.** Al hacer pocas escrituras pero exhaustivas lecturas (O(N²)), su rendimiento escala mal y colapsa con *datasets* medianos. |
| **Fuerza Bruta** | Criptoanálisis primitivo, evaluación sistemática de subcadenas string microscópicas o introducciones académicas. | $\mathcal{O}(N^2)$ | **Deficiente.** Lecturas y escrituras redundantes masivas careciendo de optimización algorítmica. Inútil salvo en listas con menos de $50$ elementos. |
| **Backtracking** | Ajedrez (IA), sudokus, combinatoria, laberintos, grafos fuertemente restringidos por bloqueos. | $\mathcal{O}(N!)$ o $\mathcal{O}(c^N)$ | **Catastrófico.** Jamás se debe usar para ordenar por la explosión combinatoria inmanejable. Totalmente colapsado ante listas diminutas ($N \le 8$). |

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
