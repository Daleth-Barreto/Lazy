#ifndef LAZYA_STRING_OPS_H
#define LAZYA_STRING_OPS_H

#include "IRuntimeFunction.h"

namespace lazya {

class StringConcatFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "string_concat"; }
    std::string getSignature() const override { return "string string_concat(string, string)"; }

    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override;
};

} // namespace lazya

#endif // LAZYA_STRING_OPS_H
