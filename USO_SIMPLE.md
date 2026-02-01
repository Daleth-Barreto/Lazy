# LazyA - Uso Simple

## Comando Simplificado

Ahora puedes compilar y ejecutar con un solo comando:

```bash
lazy program.lazy -e
```

---

## Opciones Disponibles

### Compilar solamente
```bash
lazy program.lazy
```
Crea `a.out`

### Compilar con nombre personalizado
```bash
lazy program.lazy -o mi_programa
```
Crea `mi_programa`

### Compilar y ejecutar
```bash
lazy program.lazy -r
```
Compila a `a.out` y ejecuta inmediatamente

### Compilar, ejecutar y mostrar exit code
```bash
lazy program.lazy -e
```
Compila, ejecuta y muestra el exit code

### Combinar opciones
```bash
lazy program.lazy -o test -e
```
Compila a `test`, ejecuta y muestra el exit code

---

## Ejemplos

```bash
# Test básico
lazy examples/test_complete_var.lazy -e

# Aritmética
lazy examples/test1_arithmetic.lazy -o calc -e

# Bitwise
lazy examples/test2_bitwise.lazy -r

# If/else
lazy examples/test3_if.lazy -e
```

---

## Instalación Global (Opcional)

Para usar `lazy` desde cualquier directorio, asegúrate de haber corrido `source ~/.zshrc` (o tu config shell).

Luego desde cualquier lugar:
```bash
lazy mi_programa.lazy -e
```

---

## Ayuda

```bash
lazy --help
```

---

## Resumen

| Comando | Descripción |
|---------|-------------|
| `lazy file.lazy` | Solo compilar |
| `lazy file.lazy -r` | Compilar y ejecutar |
| `lazy file.lazy -e` | Compilar, ejecutar, mostrar exit code |
| `lazy file.lazy -o name` | Especificar nombre de salida |
| `lazy --help` | Mostrar ayuda |

---

## Ejemplo Completo

```bash
# Crear un programa
cat > test.lazy << 'EOF'
func main() -> int {
    let x: int = 100;
    let y: int = 42;
    return x + y;
}
EOF

# Compilar y ejecutar
lazy test.lazy -e
```

Salida:
```
[SUCCESS] Object file generated: a.out.o
[SUCCESS] Executable created: a.out

Running a.out...
---
---
Exit code: 142
```

¡Así de fácil!

---

## Opciones Disponibles

### Compilar solamente
```bash
./lazy program.lazy
```
Crea `a.out`

### Compilar con nombre personalizado
```bash
./lazy program.lazy -o mi_programa
```
Crea `mi_programa`

### Compilar y ejecutar
```bash
./lazy program.lazy -r
```
Compila a `a.out` y ejecuta inmediatamente

### Compilar, ejecutar y mostrar exit code
```bash
./lazy program.lazy -e
```
Compila, ejecuta y muestra el exit code

### Combinar opciones
```bash
./lazy program.lazy -o test -e
```
Compila a `test`, ejecuta y muestra el exit code

---

## Ejemplos

```bash
# Test básico
./lazy examples/test_complete_var.lazy -e

# Aritmética
./lazy examples/test1_arithmetic.lazy -o calc -e

# Bitwise
./lazy examples/test2_bitwise.lazy -r

# If/else
./lazy examples/test3_if.lazy -e
```

---

## Instalación Global (Opcional)

Para usar `lazy` desde cualquier directorio:

```bash
cd /home/daleth/Escritorio/lazyA
sudo ln -s $(pwd)/lazy /usr/local/bin/lazy
```

Luego desde cualquier lugar:
```bash
lazy mi_programa.lazy -e
```

---

## Ayuda

```bash
./lazy --help
```

---

## Resumen

| Comando | Descripción |
|---------|-------------|
| `./lazy file.lazy` | Solo compilar |
| `./lazy file.lazy -r` | Compilar y ejecutar |
| `./lazy file.lazy -e` | Compilar, ejecutar, mostrar exit code |
| `./lazy file.lazy -o name` | Especificar nombre de salida |
| `./lazy --help` | Mostrar ayuda |

---

## Ejemplo Completo

```bash
cd /home/daleth/Escritorio/lazyA

# Crear un programa
cat > test.lazy << 'EOF'
func main() -> int {
    let x: int = 100;
    let y: int = 42;
    return x + y;
}
EOF

# Compilar y ejecutar
./lazy test.lazy -e
```

Salida:
```
Compiling test.lazy...
Successfully compiled to: a.out

Running a.out...
---
---
Exit code: 142
```

¡Así de fácil!
