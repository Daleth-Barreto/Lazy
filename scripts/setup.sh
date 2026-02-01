#!/bin/bash
# Setup script for LazyA development environment

set -e

echo "🚀 LazyA Development Environment Setup"
echo "======================================"

# Check for required tools
echo "Checking dependencies..."

# Check C++ compiler
if ! command -v g++ &> /dev/null; then
    echo "g++ not found. Installing..."
    sudo apt-get update
    sudo apt-get install -y build-essential
else
    echo "g++ found: $(g++ --version | head -n 1)"
fi

# Check CMake
if ! command -v cmake &> /dev/null; then
    echo "CMake not found. Installing..."
    sudo apt-get install -y cmake
else
    echo "CMake found: $(cmake --version | head -n 1)"
fi

# Check Flex
if ! command -v flex &> /dev/null; then
    echo "Flex not found. Installing..."
    sudo apt-get install -y flex
else
    echo "Flex found: $(flex --version)"
fi

# Check Bison
if ! command -v bison &> /dev/null; then
    echo "Bison not found. Installing..."
    sudo apt-get install -y bison
else
    echo "Bison found: $(bison --version | head -n 1)"
fi

# Check for LLVM
echo "Checking LLVM..."
if ! command -v llvm-config &> /dev/null; then
    echo "LLVM not found. Installing LLVM 14..."
    sudo apt-get install -y llvm-14 llvm-14-dev
    sudo ln -sf /usr/bin/llvm-config-14 /usr/bin/llvm-config
else
    echo "LLVM found: $(llvm-config --version)"
fi

# Setup TensorFlow Lite
echo ""
echo "Setting up TensorFlow Lite..."
TFLITE_DIR="$HOME/.lazya/tensorflow-lite"

if [ ! -d "$TFLITE_DIR" ]; then
    echo "Downloading TensorFlow Lite..."
    mkdir -p "$TFLITE_DIR"
    cd "$TFLITE_DIR"
    
    # Download pre-built TensorFlow Lite
    wget -q https://github.com/tensorflow/tensorflow/archive/refs/tags/v2.13.0.tar.gz
    echo "Extracting..."
    tar -xzf v2.13.0.tar.gz
    
    # Build TensorFlow Lite
    echo "Building TensorFlow Lite (this may take a while)..."
    cd tensorflow-2.13.0
    
    # Install bazel if needed
    if ! command -v bazel &> /dev/null; then
        echo "Installing Bazel..."
        sudo apt-get install -y bazel
    fi
    
    # Build
    bazel build -c opt //tensorflow/lite:libtensorflowlite.so
    
    # Copy libraries
    mkdir -p "$TFLITE_DIR/lib"
    mkdir -p "$TFLITE_DIR/include"
    cp bazel-bin/tensorflow/lite/libtensorflowlite.so "$TFLITE_DIR/lib/"
    cp -r tensorflow/lite "$TFLITE_DIR/include/"
    
    echo "TensorFlow Lite installed to $TFLITE_DIR"
else
    echo "TensorFlow Lite already installed at $TFLITE_DIR"
fi

# Download a sample embedding model
echo ""
echo "Downloading sample embedding model..."
MODELS_DIR="$(dirname "$0")/../models"
mkdir -p "$MODELS_DIR"

if [ ! -f "$MODELS_DIR/sentence_encoder.tflite" ]; then
    echo "Downloading Universal Sentence Encoder..."
    cd "$MODELS_DIR"
    # Note: In production, download actual model
    # For now, create placeholder
    echo "Model download placeholder - implement in production"
    touch sentence_encoder.tflite
else
    echo "Embedding model already exists"
fi

# Create build directory
echo ""
echo "Creating build directory..."
cd "$(dirname "$0")/.."
mkdir -p build

echo ""
echo "Setup complete!"
echo ""
echo "Next steps:"
echo "  1. cd build"
echo "  2. cmake .. -DTENSORFLOW_LITE_DIR=$TFLITE_DIR"
echo "  3. make"
echo "  4. ./lazya ../examples/01_hello_world.lazy"
echo ""
echo "Happy coding with LazyA!"
