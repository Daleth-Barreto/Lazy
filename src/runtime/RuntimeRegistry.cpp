/*
 * LazyA Runtime Registry - Implementation
 */

#include "RuntimeRegistry.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "runtime/FileIO.h"
#include <iostream>

namespace lazya {

RuntimeRegistry& RuntimeRegistry::getInstance() {
    static RuntimeRegistry instance;
    return instance;
}

void RuntimeRegistry::registerFunction(std::unique_ptr<IRuntimeFunction> func) {
    std::string name = func->getName();
    functions[name] = std::move(func);
    // std::cout << "[Runtime] Registered function: " << name << std::endl;
}

IRuntimeFunction* RuntimeRegistry::getFunction(const std::string& name) {
    auto it = functions.find(name);
    if (it != functions.end()) {
        return it->second.get();
    }
    return nullptr;
}

void RuntimeRegistry::initializeModule(llvm::Module* module, llvm::LLVMContext& context) {
    // std::cout << "[Runtime] Initializing " << functions.size() << " runtime functions..." << std::endl;
    
    for (auto& pair : functions) {
        // std::cout << "DEBUG: Init " << pair.first << std::endl;
        if (!module) std::cerr << "CRITICAL: Module is null!" << std::endl;
        pair.second->getOrCreate(module, context);
        // std::cout << "DEBUG: DONE " << pair.first << std::endl;
    }
    // std::cout << "DEBUG: All runtime functions initialized." << std::endl;
}

std::vector<std::string> RuntimeRegistry::getFunctionNames() const {
    std::vector<std::string> names;
    for (const auto& pair : functions) {
        names.push_back(pair.first);
    }
    return names;
}

} // namespace lazya
