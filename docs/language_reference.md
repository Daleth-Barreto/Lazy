# LazyA Language Reference

## Overview
LazyA is an AI-native programming language that integrates semantic understanding directly into the syntax.

## File Extension
`.lazy`

---

## Syntax

### Comments
```lazy
// Single line comment

/* 
   Multi-line
   comment
*/
```

### Variables
```lazy
// Explicit typing
let name: string = "LazyA";
let count: int = 42;
let pi: float = 3.14159;
let active: bool = true;

// Type inference
auto inferred = "hello";  // inferred as string
```

### Data Types

| Type | Description | Example |
|------|-------------|---------|
| `int` | 64-bit signed integer | `42` |
| `float` | 64-bit floating point | `3.14` |
| `string` | UTF-8 string | `"hello"` |
| `bool` | Boolean | `true`, `false` |
| `any` | Dynamic type for AI operations | - |

### Operators

#### Arithmetic
| Operator | Description |
|----------|-------------|
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division |
| `%` | Modulo |
| `**` | Power |

#### Comparison
| Operator | Description |
|----------|-------------|
| `==` | Equal |
| `!=` | Not equal |
| `<` | Less than |
| `>` | Greater than |
| `<=` | Less or equal |
| `>=` | Greater or equal |

#### Logical
| Operator | Description |
|----------|-------------|
| `&&` | Logical AND |
| `\|\|` | Logical OR |
| `!` | Logical NOT |

#### AI Semantic Operators
| Operator | Description |
|----------|-------------|
| `~=` | Semantic equality (compares meaning) |
| `~>` | Semantic implication (planned) |

### Control Flow

#### If/Else
```lazy
if condition {
    // statements
} else if other {
    // statements
} else {
    // statements
}
```

#### While Loop
```lazy
while count < 10 {
    count = count + 1;
}
```

#### For Loop
```lazy
for i in range(0, 10) {
    println(i);
}
```

#### Foreach Loop
```lazy
for item in items {
    println(item);
}
```

---

## Functions

### Standard Functions
```lazy
func add(a: int, b: int) -> int {
    return a + b;
}

func greet(name: string) {
    println("Hello, " + name);
}
```

### AI Context Functions
Let AI implement the function based on a docstring.

```lazy
@context
func power_of_two(exponent: int) -> int {
    "Calculate 2 raised to the power of 'exponent'.
    @verify: power_of_two(0) == 1
    @verify: power_of_two(3) == 8"
}
```

**Verification:**
- `@verify: condition` - Compiler tests the AI implementation
- Up to 3 retry attempts with error feedback

---

## AI Features

### Semantic Comparison (`~=`)
Compares the meaning of two values using AI.

```lazy
if input ~= "start game" {
    // Matches: "begin playing", "iniciar juego", etc.
}
```

### Ollama Integration
```lazy
let response: string = ai.ollama.chat("Explain quantum physics");
println(response);
```

### Available AI Functions
| Function | Description |
|----------|-------------|
| `ai.ollama.chat(prompt)` | Chat with local LLM |
| `ai.ollama.generate(prompt)` | Generate text |
| `ai.ollama.list_models()` | List available models |
| `ai_semantic_equals(a, b)` | Compare meaning |

---

## Built-in Functions

### I/O
| Function | Description |
|----------|-------------|
| `print(value)` | Print without newline |
| `println(value)` | Print with newline |
| `read_int()` | Read integer from stdin |

### Collections
| Function | Description |
|----------|-------------|
| `vector_new()` | Create new vector |
| `vector_push(v, val)` | Push to vector |
| `vector_get(v, idx)` | Get from vector |
| `vector_size(v)` | Get vector size |
| `map_new()` | Create new map |
| `map_put(m, key, val)` | Put in map |
| `map_get(m, key)` | Get from map |

### File I/O
| Function | Description |
|----------|-------------|
| `file_open(path, mode)` | Open file |
| `file_close(handle)` | Close file |
| `file_read(handle)` | Read file contents |
| `file_write(handle, data)` | Write to file |
| `file_exists(path)` | Check if file exists |

### String
| Function | Description |
|----------|-------------|
| `string_concat(a, b)` | Concatenate strings |

---

## Decorators

| Decorator | Description |
|-----------|-------------|
| `@context` | AI generates implementation |
| `@cached` | Cache function results |
| `@inline` | Inline function (planned) |

---

## Example Program

```lazy
// ex01_primes.lazy - Find prime numbers

func is_prime(n: int) -> bool {
    if n < 2 { return false; }
    let i: int = 2;
    while i * i <= n {
        if n % i == 0 { return false; }
        i = i + 1;
    }
    return true;
}

func main() -> int {
    println("=== Prime Finder ===");
    for i in range(2, 50) {
        if is_prime(i) {
            print(i);
            print(" ");
        }
    }
    println("");
    return 0;
}
```

---

## Compilation

```bash
# Compile to executable
./lazya program.lazy -o output

# Run
./output
```

---

## Model Configuration
Default model: `qwen2:0.5b` (or `codellama:7b` if available)

Install models:
```bash
ollama pull codellama:7b
ollama pull qwen2:0.5b
```
