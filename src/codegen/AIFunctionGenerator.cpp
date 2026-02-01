/*
 * AIFunctionGenerator.cpp
 * Implementation of compile-time AI function generation
 */

#include "AIFunctionGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <array>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>

namespace lazya {

namespace fs = std::filesystem;

// Forward declaration
std::string exec(const char* cmd);

AIFunctionGenerator& AIFunctionGenerator::getInstance() {
    static AIFunctionGenerator instance;
    return instance;
}

AIFunctionGenerator::AIFunctionGenerator() {
    // Ensure cache directory exists
    std::string cacheDir = getCacheDirectory();
    fs::create_directories(cacheDir);
}

std::string AIFunctionGenerator::getCacheDirectory() {
    const char* home = getenv("HOME");
    if (!home) {
        struct passwd* pwd = getpwuid(getuid());
        if (pwd) home = pwd->pw_dir;
    }
    
    if (!home) return "./.lazya_cache"; // Fallback
    
    return std::string(home) + "/.lazya/cache";
}

std::string AIFunctionGenerator::computeHash(const std::string& input) {
    // Simple DJB2 hash for filename generation
    unsigned long hash = 5381;
    for (char c : input) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

std::string AIFunctionGenerator::generate(const std::string& signature, const std::string& docstring) {
    std::string cacheDir = getCacheDirectory();
    std::string contentHash = computeHash(signature + docstring);
    std::string baseName = "ai_func_" + contentHash;
    std::string sourcePath = cacheDir + "/" + baseName + ".c";
    std::string objPath = cacheDir + "/" + baseName + ".o";

    // 1. Check if object file already exists
    if (fs::exists(objPath)) {
        // std::cout << "[AI-Gen] Using cached version for " << signature << "\n";
        return objPath;
    }

    std::cout << "[AI-Gen] Generating implementation for: " << signature << "...\n";
    // 2. Extract function name from signature for verification
    std::string funcName = signature.substr(0, signature.find('('));
    size_t space = funcName.rfind(' ');
    if (space != std::string::npos) funcName = funcName.substr(space + 1);

    // 3. Construct Prompt
    std::stringstream prompt;
    prompt << "You are an expert C programmer. Implement the following function in standard C (C99 compat).\n";
    prompt << "Function Signature: " << signature << "\n";
    prompt << "Description: " << docstring << "\n";
    prompt << "Rules:\n";
    prompt << "1. Output ONLY the C code. No explanations.\n";
    prompt << "2. Include necessary headers (stdio.h, stdlib.h, string.h, math.h, assert.h).\n";
    prompt << "3. Do not use C++ features, strictly C.\n";
    prompt << "4. Implement strictly what is asked. Do not try to optimize or be clever if it risks correctness.\n";
    prompt << "5. Verify your logic step-by-step before writing the code.\n";
    prompt << "6. Ensure the function name matches EXACTLY.\n";
    prompt << "7. DO NOT include a main() function. This code will be linked with an existing main.\n";
    prompt << "8. The function MUST RETURN the computed value. Do NOT use printf to output the result. Use 'return result;'.\n";
    prompt << "9. Wrap code in ```c ... ``` blocks.\n";
    prompt << "10. Hint: For 2^n, use '1 << n' if n >= 0.\n";
    // Note: User-defined @verify conditions will be used for testing, no need to ask AI for tests
    
    // Pre-extract @verify conditions from docstring before retry loop
    std::vector<std::string> verifyConditions;
    std::istringstream docStream(docstring);
    std::string line;
    std::string cleanDocstring;
    while (std::getline(docStream, line)) {
        size_t verifyPos = line.find("@verify:");
        if (verifyPos != std::string::npos) {
            std::string condition = line.substr(verifyPos + 8);
            // Trim whitespace
            size_t start = condition.find_first_not_of(" \t");
            size_t end = condition.find_last_not_of(" \t");
            if (start != std::string::npos && end != std::string::npos) {
                verifyConditions.push_back(condition.substr(start, end - start + 1));
            }
        } else {
            cleanDocstring += line + "\n";
        }
    }

    // ========== RETRY LOOP ==========
    const int maxAttempts = 3;
    std::string lastError = "";
    std::string code;
    
    for (int attempt = 1; attempt <= maxAttempts; attempt++) {
        if (attempt > 1) {
            std::cout << "[AI-Gen] Retry attempt " << attempt << "/" << maxAttempts << "...\n";
        }
        
        // Build full prompt with error feedback if retrying
        std::stringstream fullPrompt;
        fullPrompt << prompt.str();
        if (!lastError.empty()) {
            fullPrompt << "\n\n--- PREVIOUS ATTEMPT FAILED ---\n";
            fullPrompt << "Your previous code had the following error:\n";
            fullPrompt << lastError << "\n";
            fullPrompt << "Please fix this error and try again.\n";
        }
        
        // 3. Query LLM
        std::string response = queryOllama(fullPrompt.str());
        if (response.empty()) {
            lastError = "Failed to get response from Ollama.";
            continue;
        }

        // 4. Extract Code
        code = extractCode(response);
        if (code.empty()) {
            lastError = "No code block found in response.";
            continue;
        }
        
        // Post-process: Remove main function if present
        code = removeMainFunction(code);
        
        // Post-process: Fix assert() calls with message arguments
        code = fixAssertCalls(code);
        
        // Add extern "C" guard
        std::stringstream finalCode;
        finalCode << "// Generated by LazyA Compiler via " << getModelNameForEnum(currentModel_) << " (attempt " << attempt << ")\n";
        finalCode << "#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n";
        finalCode << "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <math.h>\n#include <assert.h>\n\n";
        finalCode << code << "\n";
        finalCode << "#ifdef __cplusplus\n}\n#endif\n";

        // 5. Verification Step (only if user provided @verify conditions)
        bool verificationPassed = true;
        if (!verifyConditions.empty()) {
            std::cout << "[AI-Gen] Verifying generated code with " << verifyConditions.size() << " user-defined tests...\n";
            
            // Create verification source
            std::stringstream verifySrc;
            verifySrc << finalCode.str() << "\n";
            verifySrc << "int main() {\n";
            for (const auto& cond : verifyConditions) {
                verifySrc << "    assert(" << cond << ");\n";
            }
            verifySrc << "    return 0;\n}\n";
            
            std::string verifyPath = cacheDir + "/verify_" + baseName + "_" + std::to_string(attempt) + ".c";
            std::string verifyExe = cacheDir + "/verify_" + baseName + "_" + std::to_string(attempt);
            
            std::ofstream vout(verifyPath);
            vout << verifySrc.str();
            vout.close();
            
            // Compile verification executable
            std::string vcmd = "clang " + verifyPath + " -o " + verifyExe + " 2>&1";
            std::string compileOutput = exec(vcmd.c_str());
            if (compileOutput.find("error:") != std::string::npos) {
                lastError = "Compilation error:\n" + compileOutput;
                verificationPassed = false;
                continue;
            }
            
            // Run verification and capture output
            std::string runCmd = verifyExe + " 2>&1";
            std::string runOutput = exec(runCmd.c_str());
            int runRet = WEXITSTATUS(system(("(" + std::string(verifyExe) + ") > /dev/null 2>&1").c_str()));
            if (runRet != 0) {
                // Capture which assertion failed
                lastError = "Verification failed. Assertions:\n";
                for (const auto& cond : verifyConditions) {
                    lastError += " - assert(" + cond + ")\n";
                }
                lastError += "The function returned incorrect values.";
                verificationPassed = false;
                continue;
            }
            std::cout << "[AI-Gen] All user-defined tests passed.\n";
        } else {
            std::cout << "[AI-Gen] No @verify conditions provided. Skipping verification.\n";
        }
        
        if (!verificationPassed) continue;

        // 6. Write Source File (without main)
        std::ofstream out(sourcePath);
        out << finalCode.str();
        out.close();

        // 7. Compile to Object File
        std::string cmd = "clang -c " + sourcePath + " -o " + objPath + " 2>&1";
        int ret = system(cmd.c_str());
        
        if (ret != 0) {
            lastError = "Final compilation failed.";
            continue;
        }

        std::cout << "[AI-Gen] Implementation generated and compiled successfully.\n";
        return objPath;
    }
    
    // All retries exhausted
    std::cerr << "[AI-Gen] Error: Failed after " << maxAttempts << " attempts.\n";
    std::cerr << "Last error: " << lastError << "\n";
    return "";
}

// Helper to execute shell command and get output
// Used for curling Ollama since we don't want to link full HTTP lib into the compiler executable yet for this simple task
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string AIFunctionGenerator::queryOllama(const std::string& prompt) {
    // Escape prompt for JSON
    std::string escapedPrompt;
    for (char c : prompt) {
        if (c == '"') escapedPrompt += "\\\"";
        else if (c == '\n') escapedPrompt += "\\n";
        else if (c == '\\') escapedPrompt += "\\\\";
        else escapedPrompt += c;
    }

    // Build JSON payload
    std::string payload = "{\"model\": \"" + getModelNameForEnum(currentModel_) + "\", \"prompt\": \"" + escapedPrompt + "\", \"stream\": false, \"options\": {\"temperature\": 0.1}}";
    
    // Save payload to tmp file to avoid shell escaping hell
    std::string tmpFile = "/tmp/lazya_gen_payload_" + std::to_string(rand()) + ".json";
    std::ofstream out(tmpFile);
    out << payload;
    out.close();

    // Curl command
    std::string cmd = "curl -s -X POST http://localhost:11434/api/generate -d @" + tmpFile;
    
    std::string response = exec(cmd.c_str());
    
    // Clean up
    unlink(tmpFile.c_str());
    
    // Manual JSON parsing to get "response" field (simple assumption)
    // Looking for "response":"..."
    std::string key = "\"response\":\"";
    size_t start = response.find(key);
    if (start == std::string::npos) return "";
    
    start += key.length();
    
    std::string result;
    bool escape = false;
    for (size_t i = start; i < response.length(); i++) {
        char c = response[i];
        if (escape) {
            if (c == 'n') result += '\n';
            else if (c == 't') result += '\t';
            else if (c == 'r') result += '\r';
            else if (c == '"') result += '"';
            else if (c == '\\') result += '\\';
            else if (c == 'u') {
                // Handle unicode escape \uXXXX
                // We only care about basic chars for now, skip the u
                // Actually need to read next 4 chars
                if (i + 4 < response.length()) {
                     std::string hex = response.substr(i + 1, 4);
                     int code = std::stoi(hex, nullptr, 16);
                     result += (char)code;
                     i += 4;
                }
            }
            else result += c;
            escape = false;
        } else {
            if (c == '\\') {
                escape = true;
            } else if (c == '"') {
                break; // End of string
            } else {
                result += c;
            }
        }
    }
    
    return result;
}

std::string AIFunctionGenerator::extractCode(const std::string& response) {
    // Look for ```c or ```
    size_t start = response.find("```c");
    if (start == std::string::npos) {
        start = response.find("```");
    } else {
        start += 4; // Skip ```c
    }
    
    if (start == std::string::npos) {
        // Did not find markdown block, maybe the whole response is code?
        // But usually LLMs chat a bit. Let's assume strictness for now.
        // Actually, fallback to returning whole string if it looks like code?
        // Let's rely on rule 5.
        return response; // Fallback: Assume raw code
    } else {
        if (response.substr(start, 3) == "```") start += 3;
    }
    
    size_t end = response.find("```", start);
    if (end == std::string::npos) end = response.length();
    
    // Trim whitespace
    while (start < end && isspace(response[start])) start++;
    while (end > start && isspace(response[end-1])) end--;
    
    return response.substr(start, end - start);
}

std::string AIFunctionGenerator::removeMainFunction(std::string code) {
    // Simple heuristic: Comment out "int main" or "void main"
    // Limitations: Can be fooled by comments/strings. Sufficient for MVP.
    
    size_t pos = code.find("int main");
    if (pos == std::string::npos) pos = code.find("void main");
    
    if (pos != std::string::npos) {
        // Found main. Try to comment it out or truncate?
        // Let's replace "main" with "__ignored_main"
        code.replace(pos + (code.find("main", pos) - pos), 4, "__ignored_main");
        std::cout << "[AI-Gen] Warning: Stripped 'main' function from generated code.\n";
    }
    return code;
}

std::string AIFunctionGenerator::fixAssertCalls(std::string code) {
    // Fix Python-style assert(expr, "msg") to C-style assert(expr)
    // Pattern: assert(SOMETHING, "MESSAGE")
    // Simple heuristic: Find ", " followed by a quoted string inside assert()
    
    std::string result;
    size_t i = 0;
    while (i < code.length()) {
        // Look for "assert("
        size_t assertPos = code.find("assert(", i);
        if (assertPos == std::string::npos) {
            result += code.substr(i);
            break;
        }
        
        // Copy up to and including "assert("
        result += code.substr(i, assertPos - i + 7);
        i = assertPos + 7;
        
        // Now we need to find the matching closing paren
        int parenDepth = 1;
        size_t exprStart = i;
        size_t commaPos = std::string::npos;
        
        while (i < code.length() && parenDepth > 0) {
            if (code[i] == '(') parenDepth++;
            else if (code[i] == ')') parenDepth--;
            else if (code[i] == ',' && parenDepth == 1 && commaPos == std::string::npos) {
                commaPos = i;
            }
            if (parenDepth > 0) i++;
        }
        
        // i now points to the closing paren
        if (commaPos != std::string::npos) {
            // There was a comma - take only the expression before comma
            result += code.substr(exprStart, commaPos - exprStart);
            result += ')';
            i++; // Skip original closing paren
        } else {
            // No comma - use original expression
            result += code.substr(exprStart, i - exprStart + 1);
            i++;
        }
    }
    return result;
}

void AIFunctionGenerator::setModel(AIModel model) {
    currentModel_ = model;
    std::cout << "[AI-Gen] Model set to: " << getModelNameForEnum(model) << "\n";
}

std::string AIFunctionGenerator::getModelName() const {
    return getModelNameForEnum(currentModel_);
}

} // namespace lazya
