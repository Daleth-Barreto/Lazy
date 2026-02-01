/*
 * LazyA Runtime - AI-Powered Semantic Operations
 * Uses Ollama for true semantic understanding
 */

#ifndef LAZY_AI_SEMANTIC_H

#define LAZY_AI_SEMANTIC_H

#ifndef LAZY_RUNTIME_BUILD
#include "../IRuntimeFunction.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"

namespace lazya {

class SemanticEqualsFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "ai_semantic_equals"; }
    std::string getSignature() const override { return "int ai_semantic_equals(char*, char*, float)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
};

} // namespace lazya
#endif

#ifdef __cplusplus
extern "C" {
#endif

// AI-powered semantic similarity (returns float 0.0-1.0)
float ai_semantic_similarity(const char* str1, const char* str2);

// AI-powered semantic equality with threshold
int ai_semantic_equals(const char* str1, const char* str2, float threshold);

#ifdef __cplusplus
}
#endif

#endif // LAZY_AI_SEMANTIC_H
