#!/bin/bash

# ==============================================================================
# Script de Deploy para el Proyecto de Ordenamiento
# Repositorio: https://github.com/evalenciEAFIT/EstructurasDeDatos
# Carpeta de destino: OrdenaListaEnlazada
# ==============================================================================

echo "🚀 Iniciando proceso de deploy hacia Github..."

DIR_ORIGEN="/home/edi/DOCENCIA2026/EDA/T3/T3C/proyecto_ordenamiento"
REPO_URL="https://github.com/evalenciEAFIT/EstructurasDeDatos.git"
CARPETA_DESTINO="OrdenaListaEnlazada"
TMP_DIR="/tmp/deploy_estructuras_datos"

# 1. Clonar el repositorio en un directorio temporal
echo "📥 Clonando el repositorio remoto..."
rm -rf "$TMP_DIR"
git clone "$REPO_URL" "$TMP_DIR"

if [ ! -d "$TMP_DIR" ]; then
    echo "❌ Error: No se pudo clonar el repositorio."
    exit 1
fi

# 2. Crear la carpeta de destino si no existe dentro del repositorio
mkdir -p "$TMP_DIR/$CARPETA_DESTINO"

# 3. Copiar los archivos desde el origen al destino, ignorando compilados y sistema
echo "📦 Copiando archivos a $CARPETA_DESTINO..."
rsync -av --exclude='.git' --exclude='obj' --exclude='bin' --exclude='*.o' "$DIR_ORIGEN/" "$TMP_DIR/$CARPETA_DESTINO/"

# 4. Ir al directorio del repositorio y procesar en Git
cd "$TMP_DIR" || exit

echo "⚙️  Preparando archivos para commit..."
git add "$CARPETA_DESTINO"

# Verificar si hay cambios reales
if git diff --staged --quiet; then
    echo "✅ No hay cambios nuevos para subir."
    rm -rf "$TMP_DIR"
    exit 0
fi

read -p "📝 Ingresa el mensaje del commit (Enter para usar el por defecto): " mensaje
if [ -z "$mensaje" ]; then
    mensaje="✨ Actualizacion de OrdenaListaEnlazada: CLI moderno, espanol y graficas"
fi

echo "💾 Creando commit: '$mensaje'"
git commit -m "$mensaje"

# 5. Hacer push a la rama main
echo "☁️ Subiendo cambios a GitHub..."
git push origin main

# Limpiar directorio temporal
cd "$DIR_ORIGEN" || exit
rm -rf "$TMP_DIR"

echo "✅ ¡Deploy completado con éxito en $CARPETA_DESTINO!"
