# Rendimiento y Memoria en Listas Enlazadas

El programa desarrollado `lista_rendimiento.c` demuestra dos conceptos avanzados en la gestión de estructuras de datos:
1.  **Medición de Tiempo:** Cuánto tarda el procesador en ejecutar las operaciones.
2.  **Consumo de Memoria:** Cuánta memoria RAM en bytes solicita el programa durante su ejecución.

## Medición del Tiempo (Rendimiento)

Para medir el tiempo en C utilizamos la librería `<time.h>`.

### Función principal: `clock()`
Esta función devuelve la cantidad de "ticks de reloj" que han transcurrido desde que el programa inició. Para medir cuánto dura una función específica:
1.  Llamamos a `clock()` **antes** de la operación.
2.  Llamamos a `clock()` **después** de la operación.
3.  Calculamos la diferencia y la dividimos por la macro `CLOCKS_PER_SEC` para obtener el tiempo en segundos reales.

```c
#include <time.h>

clock_t inicio = clock();
// ... código a medir (ej. un ciclo for gigante) ...
clock_t fin = clock();

// Diferencia en segundos
double segundos = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
printf("La operacion tardo %f segundos\n", segundos);
```

### Comportamiento del tiempo en las listas enlazadas:
*   **Inserción al principio:** Es **instantánea** (tiempo constante u O(1)), no importa si hay 1 elemento o 1 millón, el tiempo de insertar es el mismo.
*   **Búsqueda / Eliminación (peor caso):** Si el elemento a buscar está al final de la lista, el tiempo será proporcional a la cantidad de nodos (tiempo lineal u O(n)). En una lista de 100,000 elementos, tardará 100,000 veces más que el primer elemento.

---

## Rastreo de Memoria Dinámica

Las listas enlazadas solicitan memoria dinámicamente mediante la función `malloc()` y la liberan con `free()`.
Para medir la memoria, creamos una variable global (ej. `memoriaTotalAsignada`) que incrementa cuando creamos un nodo y se reduce cuando lo eliminamos.

```c
size_t memoriaTotalAsignada = 0; // Se inicializa en cero

// Al crear (en la función de Inserción):
memoriaTotalAsignada += sizeof(struct Nodo); 

// Al destruir (en la función Eliminar):
memoriaTotalAsignada -= sizeof(struct Nodo);
```

### ¿Cuánto pesa un Nodo?
Si utilizamos `sizeof(struct Nodo)`, C calcula el tamaño combinando el peso de los componentes:
*   La estructura `Persona`: `char[50]` (50 bytes) + `float` (4 bytes) + `float` (4 bytes) = 58 bytes.
*   El apuntador `*siguiente`: Usualmente 8 bytes en procesadores de 64 bits.
*   *Nota: Por temas de alineamiento de memoria del procesador (Padding), el peso final del nodo puede ser ligeramente superior a la suma exacta (ej. 72 bytes).*

Por tanto, 100,000 nodos consumirían aproximadamente **7 MB (Megabytes)** de memoria RAM, y podemos ver matemáticamente este impacto usando nuestro rastreador de memoria.
