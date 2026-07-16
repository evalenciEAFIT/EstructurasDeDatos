#!/bin/bash
# ==========================================
# SCRIPT DE DESPLIEGUE A GITHUB
# ==========================================

# URL de tu perfil/repositorio. 
# Si tu repositorio en GitHub tiene otro nombre, ajusta "EstructurasDeDatos.git"
REPO_URL="https://github.com/evalenciEAFIT/EstructurasDeDatos.git"
BRANCH="main"

echo "Iniciando proceso de despliegue a GitHub..."

# 1. Verificar e inicializar git si es necesario
if [ ! -d ".git" ]; then
    echo "=> Inicializando nuevo repositorio Git..."
    git init
    # Asegurarnos de que la rama principal se llame 'main'
    git branch -M $BRANCH
fi

# 2. Agregar archivos
echo "=> Agregando archivos al Stage..."
git add .

# 3. Solicitar mensaje de commit al usuario
echo -n "Introduce el mensaje del commit (Presiona ENTER para usar mensaje por defecto): "
read COMMIT_MSG

if [ -z "$COMMIT_MSG" ]; then
    COMMIT_MSG="Actualización de estructuras de datos (C & Python)"
fi

echo "=> Creando commit con el mensaje: '$COMMIT_MSG'"
git commit -m "$COMMIT_MSG"

# 4. Configurar el origen remoto
if ! git remote | grep -q "origin"; then
    echo "=> Configurando el origen remoto a $REPO_URL..."
    git remote add origin $REPO_URL
else
    echo "=> Actualizando URL del remoto origin..."
    git remote set-url origin $REPO_URL
fi

# 5. Push al repositorio
echo "=> Subiendo cambios a la rama $BRANCH en GitHub..."
git push -u origin $BRANCH

echo "=========================================="
echo "¡Despliegue finalizado!"
echo "Revisa tus cambios en: https://github.com/evalenciEAFIT/EstructurasDeDatos"
echo "=========================================="
