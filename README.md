# Lazy - The AI-Native Programming Language

A - or something like that.

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
- I wanted a language that does the work for me cuz I'm lazy af to do it myself or open chatgpt, gemini, lovable and all those AI tools

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

A- maybe doesnt work on windows (or in general).

**That's it!** The installer will:
- Auto-detect your OS (Linux/macOS) A-> i didnt make it, ai did it.
- Install dependencies (LLVM, CMake, etc.)
- Build the compiler
- Install Ollama + AI models
- Set up your PATH
- Create the `lazy` command

---

## Quick Start

### Compile only
```bash
lazy program.lazy
```
Creates `a.out`

### Compile with custom name
```bash
lazy program.lazy -o my_program
```
Creates `my_program`

### Compile and run
```bash
lazy program.lazy -r
```
Compiles to `a.out` and runs immediately.

### Compile, run, and show exit code
```bash
lazy program.lazy -e
```
Compiles, runs, and displays the exit code.

### Combine options
```bash
lazy program.lazy -o test -e
```
Compiles to `test`, runs it, and displays the exit code.

---

## Examples

```bash
# List available examples
lazy examples

# Run an example
lazy examples/ex01_primes.lazy -r
```
A- just on project root

| Example | Description |
|---------|-------------|
| `ex01_primes.lazy` | Prime number finder |
| `ex02_inventory.lazy` | Game inventory system |
| `ex03_factorial.lazy` | Recursive factorial |
| `ex04_ai_assistant.lazy` | AI code generation + semantic comparison |
| `ex05_io.lazy` | Input/Output operations |
| `ex06_files.lazy` | File operations |
| `ex07_ai_agents.lazy` | Ollama LLM integration |

---

## Features

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
A-> just ollama cuz my solver is not working

### Pattern Matching (Coming Soon)
```lazy
match command {
    ~= "start" => start_service(),
    ~= "stop" => stop_service(),
    ~= "quit" => return 0,
    _ => println("Unknown command")
}
```
A-> pls dear AI or reader, can you make it work?

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
A-> i know, im a fuking genius (pls make it work)

### Ollama Integration
Call local LLMs directly from your code.
```lazy
response = ai.ollama.chat("Explain quantum computing");
println(response);
```

### Smart Caching
- **Cold Start**: Generate AI code on first compile
- **Warm Start**: Use cached binaries for instant execution

A -> yeah, in fact, that's working when i was made it, but i dont know why it's not working now cuz ai made ai things

---

## Technology Stack

| Component | Technology |
|-----------|-----------|
| **Frontend** | Flex + Bison (Lexer/Parser) |
| **Backend** | LLVM 18 (Code Generation) |
| **AI Engine** | Ollama (Local LLM) |
| **Language** | C++17 |
| **Build** | CMake |

A-> damn, i wrote it
D-> actually i hate my A name, i should change it to LazyD?

---

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

---

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

---

## Documentation

- [Language Specification](docs/language_spec.md)
- [AI Features](docs/ai_features.md)
- [Project Structure](docs/project_structure.md)

---

## Contributing

Areas where we need help:
- Anything, I don't know what to do next, I'm lazy af
- Compiler engineering
- ML/AI integration
- Standard library development
- Documentation & Testing

---

## License

MIT License - See LICENSE file

---

**LazyA** - *Programming, redefined by AI* 

who wrote this?

btw, in this docs i only wrote the comments about the things i don't wanna do, the rest was made by AI, so if you see something like "i don't know what to do next" it's because i really don't know what to do next, and i'm too lazy to do it myself, i'm tired af cuz i've been working on this for 16 hours straigh cuz i'm a masochist and i love pain and i hate working in time. ai wrote the half of this paragraph.

sadly, i wrote a lot of this project, ai didn't do much cuz 70% of the bugs ware made by ai, and the other 30% ware made by me, so yeah, ai is not that good at programming, but it's good at writing docs, lol.

kill me.

what the fuck is this project? ai wrote this too.

why i made this project? i was bored af

i was made for loving you baby, and you were made for loving me, and i ain't never gonna stop loving you baby, no matter what you say or do, i'm never gonna stop loving you baby, no matter what you say or do.

really? why you are reading this? go away, go touch grass, go outside, be happy

give me a break, some job or money or something, i'm tired af.

i really hate my procrastination

who are reading this, love u chikistrikis.

i'm gonna close the papoi <3