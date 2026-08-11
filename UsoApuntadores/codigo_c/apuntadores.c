#include <stdio.h>
#include <stdlib.h>

/*
 * UTILIDAD DE LOS APUNTADORES EN LA PROGRAMACIÓN:
 * 1. Paso por referencia: Permite que las funciones modifiquen las variables originales 
 *    en lugar de trabajar con copias.
 * 2. Gestión dinámica de memoria: Esencial para usar funciones como malloc() y crear 
 *    estructuras de datos dinámicas como las listas enlazadas.
 * 3. Manipulación eficiente de arrays y cadenas: Permite recorrer bloques de memoria 
 *    de manera muy rápida.
 * 4. Retorno de múltiples valores: Una función en C solo puede devolver un valor. 
 *    Los apuntadores permiten "devolver" múltiples datos modificando los argumentos.
 */

// --- Funciones de Ejemplo ---

// Función que recibe un valor por copia. Sus cambios no afectan a la variable original.
void modificarPorValor(int numero) {
    numero = 999;
}

// Función que recibe un apuntador (paso por referencia).
// Usamos '*' para modificar el valor que se encuentra en la dirección de memoria apuntada.
void modificarPorReferencia(int *ptr_numero) {
    *ptr_numero = 999; // Cambia el valor real en la memoria original
}

// Función que usa un doble apuntador (**).
// Sirve para modificar un apuntador en sí (hacer que apunte a otro lado).
// Si solo pasáramos un '*', modificaríamos una copia del apuntador, no el original.
void cambiarApunta(int **doble_ptr, int *nueva_direccion) {
    // '*doble_ptr' accede al apuntador original y lo cambia para que apunte a 'nueva_direccion'
    *doble_ptr = nueva_direccion;
}

int main() {
    printf("--- Explicacion de Apuntadores en C ---\n\n");

    // 1. EL OPERADOR '&' (Dirección de / Reference operator)
    int variable = 42;
    // '&variable' obtiene la dirección en la memoria RAM donde está guardada 'variable'.
    printf("Valor de 'variable': %d\n", variable);
    printf("Direccion de memoria de 'variable' (&variable): %p\n\n", (void*)&variable);

    // 2. EL APUNTADOR SIMPLE '*' (Pointer)
    // Se declara con '*', lo que significa "esta variable guardará una dirección de memoria".
    int *ptr = &variable; 
    
    printf("Valor que guarda 'ptr': %p (Es la misma direccion de 'variable')\n", (void*)ptr);
    // El operador '*' también se usa para "desreferenciar" (acceder al valor apuntado).
    printf("Valor al que apunta 'ptr' (*ptr): %d\n\n", *ptr);

    // 3. UTILIDAD: Modificar variables desde funciones (Paso por referencia)
    int a = 10;
    printf("Valor de 'a' ANTES de las funciones: %d\n", a);
    
    modificarPorValor(a);
    printf("Valor de 'a' DESPUES de modificarPorValor: %d (No cambia)\n", a);
    
    modificarPorReferencia(&a); // Pasamos la dirección de memoria usando '&'
    printf("Valor de 'a' DESPUES de modificarPorReferencia: %d (Se modifico!)\n\n", a);

    // 4. EL DOBLE APUNTADOR '**' (Apuntador a un Apuntador)
    int x = 100;
    int y = 200;
    int *ptr_principal = &x; // Apunta a 'x'
    
    printf("Actualmente 'ptr_principal' apunta a 'x'. Valor (*ptr_principal): %d\n", *ptr_principal);
    
    // Queremos que 'ptr_principal' ahora apunte a 'y', pero a través de una función.
    // Para ello, necesitamos enviar la dirección de memoria de nuestro apuntador.
    // La dirección de un apuntador a entero (int*) se recibe en un doble apuntador (int**).
    cambiarApunta(&ptr_principal, &y);
    
    printf("Despues de cambiarApunta, 'ptr_principal' apunta a 'y'. Valor (*ptr_principal): %d\n\n", *ptr_principal);
    
    printf("--- Fin de la Explicacion ---\n");
    return 0;
}
