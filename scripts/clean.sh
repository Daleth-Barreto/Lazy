#!/bin/bash
# LazyA Cleanup Script
# Removes test executables and object files

echo "╔════════════════════════════════════════╗"
echo "║   LazyA Project Cleanup Script        ║"
echo "╚════════════════════════════════════════╝"
echo ""

cd "$(dirname "$0")/.."

echo "[1/3] Removing test executables..."
rm -f test* demo* var* t[0-9]* d[0-9]* simple* final* adv* 
rm -f baseline* complete* bitwise* io_* math_* a.out

echo "[2/3] Removing object files..."
rm -f *.o

echo "[3/3] Cleaning build artifacts..."
if [ -d "build" ]; then
    cd build
    make clean 2>/dev/null
    cd ..
fi

echo ""
echo "✓ Cleanup complete!"
echo ""
echo "Project directory is clean."
echo "Run './scripts/build.sh' to rebuild the compiler."
