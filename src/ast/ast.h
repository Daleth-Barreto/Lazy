/*
 * LazyA Abstract Syntax Tree
 * Defines node types and structures for the AST
 */

#ifndef LAZYA_AST_H
#define LAZYA_AST_H

#include <string>
#include <vector>
#include <memory>

namespace lazya {

// Node types
enum class NodeType {
    // Literals
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    BOOL_LITERAL,
    NULL_LITERAL,
    ARRAY_LITERAL,
    DICT_LITERAL,
    
    // Identifiers
    IDENTIFIER,
    
    // Operators
    BINARY_OP,
    UNARY_OP,
    
    // Declarations
    FUNCTION_DECL,
    CONTEXT_FUNCTION_DECL,
    CLASS_DECL,
    VARIABLE_DECL,
    PARAMETER,
    
    // Statements
    ASSIGNMENT,
    COMPOUND_ASSIGNMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    FOR_STATEMENT,
    C_STYLE_FOR_STATEMENT,
    RETURN_STATEMENT,
    BREAK_STATEMENT,
    CONTINUE_STATEMENT,
    
    // Expressions
    FUNCTION_CALL,
    LLM_CALL,
    EMBED_CALL,
    NEW_EXPR,
    MEMBER_ACCESS,
    SUBSCRIPT,
    
    // AI Operators
    AI_ASK,
    AI_GENERATE,
    AI_ANALYZE,
    AI_EMBED,
    AI_CLASSIFY,
    
    // Types
    TYPE,
    ARRAY_TYPE,
    OPTIONAL_TYPE,
    UNION_TYPE,
    
    // Other
    STATEMENT_LIST,
    EMPTY_STATEMENT,
    DECORATOR
};

// Base AST Node
class ASTNode {
public:
    NodeType type;
    int line_number;
    
    ASTNode(NodeType t) : type(t), line_number(0) {}
    virtual ~ASTNode() = default;
    
    virtual void print(int indent = 0) = 0;
};

// Literal nodes
class IntLiteralNode : public ASTNode {
public:
    int value;
    IntLiteralNode(int val) : ASTNode(NodeType::INT_LITERAL), value(val) {}
    void print(int indent = 0) override;
};

class FloatLiteralNode : public ASTNode {
public:
    double value;
    FloatLiteralNode(double val) : ASTNode(NodeType::FLOAT_LITERAL), value(val) {}
    void print(int indent = 0) override;
};

class StringLiteralNode : public ASTNode {
public:
    std::string value;
    StringLiteralNode(const std::string& val) : ASTNode(NodeType::STRING_LITERAL), value(val) {}
    void print(int indent = 0) override;
};

class BoolLiteralNode : public ASTNode {
public:
    bool value;
    BoolLiteralNode(bool val) : ASTNode(NodeType::BOOL_LITERAL), value(val) {}
    void print(int indent = 0) override;
};

// Identifier
class IdentifierNode : public ASTNode {
public:
    std::string name;
    IdentifierNode(const std::string& n) : ASTNode(NodeType::IDENTIFIER), name(n) {}
    void print(int indent = 0) override;
};

// Binary operator
class BinaryOpNode : public ASTNode {
public:
    std::string op;
    ASTNode* left;
    ASTNode* right;
    
    BinaryOpNode(const std::string& o, ASTNode* l, ASTNode* r) 
        : ASTNode(NodeType::BINARY_OP), op(o), left(l), right(r) {}
    ~BinaryOpNode() { delete left; delete right; }
    void print(int indent = 0) override;
};

// Unary operator
class UnaryOpNode : public ASTNode {
public:
    std::string op;
    ASTNode* operand;
    
    UnaryOpNode(const std::string& o, ASTNode* operand) 
        : ASTNode(NodeType::UNARY_OP), op(o), operand(operand) {}
    ~UnaryOpNode() { delete operand; }
    void print(int indent = 0) override;
};

// Type node
class TypeNode : public ASTNode {
public:
    std::string type_name;
    TypeNode(const std::string& name) : ASTNode(NodeType::TYPE), type_name(name) {}
    void print(int indent = 0) override;
};

// Parameter node
class ParameterNode : public ASTNode {
public:
    std::string name;
    TypeNode* param_type;
    
