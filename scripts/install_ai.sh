#!/bin/bash
# ============================================
# LazyA AI Installation Script
# ============================================
# This script installs Ollama and downloads
# the required AI models for LazyA compiler.
# ============================================

set -e

echo "==================================="
echo " LazyA AI Setup"
echo "==================================="

# Check if Ollama is already installed
if command -v ollama &> /dev/null; then
    echo "[✓] Ollama is already installed."
else
    echo "[*] Installing Ollama..."
    curl -fsSL https://ollama.com/install.sh | sh
    echo "[✓] Ollama installed successfully."
fi

# Start Ollama service if not running
if ! pgrep -x "ollama" > /dev/null; then
    echo "[*] Starting Ollama service..."
    ollama serve &
    sleep 3
fi

# Download required models
echo ""
echo "[*] Downloading AI models (this may take a while)..."
echo ""

# Primary model for code generation
echo "[1/2] Downloading codellama:7b (code generation)..."
ollama pull codellama:7b

# Secondary model for fast operations
echo "[2/2] Downloading qwen2:0.5b (fast operations)..."
ollama pull qwen2:0.5b

echo ""
echo "==================================="
echo " Installation Complete!"
echo "==================================="
echo ""
echo "Available models:"
echo "  - codellama:7b  (default for code generation)"
echo "  - qwen2:0.5b    (fast mode for simple tasks)"
echo ""
echo "You can now compile LazyA programs with AI features:"
echo "  ./build/lazya examples/ex04_ai_assistant.lazy"
echo ""
