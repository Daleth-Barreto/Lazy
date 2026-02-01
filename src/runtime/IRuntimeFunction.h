/*
 * LazyA Runtime Function Interface
 * Base interface for all runtime library functions
 */

#ifndef LAZYA_IRUNTIME_FUNCTION_H
#define LAZYA_IRUNTIME_FUNCTION_H

#include <string>
#include <memory>

// Forward declarations
namespace llvm {
    class Module;
    class Function;
    class LLVMContext;
}

namespace lazya {

/**
 * Interface for runtime functions
 * Implement this to add new runtime capabilities
 */
class IRuntimeFunction {
public:
    virtual ~IRuntimeFunction() = default;
    
    /**
     * Get or create the function in the LLVM module
     * @param module The LLVM module to add the function to
     * @param context The LLVM context
     * @return The created or existing function
     */
    virtual llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) = 0;
    
    /**
     * Get the function name
     */
    virtual std::string getName() const = 0;
    
    /**
     * Get function signature for documentation
     */
    virtual std::string getSignature() const = 0;
};

} // namespace lazya

#endif // LAZYA_IRUNTIME_FUNCTION_H
