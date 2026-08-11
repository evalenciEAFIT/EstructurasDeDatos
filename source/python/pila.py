# ==========================================
# ESTRUCTURA DE DATOS: PILA (STACK)
# ==========================================
# Explicación Detallada:
# Una Pila es una estructura de datos basada en el principio LIFO (Last In, First Out)
# o "Último en entrar, Primero en salir". 
# Imagina una pila de platos: solo puedes poner un plato encima del otro y para quitar 
# platos, debes empezar por el de arriba.
# Las operaciones principales son:
# - Apilar (Push): Agregar un elemento a la cima.
# - Desapilar (Pop): Retirar el elemento de la cima.

class Pila:
    def __init__(self):
        # Usamos una lista de Python subyacente para almacenar los elementos.
        # El final de la lista representará la 'cima' de la pila.
        self.elementos = []

    # INSERCIÓN (Push o Apilar)
    # Proceso: Agrega el dato al final de la lista interna (que simula la cima).
    def apilar(self, dato):
        self.elementos.append(dato)
        print(f"Apilado en la cima: {dato}")

    # ELIMINACIÓN (Pop o Desapilar)
    # Proceso: 
    # 1. Verifica si la pila tiene elementos.
    # 2. Si no está vacía, extrae y retorna el último elemento insertado (el de arriba).
    def desapilar(self):
        if not self.esta_vacia():
            # pop() en Python remueve y retorna el último elemento
            return self.elementos.pop()
        print("La pila está vacía.")
        return None

    # RECORRIDO
    # Proceso: Muestra los elementos desde el último (cima) hasta el primero (base).
    def recorrer(self):
        # Usamos slicing [::-1] para invertir la lista solo para visualizar de arriba hacia abajo
        print("Pila actual (cima a base):", self.elementos[::-1])

    # Utilidad para verificar si hay elementos
    def esta_vacia(self):
        return len(self.elementos) == 0

if __name__ == "__main__":
    p = Pila()
    p.apilar(1) # Base
    p.apilar(2)
    p.apilar(3) # Cima
    p.recorrer()
    print("Elemento desapilado:", p.desapilar())
    p.recorrer()