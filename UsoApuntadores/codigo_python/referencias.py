"""
CONCEPTO: "APUNTADORES" EN PYTHON (REFERENCIAS)

En Python no existen los operadores de punteros de C (& y *).
Sin embargo, Python funciona enteramente bajo un sistema de REFERENCIAS.

- Cada variable en Python no guarda el "valor", guarda la "referencia" (apuntador oculto)
  al objeto en memoria.
- Por ende, no necesitamos doble apuntadores (**) ni paso por referencia explícito para
  los objetos mutables (como Listas, Diccionarios y Clases creadas por nosotros).
"""

# 1. OBJETOS MUTABLES (Paso por referencia por defecto)
def modificar_lista(mi_lista):
    # Esto modifica el objeto en memoria RAM al que apunta la variable
    mi_lista.append(999)

# 2. OBJETOS INMUTABLES (Paso por valor simulado)
def modificar_numero(numero):
    # En Python, los números enteros (int) son inmutables.
    # Al hacer esto, no se cambia el número original, se crea un NUEVO objeto en RAM.
    numero = 999 

if __name__ == "__main__":
    print("--- Diferencia de Referencias en Python ---\n")
    
    # Prueba con objeto Mutable
    lista_original = [1, 2, 3]
    print(f"Lista ANTES de función: {lista_original}")
    modificar_lista(lista_original)
    print(f"Lista DESPUES de función: {lista_original} (¡Se modificó la original!)\n")
    
    # Prueba con objeto Inmutable
    entero_original = 10
    print(f"Entero ANTES de función: {entero_original}")
    modificar_numero(entero_original)
    print(f"Entero DESPUES de función: {entero_original} (No se modificó)\n")
    
    # En Python, si queremos crear variables separadas, debemos clonarlas.
    # Si solo las igualamos, ambas apuntarán (apuntador) a la misma memoria:
    variable_a = [10, 20]
    variable_b = variable_a  # variable_b es ahora un apuntador a la misma lista
    
    variable_b.append(30)
    print("Si igualamos variables (a = b):")
    print(f"Variable A: {variable_a}")
    print(f"Variable B: {variable_b}")
    print("Ambas cambian porque apuntan a la misma dirección física de memoria.")
