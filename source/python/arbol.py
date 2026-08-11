# ==========================================
# ESTRUCTURA DE DATOS: ÁRBOL BINARIO DE BÚSQUEDA (BST)
# ==========================================
# Explicación Detallada:
# Un árbol es una estructura jerárquica y no lineal. En un Árbol Binario de Búsqueda,
# cada nodo tiene como máximo dos hijos (izquierdo y derecho).
# La regla clave (propiedad de búsqueda) es:
# - Todos los datos en el subárbol izquierdo son MENORES que el dato del nodo raíz.
# - Todos los datos en el subárbol derecho son MAYORES que el dato del nodo raíz.
# Esto hace que la búsqueda de elementos sea sumamente rápida, comparable a una 
# búsqueda binaria.

class NodoArbol:
    # Cada nodo guarda un valor y enlaces a sus posibles dos hijos.
    def __init__(self, dato):
        self.dato = dato
        self.izq = None
        self.der = None

class Arbol:
    def __init__(self):
        # El árbol comienza con una raíz vacía.
        self.raiz = None

    # INSERCIÓN
    # Proceso:
    # 1. Si la raíz está vacía, el nuevo dato forma la raíz.
    # 2. Si no, usamos un método recursivo interno para buscar su lugar.
    #    Si el dato es menor al nodo actual, nos movemos a la izquierda.
    #    Si el dato es mayor, nos movemos a la derecha, hasta encontrar un espacio libre (None).
    def insertar(self, dato):
        if not self.raiz:
            self.raiz = NodoArbol(dato)
        else:
            self._insertar(self.raiz, dato)

    def _insertar(self, nodo, dato):
        if dato < nodo.dato:
            if nodo.izq:
                self._insertar(nodo.izq, dato) # Seguir bajando
            else:
                nodo.izq = NodoArbol(dato)     # Insertar hoja
        else:
            if nodo.der:
                self._insertar(nodo.der, dato) # Seguir bajando
            else:
                nodo.der = NodoArbol(dato)     # Insertar hoja

    # RECORRIDO (Inorden)
    # Proceso: Visita el subárbol izquierdo, luego la raíz actual, luego el derecho.
    # En un árbol binario de búsqueda, ¡el recorrido Inorden imprime los valores ORDENADOS!
    def inorden(self, nodo):
        if nodo:
            self.inorden(nodo.izq)       # 1. Todo lo de la izquierda
            print(nodo.dato, end=" ")    # 2. El nodo en sí
            self.inorden(nodo.der)       # 3. Todo lo de la derecha

    # BÚSQUEDA
    # Proceso recursivo:
    # 1. Si el nodo actual es el buscado (o es None), terminamos.
    # 2. Si es menor, buscamos en el lado izquierdo.
    # 3. Si es mayor, buscamos en el derecho.
    def buscar(self, nodo, dato):
        if not nodo or nodo.dato == dato:
            return nodo is not None
        if dato < nodo.dato:
            return self.buscar(nodo.izq, dato)
        return self.buscar(nodo.der, dato)

if __name__ == "__main__":
    a = Arbol()
    # Insertando valores (50 va primero y es la raíz)
    a.insertar(50)
    a.insertar(30) # Va a la izquierda del 50
    a.insertar(70) # Va a la derecha del 50
    a.insertar(20) # Va a la izquierda del 30
    a.insertar(40) # Va a la derecha del 30

    print("Recorrido Inorden (Los datos deben salir de menor a mayor):")
    a.inorden(a.raiz)
    print("\n\n¿El 40 está en el árbol?:", a.buscar(a.raiz, 40))
    print("¿El 99 está en el árbol?:", a.buscar(a.raiz, 99))