    ParameterNode(const std::string& n, TypeNode* t) 
        : ASTNode(NodeType::PARAMETER), name(n), param_type(t) {}
    ~ParameterNode() { delete param_type; }
    void print(int indent = 0) override;
};

// Function declaration
class FunctionNode : public ASTNode {
public:
    std::string name;
    std::vector<ParameterNode*> parameters;
    TypeNode* return_type;
    ASTNode* body;
    bool is_context_function;
    std::string docstring;  // for context functions
    
    FunctionNode(const std::string& n, TypeNode* ret_type, ASTNode* b, bool is_context = false) 
        : ASTNode(is_context ? NodeType::CONTEXT_FUNCTION_DECL : NodeType::FUNCTION_DECL),
          name(n), return_type(ret_type), body(b), is_context_function(is_context) {}
    
    ~FunctionNode() {
        for (auto p : parameters) delete p;
        delete return_type;
        delete body;
    }
    
    void print(int indent = 0) override;
};

// Variable declaration
class VariableNode : public ASTNode {
public:
    std::string name;
    TypeNode* var_type;
    ASTNode* initializer;
    
    VariableNode(const std::string& n, TypeNode* t, ASTNode* init) 
        : ASTNode(NodeType::VARIABLE_DECL), name(n), var_type(t), initializer(init) {}
    
    ~VariableNode() {
        delete var_type;
        delete initializer;
    }
    
    void print(int indent = 0) override;
};

// Assignment
class AssignmentNode : public ASTNode {
public:
    ASTNode* target;
    ASTNode* value;
    
    AssignmentNode(ASTNode* t, ASTNode* v) 
        : ASTNode(NodeType::ASSIGNMENT), target(t), value(v) {}
    
    ~AssignmentNode() { 
        delete target;
        delete value; 
    }
    void print(int indent = 0) override;
};

// Compound Assignment
class CompoundAssignmentNode : public ASTNode {
public:
    ASTNode* target;
    std::string op;
    ASTNode* value;
    
    CompoundAssignmentNode(ASTNode* t, const std::string& o, ASTNode* v) 
        : ASTNode(NodeType::COMPOUND_ASSIGNMENT), target(t), op(o), value(v) {}
        
    ~CompoundAssignmentNode() {
        delete target;
        delete value;
    }
    void print(int indent = 0) override;
};

// If statement
class IfNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* then_branch;
    ASTNode* else_branch;
    
    IfNode(ASTNode* cond, ASTNode* then_b, ASTNode* else_b) 
        : ASTNode(NodeType::IF_STATEMENT), 
          condition(cond), then_branch(then_b), else_branch(else_b) {}
    
    ~IfNode() {
        delete condition;
        delete then_branch;
        delete else_branch;
    }
    
    void print(int indent = 0) override;
};

// While statement
class WhileNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* body;
    
    WhileNode(ASTNode* cond, ASTNode* b) 
        : ASTNode(NodeType::WHILE_STATEMENT), condition(cond), body(b) {}
    
    ~WhileNode() {
        delete condition;
        delete body;
    }
    
    void print(int indent = 0) override;
};

// Return statement
class ReturnNode : public ASTNode {
public:
    ASTNode* value;
    
    ReturnNode(ASTNode* v) : ASTNode(NodeType::RETURN_STATEMENT), value(v) {}
    ~ReturnNode() { delete value; }
    void print(int indent = 0) override;
};

// For statement
class ForNode : public ASTNode {
public:
    std::string variable_name;
    ASTNode* iterable;
    ASTNode* body;
    
    ForNode(const std::string& var, ASTNode* iter, ASTNode* b) 
        : ASTNode(NodeType::FOR_STATEMENT), variable_name(var), iterable(iter), body(b) {}
    
    ~ForNode() {
        delete iterable;
        delete body;
    }
    
    void print(int indent = 0) override;
};

// C-style For statement
class CStyleForNode : public ASTNode {
public:
    ASTNode* init;      // Initialization (var decl or assignment)
    ASTNode* condition; // Loop condition
    ASTNode* update;    // Update statement
    ASTNode* body;      // Loop body
    
    CStyleForNode(ASTNode* i, ASTNode* c, ASTNode* u, ASTNode* b) 
        : ASTNode(NodeType::C_STYLE_FOR_STATEMENT), init(i), condition(c), update(u), body(b) {}
    
