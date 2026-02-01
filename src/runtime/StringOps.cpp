#include "StringOps.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include <cstring>
#include <cstdlib>

namespace lazya {

// C implementation
extern "C" {
    char* string_concat(const char* s1, const char* s2) {
        if (!s1) s1 = "";
        if (!s2) s2 = "";
        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);
        char* result = (char*)malloc(len1 + len2 + 1);
        strcpy(result, s1);
        strcat(result, s2);
        return result;
    }
}

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
