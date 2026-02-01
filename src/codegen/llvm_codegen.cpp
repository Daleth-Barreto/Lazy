/*
 * LazyA LLVM Code Generator
 * Reconstructed Implementation
 */

#include <optional>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "llvm_codegen.h"
#include "AIFunctionGenerator.h"
#include "../runtime/RuntimeRegistry.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/Support/raw_ostream.h"

namespace lazya {

// Implementation class hiding LLVM details
class LLVMCodeGenImpl {
public:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    
    // Symbol table for variables: Name -> AllocaInst (pointer to memory)
    std::map<std::string, llvm::AllocaInst*> named_values;
    
    // Symbol table for types: Name -> TypeName
    std::map<std::string, std::string> symbol_types;
    
    // Parent scopes for variables (block scoping)
    std::vector<std::map<std::string, llvm::AllocaInst*>> scope_stack;
    
    // Track generated object files (for linking)
    std::vector<std::string> generated_objects;

    LLVMCodeGenImpl() {
        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>("LazyA", *context);
        builder = std::make_unique<llvm::IRBuilder<>>(*context);
    }

    // Helper: Get LLVM type from string name
    llvm::Type* getType(const std::string& typeName) {
        if (typeName == "int") return llvm::Type::getInt32Ty(*context);
        if (typeName == "float") return llvm::Type::getDoubleTy(*context);
        if (typeName == "bool") return llvm::Type::getInt1Ty(*context);
        if (typeName == "void") return llvm::Type::getVoidTy(*context);
        if (typeName == "string") return llvm::PointerType::getUnqual(*context); // char*
        if (typeName == "any") return llvm::PointerType::getUnqual(*context);    // void*
        return llvm::PointerType::getUnqual(*context); // Default to pointer
    }
    
    // Recursive generation functions
    llvm::Value* generateNode(ASTNode* node);
    llvm::Value* generateExpression(ASTNode* node);
    void generateStatement(ASTNode* node);
    void generateFunction(FunctionNode* func);
    
    // Helpers
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* func, const std::string& name, llvm::Type* type);
    void registerRuntimeFunctions();
};

// === Implementation of LLVMCodeGenImpl methods ===

llvm::AllocaInst* LLVMCodeGenImpl::createEntryBlockAlloca(llvm::Function* func, const std::string& name, llvm::Type* type) {
    llvm::IRBuilder<> tmp_builder(&func->getEntryBlock(), func->getEntryBlock().begin());
    return tmp_builder.CreateAlloca(type, nullptr, name);
}

void LLVMCodeGenImpl::registerRuntimeFunctions() {
    RuntimeRegistry::getInstance().initializeModule(module.get(), *context);
}

// === Dispatcher ===

llvm::Value* LLVMCodeGenImpl::generateNode(ASTNode* node) {
    if (!node) return nullptr;
    // std::cout << "DEBUG: generateNode type=" << (int)node->type << "\n";
    
    switch (node->type) {
        case NodeType::INT_LITERAL:
        case NodeType::FLOAT_LITERAL:
        case NodeType::STRING_LITERAL:
        case NodeType::BOOL_LITERAL:
        case NodeType::NULL_LITERAL:
        case NodeType::IDENTIFIER:
        case NodeType::BINARY_OP:
        case NodeType::UNARY_OP:
        case NodeType::FUNCTION_CALL:
        case NodeType::LLM_CALL:
        case NodeType::MEMBER_ACCESS:
        case NodeType::SUBSCRIPT:
        case NodeType::AI_ASK:
        case NodeType::AI_GENERATE:
            return generateExpression(node);
            
        case NodeType::FUNCTION_DECL:
        case NodeType::CONTEXT_FUNCTION_DECL:
            // std::cout << "DEBUG: processing function decl\n";
            generateFunction(static_cast<FunctionNode*>(node));
            return nullptr;
            
        default:
            generateStatement(node);
            return nullptr;
    }
}

// === Expression Generation ===

