#!/bin/bash
# Lazy Uninstall Script

LAZY_HOME="${LAZY_HOME:-$HOME/.lazy}"
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}[UNINSTALL]${NC} Removing Lazy..."

if [ -d "$LAZY_HOME" ]; then
    rm -rf "$LAZY_HOME"
    echo -e "${GREEN}[OK]${NC} Removed $LAZY_HOME"
else
    echo -e "${RED}[ERROR]${NC} $LAZY_HOME not found"
fi

# Clean simple symlinks in /usr/local/bin if they exist
if [ -L "/usr/local/bin/lazy" ]; then
    sudo rm -f "/usr/local/bin/lazy"
    echo -e "${GREEN}[OK]${NC} Removed /usr/local/bin/lazy"
fi

echo -e "${BLUE}[INFO]${NC} To finish uninstallation, remove the Lazy configuration from your ~/.bashrc or ~/.zshrc manually."
echo -e "${GREEN}[DONE]${NC} Uninstallation complete."
