/*
 * LazyA Print Function - Implementation
 */

#include "PrintFunction.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

namespace lazya {

llvm::Function* PrintIntFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    // Check if already exists
    llvm::Function* func = module->getFunction("print_int");
    if (func) return func;
    
    // Create function type: void print_int(int)
    llvm::Type* int32Type = llvm::Type::getInt32Ty(context);
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context),  // return type
        {int32Type},                      // parameter types
        false                             // is vararg
    );
    
    // Create function
    func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "print_int",
        module
    );
    
    return func;
}

llvm::Function* PrintStringFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    llvm::Function* func = module->getFunction("print_string");
    if (func) return func;
    
    // Create function type: void print_string(char*)
    // Create function type: void print_string(char*)
    llvm::Type* charPtrType = llvm::PointerType::getUnqual(context);
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context),
        {charPtrType},
        false
    );
    
    func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "print_string",
        module
    );
    
    return func;
}

llvm::Function* PrintlnFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    llvm::Function* func = module->getFunction("println");
    if (func) return func;
    
    // Create function type: void println()
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context),
        {},  // no parameters
        false
    );
    
    func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "println",
        module
    );
    
    return func;
}

} // namespace lazya
