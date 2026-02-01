# Lazy - Quick Reference

## Global Installation (RECOMMENDED)

```bash
cd /home/daleth/Escritorio/lazy
sudo ln -sf $(pwd)/lazy /usr/local/bin/lazy
```

Now you can use `lazy` from anywhere.

---

## Usage

### From any directory:

```bash
# Compile and show exit code
lazy my_program.lazy -e

# Compile with specific name
lazy program.lazy -o my_app -e

# Compile only
lazy program.lazy -o app

# Compile and run
lazy program.lazy -r
```

### Real examples:

```bash
# From examples directory
cd /home/daleth/Escritorio/lazy/examples
lazy test_complete_var.lazy -e          # Exit: 42
lazy test1_arithmetic.lazy -e           # Exit: 42
lazy test2_bitwise.lazy -e              # Exit: 4
lazy test3_if.lazy -e                   # Exit: 1

# From your home
cd ~
lazy Escritorio/lazy/examples/test_complete_var.lazy -e

# From anywhere with full path
lazy /home/daleth/Escritorio/lazy/examples/test1_arithmetic.lazy -e
```

---

## Create a Program

```bash
# Create file
cat > test.lazy << 'EOF'
func main() -> int {
    let x: int = 10;
    let y: int = 32;
    return x + y;
}
EOF

# Compile and execute
lazy test.lazy -e
```

**Output:**
```
Compiling test.lazy...
Successfully compiled to: a.out

Running a.out...
---
---
Exit code: 42
```

---

## Commands

| Command | Description |
|---------|-------------|
| `lazy new <project>` | Create new project |
| `lazy run <file>` | Run a .lazy file |
| `lazy build <file>` | Compile to executable |
| `lazy examples` | List examples |
| `lazy --version` | Show version |

## Syntax

### Variables
```lazy
let x: int = 10;
let name: string = "Lazy";
auto y = 20; // Type inference
```

### Functions
```lazy
func add(a: int, b: int) -> int {
    return a + b;
}
```

### Control Flow
```lazy
if x > 0 { ... } else { ... }
while x > 0 { ... }
for i in range(0, 10) { ... }
```

### AI Operators
```lazy
// Semantic Comparison
if input ~= "hello" { ... }

// Code Generation
@context
func magic() -> int { "return 42" }
```

### AI Models
- `codellama:7b` (Default)
- `qwen2:0.5b`

### Bitwise Operators
```lazy
let result: int = 12 & 7;    // AND: 4
let result2: int = 8 | 3;    // OR: 11
let result3: int = 15 ^ 9;   // XOR: 6
let result4: int = 3 << 2;   // Left shift: 12
let result5: int = 16 >> 2;  // Right shift: 4
```

### Arithmetic Operators
```lazy
+ - * / %
```

### Comparisons
```lazy
== != < > <= >=
```

---

## Troubleshooting

### If `lazy` is not found:
```bash
# Reinstall the link
cd /home/daleth/Escritorio/lazy
sudo ln -sf $(pwd)/lazy /usr/local/bin/lazy
```

### If compiler fails:
```bash
# Recompile Lazy
cd /home/daleth/Escritorio/lazy
./install.sh 1
```

### View help:
```bash
lazy --help
```

---

## Complete Example

```bash
# 1. Create program
cat > factorial.lazy << 'EOF'
func factorial(n: int) -> int {
    if (n < 2) {
        return 1;
    } else {
        return n;
    }
}

func main() -> int {
    return factorial(5);
}
EOF

# 2. Compile and run
lazy factorial.lazy -o factorial -e

# 3. View result
# Exit code: 5
```

---

## Tips

- Exit code is the return value of `main()`
- Programs do NOT print to terminal by default (only exit code via wrapper) unless using `print/println`
- Use `-e` to see exit code automatically
- Use absolute paths if you are in another directory
- The compiler generates ~17KB executables
- Compilation takes <1 second

---

Lazy is ready to use!
