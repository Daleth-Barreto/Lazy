/*
 * LazyA LLVM Code Generator - Header
 */

#ifndef LAZYA_LLVM_CODEGEN_H
#define LAZYA_LLVM_CODEGEN_H

#include "../ast/ast.h"
#include <string>

namespace lazya {

// Forward declaration
class LLVMCodeGenImpl;

class LLVMCodeGen {
public:
    LLVMCodeGen();
    ~LLVMCodeGen();
    
    // Generate LLVM IR from AST
    bool generate(ASTNode* root);
    
    // Write output object file
    bool write_object_file(const std::string& filename);
    
    // Link object file to create executable
    bool link_executable(const std::string& obj_file, const std::string& exe_file);
    
private:
    LLVMCodeGenImpl* impl;
};

} // namespace lazya

#endif // LAZYA_LLVM_CODEGEN_H
