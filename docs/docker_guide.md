# Docker Guide for LazyA

This guide explains how to build and run LazyA using Docker, avoiding the complexity of manual dependency installation.

## Why Docker?

Building LazyA requires:
- LLVM 15+
- CMake 3.15+
- Flex & Bison
- Ollama for AI features
- Various C++ libraries

Docker packages everything into a reproducible environment.

## Quick Start

### 1. Build the Images

```bash
./scripts/docker-build.sh
```

Or manually:
```bash
docker-compose build
```

### 2. Start Ollama

```bash
docker-compose up ollama -d
```

Download AI models:
```bash
docker exec lazya-ollama ollama pull codellama:7b
docker exec lazya-ollama ollama pull qwen2:0.5b
```

### 3. Compile LazyA Code

Using the helper script:
```bash
./scripts/docker-run.sh examples/ex01_primes.lazy
```

Or manually:
```bash
docker-compose run --rm lazya-compiler lazy examples/ex01_primes.lazy
```

### 4. Run Compiled Binary

```bash
docker-compose run --rm lazya-compiler ./a.out
```

## Development Workflow

### Interactive Shell

```bash
docker-compose run --rm lazya-dev bash
```

Inside the container:
```bash
# Build from source
cd /lazya-src
mkdir -p build && cd build
cmake ..
make -j$(nproc)

# Run compiler
./lazy /workspace/my_program.lazy
```

### Edit-Compile-Run Loop

1. Edit code on your host (files are mounted in `/workspace`)
2. Compile in container:
   ```bash
   docker-compose run --rm lazya-compiler lazy my_program.lazy
   ```
3. Run in container:
   ```bash
   docker-compose run --rm lazya-compiler ./a.out
   ```

### Running All Tests

```bash
docker-compose run --rm lazya-compiler bash -c "cd /examples && ../verify_all.sh"
```

## Architecture

```
┌─────────────────────────────────────┐
│          Docker Compose             │
└──────────┬──────────────────────────┘
           │
           ├── ollama (service)
           │   └── Port: 11434
           │   └── Volume: ollama-data
           │
           ├── lazya-compiler (runtime)
           │   └── Contains: /usr/local/bin/lazy
           │   └── Mounts: ./workspace
           │
           └── lazya-dev (development)
               └── Contains: Full source + tools
               └── Mounts: ./ workspace
```

## Services

### ollama
- **Purpose**: AI model inference
- **Port**: 11434
- **Health check**: Ensures service is ready
- **Volume**: Persists downloaded models

### lazya-compiler
- **Purpose**: Run compiled LazyA binary
- **Depends on**: ollama (healthy)
- **Environment**: `OLLAMA_HOST=http://ollama:11434`
- **Volumes**: Current directory mounted to `/workspace`

### lazya-dev  
- **Purpose**: Full development environment
- **Includes**: Source code, build tools, editors
- **Use case**: Modifying compiler itself

## Common Commands

### Build

```bash
# Build all services
docker-compose build

# Build specific service
docker-compose build lazya-compiler

# Rebuild without cache
docker-compose build --no-cache
```

### Run

```bash
# Compile a file
docker-compose run --rm lazya-compiler lazy my_file.lazy

# Interactive shell
docker-compose run --rm lazya-compiler bash

# Run with custom Ollama host
docker-compose run --rm -e OLLAMA_HOST=http://my-ollama:11434 lazya-compiler lazy file.lazy
```

### Manage Services

```bash
# Start Ollama in background
docker-compose up -d ollama

# Stop all services
docker-compose down

# View logs
docker-compose logs ollama

# Remove volumes (deletes downloaded models!)
docker-compose down -v
```

## Troubleshooting

### "Ollama not reachable"

Check Ollama is running:
```bash
docker ps | grep ollama
```

Start it:
```bash
docker-compose up -d ollama
```

Test connectivity:
```bash
docker-compose run --rm lazya-compiler curl http://ollama:11434/api/tags
```

### "Model not found"

Download required models:
```bash
docker exec lazya-ollama ollama pull codellama:7b
docker exec lazya-ollama ollama pull qwen2:0.5b
```

List available models:
```bash
docker exec lazya-ollama ollama list
```

### "Build fails"

Check Docker has enough resources:
- RAM: At least 4GB
- Disk: At least 10GB free

View build logs:
```bash
docker-compose build --progress=plain
```

### "Permission denied"

Make scripts executable:
```bash
chmod +x scripts/docker-*.sh
```

## Production Deployment

### Build Production Image

```bash
docker build --target runtime -t lazya:latest .
```

### Run Without Compose

```bash
# Start Ollama
docker run -d --name ollama -p 11434:11434 ollama/ollama:latest

# Run LazyA
docker run --rm \
  -v $(pwd):/workspace \
  -e OLLAMA_HOST=http://ollama:11434 \
  --link ollama \
  lazya:latest \
  lazy /workspace/my_program.lazy
```

### Push to Registry

```bash
docker tag lazya:latest myregistry/lazya:latest
docker push myregistry/lazya:latest
```

## Advanced Usage

### Custom CMake Flags

Edit `Dockerfile` build stage:
```dockerfile
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Debug .. && \
    make -j$(nproc)
```

### Use External Ollama

```bash
# Don't start Ollama service
docker-compose run --rm \
  -e OLLAMA_HOST=http://your-ollama-server:11434 \
  lazya-compiler lazy file.lazy
```

### Volume Mounts for Large Projects

```yaml
# In docker-compose.yml
services:
  lazya-compiler:
    volumes:
      - /path/to/my/project:/workspace
      - /path/to/lockfiles:/workspace/.lazy.lock:ro
```

## CI/CD Integration

### GitHub Actions Example

```yaml
name: Build LazyA
on: [push]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Build Docker image
        run: docker-compose build lazya-compiler
        
      - name: Run tests
        run: |
          docker-compose up -d ollama
          docker-compose run --rm lazya-compiler /verify_all.sh
```

### GitLab CI Example

```yaml
build:
  image: docker:latest
  services:
    - docker:dind
  script:
    - docker-compose build
    - docker-compose up -d ollama
    - docker-compose run --rm lazya-compiler /verify_all.sh
```

## Resources

- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Reference](https://docs.docker.com/compose/)
- [Ollama Docker Hub](https://hub.docker.com/r/ollama/ollama)
- [LazyA Repository](https://github.com/Daleth-Barreto/LazyA)

## Tips

1. **Use `--rm` flag**: Automatically remove containers after exit
2. **Cache builds**: Docker caches layers, rebuilds are faster
3. **Multi-stage builds**: Keep final image small
4. **Named volumes**: Persist Ollama models across restarts
5. **Health checks**: Ensure Ollama is ready before compiling
