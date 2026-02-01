#!/bin/bash
# Quick build script for LazyA

set -e

echo "Building LazyA Compiler"
echo "=========================="

# Create build directory
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

cd build

# Configure with CMake (without AI for now)
echo "Configuring..."
cmake .. -DENABLE_AI=OFF

# Build
echo "Building..."
make -j$(nproc)

echo ""
if [ -f "lazya" ]; then
    echo "[SUCCESS] Build successful!"
    echo "Compiler: ./build/lazya"
    echo ""
    echo "Try: ./build/lazya --help"
else
    echo "[ERROR] Build failed"
    exit 1
fi
