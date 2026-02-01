# LazyA - Automated Installation System

## Overview

Lazy now has a **one-command installation** system inspired by Rust and Node.js installers. No more manual dependency hunting!

# Quick Start with Lazy

## Installation
```bash
curl -sSf https://raw.githubusercontent.com/Daleth-Barreto/Lazy/main/install.sh | sh
```

## First Program
```lazy
func main() -> int {
    println("Hello Lazy!");
    return 0;
}
```
Run it:
```bash
lazy run main.lazy
```

## AI Example
```lazy
func main() -> int {
    if "hola" ~= "hello" {
        println("It's a match!");
    }
    return 0;
}
```
Run it (requires AI models):
```bash
lazy run ai_test.lazy
```

## Installation Methods

### Method 1: One-Command Install (Recommended)

```bash
curl -sSf https://raw.githubusercontent.com/Daleth-Barreto/Lazy/main/install.sh | sh
```

This single command:
- Detects your OS automatically
- Installs all dependencies (LLVM, CMake, etc.)
- Builds the compiler
- Installs Ollama + AI models
- Sets up PATH automatically
- Creates the `lazy` CLI tool

### Method 2: Using Make

```bash
cd LazyA  
make quick-install
```

### Method 3: Clone and Install

```bash
git clone https://github.com/Daleth-Barreto/LazyA.git
cd LazyA
chmod +x install.sh
./install.sh
```

## Quick Start After Installation

```bash
# Reload your shell
source ~/.bashrc  # or ~/.zshrc

# Create a new project
lazy new my_app
cd my_app

# Run it
lazy run main.lazy
```

## The `lazy` Command

The installer creates a convenient `lazy` wrapper with subcommands:

```bash
lazy new <name>       # Create new project
lazy run <file>       # Compile and run
lazy build <file>     # Compile only
lazy examples         # List examples
lazy update           # Update LazyA
lazy --version        # Show version
lazy --help           # Show help
```

## What Gets Installed

### Directory Structure

 ```
~/.lazya/
├── bin/
│   ├── lazy          # CLI wrapper
│   └── lazya-compiler # Main compiler binary
├── lib/              # Libraries
└── examples/         # Example programs
```

### System Dependencies

**Automatically installed:**
- CMake 3.15+
- LLVM 15+
- Flex & Bison
- libcurl
- nlohmann-json
- Ollama
- AI models (codellama:7b, qwen2:0.5b)

### PATH Configuration

Automatically adds to your shell config:

```bash
export LAZYA_HOME="$HOME/.lazya"
export PATH="$LAZYA_HOME/bin:$PATH"
```

## Docker Alternative

If you prefer Docker-only:

```bash
git clone https://github.com/Daleth-Barreto/LazyA.git
cd LazyA
make docker-build

# Use docker compose
docker compose run --rm lazya-compiler lazy file.lazy
```

## Makefile Targets

Professional build system:

```bash
make help              # Show all targets
make build             # Build compiler
make install           # Install to ~/.lazya
make install-system    # Install to /usr/local/bin
make test              # Run tests
make examples          # Run all examples
make clean             # Clean build
make docker-build      # Build Docker images  
make extension         # Build VSCode extension
make extension-install # Install VSCode extension
```

## Installation Comparison

### LazyA (Now) 

```bash
curl -sSf https://lazya.dev/install.sh | sh
```

**Done in one command!**

### Rust (for comparison)

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

### Node.js (for comparison)

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.0/install.sh | bash
```

**LazyA is now just as easy!**

## Installation Options

The installer asks you to choose:

```
Installation options:
  1) Native (recommended, faster)
  2) Docker (easier, more portable)
  3) Auto (detect best option)
```

### Native Installation
- **Pro**: Faster compilation, better performance
- **Con**: Requires system dependencies
- **Best for**: Development, production use

### Docker Installation
- **Pro**: No local dependencies, portable
- **Con**: Slightly slower
- **Best for**: Testing, CI/CD, consistency

### Auto (Default)
- Checks if build tools exist
- Uses native if possible
- Falls back to Docker otherwise

## Uninstallation

```bash
lazy uninstall
```

Or manually:

```bash
rm -rf ~/.lazya
sudo rm -f /usr/local/bin/lazy
# Remove from ~/.bashrc or ~/.zshrc
```

## Advanced Usage

### Custom Installation Directory

```bash
LAZYA_HOME=/opt/lazya ./install.sh
```

### Skip AI Model Download

```bash
SKIP_MODELS=1 ./install.sh
```

### Force Docker Installation

```bash
USE_DOCKER=yes ./install.sh
```

### Build Type

```bash
BUILD_TYPE=Debug make build
```

## Documentation Files

- **INSTALL.md** - Detailed installation guide
- **README.md** - Project overview
- **docs/docker_guide.md** - Docker usage
- **docs/language_reference.md** - Language docs
- **CHANGELOG.md** - What's new

## New Features

### CLI Wrapper (`lazy`)

```bash
# Old way
./build/lazy file.lazy
./a.out