llvm::Value* LLVMCodeGenImpl::generateExpression(ASTNode* node) {
    if (!node) return nullptr;
    // std::cout << "DEBUG: generateExpression type=" << (int)node->type << "\n";
    
    switch (node->type) {
        case NodeType::INT_LITERAL: {
            auto* int_node = static_cast<IntLiteralNode*>(node);
            return llvm::ConstantInt::get(*context, llvm::APInt(32, int_node->value, true));
        }
        case NodeType::FLOAT_LITERAL: {
            auto* float_node = static_cast<FloatLiteralNode*>(node);
            return llvm::ConstantFP::get(*context, llvm::APFloat(float_node->value));
        }
        case NodeType::BOOL_LITERAL: {
            auto* bool_node = static_cast<BoolLiteralNode*>(node);
            return llvm::ConstantInt::get(*context, llvm::APInt(1, bool_node->value, false));
        }
        case NodeType::STRING_LITERAL: {
            auto* str_node = static_cast<StringLiteralNode*>(node);
            return builder->CreateGlobalStringPtr(str_node->value);
        }
        case NodeType::NULL_LITERAL: {
            return llvm::ConstantPointerNull::get(llvm::PointerType::getUnqual(*context));
        }
        case NodeType::IDENTIFIER: {
            auto* id_node = static_cast<IdentifierNode*>(node);
            std::string name = id_node->name;
            llvm::AllocaInst* alloca = nullptr;
            for (auto it = scope_stack.rbegin(); it != scope_stack.rend(); ++it) {
                if (it->count(name)) { alloca = (*it)[name]; break; }
            }
            if (!alloca && named_values.count(name)) alloca = named_values[name];
            if (!alloca) { std::cerr << "Error: Unknown variable: " << name << "\n"; return nullptr; }
            return builder->CreateLoad(alloca->getAllocatedType(), alloca, name);
        }
        case NodeType::BINARY_OP: {
            auto* bin_node = static_cast<BinaryOpNode*>(node);
            llvm::Value* L = generateExpression(bin_node->left);
            llvm::Value* R = generateExpression(bin_node->right);
            if (!L || !R) return nullptr;
            if (L->getType()->isIntegerTy(1)) L = builder->CreateZExt(L, llvm::Type::getInt32Ty(*context));
            if (R->getType()->isIntegerTy(1)) R = builder->CreateZExt(R, llvm::Type::getInt32Ty(*context));
            bool isFloat = L->getType()->isDoubleTy() || R->getType()->isDoubleTy();
            if (isFloat) {
                 if (!L->getType()->isDoubleTy()) L = builder->CreateSIToFP(L, llvm::Type::getDoubleTy(*context));
                 if (!R->getType()->isDoubleTy()) R = builder->CreateSIToFP(R, llvm::Type::getDoubleTy(*context));
            }
            if (bin_node->op == "+") {
                 if (L->getType()->isPointerTy() && R->getType()->isPointerTy()) {
                     llvm::Function* callee = module->getFunction("string_concat");
                     if (!callee) { std::cerr << "Error: string_concat not found\n"; return nullptr; }
                     std::vector<llvm::Value*> args = {L, R};
                     return builder->CreateCall(callee, args, "strcat");
                 }
                 return isFloat ? builder->CreateFAdd(L, R, "addtmp") : builder->CreateAdd(L, R, "addtmp");
            }
            if (bin_node->op == "-") return isFloat ? builder->CreateFSub(L, R, "subtmp") : builder->CreateSub(L, R, "subtmp");
            if (bin_node->op == "*") return isFloat ? builder->CreateFMul(L, R, "multmp") : builder->CreateMul(L, R, "multmp");
            if (bin_node->op == "/") return isFloat ? builder->CreateFDiv(L, R, "divtmp") : builder->CreateSDiv(L, R, "divtmp");
            if (bin_node->op == "<") return isFloat ? builder->CreateFCmpOLT(L, R) : builder->CreateICmpSLT(L, R);
            if (bin_node->op == ">") return isFloat ? builder->CreateFCmpOGT(L, R) : builder->CreateICmpSGT(L, R);
            if (bin_node->op == "==") return isFloat ? builder->CreateFCmpOEQ(L, R) : builder->CreateICmpEQ(L, R);
            
            if (bin_node->op == "!=") return isFloat ? builder->CreateFCmpONE(L, R) : builder->CreateICmpNE(L, R);
            if (bin_node->op == "<=") return isFloat ? builder->CreateFCmpOLE(L, R) : builder->CreateICmpSLE(L, R);
            if (bin_node->op == ">=") return isFloat ? builder->CreateFCmpOGE(L, R) : builder->CreateICmpSGE(L, R);
            
            if (bin_node->op == "~=") {
                 llvm::Function* callee = module->getFunction("ai_semantic_equals");
                 if (!callee) return nullptr;
                 llvm::Value* threshold = llvm::ConstantFP::get(llvm::Type::getFloatTy(*context), 0.8);
                 if (L->getType()->isPointerTy() && R->getType()->isPointerTy()) {
                     std::vector<llvm::Value*> args = {L, R, threshold};
                     return builder->CreateCall(callee, args, "sem_eq");
                 }
            }
            return nullptr;
        }
        case NodeType::FUNCTION_CALL: {
            auto* call_node = static_cast<FunctionCallNode*>(node);
            
            // Generate args first to identify types
            std::vector<llvm::Value*> args;
            for (auto* arg : call_node->arguments) {
                args.push_back(generateExpression(arg));
            }

            // Ad-hoc polymorphism for print/println
            std::string func_name = call_node->function_name;
            if (func_name == "print" || func_name == "println") {
                if (args.empty()) {
                     func_name += "_void";
                } else if (args.size() == 1) {
                    llvm::Value* argVal = args[0];
                    if (argVal) {
                        if (argVal->getType()->isIntegerTy(32)) func_name += "_int";
                        else if (argVal->getType()->isPointerTy()) func_name += "_str";
                        // else default/error
                    }
                }
            }

            llvm::Function* callee = module->getFunction(func_name);
            if (!callee) {
                // Try normalizing namespace names: ai.ollama.chat -> ai_ollama_chat
                std::string normalized = func_name;
                std::replace(normalized.begin(), normalized.end(), '.', '_');
                callee = module->getFunction(normalized);
            }
            if (!callee) { std::cerr << "Error: Unknown function: " << func_name << "\n"; return nullptr; }
            
            if (callee->getReturnType()->isVoidTy()) {
                return builder->CreateCall(callee, args);
            }
            return builder->CreateCall(callee, args, "calltmp");
        }
        default: std::cerr << "CodeGen: Unknown expression node.\n"; return nullptr;
    }
}

