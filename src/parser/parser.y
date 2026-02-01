%{
/*
 * LazyA Parser - Bison Specification
 * Builds Abstract Syntax Tree from tokens
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declaration - actual definition in ast.cpp */
typedef struct ASTNode ASTNode;

extern int yylex();
extern int yylineno;
extern FILE* yyin;

void yyerror(const char* s);

/* Forward declarations for AST creation functions (defined in ast.cpp) */
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
ASTNode* create_variable_node(const char* name, ASTNode* type, ASTNode* initializer);
ASTNode* create_assignment_node(const char* target, ASTNode* value);
ASTNode* create_compound_assignment_node(const char* target, const char* op, ASTNode* value);
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
ASTNode* create_while_node(ASTNode* condition, ASTNode* body);
ASTNode* create_for_node(const char* var, ASTNode* iterable, ASTNode* body);
ASTNode* create_c_style_for_node(ASTNode* init, ASTNode* condition, ASTNode* update, ASTNode* body);
ASTNode* create_class_node(const char* name, ASTNode* members_list);
ASTNode* create_member_access_node(ASTNode* object, const char* member);
ASTNode* create_subscript_node(ASTNode* object, ASTNode* index);
ASTNode* create_new_node(const char* class_name, ASTNode* args);
ASTNode* create_return_node(ASTNode* value);
ASTNode* create_break_node();
ASTNode* create_continue_node();
ASTNode* create_function_call_node(const char* name, ASTNode* args);
ASTNode* create_llm_call_node(const char* method, ASTNode* args);
ASTNode* create_embed_call_node(ASTNode* arg);
/* AI Operator Nodes */
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
/* Match expression nodes */
ASTNode* create_match_node(ASTNode* value, ASTNode* arms);
ASTNode* create_match_arm_node(ASTNode* pattern, ASTNode* body, int is_semantic);
ASTNode* create_wildcard_node();

// Root of the AST
ASTNode* root;
%}

%union {
    int int_val;
    double float_val;
    char* string_val;
    void* node;  /* Changed from ASTNode* to void* for C compatibility */
}

/* Keywords */
%token FUNC RETURN IF ELSE WHILE FOR FOREACH IN RANGE BREAK CONTINUE LET AUTO MATCH
%token TRUE FALSE NULL_KW CLASS NEW THIS
%token IMPORT FROM TRY CATCH FINALLY THROW
%token ANY INT_TYPE FLOAT_TYPE STRING_TYPE BOOL_TYPE

/* AI Keywords */
%token CONTEXT_DECORATOR CACHED_DECORATOR INLINE_DECORATOR
%token LLM EMBED THRESHOLD

/* AI Operators */
%token AI_ASK AI_GENERATE AI_ANALYZE AI_EMBED AI_CLASSIFY

/* AI Types */
%token PROMPT_TYPE AIRESPONSE_TYPE MODEL_TYPE

/* Operators */
%token SEMANTIC_EQ SEMANTIC_IMPLIES
%token PLUS MINUS STAR SLASH PERCENT POWER
%token EQ NE LT GT LE GE
%token AND OR NOT
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN

/* Bitwise operators */
%token AMPERSAND PIPE CARET LSHIFT RSHIFT TILDE

/* Delimiters */
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token COMMA COLON SEMICOLON DOT DOTDOT ARROW FATARROW QUESTION UNDERSCORE

/* Literals and identifiers */
%token <int_val> INT_LITERAL
%token <float_val> FLOAT_LITERAL
%token <string_val> STRING_LITERAL IDENTIFIER NAMESPACE_ID

/* Non-terminals */
%type <node> program statement_list statement
%type <node> import_statement
%type <node> function_declaration context_function_declaration
%type <node> parameter_list parameter
%type <node> type_annotation optional_type_annotation
%type <node> block statement_block
%type <node> expression literal
%type <node> if_statement while_statement for_statement
%type <node> return_statement break_statement continue_statement
%type <node> variable_declaration variable_decl_base assignment assignment_base
%type <node> function_call argument_list
%type <node> binary_expr unary_expr primary_expr
%type <node> array_literal dict_literal
%type <node> decorator_list decorator
%type <node> class_declaration class_body class_member_list class_member
%type <node> lvalue
%type <node> match_expr match_arms match_arm match_pattern

/* Operator precedence (lowest to highest) */
%left OR
%left AND
%left PIPE              /* bitwise OR */
%left CARET             /* bitwise XOR */
%left AMPERSAND         /* bitwise AND */
%left SEMANTIC_EQ SEMANTIC_IMPLIES
%left EQ NE
%left LT GT LE GE
%left LSHIFT RSHIFT     /* bit shifts */
%left PLUS MINUS
%left STAR SLASH PERCENT
%right POWER
%right NOT TILDE        /* unary operators */
%left DOT LBRACKET

