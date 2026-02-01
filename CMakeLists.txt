cmake_minimum_required(VERSION 3.15)
project(Lazy VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Options
option(BUILD_TESTS "Build test suite" ON)
option(ENABLE_AI "Enable AI features (requires TensorFlow Lite)" OFF)  # Disabled by default for MVP

# Find dependencies
find_package(LLVM 18.1 REQUIRED CONFIG)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# LLVM includes and definitions
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# Find TensorFlow Lite (if enabled)
if(ENABLE_AI)
    # User must set TENSORFLOW_LITE_DIR
    if(NOT DEFINED TENSORFLOW_LITE_DIR)
        message(WARNING "TENSORFLOW_LITE_DIR not set. AI features will be disabled.")
        set(ENABLE_AI OFF)
    else()
        include_directories(${TENSORFLOW_LITE_DIR}/include)
        link_directories(${TENSORFLOW_LITE_DIR}/lib)
        add_definitions(-DENABLE_AI)
    endif()
endif()

# Flex and Bison targets
FLEX_TARGET(LazyLexer 
    src/lexer/lexer.l 
    ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.h
)

BISON_TARGET(LazyParser 
    src/parser/parser.y 
    ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
)

ADD_FLEX_BISON_DEPENDENCY(LazyLexer LazyParser)

# Sanitization of generated files
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.sane.c
    COMMAND sed "s|${CMAKE_SOURCE_DIR}|.|g" ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c > ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.part
    COMMAND sed "s|${CMAKE_BINARY_DIR}|.|g" ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.part > ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.sane.c
    COMMAND rm ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.part
    DEPENDS ${FLEX_LazyLexer_OUTPUTS}
    COMMENT "Sanitizing lex.yy.c absolute paths"
    VERBATIM
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.sane.c
    COMMAND sed "s|${CMAKE_SOURCE_DIR}|.|g" ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c > ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.part
    COMMAND sed "s|${CMAKE_BINARY_DIR}|.|g" ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.part > ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.sane.c
    COMMAND rm ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.part
    DEPENDS ${BISON_LazyParser_OUTPUTS}
    COMMENT "Sanitizing parser.tab.c absolute paths"
    VERBATIM
)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Enable exceptions for Ollama/JSON support
add_compile_options(-fexceptions)

# Source files
set(LAZY_SOURCES
    src/main.cpp
    src/ast/ast.cpp
    src/types/type_system.cpp
    src/codegen/llvm_codegen.cpp
    src/codegen/AIFunctionGenerator.cpp
    src/runtime/cache_manager.cpp
    src/runtime/RuntimeRegistry.cpp
    src/runtime/StdLib.cpp
    src/runtime/RuntimeShim.cpp     # Added Shim
    src/runtime/PrintFunction.cpp
    src/runtime/http/HTTPClient.cpp
    src/runtime/StringOps.cpp
    src/runtime/ai/OllamaClient.cpp
    src/runtime/ai/OllamaRuntime.cpp
    src/runtime/ai/AISemanticOps.cpp
    src/runtime/ai/AISemanticRuntime.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.sane.c
    ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.sane.c
)

# Add AI sources if enabled
if(ENABLE_AI)
    list(APPEND LAZY_SOURCES
        src/ai/embedding_engine.cpp
        src/ai/llm_interface.cpp
        src/ai/context_function.cpp
    )
endif()

# Runtime Library (liblazy_runtime.a)
# This library is linked by the *generated* user programs, NOT the compiler itself.
add_library(lazy_runtime STATIC
    src/runtime/RuntimeShim.cpp
    src/runtime/StringOps.cpp
    src/runtime/ai/OllamaRuntime.cpp
    src/runtime/ai/OllamaClient.cpp  # Needed for runtime AI calls
    src/runtime/ai/AISemanticRuntime.cpp
    src/runtime/ai/AISemanticOps.cpp  # Contains ai_semantic_equals implementation
    src/runtime/http/HTTPClient.cpp # Needed by OllamaClient
)

# Define macro to exclude LLVM code from runtime build
target_compile_definitions(lazy_runtime PRIVATE LAZY_RUNTIME_BUILD)

# Installation for runtime
install(TARGETS lazy_runtime DESTINATION lib)

# Executable
add_executable(lazy ${LAZY_SOURCES})

# Link LLVM libraries
llvm_map_components_to_libnames(llvm_libs 
    core 
    support 
    irreader 
    codegen 
    target
    mc
    AllTargetsAsmParsers
    AllTargetsDescs
    AllTargetsInfos
    x86codegen
    x86asmparser
    x86desc
    x86info
)

target_link_libraries(lazy ${llvm_libs})

# Link TensorFlow Lite if enabled
if(ENABLE_AI)
    target_link_libraries(lazy tensorflowlite)
endif()

# Install
install(TARGETS lazy DESTINATION bin)

# Tests
if(BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    enable_testing()
    add_subdirectory(tests)
endif()

# Print configuration summary
message(STATUS "")
message(STATUS "LazyA Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Tests: ${BUILD_TESTS}")
message(STATUS "  AI Features (TF Lite): ${ENABLE_AI}")
message(STATUS "  AI Features (Ollama):  ON (Native)")
message(STATUS "  Flex: ${FLEX_EXECUTABLE}")
message(STATUS "  Bison: ${BISON_EXECUTABLE}")
message(STATUS "")
