# LazyA - Referencia Rápida

## Instalación Global (RECOMENDADO)

```bash
cd /home/daleth/Escritorio/lazyA
sudo ln -sf $(pwd)/lazy /usr/local/bin/lazy
```

Ahora puedes usar `lazy` desde cualquier lugar.

---

## Uso

### Desde cualquier directorio:

```bash
# Compilar y mostrar exit code
lazy mi_programa.lazy -e

# Compilar con nombre específico
lazy programa.lazy -o mi_app -e

# Solo compilar
lazy programa.lazy -o app

# Compilar y ejecutar
lazy programa.lazy -r
```

### Ejemplos reales:

```bash
# Desde el directorio examples
cd /home/daleth/Escritorio/lazyA/examples
lazy test_complete_var.lazy -e          # Exit: 42
lazy test1_arithmetic.lazy -e           # Exit: 42
lazy test2_bitwise.lazy -e              # Exit: 4
lazy test3_if.lazy -e                   # Exit: 1

# Desde tu home
cd ~
lazy Escritorio/lazyA/examples/test_complete_var.lazy -e

# Desde cualquier lugar con ruta completa
lazy /home/daleth/Escritorio/lazyA/examples/test1_arithmetic.lazy -e
```

---

## Crear un Programa

```bash
# Crear archivo
cat > test.lazy << 'EOF'
func main() -> int {
    let x: int = 10;
    let y: int = 32;
    return x + y;
}
EOF

# Compilar y ejecutar
lazy test.lazy -e
```

**Salida:**
```
Compiling test.lazy...
Successfully compiled to: a.out

Running a.out...
---
---
Exit code: 42
```

---

## Opciones del Comando

| Opción | Descripción |
|--------|-------------|
| `lazy file.lazy` | Compilar a `a.out` |
| `lazy file.lazy -o nombre` | Compilar a `nombre` |
| `lazy file.lazy -r` | Compilar y ejecutar |
| `lazy file.lazy -e` | Compilar, ejecutar y mostrar exit code |
| `lazy file.lazy -o app -e` | Todo junto |
| `lazy --help` | Mostrar ayuda |

---

## Características del Lenguaje

### Variables
```lazy
let x: int = 42;        // Tipo explícito
auto y = 100;           // Tipo inferido
```

### Funciones
```lazy
func suma(a: int, b: int) -> int {
    return a + b;
}
```

### Control de Flujo
```lazy
if (x > 10) {
    return 1;
} else {
    return 0;
}
```

### Operadores Bitwise
```lazy
let resultado: int = 12 & 7;   // AND: 4
let resultado2: int = 8 | 3;   // OR: 11
let resultado3: int = 15 ^ 9;  // XOR: 6
let resultado4: int = 3 << 2;  // Left shift: 12
let resultado5: int = 16 >> 2; // Right shift: 4
```

### Operadores Aritméticos
```lazy
+ - * / %
```

### Comparaciones
```lazy
== != < > <= >=
```

---

## Solución de Problemas

### Si `lazy` no se encuentra:
```bash
# Reinstalar el link
cd /home/daleth/Escritorio/lazyA
sudo ln -sf $(pwd)/lazy /usr/local/bin/lazy
```

### Si el compilador falla:
```bash
# Recompilar LazyA
cd /home/daleth/Escritorio/lazyA
./scripts/build.sh
```

### Ver la ayuda:
```bash
lazy --help
```

---

## Ejemplo Completo

```bash
# 1. Crear programa
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

# 2. Compilar y ejecutar
lazy factorial.lazy -o factorial -e

# 3. Ver resultado
# Exit code: 5
```

---

## Tips

- El exit code es el valor que retorna `main()`
- Los programas NO imprimen a la terminal (solo exit code)
- Usa `-e` para ver el exit code automáticamente
- Usa rutas absolutas si estás en otro directorio
- El compilador genera ejecutables de ~17KB
- La compilación toma <1 segundo

---

¡LazyA está listo para usar! 
