# ==========================================
# MAKEFILE - GENERADOR DE DATOS (C)
# ==========================================

# Compilador y Banderas de optimización
CC = gcc
# Usamos -O3 para máxima velocidad de ejecución
CFLAGS = -Wall -Wextra -O3

# Nombre del archivo ejecutable de salida
TARGET = generar_datos_c

# Regla por defecto
all: $(TARGET)

# Cómo construir el binario
$(TARGET): generar_datos.c
	$(CC) $(CFLAGS) -o $(TARGET) generar_datos.c

# Regla para limpiar archivos temporales (binarios y datos)
clean:
	rm -f $(TARGET)
	rm -f dataset.csv
