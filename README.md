# Lazy - The AI-Native Programming Language

Lazy is a compiled programming language with **native AI capabilities**. Write code that reasons, generates, and adapts using embedded AI operators.

---

## 📖 The IBM Hackathon Story

This project was forged in the fires of the **IBM DevDay AI Demystified 2026**.

What happened:
- 🔥 48 hours of intense coding trying to integrate IBM Granite 3.0 and Orchestrate
- 🗺️ Deciphering IBM's documentation (which felt like reading an ancient treasure map)
- 🤯 Multiple authentication errors: PEM errors, 500 Internal Server Errors, endpoints that didn't exist
- 😅 Finally got Granite working... then realized I submitted the wrong YouTube link
- 🔄 Reverted all IBM code because I don't have resources to maintain enterprise integrations

**But here's the thing:** The pressure of the hackathon pushed me to complete LazyA v1.0. Without that deadline, this project might still be a half-baked idea.

### Acknowledgments

**Thank you IBM** for:
- The motivation to finish this compiler
- Improving my IQ by 20 points while deciphering your documentation
- Teaching me that enterprise APIs are not for the faint of heart

The IBM integration code lives on in git history for anyone brave enough to revive it.

### Why "Lazy"?

The original name was **LazyA** because:
- I'm lazy 🦥
- My first name is **Alan**
- I wanted a language that does the work for me

Also yes, this documentation was written with AI assistance. Because... *gestures at project name*.

---

## Quick Install

**One command to rule them all:**

```bash
curl -sSf https://raw.githubusercontent.com/Daleth-Barreto/Lazy/main/install.sh | sh
```

Or clone and run:

```bash
git clone https://github.com/Daleth-Barreto/Lazy.git
cd Lazy
chmod +x install.sh
./install.sh
```

**That's it!** The installer will:
- Auto-detect your OS (Linux/macOS)
- Install dependencies (LLVM, CMake, etc.)
- Build the compiler
- Install Ollama + AI models
- Set up your PATH
- Create the `lazy` command

### Alternative: Using Make

```bash
make quick-install
```

## Quick Start

```bash
# Create a new project
lazy new my_app
cd my_app

# Run your code
lazy run main.lazy

# Or compile and run separately
lazy build main.lazy
./a.out
```

## Examples

```bash
# List available examples
lazy examples

# Run an example
lazy run examples/ex01_primes.lazy
```

## Features

### 2. Semantic Operators

```lazy
let user_input: string = "What is your name?";

// Semantic equality - uses AI embeddings
if (user_input ~= "name") {
    println("You asked about names!");
}
```

### 3. Pattern Matching (Coming Soon)

```lazy
match command {
    ~= "start" => start_service(),
    ~= "stop" => stop_service(),
    ~= "quit" => return 0,
    _ => println("Unknown command")
}
```

### Semantic Comparison (`~=`)
Compare concepts, not just strings. Uses AI to understand meaning.
```lazy
if input ~= "insulto" {
    println("Toxic content detected");
}

// Works across languages and synonyms
if "start game" ~= "begin playing" {
    println("Same meaning!");
}
```

### AI Code Generation (`@context`)
Let AI implement functions based on docstrings with automatic verification.
```lazy
@context
func power_of_two(exponent: int) -> int {
    "Calculate 2 raised to the power of 'exponent'.
    @verify: power_of_two(0) == 1
    @verify: power_of_two(3) == 8
    @verify: power_of_two(10) == 1024"
}
// AI generates implementation, compiler verifies it passes all @verify conditions
```

### Ollama Integration
Call local LLMs directly from your code.
```lazy
response = ai.ollama.chat("Explain quantum computing");
println(response);
```

### Smart Caching
- **Cold Start**: Generate AI code on first compile
- **Warm Start**: Use cached binaries for instant execution

## Technology Stack

| Component | Technology |
|-----------|-----------|
| **Frontend** | Flex + Bison (Lexer/Parser) |
| **Backend** | LLVM 18 (Code Generation) |
| **AI Engine** | Ollama (Local LLM) |
| **Language** | C++17 |
| **Build** | CMake |

## Installation

