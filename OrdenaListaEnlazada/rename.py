import os
import glob

replacements = {
    'create_persona': 'crear_persona',
    'insert_persona': 'insertar_persona',
    'free_list': 'liberar_lista',
    'generate_data': 'generar_datos',
    'copy_list': 'copiar_lista',
    'measure_time': 'medir_tiempo',
    'print_first_n_elements': 'imprimir_primeros_n_elementos',
    'print_last_n_elements': 'imprimir_ultimos_n_elementos',
    'sort_brute_force': 'ordenar_fuerza_bruta',
    'sort_greedy': 'ordenar_codicioso',
    'sort_divide_and_conquer': 'ordenar_divide_y_venceras',
    'sort_quick_sort': 'ordenar_quick_sort',
    'sort_backtracking': 'ordenar_backtracking',
    'is_sorted': 'esta_ordenado',
    'swap_personas': 'intercambiar_personas',
    'backtrack_permutations': 'permutaciones_backtracking',
    'sorted_merge': 'fusion_ordenada',
    'front_back_split': 'dividir_frente_atras',
    'get_tail': 'obtener_cola',
    'partition': 'particion',
    'quick_sort_recur': 'quick_sort_recursivo'
}

for filepath in glob.glob('src/*.c'):
    with open(filepath, 'r') as f:
        content = f.read()
    
    for old, new in replacements.items():
        content = content.replace(old, new)
        
    with open(filepath, 'w') as f:
        f.write(content)
