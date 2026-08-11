CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = comparacion
TARGET_MASIVO = simulacion_masiva
OBJS = lista.o fuerza_bruta.o codicioso.o divide_y_venceras.o backtracking.o

all: $(TARGET) $(TARGET_MASIVO)

$(TARGET): main.o $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) main.o $(OBJS)

$(TARGET_MASIVO): main_masivo.o $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET_MASIVO) main_masivo.o $(OBJS)

%.o: %.c lista.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET) $(TARGET_MASIVO)
