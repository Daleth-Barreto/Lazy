/*
 * LazyA Runtime Registry
 * Central registry for all runtime functions
 */

#ifndef LAZY_RUNTIME_REGISTRY_H
#define LAZY_RUNTIME_REGISTRY_H

#include "IRuntimeFunction.h"
#include <map>
#include <memory>
#include <vector>

namespace llvm {
    class Module;
    class LLVMContext;
}

namespace lazya {

/**
 * Singleton registry for runtime functions
 * Uses Registry pattern for extensibility
 */
class RuntimeRegistry {
public:
    static RuntimeRegistry& getInstance();
    
    // Register a runtime function
    void registerFunction(std::unique_ptr<IRuntimeFunction> func);
    
    // Get a function by name
    IRuntimeFunction* getFunction(const std::string& name);
    
    // Initialize all runtime functions in a module
    void initializeModule(llvm::Module* module, llvm::LLVMContext& context);
    
    // Get all registered functions
    std::vector<std::string> getFunctionNames() const;
    
private:
    RuntimeRegistry() = default;
    RuntimeRegistry(const RuntimeRegistry&) = delete;
    RuntimeRegistry& operator=(const RuntimeRegistry&) = delete;
    
    std::map<std::string, std::unique_ptr<IRuntimeFunction>> functions;
};

} // namespace lazya

#endif // LAZY_RUNTIME_REGISTRY_H
