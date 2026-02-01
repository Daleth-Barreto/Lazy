#!/bin/bash
# Docker Build Helper for LazyA

set -e

echo "🐳 Building LazyA Docker Images..."
echo ""

# Build all stages
docker-compose build

echo ""
echo "✅ Build complete!"
echo ""
echo "Available images:"
docker images | grep lazya

echo ""
echo "Next steps:"
echo "  1. Start Ollama: docker-compose up ollama -d"
echo "  2. Run compiler: docker-compose run --rm lazya-compiler lazy examples/ex01_primes.lazy"
echo "  3. Or enter dev environment: docker-compose run --rm lazya-dev"
