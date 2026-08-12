CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
TARGET = bin/comparacion
TARGET_MASIVO = bin/simulacion_masiva
OBJS = obj/lista.o obj/fuerza_bruta.o obj/codicioso.o obj/divide_y_venceras.o obj/backtracking.o

all: $(TARGET) $(TARGET_MASIVO)

$(TARGET): obj/main.o $(OBJS)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $(TARGET) obj/main.o $(OBJS)

$(TARGET_MASIVO): obj/main_masivo.o $(OBJS)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $(TARGET_MASIVO) obj/main_masivo.o $(OBJS)

obj/%.o: src/%.c include/lista.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj/ bin/
