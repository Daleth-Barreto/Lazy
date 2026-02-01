#include "StringOps.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include <cstring>
#include <cstdlib>

namespace lazya {

// C implementation moved to RuntimeShim.cpp to avoid LLVM dependency in runtime library

llvm::Function* StringConcatFunction::getOrCreate(llvm::Module* module, llvm::LLVMContext& context) {
    llvm::Function* func = module->getFunction("string_concat");
    if (func) return func;

    llvm::Type* charPtrTy = llvm::PointerType::getUnqual(context);
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        charPtrTy,
        {charPtrTy, charPtrTy},
        false
    );

    return llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "string_concat",
        module
    );
}

} // namespace lazya
