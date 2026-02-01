# LazyA - TODO

##  Cleanup Tasks

### Scripts (Unused ONNX)
- [ ] Delete `scripts/download_onnx_model.py`
- [ ] Delete `scripts/export_to_onnx.py`
- [ ] Delete `scripts/download_model.py`

### Empty Folders
- [ ] Delete `stdlib/ai/gemini/`
- [ ] Delete `stdlib/ai/ollama/`
- [ ] Delete `stdlib/ai/openai/`
- [ ] Consider removing entire `stdlib/` (unused)

##  Architecture Improvements

### Model Configuration
- [ ] Create `~/.lazya/config.yaml` for model settings
- [ ] Add `--ai-model` CLI flag
- [ ] Support multiple AI providers (Ollama, OpenAI, Gemini)

### Code Organization
- [ ] Consolidate all AI code in `src/runtime/ai/`
- [ ] Add proper namespacing for stdlib functions
- [ ] Document all runtime functions

##  Docker & Build System
- [x] Create multi-stage Dockerfile
- [x] Create docker-compose.yml with Ollama service
- [x] Add helper scripts (docker-build.sh, docker-run.sh)
- [x] Write comprehensive Docker documentation
- [ ] Test Docker build on fresh system
- [ ] Add CI/CD integration examples

##  Automated Installation System
- [x] One-command installer (install.sh)
- [x] Professional Makefile with all targets
- [x] CLI wrapper with subcommands (lazya new, run, build)
- [x] Automatic dependency detection and installation
- [x] PATH configuration automation
- [x] OS detection (Linux/macOS)
- [x] Installation documentation (INSTALL.md, QUICKSTART.md)
- [x] Updated README with quick install
- [ ] Test on fresh Ubuntu VM
- [ ] Test on fresh macOS
- [ ] Add Windows WSL support

##  Documentation
- [x] Syntax highlighting for VSCode
- [x] Complete language reference (`docs/language_reference.md`)
- [x] Docker setup guide
- [ ] API documentation for runtime functions
- [ ] Tutorial for beginners
- [ ] Lockfile documentation

##  Pending Features

### Semantic Match Operator
- [x] Add `match` keyword to lexer
- [x] Add `=>` (fat arrow) operator
- [x] Add `_` (wildcard) pattern
- [x] Update syntax highlighting
- [ ] Implement AST nodes (MatchNode, MatchArmNode)
- [ ] Implement codegen for semantic matching
- [ ] Add tests for match expressions

### AI Lockfile System
- [ ] Design lockfile JSON schema
- [ ] Implement LockFile class (src/LockFile.h/cpp)
- [ ] Integrate with CodeGenerator
- [ ] Add CLI flags (--lockfile, --update-lockfile)
- [ ] Add verification and hashing
- [ ] Update .gitignore to track .lazy.lock

### Other Features
- [ ] `~>` semantic implication operator (lexer/parser done)
- [ ] Try/catch exception handling
- [ ] Generic types (`func identity<T>(val: T) -> T`)
- [ ] Module/import system
- [ ] Classes and OOP support (partially done)
- [ ] Pattern matching (in progress)