    ~CStyleForNode() {
        if (init) delete init;
        if (condition) delete condition;
        if (update) delete update;
        if (body) delete body;
    }
    
    void print(int indent = 0) override;
};



// Class Declaration
class ClassNode : public ASTNode {
public:
    std::string name;
    std::vector<ASTNode*> members; // Variables and Functions
    
    ClassNode(const std::string& n, std::vector<ASTNode*> m) 
        : ASTNode(NodeType::CLASS_DECL), name(n), members(m) {}
    
    ~ClassNode() {
        for (auto member : members) delete member;
    }
    
    void print(int indent = 0) override;
};

// New Expression (Allocation)
class NewNode : public ASTNode {
public:
    std::string class_name;
    std::vector<ASTNode*> arguments;
    
    NewNode(const std::string& name, std::vector<ASTNode*> args)
        : ASTNode(NodeType::NEW_EXPR), class_name(name), arguments(args) {}
        
    ~NewNode() {
        for (auto arg : arguments) delete arg;
    }
    
    void print(int indent = 0) override;
};

// Member Access (obj.member)
class MemberAccessNode : public ASTNode {
public:
    ASTNode* object;
    std::string member_name;
    
    MemberAccessNode(ASTNode* obj, const std::string& member)
        : ASTNode(NodeType::MEMBER_ACCESS), object(obj), member_name(member) {}
        
    ~MemberAccessNode() { delete object; }
    void print(int indent = 0) override;
};

// Subscript (obj[index])
class SubscriptNode : public ASTNode {
public:
    ASTNode* object;
    ASTNode* index;
    
    SubscriptNode(ASTNode* obj, ASTNode* idx)
        : ASTNode(NodeType::SUBSCRIPT), object(obj), index(idx) {}
        
    ~SubscriptNode() { 
        delete object;
        delete index;
    }
    void print(int indent = 0) override;
};

// Function call
class FunctionCallNode : public ASTNode {
public:
    std::string function_name;
    std::vector<ASTNode*> arguments;
    
    FunctionCallNode(const std::string& name) 
        : ASTNode(NodeType::FUNCTION_CALL), function_name(name) {}
    
    ~FunctionCallNode() {
        for (auto arg : arguments) delete arg;
    }
    
    void print(int indent = 0) override;
};

// LLM call (AI-specific)
class LLMCallNode : public ASTNode {
public:
    std::string method;  // "complete", "generate", etc.
    std::vector<ASTNode*> arguments;
    
    LLMCallNode(const std::string& m) 
        : ASTNode(NodeType::LLM_CALL), method(m) {}
    
    ~LLMCallNode() {
        for (auto arg : arguments) delete arg;
    }
    
    void print(int indent = 0) override;
};

// AI Operator Nodes
class AIAskNode : public ASTNode {
public:
    ASTNode* question;  // The question/prompt expression
    
    AIAskNode(ASTNode* q) 
        : ASTNode(NodeType::AI_ASK), question(q) {}
    
    ~AIAskNode() { delete question; }
    void print(int indent = 0) override;
};

class AIGenerateNode : public ASTNode {
public:
    ASTNode* prompt;  // The generation prompt
    
    AIGenerateNode(ASTNode* p) 
        : ASTNode(NodeType::AI_GENERATE), prompt(p) {}
    
    ~AIGenerateNode() { delete prompt; }
    void print(int indent = 0) override;
};

class AIAnalyzeNode : public ASTNode {
public:
    ASTNode* text;  // The text to analyze
    
    AIAnalyzeNode(ASTNode* t) 
        : ASTNode(NodeType::AI_ANALYZE), text(t) {}
    
    ~AIAnalyzeNode() { delete text; }
    void print(int indent = 0) override;
};

class AIEmbedNode : public ASTNode {
public:
    ASTNode* text;  // The text to embed
    
    AIEmbedNode(ASTNode* t) 
        : ASTNode(NodeType::AI_EMBED), text(t) {}
    
    ~AIEmbedNode() { delete text; }
    void print(int indent = 0) override;
};

class AIClassifyNode : public ASTNode {
public:
    ASTNode* text;  // The text to classify
    