%start program

%%

program
    : statement_list { root = $1; }
    ;

statement_list
    : statement { $$ = create_statement_list($1); }
    | statement_list statement { $$ = append_statement($1, $2); }
    ;

statement
    : import_statement
    | function_declaration
    | context_function_declaration
    | variable_declaration
    | assignment
    | if_statement
    | while_statement
    | for_statement
    | return_statement
    | break_statement
    | continue_statement
    | class_declaration
    | expression SEMICOLON { $$ = $1; }
    | SEMICOLON { $$ = create_empty_statement(); }
    ;

/* Import statements */
import_statement
    : IMPORT IDENTIFIER SEMICOLON {
        // Simple import: import llm;
        $$ = create_empty_statement();  // For now, just parse it
    }
    | IMPORT IDENTIFIER FROM STRING_LITERAL SEMICOLON {
        // Named import: import llm from "module";
        $$ = create_empty_statement();
    }
    ;

/* Class Declarations */
class_declaration
    : CLASS IDENTIFIER LBRACE class_body RBRACE {
        $$ = create_class_node($2, $4);
    }
    ;

class_body
    : /* empty */ { $$ = NULL; }
    | class_member_list { $$ = $1; }
    ;

class_member_list
    : class_member { $$ = create_statement_list($1); }
    | class_member_list class_member { $$ = append_statement($1, $2); }
    ;

class_member
    : variable_declaration
    | function_declaration
    ;

/* Function declarations */
function_declaration
    : FUNC IDENTIFIER LPAREN parameter_list RPAREN optional_type_annotation block {
        $$ = create_function_node($2, $4, $6, $7, 0);
    }
    | FUNC IDENTIFIER LPAREN RPAREN optional_type_annotation block {
        $$ = create_function_node($2, NULL, $5, $6, 0);
    }
    ;

context_function_declaration
    : decorator_list FUNC IDENTIFIER LPAREN parameter_list RPAREN optional_type_annotation LBRACE STRING_LITERAL RBRACE {
        $$ = create_function_node($3, $5, $7, NULL, 1);
        set_function_docstring($$, $9);
    }
    | CONTEXT_DECORATOR FUNC IDENTIFIER LPAREN parameter_list RPAREN optional_type_annotation LBRACE STRING_LITERAL RBRACE {
        $$ = create_function_node($3, $5, $7, NULL, 1);
        set_function_docstring($$, $9);
    }
    ;

decorator_list
    : decorator
    | decorator_list decorator
    ;

decorator
    : CONTEXT_DECORATOR { $$ = create_decorator_node("context"); }
    | CACHED_DECORATOR { $$ = create_decorator_node("cached"); }
    | INLINE_DECORATOR { $$ = create_decorator_node("inline"); }
    ;

parameter_list
    : parameter { $$ = create_parameter_list($1); }
    | parameter_list COMMA parameter { $$ = append_parameter($1, $3); }
    ;

parameter
    : IDENTIFIER COLON type_annotation {
        $$ = create_parameter_node($1, $3);
    }
    ;

type_annotation
    : IDENTIFIER { $$ = create_type_node($1); }
    | INT_TYPE { $$ = create_type_node("int"); }
    | FLOAT_TYPE { $$ = create_type_node("float"); }
    | STRING_TYPE { $$ = create_type_node("string"); }
    | BOOL_TYPE { $$ = create_type_node("bool"); }
    | ANY { $$ = create_type_node("any"); }
    | PROMPT_TYPE { $$ = create_type_node("prompt"); }
    | AIRESPONSE_TYPE { $$ = create_type_node("airesponse"); }
    | MODEL_TYPE { $$ = create_type_node("model"); }
    | LBRACKET type_annotation RBRACKET { $$ = create_array_type_node($2); }
    | type_annotation QUESTION { $$ = create_optional_type_node($1); }
    | type_annotation PIPE type_annotation { $$ = create_union_type_node($1, $3); }
    ;

optional_type_annotation
    : ARROW type_annotation { $$ = $2; }
    | /* empty */ { $$ = NULL; }
    ;

block
    : LBRACE statement_list RBRACE { $$ = $2; }
    | LBRACE RBRACE { $$ = create_empty_statement(); }
    ;

/* Variable declaration */
variable_decl_base
    : LET IDENTIFIER COLON type_annotation ASSIGN expression {
        $$ = create_variable_node($2, $4, $6);
    }
    | LET IDENTIFIER ASSIGN expression {
        $$ = create_variable_node($2, NULL, $4);
    }
    | AUTO IDENTIFIER ASSIGN expression {
        $$ = create_variable_node($2, create_type_node("auto"), $4);
    }
    ;

