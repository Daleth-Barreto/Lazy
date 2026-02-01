/*
 * LazyA Abstract Syntax Tree - Implementation
 */

#include "ast.h"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace lazya {

// Helper function for indentation
static void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        std::cout << "  ";
    }
}

// IntLiteralNode
void IntLiteralNode::print(int indent) {
    print_indent(indent);
    std::cout << "IntLiteral: " << value << std::endl;
}

// FloatLiteralNode
void FloatLiteralNode::print(int indent) {
    print_indent(indent);
    std::cout << "FloatLiteral: " << value << std::endl;
}

// StringLiteralNode
void StringLiteralNode::print(int indent) {
    print_indent(indent);
    std::cout << "StringLiteral: \"" << value << "\"" << std::endl;
}

// BoolLiteralNode
void BoolLiteralNode::print(int indent) {
    print_indent(indent);
    std::cout << "BoolLiteral: " << (value ? "true" : "false") << std::endl;
}

// IdentifierNode
void IdentifierNode::print(int indent) {
    print_indent(indent);
    std::cout << "Identifier: " << name << std::endl;
}

// BinaryOpNode
void BinaryOpNode::print(int indent) {
    print_indent(indent);
    std::cout << "BinaryOp: " << op << std::endl;
    if (left) left->print(indent + 1);
    if (right) right->print(indent + 1);
}

// UnaryOpNode
void UnaryOpNode::print(int indent) {
    print_indent(indent);
    std::cout << "UnaryOp: " << op << std::endl;
    if (operand) operand->print(indent + 1);
}

// TypeNode
void TypeNode::print(int indent) {
    print_indent(indent);
    std::cout << "Type: " << type_name << std::endl;
}

// ParameterNode
void ParameterNode::print(int indent) {
    print_indent(indent);
    std::cout << "Parameter: " << name << std::endl;
    if (param_type) param_type->print(indent + 1);
}

// FunctionNode
void FunctionNode::print(int indent) {
    print_indent(indent);
    std::cout << (is_context_function ? "ContextFunction: " : "Function: ") << name << std::endl;
    
    if (!parameters.empty()) {
        print_indent(indent + 1);
        std::cout << "Parameters:" << std::endl;
        for (auto param : parameters) {
            param->print(indent + 2);
        }
    }
    
    if (return_type) {
        print_indent(indent + 1);
        std::cout << "ReturnType:" << std::endl;
        return_type->print(indent + 2);
    }
    
    if (is_context_function && !docstring.empty()) {
        print_indent(indent + 1);
        std::cout << "Docstring: \"" << docstring << "\"" << std::endl;
    }
    
    if (body) {
        print_indent(indent + 1);
        std::cout << "Body:" << std::endl;
        body->print(indent + 2);
    }
}

// VariableNode
void VariableNode::print(int indent) {
    print_indent(indent);
    std::cout << "Variable: " << name << std::endl;
    if (var_type) {
        print_indent(indent + 1);
        std::cout << "Type:" << std::endl;
        var_type->print(indent + 2);
    }
    if (initializer) {
        print_indent(indent + 1);
        std::cout << "Initializer:" << std::endl;
        initializer->print(indent + 2);
    }
}

// AssignmentNode
void AssignmentNode::print(int indent) {
    print_indent(indent);
    std::cout << "Assignment:" << std::endl;
    
    print_indent(indent + 1);
    std::cout << "Target: " << target << std::endl; // Assuming target is std::string or const char*
    
    print_indent(indent + 1);
    std::cout << "Value:" << std::endl;
    if (value) value->print(indent + 2);
}

// CompoundAssignmentNode
void CompoundAssignmentNode::print(int indent) {
    print_indent(indent);
    std::cout << "CompoundAssignment (" << op << "):" << std::endl;
    
    print_indent(indent + 1);
    std::cout << "Target:" << std::endl;
    target->print(indent + 2);
    
    print_indent(indent + 1);
    std::cout << "Value:" << std::endl;
    value->print(indent + 2);
}

// IfNode
void IfNode::print(int indent) {
    print_indent(indent);
    std::cout << "If:" << std::endl;
    
    print_indent(indent + 1);
    std::cout << "Condition:" << std::endl;
    if (condition) condition->print(indent + 2);
    
    print_indent(indent + 1);
    std::cout << "Then:" << std::endl;
    if (then_branch) then_branch->print(indent + 2);
    
    if (else_branch) {
        print_indent(indent + 1);
        std::cout << "Else:" << std::endl;
        else_branch->print(indent + 2);
    }
}

