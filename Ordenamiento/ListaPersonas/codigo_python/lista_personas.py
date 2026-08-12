"""
CONCEPTO: LISTAS ENLAZADAS CON OBJETOS COMPLEJOS EN PYTHON
En Python, todo es un objeto. No necesitamos estructuras de tipo `struct`
porque podemos crear clases. Esto hace que el código sea mucho más legible 
y orientado a objetos. 

Además, la comparación de strings en Python se hace de forma nativa con `==`,
olvidando la necesidad del complejo `strcmp` de C.
"""

class Persona:
    """Clase que representa los datos que queremos almacenar."""
    def __init__(self, nombre, peso, talla):
        self.nombre = nombre
        self.peso = peso
        self.talla = talla

class Nodo:
    """El contenedor del dato."""
    def __init__(self, persona: Persona):
        self.dato = persona
        self.siguiente = None

class ListaPersonas:
    def __init__(self):
        self.cabeza = None

    def insertar(self, persona: Persona):
        nuevo_nodo = Nodo(persona)
        nuevo_nodo.siguiente = self.cabeza
        self.cabeza = nuevo_nodo
        print(f"Registro insertado: {persona.nombre}")

    def buscar(self, nombre_buscado):
        actual = self.cabeza
        while actual is not None:
            # En Python podemos comparar strings directamente con ==
            if actual.dato.nombre == nombre_buscado:
                return actual
            actual = actual.siguiente
        return None

    def modificar(self, nombre_buscado, nuevo_peso, nueva_talla):
        nodo = self.buscar(nombre_buscado)
        if nodo is not None:
            nodo.dato.peso = nuevo_peso
            nodo.dato.talla = nueva_talla
            print(f"Modificación exitosa para: {nombre_buscado}")
        else:
            print(f"Fallo: {nombre_buscado} no existe en la lista.")

    def eliminar(self, nombre_eliminar):
        temp = self.cabeza
        previo = None

        if temp is not None and temp.dato.nombre == nombre_eliminar:
            self.cabeza = temp.siguiente
            print(f"Eliminado (era la cabeza): {nombre_eliminar}")
            return

        while temp is not None and temp.dato.nombre != nombre_eliminar:
            previo = temp
            temp = temp.siguiente

        if temp is None:
            print(f"Fallo: {nombre_eliminar} no existe.")
            return

        # Desvincular el nodo. El recolector de basura de Python limpia la memoria.
        previo.siguiente = temp.siguiente
        print(f"Eliminado de la lista: {nombre_eliminar}")

    def imprimir(self):
        print("\n[ Estado Actual de la Lista ]")
        actual = self.cabeza
        if actual is None:
            print("(Vacía)")
            return
            
        while actual is not None:
            print(f" -> {actual.dato.nombre} ({actual.dato.peso} kg, {actual.dato.talla} m)")
            actual = actual.siguiente
        print()

if __name__ == "__main__":
    lista = ListaPersonas()
    
    lista.insertar(Persona("Juan Perez", 75.5, 1.75))
    lista.insertar(Persona("Ana Gomez", 62.0, 1.68))
    lista.insertar(Persona("Carlos Ruiz", 80.2, 1.80))
    
    lista.imprimir()
    
    lista.modificar("Ana Gomez", 60.0, 1.68)
    lista.eliminar("Juan Perez")
    
    lista.imprimir()
