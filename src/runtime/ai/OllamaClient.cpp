/*
 * LazyA Runtime - Ollama Client Implementation
 */

#include "OllamaClient.h"
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>

namespace lazya {
namespace ai {

// Helper to escape JSON string
std::string escapeJSON(const std::string& input) {
    std::ostringstream oss;
    for (char c : input) {
        switch (c) {
            case '"': oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b"; break;
            case '\f': oss << "\\f"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default:
                if (c >= 0x00 && c <= 0x1f) { // Control characters
                    oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << (int)c;
                } else {
                    oss << c;
                }
                break;
        }
    }
    return oss.str();
}

OllamaClient::OllamaClient(const std::string& baseUrl) 
    : baseUrl_(baseUrl) {
    http_.setTimeout(60); // Ollama puede tardar
}

std::string OllamaClient::chat(const std::string& message, const std::string& model) {
    // Build JSON request
    std::ostringstream json;
    json << "{";
    json << "\"model\":\"" << model << "\",";
    json << "\"messages\":[{\"role\":\"user\",\"content\":\"" << escapeJSON(message) << "\"}],";
    json << "\"stream\":false,";
    json << "\"options\": {\"temperature\": 0.1}"; // Added temperature parameter
    json << "}";
    
    // Make request
    std::string url = baseUrl_ + "/api/chat";
    std::string response = http_.post(url, json.str());
    
    return parseResponse(response);
}

std::string OllamaClient::generate(const std::string& prompt, const std::string& model) {
    // Build JSON request  
    std::ostringstream json;
    json << "{";
    json << "\"model\":\"" << model << "\",";
    json << "\"prompt\":\"" << escapeJSON(prompt) << "\",";
    json << "\"stream\":false,";
    json << "\"options\": {\"temperature\": 0.1}"; // Added temperature parameter
    json << "}";
    
    // Make request
    std::string url = baseUrl_ + "/api/generate";
    std::string response = http_.post(url, json.str());
    
    return parseResponse(response);
}

std::string OllamaClient::listModels() {
    std::string url = baseUrl_ + "/api/tags";
    return http_.get(url);
}

std::string OllamaClient::parseResponse(const std::string& json) {
    // Simple JSON parsing - extract response field
    // Look for "response":"..."
    size_t start = json.find("\"response\":\"");
    if (start == std::string::npos) {
        // Try message.content for chat
        start = json.find("\"content\":\"");
        if (start == std::string::npos) {
            return ""; // Return empty if can't parse
        }
        start += 11; // Length of "content":"
    } else {
        start += 12; // Length of "response":"
    }
    
    // Find end quote
    size_t end = start;
    bool found = false;
    while (end < json.length()) {
        // Skip escaped quotes
        if (json[end] == '"' && (end == 0 || json[end-1] != '\\')) {
            found = true;
            break;
        }
        end++;
    }
    
    if (end > start) {
        return unescapeJSON(json.substr(start, end - start));
    }
    
    return json;
}

// Helper to unescape JSON string
std::string OllamaClient::unescapeJSON(const std::string& input) {
    std::string result;
    bool escape = false;
    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];
        if (escape) {
            if (c == 'n') result += '\n';
            else if (c == 't') result += '\t';
            else if (c == 'r') result += '\r';
            else if (c == '"') result += '"';
            else if (c == '\\') result += '\\';
            else if (c == 'u') {
                 if (i + 4 < input.length()) {
                     // Parse unicode hex
                     try {
                        std::string hex = input.substr(i + 1, 4);
                        int code = std::stoi(hex, nullptr, 16);
                        if (code < 128) result += (char)code;
                        // TODO: Handle multibyte UTF-8 for basic ascii compatibility
                        i += 4;
                     } catch (...) { i += 4; }
                 }
            }
            else result += c;
            escape = false;
        } else {
            if (c == '\\') escape = true;
            else result += c;
        }
    }
    return result;
}

} // namespace ai
} // namespace lazya

// C interface
extern "C" {

char* ai_ollama_chat(const char* message, const char* model) {
    static lazya::ai::OllamaClient client;
    
    std::string model_str = model ? model : "qwen2:0.5b";
    std::string result = client.chat(message, model_str);
    if (result.empty()) return nullptr;
    
    return strdup(result.c_str());
}

char* ai_ollama_generate(const char* prompt, const char* model) {
    static lazya::ai::OllamaClient client;
    
    std::string model_str = model ? model : "qwen2:0.5b";
    std::string result = client.generate(prompt, model_str);
    
    return strdup(result.c_str());
}

char* ai_ollama_list_models() {
    static lazya::ai::OllamaClient client;
    std::string result = client.listModels();
    return strdup(result.c_str());
}

}