// === Statement Generation ===

void LLVMCodeGenImpl::generateStatement(ASTNode* node) {
    if (!node) return;
    // std::cout << "DEBUG: generateStatement type=" << (int)node->type << "\n";
    switch (node->type) {
        case NodeType::STATEMENT_LIST: {
            auto* list = static_cast<StatementListNode*>(node);
            for (auto* stmt : list->statements) generateStatement(stmt);
            break;
        }
        case NodeType::VARIABLE_DECL: {
            auto* var_node = static_cast<VariableNode*>(node);
            llvm::Function* func = builder->GetInsertBlock()->getParent();
            llvm::Type* type = getType(var_node->var_type ? var_node->var_type->type_name : "int");
            llvm::AllocaInst* alloca = createEntryBlockAlloca(func, var_node->name, type);
            if (!scope_stack.empty()) scope_stack.back()[var_node->name] = alloca;
            else named_values[var_node->name] = alloca;
            if (var_node->initializer) {
                llvm::Value* init_val = generateExpression(var_node->initializer);
                if (init_val) builder->CreateStore(init_val, alloca);
            }
            break;
        }
        case NodeType::ASSIGNMENT: {
            auto* assign_node = static_cast<AssignmentNode*>(node);
            if (assign_node->target->type != NodeType::IDENTIFIER) return;
            std::string name = static_cast<IdentifierNode*>(assign_node->target)->name;
            llvm::Value* val = generateExpression(assign_node->value);
            llvm::AllocaInst* alloca = nullptr;
             for (auto it = scope_stack.rbegin(); it != scope_stack.rend(); ++it) {
                if (it->count(name)) { alloca = (*it)[name]; break; }
            }
            if (!alloca && named_values.count(name)) alloca = named_values[name];
            if (alloca && val) builder->CreateStore(val, alloca);
            break;
        }
        case NodeType::RETURN_STATEMENT: {
            auto* ret_node = static_cast<ReturnNode*>(node);
            if (ret_node->value) {
                llvm::Value* val = generateExpression(ret_node->value);
                builder->CreateRet(val);
            } else {
                builder->CreateRetVoid();
            }
            break;
        }
        case NodeType::IF_STATEMENT: {
            auto* if_node = static_cast<IfNode*>(node);
            llvm::Value* cond = generateExpression(if_node->condition);
            if (!cond) return;
            if (cond->getType()->isIntegerTy(32)) cond = builder->CreateICmpNE(cond, llvm::ConstantInt::get(*context, llvm::APInt(32, 0)), "ifcond");
            llvm::Function* func = builder->GetInsertBlock()->getParent();
            llvm::BasicBlock* then_bb = llvm::BasicBlock::Create(*context, "then", func);
            llvm::BasicBlock* else_bb = llvm::BasicBlock::Create(*context, "else", func);
            llvm::BasicBlock* merge_bb = llvm::BasicBlock::Create(*context, "ifcont");
            bool has_else = (if_node->else_branch != nullptr);
            builder->CreateCondBr(cond, then_bb, has_else ? else_bb : merge_bb);
            builder->SetInsertPoint(then_bb);
            generateStatement(if_node->then_branch);
            if (!builder->GetInsertBlock()->getTerminator()) builder->CreateBr(merge_bb);
            if (has_else) {
                // else_bb already in func
                builder->SetInsertPoint(else_bb);
                generateStatement(if_node->else_branch);
                if (!builder->GetInsertBlock()->getTerminator()) builder->CreateBr(merge_bb);
            } else {
                 else_bb->eraseFromParent(); // Remove unused block
            }
            merge_bb->insertInto(func);
            builder->SetInsertPoint(merge_bb);
            break;
        }
        case NodeType::WHILE_STATEMENT: {
            auto* while_node = static_cast<WhileNode*>(node);
            llvm::Function* func = builder->GetInsertBlock()->getParent();
            llvm::BasicBlock* cond_bb = llvm::BasicBlock::Create(*context, "loop_cond", func);
            llvm::BasicBlock* body_bb = llvm::BasicBlock::Create(*context, "loop_body", func);
            llvm::BasicBlock* end_bb = llvm::BasicBlock::Create(*context, "loop_end");
            builder->CreateBr(cond_bb);
            builder->SetInsertPoint(cond_bb);
            llvm::Value* cond = generateExpression(while_node->condition);
             if (cond->getType()->isIntegerTy(32)) {
                cond = builder->CreateICmpNE(cond, llvm::ConstantInt::get(*context, llvm::APInt(32, 0)), "loopcond");
            }
            builder->CreateCondBr(cond, body_bb, end_bb);
            
            builder->SetInsertPoint(body_bb);
            generateStatement(while_node->body);
            if (!builder->GetInsertBlock()->getTerminator()) {
                builder->CreateBr(cond_bb);
            }
            
            end_bb->insertInto(func);
            builder->SetInsertPoint(end_bb);
            break;
        }
        default: generateExpression(node); break;
    }
}

