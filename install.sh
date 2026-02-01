#!/bin/bash
# LazyA Compiler - One-Command Installer
# Usage: curl -sSf https://lazya.dev/install.sh | sh
# Or: ./install.sh

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
LAZYA_HOME="${LAZYA_HOME:-$HOME/.lazya}"
LAZYA_BIN="$LAZYA_HOME/bin"
INSTALL_DIR="${INSTALL_DIR:-/usr/local/bin}"
USE_DOCKER="${USE_DOCKER:-auto}"

print_header() {
    echo ""
    echo -e "${BLUE}========╗${NC}"
    echo -e "${BLUE}       LazyA Compiler Installer            ${NC}"
    echo -e "${BLUE}       The AI-Native Language              ${NC}"
    echo -e "${BLUE}========╝${NC}"
    echo ""
}

info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

success() {
    echo -e "${GREEN}[OK]${NC} $1"
}

warning() {
    echo -e "${YELLOW}[!]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Detect OS
detect_os() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        OS="linux"
        if [ -f /etc/os-release ]; then
            . /etc/os-release
            DISTRO=$ID
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        OS="macos"
        DISTRO="macos"
    else
        OS="unknown"
        DISTRO="unknown"
    fi
}

# Check if command exists
has_command() {
    command -v "$1" >/dev/null 2>&1
}

# Install Docker if needed
install_docker() {
    info "Checking Docker installation..."
    
    if has_command docker; then
        success "Docker already installed: $(docker --version)"
        return 0
    fi
    
    warning "Docker not found. Installing Docker..."
    
    if [[ "$OS" == "linux" ]]; then
        # Install Docker on Linux
        if [[ "$DISTRO" == "ubuntu" ]] || [[ "$DISTRO" == "debian" ]]; then
            curl -fsSL https://get.docker.com -o get-docker.sh
            sudo sh get-docker.sh
            sudo usermod -aG docker $USER
            rm get-docker.sh
            success "Docker installed. You may need to log out and back in for group changes."
        else
            error "Unsupported Linux distribution. Please install Docker manually:"
            echo "  https://docs.docker.com/engine/install/"
            exit 1
        fi
    elif [[ "$OS" == "macos" ]]; then
        if has_command brew; then
            brew install --cask docker
            success "Docker installed via Homebrew"
        else
            error "Please install Docker Desktop manually:"
            echo "  https://www.docker.com/products/docker-desktop"
            exit 1
        fi
    fi
}

# Install Docker Compose
install_docker_compose() {
    info "Checking Docker Compose..."
    
    if docker compose version >/dev/null 2>&1; then
        success "Docker Compose already installed"
        return 0
    fi
    
    warning "Installing Docker Compose plugin..."
    
    if [[ "$OS" == "linux" ]]; then
        DOCKER_CONFIG=${DOCKER_CONFIG:-$HOME/.docker}
        mkdir -p $DOCKER_CONFIG/cli-plugins
        curl -SL https://github.com/docker/compose/releases/latest/download/docker-compose-linux-x86_64 \
            -o $DOCKER_CONFIG/cli-plugins/docker-compose
        chmod +x $DOCKER_CONFIG/cli-plugins/docker-compose
        success "Docker Compose installed"
    fi
}

# Install Ollama
install_ollama() {
    info "Checking Ollama installation..."
    
    if has_command ollama; then
        success "Ollama already installed: $(ollama --version 2>&1 | head -n1)"
        return 0
    fi
    
    warning "Installing Ollama..."
    curl -fsSL https://ollama.com/install.sh | sh
    success "Ollama installed"
}

# Download AI models
download_models() {
    info "Downloading AI models..."
    
    # Check if Ollama is running
    if ! pgrep -x "ollama" > /dev/null; then
        info "Starting Ollama service..."
        ollama serve &
        sleep 3
    fi
    
    # Download models
    info "Downloading codellama:7b (this may take a while)..."
    ollama pull codellama:7b
    success "codellama:7b downloaded"
    
    info "Downloading qwen2:0.5b..."
    ollama pull qwen2:0.5b
    success "qwen2:0.5b downloaded"
}