variable_declaration
    : variable_decl_base SEMICOLON { $$ = $1; }
    ;

/* Assignment */
lvalue
    : IDENTIFIER { $$ = create_identifier_node($1); }
    | primary_expr DOT IDENTIFIER { $$ = create_member_access_node($1, $3); }
    | primary_expr LBRACKET expression RBRACKET { $$ = create_subscript_node($1, $3); }
    ;

assignment_base
    : lvalue ASSIGN expression {
        $$ = create_assignment_node($1, $3);
    }
    | lvalue PLUS_ASSIGN expression {
        $$ = create_compound_assignment_node($1, "+=", $3);
    }
    | lvalue MINUS_ASSIGN expression {
        $$ = create_compound_assignment_node($1, "-=", $3);
    }
    ;

assignment
    : assignment_base SEMICOLON { $$ = $1; }
    ;

/* Control flow */
if_statement
    : IF expression block {
        $$ = create_if_node($2, $3, NULL);
    }
    | IF expression block ELSE block {
        $$ = create_if_node($2, $3, $5);
    }
    | IF expression block ELSE if_statement {
        $$ = create_if_node($2, $3, $5);
    }
    ;

while_statement
    : WHILE expression block {
        $$ = create_while_node($2, $3);
    }
    ;

for_statement
    : FOR IDENTIFIER IN expression block {
        $$ = create_for_node($2, $4, $5);
    }
    | FOREACH IDENTIFIER IN expression block {
        $$ = create_for_node($2, $4, $5);
    }
    | FOREACH IDENTIFIER IN expression DOTDOT expression block {
        // Syntactic sugar: create range node from e1..e2
        ASTNode* range = create_binary_op_node("..", $4, $6);
        $$ = create_for_node($2, range, $7);
    }
    /* C-style For Loops */
    | FOR LPAREN variable_decl_base SEMICOLON expression SEMICOLON assignment_base RPAREN block {
        $$ = create_c_style_for_node($3, $5, $7, $9);
    }
    | FOR LPAREN assignment_base SEMICOLON expression SEMICOLON assignment_base RPAREN block {
        $$ = create_c_style_for_node($3, $5, $7, $9);
    }
    | FOR LPAREN SEMICOLON expression SEMICOLON assignment_base RPAREN block {
        $$ = create_c_style_for_node(NULL, $4, $6, $8);
    }
    | FOR LPAREN variable_decl_base SEMICOLON expression SEMICOLON RPAREN block {
        $$ = create_c_style_for_node($3, $5, NULL, $8);
    }
    ;

return_statement
    : RETURN expression SEMICOLON {
        $$ = create_return_node($2);
    }
    | RETURN SEMICOLON {
        $$ = create_return_node(NULL);
    }
    ;

break_statement
    : BREAK SEMICOLON { $$ = create_break_node(); }
    ;

continue_statement
    : CONTINUE SEMICOLON { $$ = create_continue_node(); }
    ;

/* Expressions */
expression
    : binary_expr
    | unary_expr
    | primary_expr
    ;

binary_expr
    : expression PLUS expression { $$ = create_binary_op_node("+", $1, $3); }
    | expression MINUS expression { $$ = create_binary_op_node("-", $1, $3); }
    | expression STAR expression { $$ = create_binary_op_node("*", $1, $3); }
    | expression SLASH expression { $$ = create_binary_op_node("/", $1, $3); }
    | expression PERCENT expression { $$ = create_binary_op_node("%", $1, $3); }
    | expression POWER expression { $$ = create_binary_op_node("**", $1, $3); }
    | expression EQ expression { $$ = create_binary_op_node("==", $1, $3); }
    | expression NE expression { $$ = create_binary_op_node("!=", $1, $3); }
    | expression LT expression { $$ = create_binary_op_node("<", $1, $3); }
    | expression GT expression { $$ = create_binary_op_node(">", $1, $3); }
    | expression LE expression { $$ = create_binary_op_node("<=", $1, $3); }
    | expression GE expression { $$ = create_binary_op_node(">=", $1, $3); }
    | expression AND expression { $$ = create_binary_op_node("&&", $1, $3); }
    | expression OR expression { $$ = create_binary_op_node("||", $1, $3); }
    | expression SEMANTIC_EQ expression { $$ = create_binary_op_node("~=", $1, $3); }
    | expression SEMANTIC_IMPLIES expression { $$ = create_binary_op_node("~>", $1, $3); }
    | expression AMPERSAND expression { $$ = create_binary_op_node("&", $1, $3); }
    | expression CARET expression { $$ = create_binary_op_node("^", $1, $3); }
    | expression LSHIFT expression { $$ = create_binary_op_node("<<", $1, $3); }
    | expression RSHIFT expression { $$ = create_binary_op_node(">>", $1, $3); }
    ;

