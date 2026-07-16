# ==========================================
# MAKEFILE - COMPILACIÓN AUTOMATIZADA PARA C
# ==========================================
# Un Makefile define un conjunto de reglas para decirle a la herramienta 'make' 
# cómo compilar y enlazar nuestros programas. Esto nos ahorra tener que escribir
# los largos comandos de gcc uno por uno en la terminal.

# -----------------------------------
# 1. VARIABLES
# -----------------------------------
# CC: Define el compilador de C que usaremos.
CC = gcc

# CFLAGS: Banderas (opciones) de compilación. 
# -Wall y -Wextra le dicen al compilador que nos alerte de posibles errores o malas prácticas.
CFLAGS = -Wall -Wextra

# SRCS: Un listado con todos nuestros archivos fuente (.c).
SRCS = lista_enlazada.c pila.c cola.c arbol.c tabla_hash.c grafo.c

# BINS: Esta variable toma el listado de arriba y reemplaza el ".c" por vacío "".
# Así obtenemos los nombres de los ejecutables que queremos generar (ej: de pila.c pasamos a pila).
BINS = $(SRCS:.c=)

# -----------------------------------
# 2. REGLA PRINCIPAL
# -----------------------------------
# 'all' es el objetivo por defecto que se corre al escribir "make" en la terminal.
# Le decimos que su meta principal es asegurar que existan todos los ejecutables definidos en $(BINS).
all: $(BINS)

# -----------------------------------
# 3. REGLA DE COMPILACIÓN GENÉRICA
# -----------------------------------
# Este es un patrón mágico:
# "%: %.c" significa "Para crear cualquier archivo ejecutable (%), necesitas su código fuente correspondiente (%.c)".
%: %.c
	# Las reglas deben ir indentadas con un tabulador real (no espacios).
	# $@: Es una variable automática de Make que significa "el nombre del objetivo" (ej. lista_enlazada).
	# $<: Significa "el nombre del archivo fuente" (ej. lista_enlazada.c).
	# Al final se traduce en: gcc -Wall -Wextra -o ejecutable fuente.c
	$(CC) $(CFLAGS) -o $@ $<

# -----------------------------------
# 4. REGLA DE LIMPIEZA
# -----------------------------------
# Se ejecuta corriendo "make clean" en la terminal.
# rm -f borra silenciosamente todos los ejecutables listados en $(BINS) para dejar limpio el directorio.
clean:
	rm -f $(BINS)
