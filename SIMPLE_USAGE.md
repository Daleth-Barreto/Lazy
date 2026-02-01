# Lazy - Simple Usage

## Simplified Command

You can now compile and run with a single command:

```bash
lazy program.lazy -e
```

---

## Available Options

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
# Basic test
lazy examples/test_complete_var.lazy -e

# Arithmetic
lazy examples/test1_arithmetic.lazy -o calc -e

# Bitwise
lazy examples/test2_bitwise.lazy -r

# If/else
lazy examples/test3_if.lazy -e
```

---

## Global Installation (Optional)

To use `lazy` from any directory, make sure you have sourced your shell config (e.g., `source ~/.zshrc`).

Then, from anywhere:
```bash
lazy my_program.lazy -e
```

---

## Help

```bash
lazy --help
```

---

## Summary

| Command | Description |
|---------|-------------|
| `lazy file.lazy` | Compile only |
| `lazy file.lazy -r` | Compile and run |
| `lazy file.lazy -e` | Compile, run, show exit code |
| `lazy file.lazy -o name` | Specify output name |
| `lazy --help` | Show help |

---

## Complete Example

```bash
# Create a program
cat > test.lazy << 'EOF'
func main() -> int {
    let x: int = 100;
    let y: int = 42;
    return x + y;
}
EOF

# Compile and run
lazy test.lazy -e
```

Output:
```
[SUCCESS] Object file generated: a.out.o
[SUCCESS] Executable created: a.out

Running a.out...
---
---
Exit code: 142
```

Easy as that!
