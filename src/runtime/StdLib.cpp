/*
 * LazyA Standard Library Registration
 */

#include "StdLib.h"
#include "FileIO.h"
#include "GenericIO.h"
#include "StringOps.h"
#include "RuntimeRegistry.h"
#include "ai/AISemanticOps.h"
#include "ai/OllamaRuntime.h"

namespace lazya {

// Helper to register all standard functions
void register_standard_library() {
    auto& registry = RuntimeRegistry::getInstance();
    
    // Vectors
    registry.registerFunction(std::make_unique<VectorNewFunction>());
    registry.registerFunction(std::make_unique<VectorPushFunction>());
    registry.registerFunction(std::make_unique<VectorGetFunction>());
    registry.registerFunction(std::make_unique<VectorSizeFunction>());
    
    // Maps
    registry.registerFunction(std::make_unique<MapNewFunction>());
    registry.registerFunction(std::make_unique<MapPutFunction>());
    registry.registerFunction(std::make_unique<MapGetFunction>());

    // File IO
    registry.registerFunction(std::make_unique<FileOpenFunction>());
    registry.registerFunction(std::make_unique<FileCloseFunction>());
    registry.registerFunction(std::make_unique<FileReadFunction>());
    registry.registerFunction(std::make_unique<FileWriteFunction>());
    registry.registerFunction(std::make_unique<FileExistsFunction>());
    registry.registerFunction(std::make_unique<FileSizeFunction>());
    registry.registerFunction(std::make_unique<FileDeleteFunction>());

    // Basic IO
    registry.registerFunction(std::make_unique<PrintIntFunction>());
    registry.registerFunction(std::make_unique<PrintStrFunction>());
    registry.registerFunction(std::make_unique<PrintlnIntFunction>());
    registry.registerFunction(std::make_unique<PrintlnStrFunction>());
    registry.registerFunction(std::make_unique<PrintlnVoidFunction>());
    registry.registerFunction(std::make_unique<PrintlnVoidFunction>());
    registry.registerFunction(std::make_unique<ReadIntFunction>());
    
    // Strings
    registry.registerFunction(std::make_unique<StringConcatFunction>());
    
    // AI Agents
    registry.registerFunction(std::make_unique<OllamaChatFunction>());
    registry.registerFunction(std::make_unique<OllamaGenerateFunction>());
    registry.registerFunction(std::make_unique<OllamaListModelsFunction>());
    registry.registerFunction(std::make_unique<SemanticEqualsFunction>());
}


// Static block to auto-register on startup? 
// Or call this from main.cpp?
// Safer to call from main.cpp or LLVMCodeGen constructor.

} // namespace lazya