# Build LazyA compiler
build_compiler() {
    info "Building LazyA compiler..."
    
    # Check for build dependencies
    local missing_deps=()
    
    for cmd in cmake make g++ flex bison ar; do
        if ! has_command $cmd; then
            missing_deps+=($cmd)
        fi
    done
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        warning "Missing dependencies: ${missing_deps[*]}"
        
        info "Running setup_env.sh to install dependencies..."
        if [ -f "scripts/setup_env.sh" ]; then
            ./scripts/setup_env.sh
        else
            # Download if missing (install from curl scenario)
            curl -fsSL https://raw.githubusercontent.com/Daleth-Barreto/Lazy/main/scripts/setup_env.sh | bash
        fi
        
        # Re-check
        for cmd in cmake make g++ flex bison ar; do
            if ! has_command $cmd; then
                error "Dependencies still missing after setup_env.sh: $cmd"
                exit 1
            fi
        done
    fi

    # Compile Runtime Library
    info "Compiling Runtime Library..."
    mkdir -p build/runtime
    
    # Specific runtime sources
    # 1. Core Runtime (C)
    gcc -c runtime_lib/lazy_runtime.c -o build/runtime/lazy_runtime.o -O2 -fPIC -DLAZY_RUNTIME_BUILD
    
    # 2. AI Runtime (C++)
    g++ -c src/runtime/ai/OllamaClient.cpp -o build/runtime/OllamaClient.o -I src/runtime -I src/runtime/ai -O2 -fPIC -DLAZY_RUNTIME_BUILD
    g++ -c src/runtime/http/HTTPClient.cpp -o build/runtime/HTTPClient.o -I src/runtime -I src/runtime/http -O2 -fPIC -DLAZY_RUNTIME_BUILD
    g++ -c src/runtime/ai/AISemanticOps.cpp -o build/runtime/AISemanticOps.o -I src/runtime -I src/runtime/ai -O2 -fPIC -DLAZY_RUNTIME_BUILD
    
    # Create static library
    ar rcs build/liblazy_runtime.a \
        build/runtime/lazy_runtime.o \
        build/runtime/OllamaClient.o \
        build/runtime/HTTPClient.o \
        build/runtime/AISemanticOps.o
        
    success "Runtime library built: build/liblazy_runtime.a"
    
    # Build Compiler
    mkdir -p build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    cd ..
    
    success "Lazy compiler built successfully"
}