// WhileNode
void WhileNode::print(int indent) {
    print_indent(indent);
    std::cout << "While:" << std::endl;
    
    print_indent(indent + 1);
    std::cout << "Condition:" << std::endl;
    if (condition) condition->print(indent + 2);
    
    print_indent(indent + 1);
    std::cout << "Body:" << std::endl;
    if (body) body->print(indent + 2);
}

// ReturnNode
void ReturnNode::print(int indent) {
    print_indent(indent);
    std::cout << "Return:" << std::endl;
    if (value) value->print(indent + 1);
}

// FunctionCallNode
void FunctionCallNode::print(int indent) {
    print_indent(indent);
    std::cout << "FunctionCall: " << function_name << std::endl;
    if (!arguments.empty()) {
        print_indent(indent + 1);
        std::cout << "Arguments:" << std::endl;
        for (auto arg : arguments) {
            arg->print(indent + 2);
        }
    }
}

// LLMCallNode
void LLMCallNode::print(int indent) {
    print_indent(indent);
    std::cout << "LLMCall: " << method << std::endl;
    if (!arguments.empty()) {
        print_indent(indent + 1);
        std::cout << "Arguments:" << std::endl;
        for (auto arg : arguments) {
            arg->print(indent + 2);
        }
    }
}

// AI Operator Nodes
void AIAskNode::print(int indent) {
    print_indent(indent);
    std::cout << "@ask:" << std::endl;
    if (question) question->print(indent + 1);
}

void AIGenerateNode::print(int indent) {
    print_indent(indent);
    std::cout << "@generate:" << std::endl;
    if (prompt) prompt->print(indent + 1);
}

void AIAnalyzeNode::print(int indent) {
    print_indent(indent);
    std::cout << "@analyze:" << std::endl;
    if (text) text->print(indent + 1);
}

void AIEmbedNode::print(int indent) {
    print_indent(indent);
    std::cout << "@embed:" << std::endl;
    if (text) text->print(indent + 1);
}

void AIClassifyNode::print(int indent) {
    print_indent(indent);
    std::cout << "@classify:" << std::endl;
    if (text) text->print(indent + 1);
}

// StatementListNode
void StatementListNode::print(int indent) {
    print_indent(indent);
    std::cout << "StatementList:" << std::endl;
    for (auto stmt : statements) {
        if (stmt) stmt->print(indent + 1);
    }
}

} // namespace lazya

// C interface for Bison
extern "C" {

using namespace lazya;

// Literals
ASTNode* create_int_literal_node(int value) {
    return new IntLiteralNode(value);
}

ASTNode* create_float_literal_node(double value) {
    return new FloatLiteralNode(value);
}

ASTNode* create_string_literal_node(const char* value) {
    return new StringLiteralNode(value);
}

ASTNode* create_bool_literal_node(int value) {
    return new BoolLiteralNode(value != 0);
}

ASTNode* create_null_literal_node() {
    return new IntLiteralNode(0); // Placeholder
}

// Identifiers
ASTNode* create_identifier_node(const char* name) {
    return new IdentifierNode(name);
}

// Operators
ASTNode* create_binary_op_node(const char* op, ASTNode* left, ASTNode* right) {
    return new BinaryOpNode(op, left, right);
}

ASTNode* create_unary_op_node(const char* op, ASTNode* operand) {
    return new UnaryOpNode(op, operand);
}

// Types
ASTNode* create_type_node(const char* type_name) {
    return new TypeNode(type_name);
}

ASTNode* create_array_type_node(ASTNode* element_type) {
    TypeNode* elem = static_cast<TypeNode*>(element_type);
    return new TypeNode("[" + elem->type_name + "]");
}

ASTNode* create_optional_type_node(ASTNode* base_type) {
    TypeNode* base = static_cast<TypeNode*>(base_type);
    return new TypeNode(base->type_name + "?");
}

ASTNode* create_union_type_node(ASTNode* left, ASTNode* right) {
    TypeNode* l = static_cast<TypeNode*>(left);
    TypeNode* r = static_cast<TypeNode*>(right);
    return new TypeNode(l->type_name + "|" + r->type_name);
}

// Parameters
ASTNode* create_parameter_node(const char* name, ASTNode* type) {
    return new ParameterNode(name, static_cast<TypeNode*>(type));
}

ASTNode* create_parameter_list(ASTNode* param) {
    auto list = new StatementListNode();
    list->statements.push_back(param);
    return list;
}

ASTNode* append_parameter(ASTNode* list, ASTNode* param) {
    auto stmt_list = static_cast<StatementListNode*>(list);
    stmt_list->statements.push_back(param);
    return list;
}

// Functions
ASTNode* create_function_node(const char* name, ASTNode* params, ASTNode* return_type, 
                               ASTNode* body, int is_context) {
    auto func = new FunctionNode(name, static_cast<TypeNode*>(return_type), body, is_context != 0);
    
    if (params) {
        auto param_list = static_cast<StatementListNode*>(params);
        for (auto p : param_list->statements) {
            func->parameters.push_back(static_cast<ParameterNode*>(p));
        }
    }
    
    return func;
}

void set_function_docstring(ASTNode* func, const char* docstring) {
    auto fn = static_cast<FunctionNode*>(func);
    fn->docstring = docstring;
}

// Variables
ASTNode* create_variable_node(const char* name, ASTNode* type, ASTNode* initializer) {
    return new VariableNode(name, static_cast<TypeNode*>(type), initializer);
}

ASTNode* create_assignment_node(ASTNode* target, ASTNode* value) {
    return new AssignmentNode(target, value);
}

ASTNode* create_compound_assignment_node(ASTNode* target, const char* op, ASTNode* value) {
    return new CompoundAssignmentNode(target, op, value);
}

// Control flow
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch) {
    return new IfNode(condition, then_branch, else_branch);
}