```bash
# Clone repository
git clone https://github.com/Daleth-Barreto/Lazy.git
cd Lazy

# Install dependencies (Ubuntu/Debian)
sudo apt install flex bison llvm-18-dev clang cmake libcurl4-openssl-dev

# Build
mkdir build && cd build
cmake ..
make

# Install AI models
./scripts/install_ai.sh
```

## Quick Start

### Hello World
```lazy
func main() -> int {
    println("Hello from Lazy!");
    return 0;
}
```

### Compile and Run
```bash
lazy hello.lazy -o hello
./hello
```

## Examples

| Example | Description |
|---------|-------------|
| `ex01_primes.lazy` | Prime number finder |
| `ex02_inventory.lazy` | Game inventory system |
| `ex03_factorial.lazy` | Recursive factorial |
| `ex04_ai_assistant.lazy` | AI code generation + semantic comparison |
| `ex05_io.lazy` | Input/Output operations |
| `ex06_files.lazy` | File operations |
| `ex07_ai_agents.lazy` | Ollama LLM integration |

## AI Features

### Semantic Operators
- **`~=`** - Semantic equality (uses AI to compare meaning)
- **`~>`** - Semantic implication (planned)

### Code Generation with Verification
```lazy
@context
func sentiment(text: string) -> float {
    "Analyze sentiment. Return -1.0 (negative) to 1.0 (positive).
    @verify: sentiment('great') > 0.5
    @verify: sentiment('terrible') < -0.5"
}
```
The compiler:
1. Requests AI to generate implementation
2. Compiles and runs `@verify` tests
3. If tests fail, sends error feedback to AI
4. Retries up to 3 times
5. Caches successful implementation

### Model Configuration
Two pre-configured models:
- **`codellama:7b`** (default) - Best for code generation
- **`qwen2:0.5b`** - Fast mode for simple operations

## Project Structure

```
lazy/
├── src/
│   ├── lexer/          # Flex tokenizer
│   ├── parser/         # Bison grammar
│   ├── ast/            # Abstract Syntax Tree
│   ├── codegen/        # LLVM code generation
│   └── runtime/        # Standard library + AI
├── examples/           # Example programs
├── docs/               # Documentation
├── scripts/            # Build & install scripts
└── build/              # CMake build directory
```

## Language Syntax

### Variables
```lazy
let name: string = "Lazy";
let count: int = 42;
let pi: float = 3.14159;
auto inferred = "type inference";
```

### Control Flow
```lazy
if condition {
    // ...
} else {
    // ...
}

while count < 10 {
    count = count + 1;
}

for i in range(0, 10) {
    println(i);
}
```

### Functions
```lazy
func add(a: int, b: int) -> int {
    return a + b;
}
```

## Documentation

- [Language Specification](docs/language_spec.md)
- [AI Features](docs/ai_features.md)
- [Project Structure](docs/project_structure.md)

## Contributing

Areas where we need help:
- Compiler engineering
- ML/AI integration
- Standard library development
- Documentation & Testing

## License

MIT License - See LICENSE file

---

```

##  Quick Start

```bash
# Create a new project
lazya new my_app
cd my_app

# Run your code
lazya run main.lazy

# Or compile and run separately
lazya build main.lazy
./a.out
```

## 📖 Examples

```bash
# List available examples
lazya examples

# Run an example
lazya run ~/.lazya/examples/ex01_primes.lazy
```

##  Features
```

### 2. Semantic Operators

```lazya
let user_input: string = "What is your name?";

// Semantic equality - uses AI embeddings
if (user_input ~= "name") {
    println("You asked about names!");
}
```

### 3. Pattern Matching (Coming Soon)

```lazya
match command {
    ~= "start" => start_service(),
    ~= "stop" => stop_service(),
    ~= "quit" => return 0,
    _ => println("Unknown command")
}
```

###  Semantic Comparison (`~=`)
Compare concepts, not just strings. Uses AI to understand meaning.
```lazy
if input ~= "insulto" {
    println("Toxic content detected");
}

// Works across languages and synonyms
if "start game" ~= "begin playing" {
    println("Same meaning!");
}
```

