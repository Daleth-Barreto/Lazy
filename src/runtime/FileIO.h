/*
 * LazyA Runtime - File I/O Functions
 * Provides file operations for reading and writing
 */

#ifndef LAZY_FILE_IO_H
#define LAZY_FILE_IO_H

#include "IRuntimeFunction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"

namespace lazya {

// === FILE OPEN ===
// void* file_open(char* path, char* mode)
class FileOpenFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "file_open"; }
    std::string getSignature() const override { return "void* file_open(char*, char*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = {
            ptr,  // path (char*)
            ptr   // mode (char*)
        };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            ptr,  // returns FILE* as void*
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === FILE CLOSE ===
// void file_close(void* file)
class FileCloseFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "file_close"; }
    std::string getSignature() const override { return "void file_close(void*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = { ptr };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === FILE READ ===
// char* file_read(void* file)
class FileReadFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "file_read"; }
    std::string getSignature() const override { return "char* file_read(void*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = { ptr };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            ptr,  // returns char*
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === FILE WRITE ===
// void file_write(void* file, char* data)
class FileWriteFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "file_write"; }
    std::string getSignature() const override { return "void file_write(void*, char*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = {
            ptr,  // file
            ptr   // data
        };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === FILE READ LINE ===
// char* file_read_line(void* file)
class FileReadLineFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "file_read_line"; }
    std::string getSignature() const override { return "char* file_read_line(void*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = { ptr };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            ptr,  // returns char*
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === FILE EXISTS ===
// int file_exists(char* path)
class FileExistsFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "file_exists"; }
    std::string getSignature() const override { return "int file_exists(char*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = { ptr };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context),  // returns bool as int
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === FILE SIZE ===
// int file_size(char* path)
class FileSizeFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "file_size"; }
    std::string getSignature() const override { return "int file_size(char*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = { ptr };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context),
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

// === FILE DELETE ===
// int file_delete(char* path)
class FileDeleteFunction : public IRuntimeFunction {
public:
    std::string getName() const override { return "file_delete"; }
    std::string getSignature() const override { return "int file_delete(char*)"; }
    
    llvm::Function* getOrCreate(llvm::Module* module, llvm::LLVMContext& context) override {
        if (auto* f = module->getFunction(getName())) return f;
        
        llvm::Type* ptr = llvm::PointerType::getUnqual(context);
        
        std::vector<llvm::Type*> args = { ptr };
        
        llvm::FunctionType* type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context),  // returns bool as int
            args,
            false
        );
        return llvm::Function::Create(type, llvm::Function::ExternalLinkage, getName(), module);
    }
};

} // namespace lazya

#endif // LAZY_FILE_IO_H
