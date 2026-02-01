# LazyA Project Structure

```
lazyA/
├── CMakeLists.txt              # Main build configuration
├── README.md                   # Project documentation
├── .gitignore                 # Git ignore patterns
│
├── docs/                      # Documentation
│   ├── language_spec.md       # Complete language specification
│   ├── ai_features.md         # AI features documentation
│   └── architecture.md        # System architecture docs
│
├── src/                       # Source code
│   ├── main.cpp              # Compiler entry point
│   │
│   ├── lexer/                # Lexical analysis
│   │   └── lexer.l           # Flex specification
│   │
│   ├── parser/               # Syntax analysis
│   │   └── parser.y          # Bison grammar
│   │
│   ├── ast/                  # Abstract Syntax Tree
│   │   ├── ast.h            # AST node definitions
│   │   └── ast.cpp          # AST implementation
│   │
│   ├── types/                # Type system
│   │   ├── type_system.h
│   │   └── type_system.cpp
│   │
│   ├── semantic/             # Semantic analysis
│   │   ├── symbol_table.h
│   │   ├── symbol_table.cpp
│   │   ├── type_checker.h
│   │   └── type_checker.cpp
│   │
│   ├── codegen/              # Code generation
│   │   ├── llvm_codegen.h
│   │   └── llvm_codegen.cpp
│   │
│   ├── ai/                   # AI integration
│   │   ├── embedding_engine.h       # TensorFlow Lite embeddings
│   │   ├── embedding_engine.cpp
│   │   ├── llm_interface.h          # LLM call interface
│   │   ├── llm_interface.cpp
│   │   ├── context_function.h       # AI code generation
│   │   └── context_function.cpp
│   │
│   ├── runtime/              # Runtime system
│   │   ├── cold_start.h
│   │   ├── cold_start.cpp
│   │   ├── warm_start.h
│   │   ├── warm_start.cpp
│   │   ├── cache_manager.h
│   │   └── cache_manager.cpp
│   │
│   └── meta/                 # Self-modification
│       ├── self_modify.h
│       └── self_modify.cpp
│
├── models/                    # ML models
│   ├── sentence_encoder.tflite    # Embedding model
│   └── README.md                  # Model documentation
│
├── examples/                  # Example programs
│   ├── 01_hello_world.lazy
│   ├── 02_ai_operators.lazy
│   ├── 03_context_function.lazy
│   └── 04_llm_call.lazy
│
├── tests/                     # Test suite
│   ├── CMakeLists.txt
│   ├── lexer_test.cpp
│   ├── parser_test.cpp
│   ├── codegen_test.cpp
│   └── ai_test.cpp
│
├── scripts/                   # Utility scripts
│   ├── setup.sh              # Environment setup
│   └── build.sh              # Build script
│
└── build/                     # Build artifacts (gitignored)
    ├── lazya                 # Compiled compiler
    └── ...
```

## Key Components

### Frontend (Lexer + Parser)
- **lexer.l**: Tokenizes LazyA source code, recognizes AI operators
- **parser.y**: Builds AST from tokens using Bison grammar
- **ast.h/cpp**: AST node definitions and operations

### Type System
- Hybrid typing (weak for AI, strong for critical ops)
- Type inference
- Support for arrays, dictionaries, unions, optionals

### Code Generation
- LLVM backend for optimization and native code generation
- IR generation from AST
- Platform-specific compilation

### AI Integration
- **embedding_engine**: TensorFlow Lite for semantic operations
- **llm_interface**: API for local/cloud LLM calls
- **context_function**: AI code generation from docstrings

### Runtime
- **cold_start**: First-time AI code generation
- **warm_start**: Cached binary execution
- **cache_manager**: Multi-level caching strategy

## Build Process

1. Flex generates lexer C code from `lexer.l`
2. Bison generates parser C code from `parser.y`
3. C++ compiler builds all components
4. LLVM links for code generation
5. TensorFlow Lite links for AI features
6. Final executable: `lazya` compiler

## Usage Flow

```
source.lazy → [lexer] → tokens → [parser] → AST → [semantic] → 
typed AST → [codegen] → LLVM IR → [LLVM] → native binary
                ↓
           [AI layer] (for ~=, @context, llm.*)
```
