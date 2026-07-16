# ==========================================
# MAKEFILE - COMPILACIÓN AUTOMATIZADA PARA C
# ==========================================

# 1. VARIABLES
CC = gcc
CFLAGS = -Wall -Wextra

# Directorios de la nueva estructura
SRC_DIR = source/c
BIN_DIR = bin

# Obtener dinámicamente los archivos fuente y nombres de binarios
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Reemplaza source/c/archivo.c por bin/archivo
BINS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

# 2. REGLA PRINCIPAL
all: $(BIN_DIR) $(BINS)

# Asegurarse de que exista la carpeta bin/
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# 3. REGLA DE COMPILACIÓN GENÉRICA
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

# 4. REGLA DE LIMPIEZA
clean:
	rm -rf $(BIN_DIR)
