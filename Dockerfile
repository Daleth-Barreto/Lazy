# Dockerfile for LazyA Compiler
# Multi-stage build for optimized image size

# ============================================
# Stage 1: Builder - Compile LazyA
# ============================================
FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    clang \
    llvm-15 \
    llvm-15-dev \
    flex \
    bison \
    git \
    curl \
    libcurl4-openssl-dev \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

# Create working directory
WORKDIR /build

# Copy source code
COPY . /build/

# Build LazyA compiler
RUN mkdir -p build && cd build && \
    cmake .. && \
    make -j$(nproc)

# ============================================
# Stage 2: Runtime - Install Ollama and Models
# ============================================
FROM ubuntu:24.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    curl \
    ca-certificates \
    libcurl4 \
    && rm -rf /var/lib/apt/lists/*

# Install Ollama
RUN curl -fsSL https://ollama.com/install.sh | sh

# Copy compiled binary from builder
COPY --from=builder /build/build/lazy /usr/local/bin/lazy
COPY --from=builder /build/examples /examples
COPY --from=builder /build/verify_all.sh /verify_all.sh

# Create workspace directory
WORKDIR /workspace

# Expose Ollama port (if running Ollama in same container)
EXPOSE 11434

# Default command
CMD ["bash"]

# ============================================
# Stage 3: Development - Full environment
# ============================================
FROM runtime AS development

# Install additional dev tools
RUN apt-get update && apt-get install -y \
    vim \
    git \
    make \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Copy entire source for development
COPY --from=builder /build /lazya-src

WORKDIR /lazya-src

CMD ["bash"]
