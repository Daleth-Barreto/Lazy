#!/bin/bash
# Script para instalar Ollama y configurar un modelo ligero

echo "======================================"
echo "  Instalación de Ollama para LazyA"
echo "======================================"
echo ""

# 1. Instalar Ollama
echo "Paso 1: Instalando Ollama..."
curl -fsSL https://ollama.com/install.sh | sh

if [ $? -ne 0 ]; then
    echo "❌ Error instalando Ollama"
    exit 1
fi

echo "✅ Ollama instalado"
echo ""

# 2. Iniciar servicio Ollama
echo "Paso 2: Iniciando servicio Ollama..."
ollama serve &
OLLAMA_PID=$!
sleep 5

# 3. Descargar modelo súper ligero
echo "Paso 3: Descargando modelo ligero..."
echo "Opciones:"
echo "  - qwen2:0.5b (500MB) - MUY ligero"
echo "  - tinyllama (637MB) - Ligero"
echo "  - phi3:mini (2.3GB) - Pequeño"
echo ""

# Descargar el modelo más ligero
echo "Descargando qwen2:0.5b (modelo más ligero)..."
ollama pull qwen2:0.5b

if [ $? -eq 0 ]; then
    echo "✅ Modelo qwen2:0.5b descargado"
else
    echo "⚠️  Intentando con tinyllama..."
    ollama pull tinyllama
fi

echo ""
echo "======================================"
echo "  Instalación Completa"
echo "======================================"
echo ""
echo "Para usar Ollama:"
echo "  1. Asegúrate de que el servicio esté corriendo:"
echo "     ollama serve"
echo ""
echo "  2. Listar modelos instalados:"
echo "     ollama list"
echo ""  
echo "  3. Probar el modelo:"
echo "     ollama run qwen2:0.5b"
echo ""
echo "Modelos disponibles para descargar:"
echo "  - qwen2:0.5b    (500MB)  - Super ligero"
echo "  - tinyllama     (637MB)  - Ligero"
echo "  - phi3:mini     (2.3GB)  - Pequeño pero potente"
echo "  - llama3.2:1b   (1.3GB)  - Ligero, buena calidad"
echo ""