// === Function Generation ===

void LLVMCodeGenImpl::generateFunction(FunctionNode* func) {
    if (func->is_context_function) {
        if (!func->body || (func->body->type == NodeType::STATEMENT_LIST && static_cast<StatementListNode*>(func->body)->statements.empty())) {
             std::cout << "[AI] Generating implementation for " << func->name << "...\n";
             std::string obj_file = AIFunctionGenerator::getInstance().generate(func->name, func->docstring);
             generated_objects.push_back(obj_file);
             
             std::vector<llvm::Type*> param_types;
             for (auto* param : func->parameters) param_types.push_back(getType(param->param_type->type_name));
             llvm::FunctionType* func_type = llvm::FunctionType::get(getType(func->return_type->type_name), param_types, false);
             llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, func->name, module.get());
             return;
        }
    }

    named_values.clear();
    scope_stack.clear();
    scope_stack.push_back(std::map<std::string, llvm::AllocaInst*>());

    std::vector<llvm::Type*> param_types;
    for (auto* param : func->parameters) param_types.push_back(getType(param->param_type->type_name));
    llvm::FunctionType* func_type = llvm::FunctionType::get(getType(func->return_type->type_name), param_types, false);
    
    // std::cout << "DEBUG: Creating function " << func->name << "\n";
    llvm::Function* llvm_func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, func->name, module.get());
    
    llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", llvm_func);
    builder->SetInsertPoint(entry);
    
    unsigned idx = 0;
    for (auto& arg : llvm_func->args()) {
        std::string arg_name = func->parameters[idx]->name;
        arg.setName(arg_name);
        llvm::AllocaInst* alloca = createEntryBlockAlloca(llvm_func, arg_name, arg.getType());
        builder->CreateStore(&arg, alloca);
        scope_stack.back()[arg_name] = alloca;
        idx++;
    }
    
    generateStatement(func->body);
    
    if (!builder->GetInsertBlock()->getTerminator()) {
        if (func->return_type->type_name == "void") builder->CreateRetVoid();
        else builder->CreateRet(llvm::ConstantInt::get(*context, llvm::APInt(32, 0)));
    }
    llvm::verifyFunction(*llvm_func);
}

