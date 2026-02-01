/*
 * AIFunctionGenerator.h
 * 
 * Generates implementation for AI-defined functions (@context)
 * at compile time using a local LLM (Ollama).
 */

#ifndef LAZYA_AI_FUNCTION_GENERATOR_H
#define LAZYA_AI_FUNCTION_GENERATOR_H

#include <string>
#include <vector>

namespace lazya {

// Available AI models for code generation
enum class AIModel {
    CODELLAMA_7B,   // Best for code generation (default)
    QWEN2_05B       // Fast mode for simple operations
};

class AIFunctionGenerator {
public:
    static AIFunctionGenerator& getInstance();

    // Generates an object file for the given function signature and docstring
    // Returns the absolute path to the .o file
    std::string generate(const std::string& signature, const std::string& docstring);
    
    // Set the AI model to use
    void setModel(AIModel model);
    
    // Get current model name
    std::string getModelName() const;

private:
    AIFunctionGenerator();
    
    // Helper to get cache directory (~/.lazya/cache)
    std::string getCacheDirectory();
    
    // Helper to compute hash of string
    std::string computeHash(const std::string& input);
    
    // Helper to query Ollama
    std::string queryOllama(const std::string& prompt);
    
    // Helper to extract code from markdown block
    std::string extractCode(const std::string& response);
    
    // Helper to strip main function from generated code
    std::string removeMainFunction(std::string code);
    
    // Helper to fix Python-style assert(expr, "msg") to C-style assert(expr)
    std::string fixAssertCalls(std::string code);
    
    // Model configuration
    AIModel currentModel_ = AIModel::CODELLAMA_7B;
    
    std::string getModelNameForEnum(AIModel model) const {
        switch (model) {
            case AIModel::CODELLAMA_7B: return "codellama:7b";
            case AIModel::QWEN2_05B: return "qwen2:0.5b";
            default: return "codellama:7b";
        }
    }
};

} // namespace lazya

#endif // LAZYA_AI_FUNCTION_GENERATOR_H
