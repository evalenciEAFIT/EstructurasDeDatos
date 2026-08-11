# ==========================================
# ESTRUCTURA DE DATOS: COLA (QUEUE)
# ==========================================
# Explicación Detallada:
# Una Cola funciona bajo el principio FIFO (First In, First Out)
# o "Primero en entrar, Primero en salir". 
# Es análoga a la fila de un banco: la primera persona en llegar es la primera en ser atendida.
# - Encolar (Enqueue): Agregar al final.
# - Desencolar (Dequeue): Retirar del inicio (el frente).

from collections import deque

class Cola:
    def __init__(self):
        # Usamos deque (Double Ended Queue) de la librería estándar, ya que
        # es mucho más eficiente para eliminar elementos al inicio que una lista normal (O(1) vs O(n)).
        self.elementos = deque()

    # INSERCIÓN (Encolar)
    # Proceso: El nuevo elemento siempre se inserta al final de la cola.
    def encolar(self, dato):
        self.elementos.append(dato)
        print(f"Encolado al final: {dato}")

    # ELIMINACIÓN (Desencolar)
    # Proceso: Si la cola tiene elementos, extraemos el primero (el del frente).
    def desencolar(self):
        if self.elementos:
            # popleft() retira y devuelve el primer elemento del deque
            return self.elementos.popleft()
        print("La cola está vacía.")
        return None

    # RECORRIDO
    # Proceso: Mostramos todos los elementos desde el frente hacia el final.
    def recorrer(self):
        print("Cola actual (frente a final):", list(self.elementos))

if __name__ == "__main__":
    c = Cola()
    c.encolar("Cliente A")
    c.encolar("Cliente B")
    c.encolar("Cliente C")
    c.recorrer()
    print("Atendiendo a (Desencolado):", c.desencolar())
    c.recorrer()