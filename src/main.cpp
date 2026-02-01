/*
 * Lazy Compiler - Main Entry Point
 * 
 * Usage: lazy [options] <source.lazy>
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

#include "codegen/llvm_codegen.h"

// Forward declarations from Flex/Bison
extern "C" {
    extern FILE* yyin;
    extern int yyparse();
    extern int yylineno;
}

// Root is ASTNode*, not void*
extern ASTNode* root;
extern void print_ast(ASTNode* node);

void print_usage(const char* program) {
    std::cout << "Lazy Compiler v0.1.0\n";
    std::cout << "\nUsage: lazy [command] [options] <file>\n";
    std::cout << "\nCommands:\n";
    std::cout << "  new <name>           Create a new project\n";
    std::cout << "  examples             List available examples\n";
    std::cout << "  uninstall            Uninstall Lazy\n";
    std::cout << "\nOptions:\n";
    std::cout << "  -h, --help           Show this help message\n";
    std::cout << "  -v, --verbose        Verbose output\n";
    std::cout << "  -o <file>            Output file (default: a.out)\n";
    std::cout << "  -r                   Compile and run immediately\n";
    std::cout << "  -e                   Compile, run, and show exit code\n";
    std::cout << "  --ast                Print AST and exit\n";
    std::cout << "  --cold-start         Force AI code generation\n";
    std::cout << "  --no-ai              Disable AI features\n";
    std::cout << "  --version            Show version\n";
    std::cout << "\nExamples:\n";
    std::cout << "  lazy new my_app\n";
    std::cout << "  lazy examples\n";
    std::cout << "  lazy main.lazy -e\n";
}

void print_version() {
    std::cout << "Lazy Compiler v0.1.0\n";
    std::cout << "Built with:\n";
    std::cout << "  - LLVM (code generation)\n";
    std::cout << "  - TensorFlow Lite (AI engine)\n";
    std::cout << "  - Flex & Bison (parser)\n";
}

struct CompilerOptions {
    std::string input_file;
    std::string output_file = "a.out";
    bool verbose = false;
    bool print_ast = false;
    bool cold_start = false;
    bool no_ai = false;
};

// Return codes: 0 = continue, 1 = exit success, -1 = exit error
int parse_arguments(int argc, char** argv, CompilerOptions& opts) {
    if (argc < 2) {
        // No args -> Show help
        print_usage("lazy");
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            print_usage("lazy");
            return 1;
        } else if (arg == "--version") {
            print_version();
            return 1;
        } else if (arg == "-v" || arg == "--verbose") {
            opts.verbose = true;
        } else if (arg == "--ast") {
            opts.print_ast = true;
        } else if (arg == "--cold-start") {
            opts.cold_start = true;
        } else if (arg == "--no-ai") {
            opts.no_ai = true;
        } else if (arg == "-r") {
            // Handled by wrapper, but accept it to avoid errors if passed directly
        } else if (arg == "-e") {
            // Handled by wrapper, but accept it to avoid errors if passed directly
        } else if (arg == "-o") {
            if (i + 1 < argc) {
                opts.output_file = argv[++i];
            } else {
                std::cerr << "Error: -o requires an argument\n";
                return -1;
            }
        } else if (arg[0] == '-') {
            std::cerr << "Error: Unknown option: " << arg << "\n";
            return -1;
        } else {
            if (opts.input_file.empty()) {
                opts.input_file = arg;
            } else {
                std::cerr << "Error: Multiple input files not supported\n";
                return -1;
            }
        }
    }
    
    if (opts.input_file.empty()) {
        std::cerr << "Error: No input file specified\n";
        return -1;
    }
    
    return 0;
}

#include "runtime/StdLib.h"

int main(int argc, char** argv) {
    // Register standard library functions (IO, Vectors, Maps)
    lazya::register_standard_library();

    CompilerOptions opts;
    
    int parse_status = parse_arguments(argc, argv, opts);
    if (parse_status == 1) return 0; // Exit success (help/version)
    if (parse_status == -1) return 1; // Exit error
    
    // Continue compilation...
    
    if (opts.verbose) {
        std::cout << "LazyA Compiler v0.1.0\n";
        std::cout << "Input:  " << opts.input_file << "\n";
        std::cout << "Output: " << opts.output_file << "\n";
        if (opts.no_ai) std::cout << "AI features: DISABLED\n";
        if (opts.cold_start) std::cout << "Mode: COLD START\n";
        std::cout << "\n";
    }
    
    // Open input file
    yyin = fopen(opts.input_file.c_str(), "r");
    if (!yyin) {
        std::cerr << "Error: Could not open file: " << opts.input_file << "\n";
        return 1;
    }
    
    // Parse
    if (opts.verbose) {
        std::cout << "Parsing...\n";
    }
    
    int parse_result = yyparse();
    
    if (parse_result != 0) {
        std::cerr << "Parse failed with errors\n";
        fclose(yyin);
        return 1;
    }
    
    if (opts.verbose) {
        std::cout << "Parse successful!\n";
    }
    
    // Print AST if requested
    if (opts.print_ast && root) {
        std::cout << "\n=== Abstract Syntax Tree ===\n";
        print_ast(root);
    }
    
    // Semantic analysis (TODO)
    if (opts.verbose) {
        std::cout << "\n--- Semantic Analysis ---\n";
        std::cout << "TODO: Type checking and validation\n";
    }
    
    // Code generation
    if (!opts.print_ast && root) {
        std::cout << "\n--- Code Generation ---\n";
        
        lazya::LLVMCodeGen codegen;
        
        if (!codegen.generate(root)) {
            std::cerr << "Code generation failed\n";
            fclose(yyin);
            return 1;
        }
        
        // Generate object file
        std::string obj_file = opts.output_file + ".o";
        if (opts.verbose) {
            std::cout << "\nGenerating object file: " << obj_file << "\n";
        }
        
        if (codegen.write_object_file(obj_file)) {
            std::cout << "\n[SUCCESS] Object file generated: " << obj_file << "\n";
            
            // Link to create executable
            if (codegen.link_executable(obj_file, opts.output_file)) {
                std::cout << "[SUCCESS] Executable created: " << opts.output_file << "\n";
                std::cout << "\nYou can now run: ./" << opts.output_file << "\n";
            } else {
                std::cerr << "[WARNING] Linking failed - object file is available at: " << obj_file << "\n";
            }
        } else {
            std::cerr << "Failed to generate object file\n";
        }
    }
    
    fclose(yyin);
    
    std::cout << "\n[INFO] Compilation completed successfully\n";
    
    return 0;
}
