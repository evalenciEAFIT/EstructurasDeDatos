#!/bin/bash
# ==========================================
# SCRIPT DE DESPLIEGUE A GITHUB
# ==========================================

# URL de tu repositorio
REPO_URL="https://github.com/evalenciEAFIT/EstructurasDeDatos.git"
BRANCH="main"
FOLDER_NAME="Ordenamiento"

echo "Iniciando proceso de despliegue a GitHub en la carpeta '$FOLDER_NAME'..."

# Crear un directorio temporal
TEMP_DIR=$(mktemp -d)
echo "=> Clonando el repositorio en un directorio temporal..."
git clone $REPO_URL $TEMP_DIR

if [ $? -ne 0 ]; then
    echo "❌ ERROR: No se pudo clonar el repositorio. Verifica la URL y tu acceso."
    rm -rf $TEMP_DIR
    exit 1
fi

# Guardar el directorio actual
ORIGIN_DIR=$(pwd)

cd $TEMP_DIR || exit

# 1. Crear la carpeta si no existe
mkdir -p $FOLDER_NAME

# 2. Copiar archivos usando rsync
echo "=> Copiando archivos a la carpeta '$FOLDER_NAME'..."
# Usamos rsync para evitar copiar la carpeta .git y archivos de compilación
rsync -av --exclude='.git/' --exclude='*.o' --exclude='simulacion_masiva' --exclude='comparacion' "$ORIGIN_DIR/" "$FOLDER_NAME/"

# 3. Agregar los archivos al stage
echo "=> Agregando archivos al Stage..."
git add $FOLDER_NAME/

# 4. Solicitar mensaje de commit
echo -n "Introduce el mensaje del commit (Presiona ENTER para usar mensaje por defecto): "
read COMMIT_MSG

if [ -z "$COMMIT_MSG" ]; then
    COMMIT_MSG="Actualización de estructuras de datos (C & Python) en $FOLDER_NAME"
fi

echo "=> Creando commit con el mensaje: '$COMMIT_MSG'"
git commit -m "$COMMIT_MSG" || echo "=> (Aviso: No hay cambios nuevos para confirmar)"

# 5. Push al repositorio
echo "=> Subiendo cambios a la rama $BRANCH en GitHub..."
if git push origin $BRANCH; then
    echo "=========================================="
    echo "✅ ¡DESPLIEGUE EXITOSO!"
    echo "Revisa tus cambios en: https://github.com/evalenciEAFIT/EstructurasDeDatos/tree/main/$FOLDER_NAME"
    echo "=========================================="
else
    echo "=========================================="
    echo "❌ ERROR FATAL: Falló la subida a GitHub."
    echo "=========================================="
fi

# Limpieza
cd "$ORIGIN_DIR" || exit
rm -rf $TEMP_DIR
echo "=> Limpieza completada."
