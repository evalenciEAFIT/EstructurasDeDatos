#!/bin/bash
# ==========================================
# SCRIPT DE DESPLIEGUE A GITHUB
# ==========================================

# URL de tu perfil/repositorio
REPO_URL="https://github.com/evalenciEAFIT/EstructurasDeDatos.git"
BRANCH="main"

echo "Iniciando proceso de despliegue a GitHub..."

# 1. Verificar e inicializar git si es necesario
if [ ! -d ".git" ]; then
    echo "=> Inicializando nuevo repositorio Git..."
    git init
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
# Ejecutamos el commit. Si falla (por ejemplo, porque no hay cambios nuevos), el script continúa.
git commit -m "$COMMIT_MSG" || echo "=> (Aviso: No hay cambios nuevos para confirmar)"

# 4. Configurar el origen remoto
if ! git remote | grep -q "origin"; then
    echo "=> Configurando el origen remoto a $REPO_URL..."
    git remote add origin $REPO_URL
else
    echo "=> Actualizando URL del remoto origin..."
    git remote set-url origin $REPO_URL
fi

# 5. Push al repositorio con control de errores
echo "=> Subiendo cambios a la rama $BRANCH en GitHub..."
if git push -u origin $BRANCH; then
    echo "=========================================="
    echo "✅ ¡DESPLIEGUE EXITOSO!"
    echo "Revisa tus cambios en: https://github.com/evalenciEAFIT/EstructurasDeDatos"
    echo "=========================================="
else
    echo "=========================================="
    echo "❌ ERROR FATAL: Falló la subida a GitHub."
    echo ""
    echo "Posibles causas:"
    echo " 1. El repositorio no existe: Asegúrate de haber ido a GitHub.com y creado un repositorio vacío llamado 'EstructurasDeDatos'."
    echo " 2. Problema de Autenticación: Es posible que necesites configurar tu Personal Access Token (PAT) o llave SSH."
    echo " 3. URL incorrecta: ¿Tu usuario es exactamente 'evalenciEAFIT'?"
    echo "=========================================="
    exit 1
fi
