#!/bin/bash
#
# LazyA - Update Script
# Recompiles the compiler after making changes

echo "==============================================="
echo "  LazyA Compiler - Update"
echo "==============================================="
echo ""

cd "$(dirname "$0")"

echo "[1/2] Recompiling LazyA..."
cd build
make -j$(nproc)
BUILD_STATUS=$?

if [ $BUILD_STATUS -ne 0 ]; then
    echo ""
    echo "[ERROR] Build failed"
    exit 1
fi

cd ..

echo ""
echo "[2/2] Verifying installation..."

if [ -f "build/lazya" ]; then
    echo "[OK] Compiler: build/lazya"
else
    echo "[ERROR] Compiler not found"
    exit 1
fi

if [ -L "/usr/local/bin/lazy" ]; then
    echo "[OK] Global command: lazy (already installed)"
else
    echo "[INFO] Global command not installed"
    echo "      Run: sudo ln -sf $(pwd)/lazy /usr/local/bin/lazy"
fi

echo ""
echo "==============================================="
echo "  Update Complete!"
echo "==============================================="
echo ""
echo "You can now use:"
echo "  ./lazy examples/test.lazy -e"
echo ""

if [ -L "/usr/local/bin/lazy" ]; then
    echo "Or from anywhere:"
    echo "  lazy /path/to/file.lazy -e"
    echo ""
fi

exit 0