// === Public Interface Implementation ===

LLVMCodeGen::LLVMCodeGen() : impl(new LLVMCodeGenImpl()) {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    // std::cout << "[CodeGen] Initialized LLVM backend (Native)\n";
}

LLVMCodeGen::~LLVMCodeGen() {
    delete impl;
}

bool LLVMCodeGen::generate(ASTNode* root) {
    if (!root) return false;
    // std::cout << "DEBUG: generate start\n";
    impl->registerRuntimeFunctions();
    // std::cout << "DEBUG: registered runtime\n";
    // std::cout << "[CodeGen] Generating LLVM IR...\n";
    
    if (root->type == NodeType::STATEMENT_LIST) {
        StatementListNode* list = static_cast<StatementListNode*>(root);
        for (auto* stmt : list->statements) impl->generateNode(stmt);
    } else {
        impl->generateNode(root);
    }
    
    if (llvm::verifyModule(*impl->module, &llvm::errs())) {
        std::cerr << "[CodeGen] Error: Module verification failed\n";
    }
    return true;
}

bool LLVMCodeGen::write_object_file(const std::string& filename) {
    std::string error;
    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
    if (!target) { std::cerr << error; return false; }
    
    auto cpu = "generic";
    auto features = "";
    llvm::TargetOptions opt;
    std::optional<llvm::Reloc::Model> rm = llvm::Reloc::PIC_;
    auto targetMachine = target->createTargetMachine(targetTriple, cpu, features, opt, rm);
    
    impl->module->setDataLayout(targetMachine->createDataLayout());
    impl->module->setTargetTriple(targetTriple);
    
    std::error_code ec;
    llvm::raw_fd_ostream dest(filename, ec, llvm::sys::fs::OF_None);
    if (ec) { std::cerr << ec.message(); return false; }
    
    llvm::legacy::PassManager pass;
    if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, llvm::CodeGenFileType::ObjectFile)) return false;
    
    pass.run(*impl->module);
    dest.flush();
    return true;
}

bool LLVMCodeGen::link_executable(const std::string& obj_file, const std::string& exe_file) {
    // Get LAZY_HOME from environment or default
    const char* lazy_home_env = std::getenv("LAZY_HOME");
    std::string lazy_home = lazy_home_env ? lazy_home_env : (std::string(std::getenv("HOME")) + "/.lazy");
    std::string lib_path = lazy_home + "/lib";

    // Build the link command
    // gcc <obj_file> -L<lib_path> -llazy_runtime -lzstd -lz -lstdc++ -lm -o <exe_file>
    std::string cmd_link = "gcc " + obj_file;
    
    // Add AI generated objects if any
    for (const auto& ai_obj : impl->generated_objects) {
        cmd_link += " " + ai_obj;
    }
    
    cmd_link += " -L" + lib_path + " -llazy_runtime";
    cmd_link += " -lzstd -lz -lstdc++ -lm";
    cmd_link += " -o " + exe_file;
    
    // std::cout << "[Linker] " << cmd_link << "\n";
    int res = system(cmd_link.c_str());
    
    if (res != 0) {
        std::cerr << "[Linker] Error: Linking failed.\n";
        std::cerr << "Command: " << cmd_link << "\n";
        std::cerr << "Ensure library path " << lib_path << " exists and contains liblazy_runtime.a\n";
    }
    
    return (res == 0);
}

} // namespace lazya
