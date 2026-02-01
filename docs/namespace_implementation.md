# Implementación del Sistema de Namespaces - Resumen Técnico

## Estado Actual
-  Lexer reconoce `NAMESPACE_ID` para `module.function`
-  Parser maneja llamadas simples tipo `llm.complete()`
- ❌ NO soporta namespaces anidados (`ai.ollama.chat`)
- ❌ NO hay resolución de nombres completa

## Plan de Implementación

### 1. Actualizar Lexer (lexer.l)
Cambiar de `NAMESPACE_ID` simple a reconocimiento de cadenas completas:
- Actual: `llm.chat` → Token único
- Nuevo: `ai.ollama.chat` → Analizar en parser

### 2. Actualizar Parser (parser.y)
Permitir member access chains para function calls:
```
ai.ollama.chat()
└─ ai 
   └─ ollama
      └─ chat()
```

### 3. Code Generation
Resolver namespace paths a nombres de funciones runtime:
- `ai.ollama.chat()` → `ai_ollama_chat` (función C)

### 4. Runtime Functions
Crear funciones con naming convention:
```cpp
extern "C" char* ai_ollama_chat(char* message, char* model);
extern "C" char* ai_gemini_chat(char* message, char* model);
```

## Archivos a Modificar
1. `src/lexer/lexer.l` - Pattern para namespaces
2. `src/parser/parser.y` - Grammar para nested member access
3. `src/codegen/llvm_codegen.cpp` - Resolución de namespaces
4. `src/runtime/ai/` - Implementaciones reales

## Estrategia
Usar member access existente (`primary_expr DOT IDENTIFIER`) para construir namespaces,
luego resolver en codegen.
