/*
 * LazyA Runtime - Ollama Client
 * Interface with local Ollama server
 */

#ifndef LAZYA_OLLAMA_CLIENT_H
#define LAZYA_OLLAMA_CLIENT_H

#include <string>
#include "../http/HTTPClient.h"

namespace lazya {
namespace ai {

class OllamaClient {
public:
    OllamaClient(const std::string& baseUrl = "http://localhost:11434");
    
    // Chat completion
    std::string chat(const std::string& message, 
                    const std::string& model = "qwen2:0.5b");
    
    // Text generation
    std::string generate(const std::string& prompt,
                        const std::string& model = "qwen2:0.5b");
    
    // List available models
    std::string listModels();
    
private:
    std::string baseUrl_;
    http::HTTPClient http_;
    
    std::string parseResponse(const std::string& json);
    std::string unescapeJSON(const std::string& input);
};

} // namespace ai
} // namespace lazya

// C interface for LazyA runtime
extern "C" {
    char* ai_ollama_chat(const char* message, const char* model);
    char* ai_ollama_generate(const char* prompt, const char* model);
    char* ai_ollama_list_models();
}

#endif // LAZYA_OLLAMA_CLIENT_H
