import csv
import random
import sys
import time

def generar_datos(n, archivo_salida="dataset.csv"):
    nombres_h = ["Juan", "Carlos", "Luis", "Pedro", "Miguel", "Andres", "Diego", "Fernando", "Jorge", "Mateo"]
    nombres_m = ["Maria", "Ana", "Laura", "Carmen", "Sofia", "Isabel", "Camila", "Valentina", "Lucia", "Elena"]
    apellidos = ["Garcia", "Martinez", "Rodriguez", "Lopez", "Perez", "Williams", "Gomez", "Silva", "Ruiz", "Gonzalez", "Hernandez", "Diaz"]

    print(f"Preparando la generación de {n:,} registros...")
    start_time = time.time()

    with open(archivo_salida, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        # Cabecera
        writer.writerow(["ID", "Nombre_Completo", "Sexo", "Edad", "Peso_kg", "Altura_cm"])

        # Para un rendimiento rápido en Python puro al generar millones de datos
        for i in range(1, n + 1):
            sexo = random.choice(["M", "F"])
            nombre = random.choice(nombres_h) if sexo == "M" else random.choice(nombres_m)
            apellido1 = random.choice(apellidos)
            apellido2 = random.choice(apellidos)
            nombre_completo = f"{nombre} {apellido1} {apellido2}"
            
            edad = random.randint(18, 90)
            peso = round(random.uniform(50.0, 110.0), 1)
            altura = random.randint(150, 200)

            writer.writerow([i, nombre_completo, sexo, edad, peso, altura])
            
            # Progress print
            if i % 1000000 == 0:
                print(f"... {i:,} registros generados.")

    elapsed = round(time.time() - start_time, 2)
    print(f"¡Generación completada en {elapsed} segundos! Datos guardados en '{archivo_salida}'.")

if __name__ == "__main__":
    # Valor por defecto: 10,000 registros
    n_registros = 10000
    if len(sys.argv) > 1:
        try:
            n_registros = int(sys.argv[1])
        except ValueError:
            print("Por favor provee un número entero válido.")
            sys.exit(1)
            
    generar_datos(n_registros, "dataset.csv")
