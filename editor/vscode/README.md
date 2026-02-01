# Syntax Highlighting para LazyA

## Problema Solucionado 

El syntax highlighting no funcionaba debido a **errores de escaping en los patrones regex** del archivo `tmLanguage.json`.

### Errores Corregidos:

1. **Operadores de comparación** (`<`, `>`, `<=`, `>=`) - No estaban escapados correctamente
2. **Operador semántico** (`~>`) - El `>` no estaba escapado
3. **Operadores bitwise** (`<<`, `>>`, `&`) - Faltaba escaping
4. **Operador arrow** (`->`) - No estaba escapado
5. **Operador lógico** (`&&`) - Faltaba escaping

## Instalación

### Opción 1: Script Automático (Recomendado)
```bash
cd /home/daleth/Escritorio/lazyA/editor/vscode
chmod +x install.sh
./install.sh
```

### Opción 2: Instalación Manual desde VSCode
1. Abre VSCode
2. Presiona `Ctrl+Shift+P`
3. Busca: `Extensions: Install from VSIX`
4. Selecciona: `/home/daleth/Escritorio/lazyA/editor/vscode/lazya-0.1.0.vsix`
5. Reinicia VSCode

### Opción 3: Línea de comandos
```bash
# Si tienes 'code' en el PATH:
code --install-extension /home/daleth/Escritorio/lazyA/editor/vscode/lazya-0.1.0.vsix

# Para VSCodium:
codium --install-extension /home/daleth/Escritorio/lazyA/editor/vscode/lazya-0.1.0.vsix
```

## Verificación

Después de instalar:
1. Reinicia VSCode completamente
2. Abre cualquier archivo `.lazy` (por ejemplo: `examples/ex01_primes.lazy`)
3. Verifica que veas colores en:
   - **Keywords** (azul): `func`, `let`, `if`, `while`, `return`
   - **Types** (verde): `int`, `string`, `bool`
   - **Strings** (naranja/rojo): `"texto entre comillas"`
   - **Comments** (gris): `// comentarios`
   - **Numbers** (verde claro): `123`, `45.67`
   - **Decorators** (amarillo): `@verify`, `@ask`, `@generate`

## Características del Syntax Highlighting

La extensión incluye resaltado para:

### Keywords
- Control: `if`, `else`, `while`, `for`, `return`, `break`, `continue`
- Declaración: `func`, `let`, `auto`, `var`, `class`, `new`, `import`
- AI: `llm`, `embed`, `threshold`, `ai`, `ollama`, `model`, `prompt`

### Tipos de Datos
- Primitivos: `int`, `float`, `string`, `bool`, `void`, `auto`
- AI Types: `prompt`, `airesponse`, `model`
- Arrays: `[tipo]`
- Maps: `{key: value}`

### Operadores
- Semánticos: `~=`, `~>`
- Comparación: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Aritméticos: `+`, `-`, `*`, `/`, `%`, `**`
- Lógicos: `&&`, `||`, `!`
- Bitwise: `&`, `|`, `^`, `<<`, `>>`, `~`
- Arrow: `->`, `...`

### Decoradores AI
- `@ask` - Consultas a LLM
- `@generate` - Generación de código
- `@verify` - Verificación con AI
- `@context`, `@cached`, `@inline`, etc.

### Funciones Built-in
- I/O: `print`, `println`, `print_str`, `print_int`
- Archivos: `file_open`, `file_write`, `file_read`, `file_close`, `file_size`
- AI: `cosine_similarity`, `embed`
- Utilidades: `append`, `length`

## Solución de Problemas

### El highlighting no aparece después de instalar
1. **Reinicia VSCode completamente** (cierra todas las ventanas)
2. Verifica que la extensión esté instalada: `Ctrl+Shift+X` → Busca "LazyA"
3. Verifica que el archivo tenga extensión `.lazy`
4. Comprueba que VSCode reconozca el lenguaje (abajo a la derecha debe decir "LazyA")

### El archivo se abre como texto plano
1. Click en el selector de lenguaje (esquina inferior derecha)
2. Busca y selecciona "LazyA"
3. VSCode debería recordar esta asociación para futuros archivos `.lazy`

### Quiero modificar los colores
Los colores dependen del theme de VSCode que uses. Puedes personalizar los tokens en:
`Settings` → `Editor: Token Color Customizations`

Ejemplo:
```json
{
  "editor.tokenColorCustomizations": {
    "textMateRules": [
      {
        "scope": "entity.name.function.decorator.lazya",
        "settings": {
          "foreground": "#FFD700",
          "fontStyle": "bold"
        }
      }
    ]
  }
}
```

## Desarrollo

Si quieres modificar la extensión:

1. Edita los archivos:
   - `syntaxes/lazya.tmLanguage.json` - Reglas de syntax highlighting
   - `language-configuration.json` - Configuración del lenguaje (brackets, comments, etc.)
   - `package.json` - Metadatos de la extensión

2. Recompila:
   ```bash
   cd /home/daleth/Escritorio/lazyA/editor/vscode
   npx @vscode/vsce package
   ```

3. Reinstala:
   ```bash
   ./install.sh
   ```

## Recursos Adicionales

- [TextMate Grammar Documentation](https://macromates.com/manual/en/language_grammars)
- [VSCode Language Extensions Guide](https://code.visualstudio.com/api/language-extensions/overview)
- [Scope Naming Conventions](https://www.sublimetext.com/docs/scope_naming.html)
