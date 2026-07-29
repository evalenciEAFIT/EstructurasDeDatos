"""
CONCEPTO: LISTAS ENLAZADAS EN PYTHON
En Python no necesitamos gestionar la memoria manualmente (no hay malloc ni free).
El recolector de basura (Garbage Collector) se encarga de liberar los objetos
cuando ya no hay variables apuntando a ellos.
"""

class Nodo:
    """
    Clase que representa un nodo de la lista enlazada.
    """
    def __init__(self, dato):
        self.dato = dato          # El valor entero (u otro tipo)
        self.siguiente = None     # Referencia al siguiente nodo (nuestro "apuntador")

class ListaEnlazada:
    def __init__(self):
        self.cabeza = None        # La lista inicia vacía

    def insertar_al_principio(self, valor):
        # 1. Creamos el nuevo nodo
        nuevo_nodo = Nodo(valor)
        # 2. Conectamos el nuevo nodo con el que era la cabeza actual
        nuevo_nodo.siguiente = self.cabeza
        # 3. La nueva cabeza es el nuevo nodo
        self.cabeza = nuevo_nodo
        print(f"Nodo con valor {valor} insertado.")

    def buscar(self, valor_buscado):
        actual = self.cabeza
        # Recorremos la lista mientras no lleguemos al final
        while actual is not None:
            if actual.dato == valor_buscado:
                return actual     # Retorna la referencia al objeto Nodo
            actual = actual.siguiente
        return None

    def modificar(self, valor_buscado, nuevo_valor):
        nodo_encontrado = self.buscar(valor_buscado)
        if nodo_encontrado is not None:
            nodo_encontrado.dato = nuevo_valor
            print(f"Valor {valor_buscado} modificado por {nuevo_valor} con éxito.")
        else:
            print(f"Error: No se encontró el valor {valor_buscado}.")

    def eliminar(self, valor_eliminar):
        temp = self.cabeza
        previo = None
        
        # Caso 1: El nodo a eliminar es la cabeza
        if temp is not None and temp.dato == valor_eliminar:
            self.cabeza = temp.siguiente
            # En Python, simplemente perdiendo la referencia al objeto original,
            # el recolector de basura lo eliminará de la RAM.
            print(f"Nodo {valor_eliminar} eliminado (era la cabeza).")
            return

        # Caso 2: Buscar en el resto de la lista
        while temp is not None and temp.dato != valor_eliminar:
            previo = temp
            temp = temp.siguiente
            
        # Si no se encontró
        if temp is None:
            print(f"Error: Nodo {valor_eliminar} no encontrado.")
            return
            
        # Desvinculamos el nodo
        previo.siguiente = temp.siguiente
        print(f"Nodo {valor_eliminar} eliminado de la lista.")

    def imprimir_lista(self):
        print("Estado de la lista: ", end="")
        actual = self.cabeza
        while actual is not None:
            print(f"{actual.dato} -> ", end="")
            actual = actual.siguiente
        print("None\n")


# Bloque de pruebas
if __name__ == "__main__":
    lista = ListaEnlazada()
    
    lista.insertar_al_principio(10)
    lista.insertar_al_principio(20)
    lista.insertar_al_principio(30)
    lista.insertar_al_principio(40)
    lista.imprimir_lista()
    
    resultado = lista.buscar(20)
    if resultado:
        print(f"Búsqueda: Se encontró el nodo con valor {resultado.dato}.\n")
        
    lista.modificar(30, 35)
    lista.imprimir_lista()
    
    lista.eliminar(40)
    lista.imprimir_lista()
    
    lista.eliminar(10)
    lista.imprimir_lista()