ASTNode* create_while_node(ASTNode* condition, ASTNode* body) {
    return new WhileNode(condition, body);
}

ASTNode* create_for_node(const char* var, ASTNode* iterable, ASTNode* body) {
    return new lazya::ForNode(var, iterable, body);
}

ASTNode* create_return_node(ASTNode* value) {
    return new ReturnNode(value);
}

ASTNode* create_break_node() {
    return new IntLiteralNode(0); // Placeholder
}

ASTNode* create_continue_node() {
    return new IntLiteralNode(0); // Placeholder
}

// Function calls
ASTNode* create_function_call_node(const char* name, ASTNode* args) {
    auto call = new FunctionCallNode(name);
    
    if (args) {
        auto arg_list = static_cast<StatementListNode*>(args);
        for (auto arg : arg_list->statements) {
            call->arguments.push_back(arg);
        }
    }
    
    return call;
}

ASTNode* create_llm_call_node(const char* method, ASTNode* args) {
    auto call = new LLMCallNode(method);
    
    if (args) {
        auto arg_list = static_cast<StatementListNode*>(args);
        for (auto arg : arg_list->statements) {
            call->arguments.push_back(arg);
        }
    }
    
    return call;
}

ASTNode* create_embed_call_node(ASTNode* arg) {
    auto call = new FunctionCallNode("embed");
    call->arguments.push_back(arg);
    return call;
}

ASTNode* create_argument_list(ASTNode* arg) {
    auto list = new StatementListNode();
    list->statements.push_back(arg);
    return list;
}

ASTNode* append_argument(ASTNode* list, ASTNode* arg) {
    auto stmt_list = static_cast<StatementListNode*>(list);
    stmt_list->statements.push_back(arg);
    return list;
}

// Member access
// Member access
ASTNode* create_member_access_node(ASTNode* object, const char* member) {
    return new MemberAccessNode(object, member);
}

ASTNode* create_subscript_node(ASTNode* object, ASTNode* index) {
    return new SubscriptNode(object, index);
}

// Literals
ASTNode* create_array_literal_node(ASTNode* elements) {
    // Placeholder - return statement list
    if (elements) {
        return elements;
    }
    return new StatementListNode();
}

ASTNode* create_dict_literal_node(ASTNode* pairs) {
    return new StatementListNode(); // Placeholder
}

// Statements
ASTNode* create_statement_list(ASTNode* stmt) {
    auto list = new StatementListNode();
    if (stmt) list->statements.push_back(stmt);
    return list;
}

ASTNode* append_statement(ASTNode* list, ASTNode* stmt) {
    auto stmt_list = static_cast<StatementListNode*>(list);
    if (stmt) stmt_list->statements.push_back(stmt);
    return list;
}

ASTNode* create_empty_statement() {
    return new StatementListNode();
}

// Decorators
ASTNode* create_decorator_node(const char* name) {
    return new IdentifierNode(std::string("@") + name);
}