###  AI Code Generation (`@context`)
Let AI implement functions based on docstrings with automatic verification.
```lazy
@context
func power_of_two(exponent: int) -> int {
    "Calculate 2 raised to the power of 'exponent'.
    @verify: power_of_two(0) == 1
    @verify: power_of_two(3) == 8
    @verify: power_of_two(10) == 1024"
}
// AI generates implementation, compiler verifies it passes all @verify conditions
```

###  Ollama Integration
Call local LLMs directly from your code.
```lazy
response = ai.ollama.chat("Explain quantum computing");
println(response);
```

###  Smart Caching
- **Cold Start**: Generate AI code on first compile
- **Warm Start**: Use cached binaries for instant execution

##  Technology Stack

| Component | Technology |
|-----------|-----------|
| **Frontend** | Flex + Bison (Lexer/Parser) |
| **Backend** | LLVM 18 (Code Generation) |
| **AI Engine** | Ollama (Local LLM) |
| **Language** | C++17 |
| **Build** | CMake |

##  Installation

```bash
# Clone repository
git clone https://github.com/yourusername/lazyA.git
cd lazyA

# Install dependencies (Ubuntu/Debian)
sudo apt install flex bison llvm-18-dev clang cmake libcurl4-openssl-dev

# Build
mkdir build && cd build
cmake ..
make

# Install AI models
./scripts/install_ai.sh
```

##  Quick Start

### Hello World
```lazy
func main() -> int {
    println("Hello from LazyA!");
    return 0;
}
```

### Compile and Run
```bash
./build/lazya hello.lazy -o hello
./hello
```

##  Examples

| Example | Description |
|---------|-------------|
| `ex01_primes.lazy` | Prime number finder |
| `ex02_inventory.lazy` | Game inventory system |
| `ex03_factorial.lazy` | Recursive factorial |
| `ex04_ai_assistant.lazy` | AI code generation + semantic comparison |
| `ex05_io.lazy` | Input/Output operations |
| `ex06_files.lazy` | File operations |
| `ex07_ai_agents.lazy` | Ollama LLM integration |

##  AI Features

### Semantic Operators
- **`~=`** - Semantic equality (uses AI to compare meaning)
- **`~>`** - Semantic implication (planned)

### Code Generation with Verification
```lazy
@context
func sentiment(text: string) -> float {
    "Analyze sentiment. Return -1.0 (negative) to 1.0 (positive).
    @verify: sentiment('great') > 0.5
    @verify: sentiment('terrible') < -0.5"
}
```
The compiler:
1. Requests AI to generate implementation
2. Compiles and runs `@verify` tests
3. If tests fail, sends error feedback to AI
4. Retries up to 3 times
5. Caches successful implementation

### Model Configuration
Two pre-configured models:
- **`codellama:7b`** (default) - Best for code generation
- **`qwen2:0.5b`** - Fast mode for simple operations

## 📁 Project Structure

```
lazyA/
├── src/
│   ├── lexer/          # Flex tokenizer
│   ├── parser/         # Bison grammar
│   ├── ast/            # Abstract Syntax Tree
│   ├── codegen/        # LLVM code generation
│   └── runtime/        # Standard library + AI
├── examples/           # Example programs
├── docs/               # Documentation
├── scripts/            # Build & install scripts
└── build/              # CMake build directory
```

##  Language Syntax

### Variables
```lazy
let name: string = "LazyA";
let count: int = 42;
let pi: float = 3.14159;
auto inferred = "type inference";
```

### Control Flow
```lazy
if condition {
    // ...
} else {
    // ...
}

while count < 10 {
    count = count + 1;
}

for i in range(0, 10) {
    println(i);
}
```

### Functions
```lazy
func add(a: int, b: int) -> int {
    return a + b;
}
```

##  Documentation

- [Language Specification](docs/language_spec.md)
- [AI Features](docs/ai_features.md)
- [Project Structure](docs/project_structure.md)

##  Contributing

Areas where we need help:
- Compiler engineering
- ML/AI integration
- Standard library development
- Documentation & Testing

##  License

MIT License - See LICENSE file

---

**LazyA** - *Programming, redefined by AI*
