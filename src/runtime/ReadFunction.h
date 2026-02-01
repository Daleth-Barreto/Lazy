/*
 * LazyA Runtime - Read Function
 */

#ifndef LAZY_READ_FUNCTION_H
#define LAZY_READ_FUNCTION_H

#include "IRuntimeFunction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"

namespace lazya {

class ReadFunction : public IRuntimeFunction {
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

#endif // LAZY_READ_FUNCTION_H
