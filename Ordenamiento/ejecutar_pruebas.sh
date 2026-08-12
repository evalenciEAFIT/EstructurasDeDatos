#!/bin/bash
# Script para compilar y ejecutar las pruebas de ordenamiento

echo "Limpiando binarios antiguos..."
make clean

echo -e "\nCompilando proyecto..."
make

if [ $? -ne 0 ]; then
    echo "Error de compilacion."
    exit 1
fi

echo -e "\n======================================="
echo "EJECUTANDO PRUEBA ESTANDAR"
echo "======================================="
./comparacion

echo -e "\n======================================="
echo "EJECUTANDO SIMULACION MASIVA (100,000)"
echo "======================================="
./simulacion_masiva
