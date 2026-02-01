#!/bin/bash

# Script para instalar la extensión LazyA en VSCode
echo "=== Instalando extensión LazyA para VSCode ==="

EXTENSION_PATH="$(dirname "$0")/lazya-0.1.0.vsix"

# Verificar que el archivo .vsix existe
if [ ! -f "$EXTENSION_PATH" ]; then
    echo "❌ Error: No se encuentra el archivo lazya-0.1.0.vsix"
    exit 1
fi

# Detectar el editor (VSCode o VSCodium)
if command -v code &> /dev/null; then
    EDITOR="code"
elif command -v codium &> /dev/null; then
    EDITOR="codium"
else
    echo "❌ Error: No se encontró VSCode ni VSCodium en el sistema"
    echo ""
    echo "Por favor, instala VSCode o realiza la instalación manual:"
    echo "1. Abre VSCode"
    echo "2. Presiona Ctrl+Shift+P"
    echo "3. Busca 'Extensions: Install from VSIX'"
    echo "4. Selecciona el archivo: $EXTENSION_PATH"
    exit 1
fi

echo "📦 Instalando extensión usando: $EDITOR"
$EDITOR --install-extension "$EXTENSION_PATH"

if [ $? -eq 0 ]; then
    echo "✅ Extensión instalada correctamente!"
    echo ""
    echo "Pasos siguientes:"
    echo "1. Reinicia VSCode si está abierto"
    echo "2. Abre cualquier archivo .lazy"
    echo "3. El syntax highlighting debería funcionar automáticamente"
else
    echo "❌ Error al instalar la extensión"
    exit 1
fi