# New way
lazy run file.lazy
```

### Project Scaffolding

```bash
lazy new my_game
cd my_game
# main.lazy is created automatically
lazy run main.lazy
```

### Example Browser

```bash
lazy examples
# Lists:
# - ex01_primes.lazy
# - ex02_inventory.lazy
# - ex03_factorial.lazy
# - ...
```

### Auto-Update

```bash
lazy update
# Downloads and installs latest version
```

## Comparison with Other Languages

| Feature | LazyA | Rust | Go | C++ |
|---------|-------|------|----|----|
| One-command install | yes | yes | yes | no |
| Auto dependencies | yes | yes | yes | no |
| PATH setup | yes | yes | yes | no |
| CLI wrapper | yes | yes | yes | no |
| Project templates | yes | yes | yes | no |
| Native AI features | yes | no | no | no |

## Next Steps After Install

1. **Try examples:**
   ```bash
   lazy run examples/ex01_primes.lazy
   ```

2. **Create a project:**
   ```bash
   lazy new hello_ai
   cd hello_ai
   # Edit main.lazy
   lazy run main.lazy
   ```

3. **Read the docs:**
   ```bash
   cat ~/.lazya/docs/language_reference.md
   ```

4. **Install VSCode extension:**
   ```bash
   cd ~/.lazya
   make extension-install
   ```

## Tips

- Use `lazy run` for development (compile + run)
- Use `lazy build` for production (compile only)
- Examples are in `~/.lazya/examples/`
- Compiler binary is at `~/.lazya/bin/lazya-compiler`
- Check `lazy --help` for all commands

## Summary

LazyA installation is now:
- **One command** instead of 10+ steps
- **Automatic** dependency resolution
- **Cross-platform** (Linux/macOS)
- **User-friendly** with CLI wrapper
- **As easy as** Rust or Node.js

**Just run:**
```bash
curl -sSf https://lazya.dev/install.sh | sh
```

**And start coding with AI!**


### Method 1: One-Command Install (Recommended)

```bash
curl -sSf https://raw.githubusercontent.com/yourrepo/lazya/main/install.sh | sh
```

This single command:
-  Detects your OS automatically
-  Installs all dependencies (LLVM, CMake, etc.)
-  Builds the compiler
-  Installs Ollama + AI models
-  Sets up PATH automatically
-  Creates the `lazya` CLI tool

### Method 2: Using Make

```bash
git clone https://github.com/yourrepo/lazya
cd lazya  
make quick-install
```

### Method 3: Clone and Install

```bash
git clone https://github.com/yourrepo/lazya
cd lazya
chmod +x install.sh
./install.sh
```

##  Quick Start After Installation

```bash
# Reload your shell
source ~/.bashrc  # or ~/.zshrc

# Create a new project
lazya new my_app
cd my_app

# Run it
lazya run main.lazy
```

##  The `lazya` Command

The installer creates a convenient `lazya` wrapper with subcommands:

```bash
lazya new <name>       # Create new project
lazya run <file>       # Compile and run
lazya build <file>     # Compile only
lazya examples         # List examples
lazya update           # Update LazyA
lazya --version        # Show version
lazya --help           # Show help
```

##  What Gets Installed

### Directory Structure

 ```
~/.lazya/
├── bin/
│   ├── lazy      # Main compiler
│   └── lazya     # CLI wrapper
├── lib/          # Libraries
└── examples/     # Example programs
```

### System Dependencies

**Automatically installed:**
- CMake 3.15+
- LLVM 15+
- Flex & Bison
- libcurl
- nlohmann-json
- Ollama
- AI models (codellama:7b, qwen2:0.5b)

### PATH Configuration

Automatically adds to your shell config:

```bash
export LAZYA_HOME="$HOME/.lazya"
export PATH="$LAZYA_HOME/bin:$PATH"
```

##  Docker Alternative

If you prefer Docker-only:

```bash
git clone https://github.com/yourrepo/lazya
cd lazya
make docker-build

