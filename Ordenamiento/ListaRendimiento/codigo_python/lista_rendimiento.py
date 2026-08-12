import time
import sys

"""
CONCEPTO: RENDIMIENTO EN PYTHON
Python es un lenguaje interpretado de alto nivel.
Por ello, es notablemente más lento que C, y sus objetos
consumen mucha más memoria RAM (cada objeto tiene un 
'overhead' por las funciones nativas y metadatos del lenguaje).

Aquí medimos el tiempo con time.perf_counter() y aproximamos la 
memoria con sys.getsizeof().
"""

class Persona:
    def __init__(self, nombre, peso, talla):
        self.nombre = nombre
        self.peso = peso
        self.talla = talla

class Nodo:
    def __init__(self, persona):
        self.dato = persona
        self.siguiente = None

class ListaRendimiento:
    def __init__(self):
        self.cabeza = None

    def insertar(self, persona):
        nuevo_nodo = Nodo(persona)
        nuevo_nodo.siguiente = self.cabeza
        self.cabeza = nuevo_nodo

    def buscar(self, nombre_buscado):
        actual = self.cabeza
        while actual is not None:
            if actual.dato.nombre == nombre_buscado:
                return actual
            actual = actual.siguiente
        return None

    def eliminar(self, nombre_eliminar):
        temp = self.cabeza
        previo = None

        if temp is not None and temp.dato.nombre == nombre_eliminar:
            self.cabeza = temp.siguiente
            return

        while temp is not None and temp.dato.nombre != nombre_eliminar:
            previo = temp
            temp = temp.siguiente

        if temp is None:
            return

        previo.siguiente = temp.siguiente


if __name__ == "__main__":
    lista = ListaRendimiento()
    
    print("=== PRUEBAS DE RENDIMIENTO Y MEMORIA EN PYTHON ===\n")
    
    # 1. PRUEBA DE INSERCIÓN MASIVA
    inicio = time.perf_counter()
    
    # Calcular memoria superficialmente
    memoria_estimada_bytes = 0
    
    for i in range(100000):
        p = Persona(f"Persona_{i}", 70.0, 1.75)
        n = Nodo(p)
        # sys.getsizeof() nos da los bytes del objeto en la RAM
        memoria_estimada_bytes += sys.getsizeof(p) + sys.getsizeof(n)
        
        # En vez de usar la función insertar y duplicar Nodos, 
        # enlazamos directamente para medir puramente
        n.siguiente = lista.cabeza
        lista.cabeza = n

    fin = time.perf_counter()
    
    print("1. Inserción de 100,000 nodos al principio:")
    print(f"-> Tiempo de operación: {fin - inicio:.6f} segundos")
    print(f"-> Uso de Memoria Dinámica (Aprox): {memoria_estimada_bytes} bytes (~{memoria_estimada_bytes // 1024} KB)\n")
    
    # 2. PRUEBA DE BÚSQUEDA
    inicio = time.perf_counter()
    busqueda = lista.buscar("Persona_0")
    fin = time.perf_counter()
    
    print("2. Búsqueda en el peor de los casos (elemento al final):")
    if busqueda:
        print(f"-> Encontrado: {busqueda.dato.nombre}")
    print(f"-> Tiempo de operación: {fin - inicio:.6f} segundos\n")
    
    # 3. PRUEBA DE ELIMINACIÓN
    inicio = time.perf_counter()
    lista.eliminar("Persona_0")
    fin = time.perf_counter()
    
    print("4. Eliminación del peor caso (elemento al final):")
    print(f"-> Tiempo de operación: {fin - inicio:.6f} segundos\n")
