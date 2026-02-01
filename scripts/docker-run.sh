#!/bin/bash
# Docker Run Helper for LazyA

set -e

# Start Ollama if not running
if ! docker ps | grep -q lazya-ollama; then
    echo "🚀 Starting Ollama service..."
    docker-compose up -d ollama
    echo "⏳ Waiting for Ollama to be healthy..."
    sleep 5
fi

# Check if file argument provided
if [ $# -eq 0 ]; then
    echo "📝 Usage: $0 <file.lazy> [additional args]"
    echo ""
    echo "Examples:"
    echo "  $0 examples/ex01_primes.lazy"
    echo "  $0 my_program.lazy --verbose"
    echo ""
    echo "Or enter interactive shell:"
    echo "  docker-compose run --rm lazya-compiler bash"
    exit 1
fi

FILE=$1
shift  # Remove first argument

echo "🔨 Compiling $FILE..."
docker-compose run --rm lazya-compiler lazy "$FILE" "$@"

echo ""
echo "✅ Compilation complete!"
