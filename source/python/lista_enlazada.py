# ==========================================
# ESTRUCTURA DE DATOS: LISTA ENLAZADA
# ==========================================
# Explicación Detallada:
# Una lista enlazada es una estructura de datos lineal que consiste en una 
# secuencia de elementos (nodos). A diferencia de los arrays (arreglos convencionales), 
# los elementos de una lista enlazada no están almacenados en ubicaciones de memoria contiguas. 
# En cambio, cada nodo contiene un enlace (referencia o puntero) al siguiente nodo de la secuencia.
# Ventajas: Tamaño dinámico, inserción/eliminación eficiente sin desplazar elementos.

class Nodo:
    # La clase Nodo representa cada elemento individual de la lista.
    def __init__(self, dato):
        self.dato = dato         # 'dato' almacena la información útil (número, texto, etc.)
        self.siguiente = None    # 'siguiente' es la referencia al próximo nodo (None si es el último)

class ListaEnlazada:
    def __init__(self):
        # Al crear la lista, inicialmente no hay elementos, por lo que la 'cabeza' apunta a None.
        self.cabeza = None

    # INSERCIÓN (al final de la lista)
    # Proceso:
    # 1. Se crea un nuevo nodo con el dato proporcionado.
    # 2. Si la lista está vacía (self.cabeza es None), el nuevo nodo se convierte en el primer elemento.
    # 3. Si no está vacía, iteramos nodo por nodo usando un bucle 'while' hasta llegar al último nodo.
    # 4. Enlazamos el puntero 'siguiente' del último nodo al nuevo nodo que acabamos de crear.
    def insertar(self, dato):
        nuevo_nodo = Nodo(dato)
        if not self.cabeza:
            self.cabeza = nuevo_nodo
            return
        actual = self.cabeza
        while actual.siguiente:      # Avanzar mientras haya un nodo siguiente
            actual = actual.siguiente
        actual.siguiente = nuevo_nodo # El último nodo ahora apunta al nuevo nodo

    # RECORRIDO
    # Proceso:
    # 1. Empezamos en la cabeza (el primer elemento).
    # 2. Mientras el nodo actual no sea None, leemos su dato.
    # 3. Actualizamos la referencia al siguiente nodo (actual = actual.siguiente).
    def recorrer(self):
        elementos = []
        actual = self.cabeza
        while actual:
            elementos.append(actual.dato)
            actual = actual.siguiente
        print("Lista Enlazada:", " -> ".join(map(str, elementos)))

    # BÚSQUEDA
    # Proceso:
    # 1. Recorremos secuencialmente los nodos comparando el 'dato_buscado' con el 'dato' del nodo actual.
    # 2. Si coinciden, retornamos True (elemento encontrado).
    # 3. Si llegamos al final de la lista sin coincidencias, retornamos False.
    def buscar(self, dato_buscado):
        actual = self.cabeza
        while actual:
            if actual.dato == dato_buscado:
                return True
            actual = actual.siguiente
        return False

if __name__ == "__main__":
    lista = ListaEnlazada()
    lista.insertar(10)
    lista.insertar(20)
    lista.insertar(30)
    lista.recorrer()
    print("¿El 20 está en la lista?:", lista.buscar(20))