# Install to system
install_to_system() {
    info "Installing Lazy to system..."
    
    # Create directories
    mkdir -p "$LAZY_HOME/bin"
    mkdir -p "$LAZY_HOME/lib"
    mkdir -p "$LAZY_HOME/examples"
    
    # Install Runtime Library
    if [ -f "build/liblazy_runtime.a" ]; then
        cp build/liblazy_runtime.a "$LAZY_HOME/lib/"
        success "Installed runtime library to ~/.lazy/lib/liblazy_runtime.a"
    else
        error "Runtime library not found! Build failed."
        exit 1
    fi

    # Fix for missing libcurl dev package (symlink runtime lib)
    # This ensures -lcurl works even if only libcurl.so.4 is installed
    if [ ! -f "$LAZY_HOME/lib/libcurl.so" ]; then
        # Try to find libcurl in system library cache
        if has_command ldconfig; then
            LIBCURL_PATH=$(ldconfig -p | grep "libcurl.so" | head -n 1 | awk '{print $NF}')
            if [ -n "$LIBCURL_PATH" ] && [ -f "$LIBCURL_PATH" ]; then
                ln -sf "$LIBCURL_PATH" "$LAZY_HOME/lib/libcurl.so"
                info "Created local libcurl.so symlink pointing to $LIBCURL_PATH"
            fi
        fi
    fi
    
    # Copy binary (renaming to lazy-compiler to avoid conflict with wrapper)
    if [ -f "build/lazya" ]; then # Original binary name might still be 'lazya'
        cp build/lazya "$LAZY_BIN/lazy-compiler"
        chmod +x "$LAZY_BIN/lazy-compiler"
        success "Installed compiler binary to ~/.lazy/bin/lazy-compiler"
    elif [ -f "build/lazy" ]; then
        cp build/lazy "$LAZY_BIN/lazy-compiler"
        chmod +x "$LAZY_BIN/lazy-compiler"
        success "Installed compiler binary to ~/.lazy/bin/lazy-compiler"
    else
        error "Compiler binary not found. Build may have failed."
        exit 1
    fi
    
    # Copy examples
    if [ -d "examples" ]; then
        cp -r examples/* "$LAZY_HOME/examples/"
        success "Installed examples to ~/.lazy/examples"
    fi
    
    # Create wrapper script
    cat > "$LAZY_BIN/lazy" << 'EOF'
#!/bin/bash
# Lazy wrapper - implements -r and -e flags from USO_SIMPLE.md
# Points to actual ELF binary to avoid recursion

LAZY_HOME="${LAZY_HOME:-$HOME/.lazy}"
BINARY="$LAZY_HOME/bin/lazy-compiler"

# Check for special commands first
if [ "$1" = "uninstall" ]; then
    echo "Uninstalling Lazy..."
    rm -rf "$LAZY_HOME"
    sudo rm -f /usr/local/bin/lazy 2>/dev/null
    echo "Lazy uninstalled"
    echo "You may want to remove LAZY_HOME from your shell config"
    exit 0
fi

if [ "$1" = "examples" ]; then
    echo "Available examples in $LAZY_HOME/examples:"
    ls -1 "$LAZY_HOME/examples/" | grep ".lazy$"
    exit 0
fi

if [ "$1" = "new" ]; then
    if [ -z "$2" ]; then
        echo "Usage: lazy new <project_name>"
        exit 1
    fi
    PROJECT_NAME="$2"
    if [ -d "$PROJECT_NAME" ]; then
        echo "Error: Directory '$PROJECT_NAME' already exists"
        exit 1
    fi
    mkdir "$PROJECT_NAME"
    cat > "$PROJECT_NAME/main.lazy" << 'END_TEMPLATE'
func main() -> int {
    println("Hello from Lazy!");
    return 0;
}
END_TEMPLATE
    echo "Created new project: $PROJECT_NAME"
    echo "Try it: cd $PROJECT_NAME && lazy main.lazy -e"
    exit 0
fi

# Parse arguments for -r and -e flags
RUN_AFTER=false
SHOW_EXIT=false
declare -a ARGS

while [[ $# -gt 0 ]]; do
    case "$1" in
        -r)
            RUN_AFTER=true
            shift
            ;;
        -e)
            RUN_AFTER=true
            SHOW_EXIT=true
            shift
            ;;
        *)
            ARGS+=("$1")

            shift
            ;;
    esac
done

# Run the compiler with remaining arguments
if [ ${#ARGS[@]} -gt 0 ]; then
    "$BINARY" "${ARGS[@]}"
    COMPILE_EXIT=$?
else
    # No args -> Show help
    "$BINARY" --help
    exit $?
fi

# If compilation failed, exit
if [ $COMPILE_EXIT -ne 0 ]; then
    exit $COMPILE_EXIT
fi

# Run if -r or -e was specified
if [ "$RUN_AFTER" = true ]; then
    # Determine output file (check if -o was used)
    OUTPUT="a.out"
    for ((i=0; i<${#ARGS[@]}; i++)); do
        if [ "${ARGS[$i]}" = "-o" ] && [ $((i+1)) -lt ${#ARGS[@]} ]; then
            OUTPUT="${ARGS[$((i+1))]}"
            break
        fi
    done
    
    # Run the compiled program
    if [ -f "$OUTPUT" ]; then
        if [ "$SHOW_EXIT" = true ]; then
            echo ""
            echo "Running $OUTPUT..."
            echo "---"
            ./"$OUTPUT"
            EXIT_CODE=$?
            echo "---"
            echo "Exit code: $EXIT_CODE"
            exit $EXIT_CODE
        else
            ./"$OUTPUT"
            exit $?
        fi
    else
        echo "Error: Output file $OUTPUT not found"
        exit 1
    fi
fi
EOF
    chmod +x "$LAZY_BIN/lazy"
    success "Created lazy wrapper script"
}

# Setup shell configuration
setup_shell() {
    info "Setting up shell environment..."
    
    # Detect which shell is being used
    local current_shell=$(basename "$SHELL")
    local shell_rc=""
    
    case "$current_shell" in
        bash)
            shell_rc="$HOME/.bashrc"
            ;;
        zsh)
            shell_rc="$HOME/.zshrc"
            ;;
        fish)
            shell_rc="$HOME/.config/fish/config.fish"
            info "Fish shell detected. Manual configuration required."
            info "Add this to your config.fish:"
            echo "  set -gx LAZY_HOME \$HOME/.lazy"
            echo "  set -gx PATH \$LAZY_HOME/bin \$PATH"
            return 0
            ;;
        *)
            shell_rc="$HOME/.profile"
            warning "Unknown shell: $current_shell. Using .profile"
            ;;
    esac
    
    # Add to PATH if not already there
    if ! grep -q "LAZY_HOME" "$shell_rc" 2>/dev/null; then
        cat >> "$shell_rc" << EOF

# Lazy Configuration
export LAZY_HOME="\$HOME/.lazy"
export PATH="\$LAZY_HOME/bin:\$PATH"
EOF
        success "Added Lazy to $shell_rc"
        warning "Please run: source $shell_rc"
    else
        success "Lazy already in $shell_rc"
    fi
}

# Docker-based installation
install_with_docker() {
    info "Installing Lazy with Docker..."
    
    install_docker
    install_docker_compose
    install_ollama
    
    # Clone or use existing source
    if [ ! -d "build" ]; then
        info "Building Docker images..."
        docker compose build
        success "Docker images built"
    fi
    
    # Create wrapper that uses Docker
    mkdir -p "$LAZY_BIN"
    cat > "$LAZY_BIN/lazy" << 'EOF'
#!/bin/bash
docker compose run --rm lazy-compiler lazy "$@"
EOF
    chmod +x "$LAZY_BIN/lazy"
    
    setup_shell
    success "Docker-based installation complete"
}

# Native installation
install_native() {
    info "Installing Lazy natively..."
    
    install_ollama
    download_models
    build_compiler
    install_to_system
    setup_shell
    
    success "Native installation complete"
}

# Main installation
main() {
    print_header
    
    detect_os
    info "Detected OS: $OS ($DISTRO)"
    
    echo ""
    info "Installation options:"
    echo "  1) Native (recommended, faster)"
    echo "  2) Docker (easier, more portable)"
    echo "  3) Auto (detect best option)"
    echo ""
    read -p "Choose installation method [1/2/3]: " choice
    
    case $choice in
        1)
            install_native
            ;;
        2)
            install_with_docker
            ;;
        3|"")
            if has_command cmake && has_command make; then
                info "Build tools found, using native installation"
                install_native
            else
                info "Build tools not found, using Docker installation"
                install_with_docker
            fi
            ;;
        *)
            error "Invalid choice"
            exit 1
            ;;
    esac
    
    # Verify installation
    echo ""
    info "Verifying installation..."
    
    export PATH="$LAZY_BIN:$PATH"
    
    if has_command lazy; then
        success "Lazy installed successfully!"
        echo ""
        echo -e "${GREEN}========================================${NC}"
        echo -e "${GREEN}  Installation Complete!                ${NC}"
        echo -e "${GREEN}========================================${NC}"
        echo ""
        echo "Quick start:"
        echo "  1. Reload your shell: source ~/.bashrc  (or ~/.zshrc)"
        echo "  2. Create a project:  lazy new my_app"
        echo "  3. Run an example:    lazy examples/ex01_primes.lazy -e"
        echo ""
        echo "More info:"
        echo "  lazy --help         Show help"
        echo "  lazy examples       List examples"
        echo ""
    else
        warning "Installation completed but 'lazy' not found in PATH"
        echo "Please add $LAZY_BIN to your PATH manually"
    fi
}

# Run installer
main "$@"
```
