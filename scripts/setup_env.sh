#!/bin/bash
# scripts/setup_env.sh - Automates dependency installation for LazyA

set -e

# Detect OS
if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
    VERSION_ID=$VERSION_ID
else
    DISTRO="unknown"
    VERSION_ID="unknown"
fi

if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
else
    OS="linux"
fi

echo "[INFO] Detected OS: $OS ($DISTRO $VERSION_ID)"

install_linux_deps() {
    # Update package lists
    sudo apt-get update

    # Install basic build tools
    sudo apt-get install -y build-essential cmake flex bison git curl \
        libcurl4-openssl-dev nlohmann-json3-dev libzstd-dev zlib1g-dev

    # Try installing LLVM 18 first (Universe repo on Ubuntu 24.04)
    # Use 'apt-cache show' to verify exact package existence, not just regex match
    if apt-cache show llvm-18 >/dev/null 2>&1; then
        echo "[INFO] Installing LLVM 18 from repository..."
        sudo apt-get install -y llvm-18 llvm-18-dev clang-18 libllvm-18-ocaml-dev libclang-18-dev
        
        # Create symlinks if needed (clang -> clang-18)
        # (This is optional but helpful for CMake if it doesn't find clang-18 automatically)
        if ! command -v clang &> /dev/null; then
            echo "[INFO] Creating clang symlink..."
            sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 100
            sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100
        fi
    else
        echo "[WARN] LLVM 18 not found in default repositories. Trying official script..."
        
        # Install script dependencies
        sudo apt-get install -y lsb-release wget software-properties-common gnupg

        # Run official LLVM script
        wget https://apt.llvm.org/llvm.sh
        chmod +x llvm.sh
        sudo ./llvm.sh 18
        rm llvm.sh
        
        # Install dev headers explicitly if script didn't
        sudo apt-get install -y llvm-18-dev libclang-18-dev
    fi
}

install_macos_deps() {
    if ! command -v brew &> /dev/null; then
        echo "[ERROR] Homebrew not found. Please install it first: https://brew.sh"
        exit 1
    fi

    echo "[INFO] Installing dependencies via Homebrew..."
    brew install cmake llvm@18 flex bison curl nlohmann-json zstd

    # Add llvm@18 to PATH for this session
    export PATH="/opt/homebrew/opt/llvm@18/bin:$PATH"
    echo "[INFO] Dependencies installed."
}

# Main execution
if [[ "$OS" == "linux" ]]; then
    if [[ "$DISTRO" == "ubuntu" ]] || [[ "$DISTRO" == "debian" ]]; then
        install_linux_deps
    else
        echo "[ERROR] Unsupported Linux distribution: $DISTRO"
        echo "Please install dependencies manually."
        exit 1
    fi
elif [[ "$OS" == "macos" ]]; then
    install_macos_deps
else
    echo "[ERROR] Unsupported OS: $OSTYPE"
    exit 1
fi

echo "[OK] Environment setup complete."
