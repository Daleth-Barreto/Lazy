#ifndef LAZYA_STDLIB_H
#define LAZYA_STDLIB_H

#include "IRuntimeFunction.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

namespace lazya {

// === VECTOR ===

class VectorNewFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "vector_new"; }
    std::string getSignature() const override { return "void* vector_new()"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        // void* vector_new() -> returns ptr
        llvm::Type* ptr = llvm::PointerType::getUnqual(context); 
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            ptr,
            {},
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

class VectorPushFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "vector_push"; }
    std::string getSignature() const override { return "void vector_push(void*, int)"; }

    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;

        // void vector_push(void*, int)
        llvm::Type* ptr = llvm::PointerType::getUnqual(context); 
        
        std::vector<llvm::Type*> args = {
            ptr,
            llvm::Type::getInt32Ty(context)
        };
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

class VectorGetFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "vector_get"; }
    std::string getSignature() const override { return "int vector_get(void*, int)"; }

    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;

        // int vector_get(void*, int)
        llvm::Type* ptr = llvm::PointerType::getUnqual(context); 
        
        std::vector<llvm::Type*> args = {
            ptr,
            llvm::Type::getInt32Ty(context)
        };
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context),
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

class VectorSizeFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "vector_size"; }
    std::string getSignature() const override { return "int vector_size(void*)"; }

    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;

        // int vector_size(void*)
        llvm::Type* ptr = llvm::PointerType::getUnqual(context); 
        
        std::vector<llvm::Type*> args = {
            ptr
        };
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context),
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === MAP ===

class MapNewFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "map_new"; }
    std::string getSignature() const override { return "void* map_new()"; }

    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;

        // void* map_new()
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            ptr,
            {},
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

class MapPutFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "map_put"; }
    std::string getSignature() const override { return "void map_put(void*, char*, int)"; }

    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;

        // void map_put(void*, char*, int)
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = {
            ptr,
            ptr, // string is also ptr (char*)
            llvm::Type::getInt32Ty(context)
        };
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

class MapGetFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "map_get"; }
    std::string getSignature() const override { return "int map_get(void*, char*)"; }

    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;

        // int map_get(void*, char*)
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = {
            ptr,
            ptr
        };
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context),
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

void register_standard_library();

} // namespace lazya

#endif // LAZYA_STDLIB_H
