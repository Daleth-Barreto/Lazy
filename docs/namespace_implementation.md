# Namespace System Implementation - Technical Summary

## Current Status
- Lexer recognizes `NAMESPACE_ID` for `module.function`
- Parser handles simple calls like `llm.complete()`
- ❌ NO support for nested namespaces (`ai.ollama.chat`)
- ❌ NO full name resolution

## Implementation Plan

### 1. Update Lexer (lexer.l)
Switch from simple `NAMESPACE_ID` to full string recognition:
- Current: `llm.chat` → Single token
- New: `ai.ollama.chat` → Parse in parser

### 2. Update Parser (parser.y)
Allow member access chains for function calls:
```
ai.ollama.chat()
└─ ai 
   └─ ollama
      └─ chat()
```

### 3. Code Generation
Resolve namespace paths to runtime function names:
- `ai.ollama.chat()` → `ai_ollama_chat` (C function)

### 4. Runtime Functions
Create functions with naming convention:
```cpp
extern "C" char* ai_ollama_chat(char* message, char* model);
extern "C" char* ai_gemini_chat(char* message, char* model);
```

## Files to Modify
1. `src/lexer/lexer.l` - Namespace pattern
2. `src/parser/parser.y` - Nested member access grammar
3. `src/codegen/llvm_codegen.cpp` - Namespace resolution
4. `src/runtime/ai/` - Actual implementations

## Strategy
Use existing member access (`primary_expr DOT IDENTIFIER`) to build namespaces,
then resolve in codegen.
