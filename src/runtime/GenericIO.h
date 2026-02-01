/*
 * LazyA Runtime - Generic I/O Functions
 */

#ifndef LAZYA_GENERIC_IO_H
#define LAZYA_GENERIC_IO_H

#include "IRuntimeFunction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"

namespace lazya {

// Print functions (no newline)
class PrintIntFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "print_int"; }
    std::string getSignature() const override { return "void print_int(int)"; }
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("print_int");
        if (func) return func;
        std::vector<llvm::Type*> params = {llvm::Type::getInt32Ty(context)};
        llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), params, false);
        return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "print_int", module);
    }
};

class PrintStrFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "print_str"; }
    std::string getSignature() const override { return "void print_str(string)"; }
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("print_str");
        if (func) return func;
        std::vector<llvm::Type*> params = {llvm::PointerType::getUnqual(context)};
        llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), params, false);
        return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "print_str", module);
    }
};

// Println functions (with newline)
class PrintlnIntFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "println_int"; }
    std::string getSignature() const override { return "void println_int(int)"; }
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("println_int");
        if (func) return func;
        std::vector<llvm::Type*> params = {llvm::Type::getInt32Ty(context)};
        llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), params, false);
        return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "println_int", module);
    }
};

class PrintlnStrFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "println_str"; }
    std::string getSignature() const override { return "void println_str(string)"; }
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("println_str");
        if (func) return func;
        std::vector<llvm::Type*> params = {llvm::PointerType::getUnqual(context)};
        llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), params, false);
        return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "println_str", module);
    }
};

class PrintlnVoidFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "println_void"; }
    std::string getSignature() const override { return "void println_void()"; }
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("println_void");
        if (func) return func;
        llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
        return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "println_void", module);
    }
};

// Read functions
class ReadIntFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "read_int"; }
    std::string getSignature() const override { return "int read_int()"; }
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("read_int");
        if (func) return func;
        llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), false);
        return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "read_int", module);
    }
};

} // namespace lazya

#endif // LAZYA_GENERIC_IO_H
