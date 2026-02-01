/*
 * LazyA Print Function
 * Runtime function for output
 */

#ifndef LAZY_PRINT_FUNCTION_H
#define LAZY_PRINT_FUNCTION_H

#include "IRuntimeFunction.h"

namespace lazya {

/**
 * Print integer to stdout
 * Signature: void print_int(int value)
 */
class PrintIntFunction : public IRuntimeFunction {
public:
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
    std::string getName() const override { return "print_int"; }
    std::string getSignature() const override { return "void print_int(int)"; }
};

/**
 * Print string to stdout
 * Signature: void print_string(char* str)
 */
class PrintStringFunction : public IRuntimeFunction {
public:
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
    std::string getName() const override { return "print_string"; }
    std::string getSignature() const override { return "void print_string(char*)"; }
};

/**
 * Print newline
 * Signature: void println()
 */
class PrintlnFunction : public IRuntimeFunction {
public:
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
    std::string getName() const override { return "println"; }
    std::string getSignature() const override { return "void println()"; }
};

} // namespace lazya

#endif // LAZY_PRINT_FUNCTION_H
