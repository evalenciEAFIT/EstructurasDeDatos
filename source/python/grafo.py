# ==========================================
# ESTRUCTURA DE DATOS: GRAFO (Lista de Adyacencia)
# ==========================================
# Explicación Detallada:
# Un grafo modela relaciones entre objetos. Consiste en 'Vértices' (nodos) y 'Aristas' 
# (conexiones entre ellos).
# En esta implementación usamos "Listas de Adyacencia", que es un diccionario donde 
# la clave es un vértice y su valor es una lista con todos los vértices a los que está conectado.
# Esto es muy eficiente en términos de memoria para grafos dispersos (pocas conexiones).

class Grafo:
    def __init__(self):
        # adj será un diccionario, por ej: {'A': ['B', 'C'], 'B': ['A']}
        self.adj = {}

    # INSERCIÓN (Agregar Vértice y Arista)
    # Proceso: Si los nodos u y v no existen en el diccionario, se crean listas vacías.
    # Como es un grafo NO dirigido, u se conecta con v, y v se conecta con u.
    def agregar_arista(self, u, v):
        if u not in self.adj: self.adj[u] = []
        if v not in self.adj: self.adj[v] = []
        
        self.adj[u].append(v)
        self.adj[v].append(u) # Omitir esta línea para hacer un Grafo Dirigido

    # RECORRIDO / BÚSQUEDA (BFS - Búsqueda en Anchura)
    # Proceso Detallado:
    # 1. Se usa una estructura 'Cola' y un conjunto 'visitados' para evitar ciclos.
    # 2. Agregamos el nodo inicial a la cola y lo marcamos visitado.
    # 3. Mientras la cola no esté vacía, sacamos el nodo y exploramos todos sus "vecinos".
    # 4. Si los vecinos no han sido visitados, los encolamos y los marcamos visitados.
    # El BFS sirve para explorar por "capas" de distancia.
    def bfs(self, inicio):
        visitados = set([inicio])
        cola = [inicio]
        recorrido = []
        
        while cola:
            nodo = cola.pop(0) # Extraer frente de la cola (Dequeue)
            recorrido.append(nodo)
            
            # Explorar vecinos
            for vecino in self.adj.get(nodo, []):
                if vecino not in visitados:
                    visitados.add(vecino)
                    cola.append(vecino)
                    
        print(f"Recorrido BFS comenzando desde '{inicio}':", recorrido)

if __name__ == "__main__":
    g = Grafo()
    # Conexiones (Red de amigos, o carreteras)
    g.agregar_arista('A', 'B')
    g.agregar_arista('A', 'C')
    g.agregar_arista('B', 'D')
    g.agregar_arista('C', 'E')
    
    # Recorrer grafo
    g.bfs('A')