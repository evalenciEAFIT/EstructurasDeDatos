#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char* nombres_h[] = {"Juan", "Carlos", "Luis", "Pedro", "Miguel", "Andres", "Diego", "Fernando", "Jorge", "Mateo"};
const char* nombres_m[] = {"Maria", "Ana", "Laura", "Carmen", "Sofia", "Isabel", "Camila", "Valentina", "Lucia", "Elena"};
const char* apellidos[] = {"Garcia", "Martinez", "Rodriguez", "Lopez", "Perez", "Williams", "Gomez", "Silva", "Ruiz", "Gonzalez", "Hernandez", "Diaz"};

// Función para obtener un double aleatorio en un rango
double rand_uniform(double min, double max) {
    double scale = rand() / (double) RAND_MAX; 
    return min + scale * ( max - min ); 
}

int main(int argc, char *argv[]) {
    long long n = 10000;
    
    // Si el usuario pasa un argumento, lo tomamos como N
    if (argc > 1) {
        n = atoll(argv[1]);
    }
    
    printf("Preparando la generación de %lld registros usando C...\n", n);
    
    FILE *file = fopen("dataset.csv", "w");
    if (file == NULL) {
        printf("Error fatal: No se pudo crear el archivo dataset.csv.\n");
        return 1;
    }
    
    // Imprimir cabecera CSV
    fprintf(file, "ID,Nombre_Completo,Sexo,Edad,Peso_kg,Altura_cm\n");
    
    // Inicializar semilla de aleatoriedad
    srand(time(NULL));
    
    for (long long i = 1; i <= n; i++) {
        char sexo = (rand() % 2 == 0) ? 'M' : 'F';
        
        const char* nombre;
        if (sexo == 'M') {
            nombre = nombres_h[rand() % 10];
        } else {
            nombre = nombres_m[rand() % 10];
        }
        
        const char* apellido1 = apellidos[rand() % 12];
        const char* apellido2 = apellidos[rand() % 12];
        
        int edad = 18 + rand() % (90 - 18 + 1);
        double peso = rand_uniform(50.0, 110.0);
        int altura = 150 + rand() % (200 - 150 + 1);
        
        // Escribir el registro en el archivo de texto
        fprintf(file, "%lld,%s %s %s,%c,%d,%.1f,%d\n", i, nombre, apellido1, apellido2, sexo, edad, peso, altura);
        
        // Progreso para el usuario
        if (i % 1000000 == 0) {
            printf("... %lld registros generados.\n", i);
        }
    }
    
    fclose(file);
    printf("¡Generación completada a la velocidad de C! Datos guardados en 'dataset.csv'.\n");
    
    return 0;
}
