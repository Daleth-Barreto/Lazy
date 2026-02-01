/*
 * LazyA Runtime - Semantic Similarity Functions (Demo)
 * Simple text similarity without ML models for quick demo
 */

#ifndef LAZY_SEMANTIC_OPS_H
#define LAZY_SEMANTIC_OPS_H

#include "IRuntimeFunction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"

namespace lazya {

// === SEMANTIC EQUALITY ===
// bool semantic_equals(char* str1, char* str2, float threshold)
class SemanticEqualsFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "semantic_equals"; }
    std::string getSignature() const override { return "int semantic_equals(char*, char*, float)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = {
            ptr,  // str1
            ptr,  // str2
            llvm::Type::getFloatTy(context)  // threshold
        };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context),  // returns bool as int
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === SEMANTIC SIMILARITY ===
// float semantic_similarity(char* str1, char* str2)
class SemanticSimilarityFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "semantic_similarity"; }
    std::string getSignature() const override { return "float semantic_similarity(char*, char*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = {
            ptr,  // str1
            ptr   // str2
        };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getFloatTy(context),  // returns similarity score
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

} // namespace lazya

#endif // LAZY_SEMANTIC_OPS_H
