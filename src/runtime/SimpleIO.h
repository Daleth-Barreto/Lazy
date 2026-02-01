/*
 * LazyA Runtime - Simple I/O Functions
 */

#ifndef LAZYA_SIMPLE_IO_H
#define LAZYA_SIMPLE_IO_H

#include "IRuntimeFunction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"

namespace lazya {

class SimplePrintFunction : public IRuntimeFunction {
public:
    std::string getName() const override {
        return "print";
    }
    
    std::string getSignature() const override {
        return "void print(int)";
    }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("print");
        if (func) return func;
        
        std::vector<llvm::Type*> paramTypes = {
            llvm::Type::getInt32Ty(context)
        };
        
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            paramTypes,
            false
        );
        
        func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            "print",
            module
        );
        
        return func;
    }
};

class PrintStrFunction : public IRuntimeFunction {
public:
    std::string getName() const override {
        return "print_str";
    }
    
    std::string getSignature() const override {
        return "void print_str(string)";
    }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("print_str");
        if (func) return func;
        
        std::vector<llvm::Type*> paramTypes = {
            llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0)
        };
        
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            paramTypes,
            false
        );
        
        func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            "print_str",
            module
        );
        
        return func;
    }
};

class SimpleReadFunction : public IRuntimeFunction {
public:
    std::string getName() const override {
        return "read";
    }
    
    std::string getSignature() const override {
        return "int read()";
    }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        llvm::Function* func = module->getFunction("read");
        if (func) return func;
        
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context),
            false
        );
        
        func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            "read",
            module
        );
        
        return func;
    }
};

} // namespace lazya

#endif // LAZYA_SIMPLE_IO_H
