/*
 * LazyA AI Semantic Runtime Wrappers - Implementation
 */

#include "AISemanticRuntime.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"

namespace lazya {

// Forward declarations for C functions
extern "C" {
    float ai_semantic_similarity(const char* str1, const char* str2);
    int ai_semantic_equals(const char* str1, const char* str2, float threshold);
}

llvm::Function* AISemanticSimilarityFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    if (auto* f = module->getFunction(getName())) return f;
    
    llvm::Type* charPtrTy = llvm::PointerType::getUnqual(context);
    llvm::Type* floatTy = llvm::Type::getFloatTy(context);
    
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        floatTy,
        {charPtrTy, charPtrTy},
        false
    );
    
    return llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        getName(),
        module
    );
}

llvm::Function* AISemanticEqualsFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    if (auto* f = module->getFunction(getName())) return f;
    
    llvm::Type* charPtrTy = llvm::PointerType::getUnqual(context);
    llvm::Type* floatTy = llvm::Type::getFloatTy(context);
    llvm::Type* int32Ty = llvm::Type::getInt32Ty(context);
    
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        int32Ty,
        {charPtrTy, charPtrTy, floatTy},
        false
    );
    
    return llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        getName(),
        module
    );
}

} // namespace lazya