unary_expr
    : NOT expression { $$ = create_unary_op_node("!", $2); }
    | MINUS expression { $$ = create_unary_op_node("-", $2); }
    | TILDE expression { $$ = create_unary_op_node("~", $2); }
    | AI_ASK expression { $$ = create_ai_ask_node($2); }
    | AI_GENERATE expression { $$ = create_ai_generate_node($2); }
    | AI_ANALYZE expression { $$ = create_ai_analyze_node($2); }
    | AI_EMBED expression { $$ = create_ai_embed_node($2); }
    | AI_CLASSIFY expression { $$ = create_ai_classify_node($2); }
    ;

primary_expr
    : literal
    | IDENTIFIER { $$ = create_identifier_node($1); }
    | THIS { $$ = create_identifier_node("this"); }
    | function_call
    | array_literal
    | dict_literal
    | match_expr
    | LPAREN expression RPAREN { $$ = $2; }
    | primary_expr DOT IDENTIFIER { $$ = create_member_access_node($1, $3); }
    | primary_expr LBRACKET expression RBRACKET { $$ = create_subscript_node($1, $3); }
    | NEW IDENTIFIER LPAREN argument_list RPAREN { $$ = create_new_node($2, $4); }
    | NEW IDENTIFIER LPAREN RPAREN { $$ = create_new_node($2, NULL); }
    ;

function_call
    : IDENTIFIER LPAREN argument_list RPAREN {
        $$ = create_function_call_node($1, $3);
    }
    | IDENTIFIER LPAREN RPAREN {
        $$ = create_function_call_node($1, NULL);
    }
    | NAMESPACE_ID LPAREN argument_list RPAREN {
        // namespace.function(args) - parse and create appropriate call
        $$ = create_function_call_node($1, $3);
    }
    | NAMESPACE_ID LPAREN RPAREN {
        // namespace.function() - no args
        $$ = create_function_call_node($1, NULL);
    }
    | LLM DOT IDENTIFIER LPAREN argument_list RPAREN {
        $$ = create_llm_call_node($3, $5);
    }
    | IDENTIFIER DOT IDENTIFIER DOT IDENTIFIER LPAREN argument_list RPAREN {
        char buffer[256];
        sprintf(buffer, "%s.%s.%s", $1, $3, $5);
        $$ = create_function_call_node(buffer, $7);
    }
    | EMBED LPAREN expression RPAREN {
        $$ = create_embed_call_node($3);
    }
    ;

argument_list
    : expression { $$ = create_argument_list($1); }
    | argument_list COMMA expression { $$ = append_argument($1, $3); }
    ;

literal
    : INT_LITERAL { $$ = create_int_literal_node($1); }
    | FLOAT_LITERAL { $$ = create_float_literal_node($1); }
    | STRING_LITERAL { $$ = create_string_literal_node($1); }
    | TRUE { $$ = create_bool_literal_node(1); }
    | FALSE { $$ = create_bool_literal_node(0); }
    | NULL_KW { $$ = create_null_literal_node(); }
    ;

array_literal
    : LBRACKET argument_list RBRACKET {
        $$ = create_array_literal_node($2);
    }
    | LBRACKET RBRACKET {
        $$ = create_array_literal_node(NULL);
    }
    ;

dict_literal
    : LBRACE RBRACE {
        $$ = create_dict_literal_node(NULL);
    }
    ;

/* Match expressions - Semantic pattern matching */
match_expr
    : MATCH expression LBRACE match_arms RBRACE {
        $$ = create_match_node($2, $4);
    }
    ;

match_arms
    : match_arm { $$ = create_statement_list($1); }
    | match_arms match_arm { $$ = append_statement($1, $2); }
    ;

match_arm
    : SEMANTIC_EQ match_pattern FATARROW expression COMMA {
        $$ = create_match_arm_node($2, $4, 1); /* semantic = 1 */
    }
    | match_pattern FATARROW expression COMMA {
        $$ = create_match_arm_node($1, $3, 0); /* literal = 0 */
    }
    | SEMANTIC_EQ match_pattern FATARROW expression {
        $$ = create_match_arm_node($2, $4, 1); /* last arm without comma */
    }
    | match_pattern FATARROW expression {
        $$ = create_match_arm_node($1, $3, 0); /* last arm without comma */
    }
    ;

match_pattern
    : UNDERSCORE { $$ = create_wildcard_node(); }
    | literal { $$ = $1; }
    | IDENTIFIER { $$ = create_identifier_node($1); }
    ;

%%

extern FILE *yyin;
extern int yylineno;
ASTNode* root = NULL; // Global root AST node

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}

