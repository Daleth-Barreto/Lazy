# Quick Installation Guide

## One-Command Install

```bash
curl -sSf https://raw.githubusercontent.com/Daleth-Barreto/Lazy/main/install.sh | sh
```

Or if you have the repository:

```bash
chmod +x install.sh
./install.sh
```

Or using Make:

```bash
make quick-install
```

## What Gets Installed

The installer automatically:

1. **Detects your OS** (Linux or macOS)
2. **Installs dependencies:**
   - CMake, Make, G++
   - LLVM 18
   - Flex & Bison
   - libcurl, nlohmann-json
3. **Installs Docker** (optional, if chosen)
4. **Installs Ollama** (AI model server)
5. **Downloads AI models:**
   - `codellama:7b` (for code generation)
   - `qwen2:0.5b` (for faster tasks)
6. **Builds Lazy compiler** from source
7. **Installs to `~/.lazy/`**
8. **Adds to your PATH**

## Installation Methods

The installer gives you 3 options:

### 1. Native Installation (Recommended)
- Faster compilation
- Better performance
- Direct binary access
- Requires: CMake, LLVM, build tools

### 2. Docker Installation
- Easier setup
- No local dependencies
- Portable across systems
- Requires: Docker, Docker Compose

### 3. Auto (Default)
- Automatically chooses best method
- Checks for build tools
- Falls back to Docker if needed

## After Installation

### Add to PATH

The installer adds Lazy to your shell config automatically. Reload your shell:

```bash
source ~/.bashrc  # or ~/.zshrc on macOS
```

Or restart your terminal.

### Verify Installation

```bash
lazy --version
# Output: Lazy 0.1.0
```

### Quick Start

```bash
# Create new project
lazy new hello_world
cd hello_world

# Edit main.lazy (created automatically)
# Then run it:
lazy run main.lazy
```

### Run Examples

```bash
# List available examples
lazy examples

# Run an example
lazy run ~/.lazy/examples/ex01_primes.lazy
```

## Manual Installation

If the installer fails or you prefer manual setup:

### 1. Install Dependencies

**Ubuntu/Debian:**
```bash
# Use setup script for reliable installation
sudo apt-get update
./scripts/setup_env.sh
```

**macOS:**
```bash
brew install cmake llvm@18 flex bison curl nlohmann-json zstd
```

### 2. Install Ollama

```bash
curl -fsSL https://ollama.com/install.sh | sh
```

### 3. Download AI Models

```bash
ollama pull codellama:7b
ollama pull qwen2:0.5b
```

### 4. Build Lazy

```bash
git clone https://github.com/Daleth-Barreto/Lazy.git
cd Lazy
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### 5. Install

```bash
cd ..
make install  # Installs to ~/.lazy
```

### 6. Add to PATH

Add to `~/.bashrc` or `~/.zshrc`:

```bash
export LAZY_HOME="$HOME/.lazy"
export PATH="$LAZY_HOME/bin:$PATH"
```

Then reload:

```bash
source ~/.bashrc
```

## Docker-Only Installation

If you only want to use Docker:

```bash
git clone https://github.com/Daleth-Barreto/Lazy.git
cd Lazy
docker compose build
docker compose up -d ollama

# Run compiler
docker compose run --rm lazy-compiler lazy file.lazy
```

## Troubleshooting

### "Command not found: lazya"

PATH not set. Add to your shell config:

```bash
export PATH="$HOME/.lazya/bin:$PATH"
source ~/.bashrc
```

### "Ollama connection failed"

Start Ollama:

```bash
ollama serve
```

Or via Docker:

```bash
docker compose up -d ollama
```

### "Missing dependencies"

Install build tools:

```bash
# Ubuntu
sudo apt-get install build-essential cmake

# macOS
brew install cmake
```

### "Permission denied"

Make installer executable:

```bash
chmod +x install.sh
```

### "Docker not found"

Install Docker:

```bash
# Linux
curl -fsSL https://get.docker.com | sh

# macOS
brew install --cask docker
```

## Uninstallation

```bash
make uninstall
```

Or manually:

```bash
rm -rf ~/.lazya
sudo rm -f /usr/local/bin/lazy
```

Remove from shell config:
- Delete the `# LazyA Configuration` section from `~/.bashrc` or `~/.zshrc`

## Updating

```bash
lazya update
```

Or manually:

```bash
cd LazyA
git pull
make clean
make build
make install
```

## Next Steps

- **Documentation**: `docs/language_reference.md`
- **Quick Reference**: `REFERENCIA_RAPIDA.md`
- **Docker Guide**: `docs/docker_guide.md`
- **Examples**: `~/.lazya/examples/`

## Support

- GitHub Issues: https://github.com/Daleth-Barreto/LazyA/issues
- Documentation: https://lazya.dev/docs

## System Requirements

### Minimum
- OS: Linux (Ubuntu 20.04+) or macOS (11+)
- RAM: 4 GB
- Disk: 2 GB free
- Internet: Required for AI models

### Recommended
- OS: Linux (Ubuntu 22.04+) or macOS (12+)
- RAM: 8 GB
- Disk: 5 GB free
- CPU: 4+ cores (for faster builds)
