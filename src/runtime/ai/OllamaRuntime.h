/*
 * LazyA Ollama AI Runtime Functions
 * Wrapper for Ollama client integration
 */

#ifndef LAZY_OLLAMA_RUNTIME_H
#define LAZY_OLLAMA_RUNTIME_H

#include "../IRuntimeFunction.h"

namespace lazya {

/**
 * Ollama chat function
 * Signature: char* ai_ollama_chat(char* message, char* model)
 */
class OllamaChatFunction : public IRuntimeFunction {
public:
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
    std::string getName() const override { return "ai.ollama.chat"; }
    std::string getSignature() const override { return "char* ai_ollama_chat(char*, char*)"; }
};

/**
 * Ollama generate function
 * Signature: char* ai_ollama_generate(char* prompt, char* model)
 */
class OllamaGenerateFunction : public IRuntimeFunction {
public:
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
    std::string getName() const override { return "ai.ollama.generate"; }
    std::string getSignature() const override { return "char* ai_ollama_generate(char*, char*)"; }
};

/**
 * Ollama list models function
 * Signature: char* ai_ollama_list_models()
 */
class OllamaListModelsFunction : public IRuntimeFunction {
public:
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
    std::string getName() const override { return "ai.ollama.list_models"; }
    std::string getSignature() const override { return "char* ai_ollama_list_models()"; }
};

} // namespace lazya

#endif // LAZY_OLLAMA_RUNTIME_H
