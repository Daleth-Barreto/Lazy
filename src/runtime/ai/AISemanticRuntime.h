/*
 * LazyA AI Semantic Runtime Wrappers
 * Exposes AI semantic operations to LLVM
 */

#ifndef LAZYA_AI_SEMANTIC_RUNTIME_H
#define LAZYA_AI_SEMANTIC_RUNTIME_H

#include "../IRuntimeFunction.h"

namespace lazya {

/**
 * AI Semantic Similarity
 * Signature: float ai_semantic_similarity(char* str1, char* str2)
 */
class AISemanticSimilarityFunction : public IRuntimeFunction {
public:
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
    std::string getName() const override { return "ai_semantic_similarity"; }
    std::string getSignature() const override { return "float ai_semantic_similarity(char*, char*)"; }
};

/**
 * AI Semantic Equality
 * Signature: int ai_semantic_equals(char* str1, char* str2, float threshold)
 */
class AISemanticEqualsFunction : public IRuntimeFunction {
public:
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
    std::string getName() const override { return "ai_semantic_equals"; }
    std::string getSignature() const override { return "int ai_semantic_equals(char*, char*, float)"; }
};

} // namespace lazya

#endif // LAZYA_AI_SEMANTIC_RUNTIME_H