    AIClassifyNode(ASTNode* t) 
        : ASTNode(NodeType::AI_CLASSIFY), text(t) {}
    
    ~AIClassifyNode() { delete text; }
    void print(int indent = 0) override;
};

// Statement list
class StatementListNode : public ASTNode {
public:
    std::vector<ASTNode*> statements;
    
    StatementListNode() : ASTNode(NodeType::STATEMENT_LIST) {}
    
    ~StatementListNode() {
        for (auto stmt : statements) delete stmt;
    }
    
    void print(int indent = 0) override;
};

} // namespace lazya

// C interface for Bison
extern "C" {
    typedef lazya::ASTNode ASTNode;
    
    // Node creation functions
    ASTNode* create_int_literal_node(int value);
    ASTNode* create_float_literal_node(double value);
    ASTNode* create_string_literal_node(const char* value);
    ASTNode* create_bool_literal_node(int value);
    ASTNode* create_null_literal_node();
    
    ASTNode* create_identifier_node(const char* name);
    
    ASTNode* create_binary_op_node(const char* op, ASTNode* left, ASTNode* right);
    ASTNode* create_unary_op_node(const char* op, ASTNode* operand);
    
    ASTNode* create_type_node(const char* type_name);
    ASTNode* create_array_type_node(ASTNode* element_type);
    ASTNode* create_optional_type_node(ASTNode* base_type);
    ASTNode* create_union_type_node(ASTNode* left, ASTNode* right);
    
    ASTNode* create_parameter_node(const char* name, ASTNode* type);
    ASTNode* create_parameter_list(ASTNode* param);
    ASTNode* append_parameter(ASTNode* list, ASTNode* param);
    
    ASTNode* create_function_node(const char* name, ASTNode* params, ASTNode* return_type, 
                                   ASTNode* body, int is_context);
    void set_function_docstring(ASTNode* func, const char* docstring);
    ASTNode* create_class_node(const char* name, ASTNode* members_list);
    
    ASTNode* create_variable_node(const char* name, ASTNode* type, ASTNode* initializer);
    ASTNode* create_assignment_node(ASTNode* target, ASTNode* value);
    ASTNode* create_compound_assignment_node(ASTNode* target, const char* op, ASTNode* value);
    
    ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
    ASTNode* create_while_node(ASTNode* condition, ASTNode* body);
    ASTNode* create_for_node(const char* var, ASTNode* iterable, ASTNode* body);
    
    ASTNode* create_return_node(ASTNode* value);
    ASTNode* create_break_node();
    ASTNode* create_continue_node();
    
    ASTNode* create_function_call_node(const char* name, ASTNode* args);
    ASTNode* create_function_call_node(const char* name, ASTNode* args);
    ASTNode* create_llm_call_node(const char* method, ASTNode* args);
    ASTNode* create_member_access_node(ASTNode* object, const char* member);
    ASTNode* create_subscript_node(ASTNode* object, ASTNode* index);
    
    ASTNode* create_new_node(const char* class_name, ASTNode* args);
    ASTNode* create_embed_call_node(ASTNode* arg);
    
    // AI Operator Node creation functions
    ASTNode* create_ai_ask_node(ASTNode* question);
    ASTNode* create_ai_generate_node(ASTNode* prompt);
    ASTNode* create_ai_analyze_node(ASTNode* text);
    ASTNode* create_ai_embed_node(ASTNode* text);
    ASTNode* create_ai_classify_node(ASTNode* text);
    
    ASTNode* create_argument_list(ASTNode* arg);
    ASTNode* append_argument(ASTNode* list, ASTNode* arg);
    
    ASTNode* create_member_access_node(ASTNode* object, const char* member);
    ASTNode* create_subscript_node(ASTNode* object, ASTNode* index);
    
    ASTNode* create_array_literal_node(ASTNode* elements);
    ASTNode* create_dict_literal_node(ASTNode* pairs);
    
    ASTNode* create_statement_list(ASTNode* stmt);
    ASTNode* append_statement(ASTNode* list, ASTNode* stmt);
    ASTNode* create_empty_statement();
    
    ASTNode* create_decorator_node(const char* name);
    
    void print_ast(ASTNode* node);
}

#endif // LAZYA_AST_H
