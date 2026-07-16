# ==========================================
# ESTRUCTURA DE DATOS: TABLA HASH
# ==========================================
# Explicación Detallada:
# Una Tabla Hash permite accesos sumamente rápidos (O(1) en el mejor caso) mapeando 
# una "clave" (como un texto o identificador) a un "valor".
# Utiliza una "función hash" que convierte la clave en un índice numérico dentro 
# de un arreglo (o lista).
# Colisiones: Si dos claves distintas producen el mismo índice, se produce una colisión.
# Aquí manejamos colisiones mediante "encadenamiento": cada índice almacena una lista
# donde agregamos los pares [clave, valor] que colisionen ahí.

class TablaHash:
    def __init__(self, tamano):
        self.tamano = tamano
        # Crear 'tamano' cantidad de listas vacías (cubetas)
        self.tabla = [[] for _ in range(self.tamano)]

    # FUNCIÓN HASH
    # Proceso: Usa la función nativa hash() de Python, y aplica el operador módulo (%)
    # para asegurar que el índice resultante no exceda el tamaño de nuestra tabla.
    def _hash(self, clave):
        return hash(clave) % self.tamano

    # INSERCIÓN
    # Proceso:
    # 1. Calculamos el índice para la clave.
    # 2. Revisamos si la clave ya existe en la cubeta (la lista ubicada en ese índice).
    # 3. Si existe, actualizamos su valor. Si no existe, agregamos el par [clave, valor].
    def insertar(self, clave, valor):
        indice = self._hash(clave)
        cubeta = self.tabla[indice]
        
        for par in cubeta:
            if par[0] == clave:
                par[1] = valor # Actualizar valor existente
                return
        # Si no existe, lo agregamos a la cubeta
        cubeta.append([clave, valor])

    # BÚSQUEDA
    # Proceso:
    # 1. Calculamos el índice a partir de la clave.
    # 2. Iteramos solo sobre la pequeña lista contenida en ese índice.
    # 3. Si hallamos la clave, devolvemos el valor.
    def buscar(self, clave):
        indice = self._hash(clave)
        for par in self.tabla[indice]:
            if par[0] == clave:
                return par[1]
        return None # No encontrado

    # RECORRIDO
    # Muestra el contenido de todas las cubetas (índices del arreglo).
    def recorrer(self):
        print("Estado de la Tabla Hash:")
        for i, cubeta in enumerate(self.tabla):
            print(f" Índice {i}: {cubeta}")

if __name__ == "__main__":
    # Creamos una tabla muy pequeña (5) para forzar colisiones si ingresamos muchos datos
    th = TablaHash(5)
    th.insertar("nombre", "Juan")
    th.insertar("edad", 30)
    th.insertar("profesion", "Ingeniero")
    
    th.recorrer()
    print("\nBuscando 'edad':", th.buscar("edad"))