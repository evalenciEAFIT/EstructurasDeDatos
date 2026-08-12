import os
import glob
import re

replacements = {
    'next': 'siguiente',
    'head': 'cabeza',
    'head_ref': 'ref_cabeza',
    'headRef': 'ref_cabeza',
    'new_node': 'nuevo_nodo',
    'curr': 'actual',
    'current': 'actual',
    'temp': 'temporal',
    'num_elements': 'num_elementos',
    'sort_function': 'funcion_ordenamiento',
    'data': 'datos',
    'name': 'nombre_algoritmo',
    'label': 'etiqueta',
    'new_head': 'nueva_cabeza',
    'newHead': 'nueva_cabeza',
    'curr_orig': 'actual_orig',
    'curr_new': 'actual_nuevo',
    'temp_name': 'nombre_temporal',
    'start': 'inicio',
    'end': 'fin',
    'start_index': 'indice_inicio',
    'count': 'contador',
    'frontRef': 'ref_frente',
    'backRef': 'ref_atras',
    'source': 'origen',
    'fast': 'rapido',
    'slow': 'lento',
    'newEnd': 'nuevo_fin',
    'pivot': 'pivote',
    'prev': 'anterior',
    'tail': 'cola'
}

for filepath in glob.glob('src/*.c') + ['include/lista.h']:
    with open(filepath, 'r') as f:
        content = f.read()
    
    for old, new in replacements.items():
        # Match only exact words to avoid sub-word replacements like replacing 'head' inside 'new_head'
        content = re.sub(r'\b' + old + r'\b', new, content)
        
    with open(filepath, 'w') as f:
        f.write(content)
