/*
 * LazyA Ollama AI Runtime Functions - Implementation
 */

#include "OllamaRuntime.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"

namespace lazya {

// Forward declarations for the C functions from OllamaClient.cpp
extern "C" {
    char* ai_ollama_chat(const char* message, const char* model);
    char* ai_ollama_generate(const char* prompt, const char* model);
    char* ai_ollama_list_models();
}

llvm::Function* OllamaChatFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    // Check if function already exists
    llvm::Function* func = module->getFunction("ai_ollama_chat");
    if (func) {
        return func;
    }
    
    // Create function type: char* (char*, char*)
    llvm::Type* charPtrTy = llvm::PointerType::getUnqual(context);
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,  // return type
        {charPtrTy, charPtrTy},  // parameters
        false  // not vararg
    );
    
    // Create function declaration
    func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "ai_ollama_chat",
        module
    );
    
    return func;
}

llvm::Function* OllamaGenerateFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    // Check if function already exists
    llvm::Function* func = module->getFunction("ai_ollama_generate");
    if (func) {
        return func;
    }
    
    // Create function type: char* (char*, char*)
    llvm::Type* charPtrTy = llvm::PointerType::getUnqual(context);
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,  // return type
        {charPtrTy, charPtrTy},  // parameters
        false  // not vararg
    );
    
    // Create function declaration
    func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "ai_ollama_generate",
        module
    );
    
    return func;
}

llvm::Function* OllamaListModelsFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    // Check if function already exists
    llvm::Function* func = module->getFunction("ai_ollama_list_models");
    if (func) {
        return func;
    }
    
    // Create function type: char* ()
    llvm::Type* charPtrTy = llvm::PointerType::getUnqual(context);
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,  // return type
        {},  // no parameters
        false  // not vararg
    );
    
    // Create function declaration
    func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "ai_ollama_list_models",
        module
    );
    
    return func;
}

} // namespace lazya