// ForNode
void ForNode::print(int indent) {
    print_indent(indent);
    std::cout << "For Statement (" << variable_name << ")" << std::endl;
    print_indent(indent + 1);
    std::cout << "Iterable:" << std::endl;
    iterable->print(indent + 2);
    print_indent(indent + 1);
    std::cout << "Body:" << std::endl;
    body->print(indent + 2);
}

// Print AST
void print_ast(ASTNode* node) {
    if (node) {
        node->print(0);
    }
}

} // extern "C"
// CStyleForNode
void CStyleForNode::print(int indent) {
    print_indent(indent);
    std::cout << "CStyleFor Statement:" << std::endl;
    
    print_indent(indent + 1);
    std::cout << "Init:" << std::endl;
    if (init) init->print(indent + 2);
    else { print_indent(indent + 2); std::cout << "(none)" << std::endl; }
    
    print_indent(indent + 1);
    std::cout << "Condition:" << std::endl;
    if (condition) condition->print(indent + 2);
    else { print_indent(indent + 2); std::cout << "(none)" << std::endl; }
    
    print_indent(indent + 1);
    std::cout << "Update:" << std::endl;
    if (update) update->print(indent + 2);
    else { print_indent(indent + 2); std::cout << "(none)" << std::endl; }
    
    print_indent(indent + 1);
    std::cout << "Body:" << std::endl;
    if (body) body->print(indent + 2);
}

// ClassNode
void ClassNode::print(int indent) {
    print_indent(indent);
    std::cout << "Class: " << name << std::endl;
    
    print_indent(indent + 1);
    std::cout << "Members:" << std::endl;
    for (auto member : members) {
        member->print(indent + 2);
    }
}

// NewNode
void NewNode::print(int indent) {
    print_indent(indent);
    std::cout << "New: " << class_name << std::endl;
    
    print_indent(indent + 1);
    std::cout << "Arguments:" << std::endl;
    for (auto arg : arguments) {
        arg->print(indent + 2);
    }
}

// MemberAccessNode
void MemberAccessNode::print(int indent) {
    print_indent(indent);
    std::cout << "MemberAccess: ." << member_name << std::endl;
    object->print(indent + 1);
}

// SubscriptNode
void SubscriptNode::print(int indent) {
    print_indent(indent);
    std::cout << "Subscript:" << std::endl;
    object->print(indent + 1);
    index->print(indent + 1);
}

// C wrapper for CStyleFor
extern "C" {
    ASTNode* create_c_style_for_node(ASTNode* init, ASTNode* condition, ASTNode* update, ASTNode* body) {
        return new CStyleForNode(init, condition, update, body);
    }
    
    ASTNode* create_class_node(const char* name, ASTNode* members_list) {
        std::vector<ASTNode*> members;
        if (members_list) {
            StatementListNode* list = static_cast<StatementListNode*>(members_list);
            members = list->statements;
            list->statements.clear(); 
            delete list;
        }
        return new ClassNode(name, members);
    }

    ASTNode* create_new_node(const char* class_name, ASTNode* args) {
         std::vector<ASTNode*> arguments;
        if (args) {
            StatementListNode* list = static_cast<StatementListNode*>(args);
            arguments = list->statements;
            list->statements.clear();
            delete list;
        }
        return new NewNode(class_name, arguments);
    }
    
    // AI Operator Node creation functions
    ASTNode* create_ai_ask_node(ASTNode* question) {
        return new AIAskNode(question);
    }
    
    ASTNode* create_ai_generate_node(ASTNode* prompt) {
        return new AIGenerateNode(prompt);
    }
    
    ASTNode* create_ai_analyze_node(ASTNode* text) {
        return new AIAnalyzeNode(text);
    }
    
    ASTNode* create_ai_embed_node(ASTNode* text) {
        return new AIEmbedNode(text);
    }
    
    ASTNode* create_ai_classify_node(ASTNode* text) {
        return new AIClassifyNode(text);
    }
    
    // Match expression nodes (stub implementations for now)
    ASTNode* create_match_node(ASTNode* value, ASTNode* arms) {
        // TODO: Implement proper MatchNode
        // For now, return as a statement list placeholder
        return arms; // Temporary
    }
    
    ASTNode* create_match_arm_node(ASTNode* pattern, ASTNode* body, int is_semantic) {
        // TODO: Implement proper MatchArmNode
        // For now, return body as placeholder
        return body; // Temporary
    }
    
    ASTNode* create_wildcard_node() {
        // TODO: Implement proper WildcardNode
        // For now, return as identifier placeholder
        return new IdentifierNode("_");
    }
}
