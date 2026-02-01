# LazyA Compiler Makefile

.PHONY: all build install uninstall clean test examples docker help

# Configuration
PREFIX ?= /usr/local
LAZYA_HOME ?= $(HOME)/.lazy
BUILD_TYPE ?= Release
JOBS ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Colors
BLUE := \033[0;34m
GREEN := \033[0;32m
YELLOW := \033[1;33m
NC := \033[0m

all: build

##@ Building

build: ## Build the LazyA compiler
	@echo "$(BLUE)[BUILD]$(NC) Building LazyA compiler..."
	@mkdir -p build
	@cd build && cmake .. -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) && make -j$(JOBS)
	@echo "$(GREEN)[✓]$(NC) Build complete: build/lazy"

clean: ## Clean build artifacts
	@echo "$(BLUE)[CLEAN]$(NC) Removing build directory..."
	@rm -rf build
	@echo "$(GREEN)[✓]$(NC) Clean complete"

##@ Installation

install: build ## Install LazyA to system (requires sudo)
	@echo "$(BLUE)[INSTALL]$(NC) Installing to $(LAZYA_HOME)..."
	@mkdir -p $(LAZYA_HOME)/bin
	@mkdir -p $(LAZYA_HOME)/lib
	@mkdir -p $(LAZYA_HOME)/examples
	@cp build/lazy $(LAZYA_HOME)/bin/
	@cp -r examples/* $(LAZYA_HOME)/examples/ 2>/dev/null || true
	@chmod +x $(LAZYA_HOME)/bin/lazy
	@echo "$(GREEN)[✓]$(NC) Installed to $(LAZYA_HOME)"
	@echo ""
	@echo "Add to your PATH:"
	@echo '  export PATH="$(LAZYA_HOME)/bin:$$PATH"'

install-system: build ## Install to /usr/local/bin (requires sudo)
	@echo "$(BLUE)[INSTALL]$(NC) Installing to $(PREFIX)/bin..."
	@sudo cp build/lazy $(PREFIX)/bin/
	@sudo chmod +x $(PREFIX)/bin/lazy
	@echo "$(GREEN)[✓]$(NC) Installed to $(PREFIX)/bin/lazy"

uninstall: ## Uninstall LazyA from system
	@echo "$(BLUE)[UNINSTALL]$(NC) Removing LazyA..."
	@rm -rf $(LAZYA_HOME)
	@sudo rm -f $(PREFIX)/bin/lazy
	@echo "$(GREEN)[✓]$(NC) Uninstalled"

##@ Testing

test: build ## Run all tests
	@echo "$(BLUE)[TEST]$(NC) Running tests..."
	@./verify_all.sh
	@echo "$(GREEN)[✓]$(NC) Tests complete"

examples: build ## Run all examples
	@echo "$(BLUE)[EXAMPLES]$(NC) Running examples..."
	@for file in examples/*.lazy; do \
		echo "$(YELLOW)[RUN]$(NC) $$file"; \
		./build/lazy $$file && ./a.out || exit 1; \
		echo ""; \
	done
	@echo "$(GREEN)[✓]$(NC) All examples passed"

##@ Docker

docker-build: ## Build Docker images
	@echo "$(BLUE)[DOCKER]$(NC) Building images..."
	@docker compose build
	@echo "$(GREEN)[✓]$(NC) Docker images built"

docker-run: ## Run compiler in Docker
	@echo "$(BLUE)[DOCKER]$(NC) Starting LazyA in Docker..."
	@docker compose run --rm lazya-compiler bash

docker-clean: ## Remove Docker containers and images
	@echo "$(BLUE)[DOCKER]$(NC) Cleaning Docker resources..."
	@docker compose down -v
	@docker rmi lazya-compiler lazya-dev 2>/dev/null || true
	@echo "$(GREEN)[✓]$(NC) Docker cleaned"

docker-test: ## Run tests in Docker
	@echo "$(BLUE)[DOCKER]$(NC) Running tests in Docker..."
	@docker compose run --rm lazya-compiler /verify_all.sh

##@ Development

dev: ## Start development environment
	@echo "$(BLUE)[DEV]$(NC) Starting development environment..."
	@docker compose run --rm lazya-dev bash

format: ## Format source code (requires clang-format)
	@echo "$(BLUE)[FORMAT]$(NC) Formatting code..."
	@find src -name "*.cpp" -o -name "*.h" | xargs clang-format -i
	@echo "$(GREEN)[✓]$(NC) Code formatted"

lint: ## Lint source code (requires cpplint)
	@echo "$(BLUE)[LINT]$(NC) Linting code..."
	@cpplint --recursive src/
	@echo "$(GREEN)[✓]$(NC) Linting complete"

##@ VSCode Extension

extension: ## Build VSCode extension
	@echo "$(BLUE)[EXTENSION]$(NC) Building VSCode extension..."
	@cd editor/vscode && npx @vscode/vsce package
	@echo "$(GREEN)[✓]$(NC) Extension built: editor/vscode/lazya-0.1.0.vsix"

extension-install: extension ## Install VSCode extension
	@echo "$(BLUE)[EXTENSION]$(NC) Installing VSCode extension..."
	@cd editor/vscode && ./install.sh
	@echo "$(GREEN)[✓]$(NC) Extension installed"

##@ One-Command Install

quick-install: ## Quick install (auto-detect best method)
	@chmod +x install.sh
	@./install.sh

##@ Utilities

info: ## Show build information
	@echo "LazyA Build Information:"
	@echo "  Build type: $(BUILD_TYPE)"
	@echo "  Jobs: $(JOBS)"
	@echo "  Install prefix: $(PREFIX)"
	@echo "  LazyA home: $(LAZYA_HOME)"
	@echo ""
	@echo "Dependencies:"
	@command -v cmake >/dev/null 2>&1 && echo "  ✓ cmake" || echo "  ✗ cmake"
	@command -v make >/dev/null 2>&1 && echo "  ✓ make" || echo "  ✗ make"
	@command -v g++ >/dev/null 2>&1 && echo "  ✓ g++" || echo "  ✗ g++"
	@command -v flex >/dev/null 2>&1 && echo "  ✓ flex" || echo "  ✗ flex"
	@command -v bison >/dev/null 2>&1 && echo "  ✓ bison" || echo "  ✗ bison"
	@command -v docker >/dev/null 2>&1 && echo "  ✓ docker" || echo "  ✗ docker"
	@command -v ollama >/dev/null 2>&1 && echo "  ✓ ollama" || echo "  ✗ ollama"

help: ## Show this help message
	@echo "$(BLUE)LazyA Compiler - Build System$(NC)"
	@echo ""
	@awk 'BEGIN {FS = ":.*##"; printf "Usage: make $(YELLOW)<target>$(NC)\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  $(BLUE)%-20s$(NC) %s\n", $$1, $$2 } /^##@/ { printf "\n$(GREEN)%s$(NC)\n", substr($$0, 5) } ' $(MAKEFILE_LIST)
	@echo ""
	@echo "Quick start:"
	@echo "  make quick-install   # One-command installation"
	@echo "  make build           # Build compiler"
	@echo "  make test            # Run tests"
	@echo "  make install         # Install to ~/.lazya"