# Use docker compose
docker compose run --rm lazya-compiler lazy file.lazy
```

## 📖 Makefile Targets

Professional build system:

```bash
make help              # Show all targets
make build             # Build compiler
make install           # Install to ~/.lazya
make install-system    # Install to /usr/local/bin
make test              # Run tests
make examples          # Run all examples
make clean             # Clean build
make docker-build      # Build Docker images  
make extension         # Build VSCode extension
make extension-install # Install VSCode extension
```

##  Installation Comparison

### LazyA (Now) 

```bash
curl -sSf https://lazya.dev/install.sh | sh
```

**Done in one command!**

### Rust (for comparison)

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

### Node.js (for comparison)

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.0/install.sh | bash
```

**LazyA is now just as easy!**

##  Installation Options

The installer asks you to choose:

```
Installation options:
  1) Native (recommended, faster)
  2) Docker (easier, more portable)
  3) Auto (detect best option)
```

### Native Installation
- **Pro**: Faster compilation, better performance
- **Con**: Requires system dependencies
- **Best for**: Development, production use

### Docker Installation
- **Pro**: No local dependencies, portable
- **Con**: Slightly slower
- **Best for**: Testing, CI/CD, consistency

### Auto (Default)
- Checks if build tools exist
- Uses native if possible
- Falls back to Docker otherwise

##  Uninstallation

```bash
make uninstall
```

Or manually:

```bash
rm -rf ~/.lazya
sudo rm -f /usr/local/bin/lazy
# Remove from ~/.bashrc or ~/.zshrc
```

##  Advanced Usage

### Custom Installation Directory

```bash
LAZYA_HOME=/opt/lazya ./install.sh
```

### Skip AI Model Download

```bash
SKIP_MODELS=1 ./install.sh
```

### Force Docker Installation

```bash
USE_DOCKER=yes ./install.sh
```

### Build Type

```bash
BUILD_TYPE=Debug make build
```

##  Documentation Files

- **INSTALL.md** - Detailed installation guide
- **README.md** - Project overview
- **docs/docker_guide.md** - Docker usage
- **docs/language_reference.md** - Language docs
- **CHANGELOG.md** - What's new

##  New Features

### CLI Wrapper (`lazya`)

```bash
# Old way
./build/lazy file.lazy
./a.out

# New way
lazya run file.lazy
```

### Project Scaffolding

```bash
lazya new my_game
cd my_game
# main.lazy is created automatically
lazya run main.lazy
```

### Example Browser

```bash
lazya examples
# Lists:
# - ex01_primes.lazy
# - ex02_inventory.lazy
# - ex03_factorial.lazy
# - ...
```

### Auto-Update

```bash
lazya update
# Downloads and installs latest version
```

##  Comparison with Other Languages

| Feature | LazyA | Rust | Go | C++ |
|---------|-------|------|----|----|
| One-command install |  |  |  | ❌ |
| Auto dependencies |  |  |  | ❌ |
| PATH setup |  |  |  | ❌ |
| CLI wrapper |  |  (`cargo`) |  (`go`) | ❌ |
| Project templates |  |  |  | ❌ |
| Native AI features |  | ❌ | ❌ | ❌ |

##  Next Steps After Install

1. **Try examples:**
   ```bash
   lazya run ~/.lazya/examples/ex01_primes.lazy
   ```

2. **Create a project:**
   ```bash
   lazya new hello_ai
   cd hello_ai
   # Edit main.lazy
   lazya run main.lazy
   ```

3. **Read the docs:**
   ```bash
   cat ~/.lazya/docs/language_reference.md
   ```

4. **Install VSCode extension:**
   ```bash
   cd ~/.lazya
   make extension-install
   ```

##  Tips

- Use `lazya run` for development (compile + run)
- Use `lazya build` for production (compile only)
- Examples are in `~/.lazya/examples/`
- Compiler binary is at `~/.lazya/bin/lazy`
- Check `lazya --help` for all commands

## Summary

LazyA installation is now:
- **One command** instead of 10+ steps
- **Automatic** dependency resolution
- **Cross-platform** (Linux/macOS)
- **User-friendly** with CLI wrapper
- **As easy as** Rust or Node.js

**Just run:**
```bash
curl -sSf https://lazya.dev/install.sh | sh
```

**And start coding with AI!** 
