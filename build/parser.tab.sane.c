/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./src/parser/parser.y"

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

#line 151 "./build/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FUNC = 3,                       /* FUNC  */
  YYSYMBOL_RETURN = 4,                     /* RETURN  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_FOR = 8,                        /* FOR  */
  YYSYMBOL_FOREACH = 9,                    /* FOREACH  */
  YYSYMBOL_IN = 10,                        /* IN  */
  YYSYMBOL_RANGE = 11,                     /* RANGE  */
  YYSYMBOL_BREAK = 12,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_LET = 14,                       /* LET  */
  YYSYMBOL_AUTO = 15,                      /* AUTO  */
  YYSYMBOL_MATCH = 16,                     /* MATCH  */
  YYSYMBOL_TRUE = 17,                      /* TRUE  */
  YYSYMBOL_FALSE = 18,                     /* FALSE  */
  YYSYMBOL_NULL_KW = 19,                   /* NULL_KW  */
  YYSYMBOL_CLASS = 20,                     /* CLASS  */
  YYSYMBOL_NEW = 21,                       /* NEW  */
  YYSYMBOL_THIS = 22,                      /* THIS  */
  YYSYMBOL_IMPORT = 23,                    /* IMPORT  */
  YYSYMBOL_FROM = 24,                      /* FROM  */
  YYSYMBOL_TRY = 25,                       /* TRY  */
  YYSYMBOL_CATCH = 26,                     /* CATCH  */
  YYSYMBOL_FINALLY = 27,                   /* FINALLY  */
  YYSYMBOL_THROW = 28,                     /* THROW  */
  YYSYMBOL_ANY = 29,                       /* ANY  */
  YYSYMBOL_INT_TYPE = 30,                  /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 31,                /* FLOAT_TYPE  */
  YYSYMBOL_STRING_TYPE = 32,               /* STRING_TYPE  */
  YYSYMBOL_BOOL_TYPE = 33,                 /* BOOL_TYPE  */
  YYSYMBOL_CONTEXT_DECORATOR = 34,         /* CONTEXT_DECORATOR  */
  YYSYMBOL_CACHED_DECORATOR = 35,          /* CACHED_DECORATOR  */
  YYSYMBOL_INLINE_DECORATOR = 36,          /* INLINE_DECORATOR  */
  YYSYMBOL_LLM = 37,                       /* LLM  */
  YYSYMBOL_EMBED = 38,                     /* EMBED  */
  YYSYMBOL_THRESHOLD = 39,                 /* THRESHOLD  */
  YYSYMBOL_AI_ASK = 40,                    /* AI_ASK  */
  YYSYMBOL_AI_GENERATE = 41,               /* AI_GENERATE  */
  YYSYMBOL_AI_ANALYZE = 42,                /* AI_ANALYZE  */
  YYSYMBOL_AI_EMBED = 43,                  /* AI_EMBED  */
  YYSYMBOL_AI_CLASSIFY = 44,               /* AI_CLASSIFY  */
  YYSYMBOL_PROMPT_TYPE = 45,               /* PROMPT_TYPE  */
  YYSYMBOL_AIRESPONSE_TYPE = 46,           /* AIRESPONSE_TYPE  */
  YYSYMBOL_MODEL_TYPE = 47,                /* MODEL_TYPE  */
  YYSYMBOL_SEMANTIC_EQ = 48,               /* SEMANTIC_EQ  */
  YYSYMBOL_SEMANTIC_IMPLIES = 49,          /* SEMANTIC_IMPLIES  */
  YYSYMBOL_PLUS = 50,                      /* PLUS  */
  YYSYMBOL_MINUS = 51,                     /* MINUS  */
  YYSYMBOL_STAR = 52,                      /* STAR  */
  YYSYMBOL_SLASH = 53,                     /* SLASH  */
  YYSYMBOL_PERCENT = 54,                   /* PERCENT  */
  YYSYMBOL_POWER = 55,                     /* POWER  */
  YYSYMBOL_EQ = 56,                        /* EQ  */
  YYSYMBOL_NE = 57,                        /* NE  */
  YYSYMBOL_LT = 58,                        /* LT  */
  YYSYMBOL_GT = 59,                        /* GT  */
  YYSYMBOL_LE = 60,                        /* LE  */
  YYSYMBOL_GE = 61,                        /* GE  */
  YYSYMBOL_AND = 62,                       /* AND  */
  YYSYMBOL_OR = 63,                        /* OR  */
  YYSYMBOL_NOT = 64,                       /* NOT  */
  YYSYMBOL_ASSIGN = 65,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 66,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 67,              /* MINUS_ASSIGN  */
  YYSYMBOL_STAR_ASSIGN = 68,               /* STAR_ASSIGN  */
  YYSYMBOL_SLASH_ASSIGN = 69,              /* SLASH_ASSIGN  */
  YYSYMBOL_AMPERSAND = 70,                 /* AMPERSAND  */
  YYSYMBOL_PIPE = 71,                      /* PIPE  */
  YYSYMBOL_CARET = 72,                     /* CARET  */
  YYSYMBOL_LSHIFT = 73,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 74,                    /* RSHIFT  */
  YYSYMBOL_TILDE = 75,                     /* TILDE  */
  YYSYMBOL_LPAREN = 76,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 77,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 78,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 79,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 80,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 81,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 82,                     /* COMMA  */
  YYSYMBOL_COLON = 83,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 84,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 85,                       /* DOT  */
  YYSYMBOL_DOTDOT = 86,                    /* DOTDOT  */
  YYSYMBOL_ARROW = 87,                     /* ARROW  */
  YYSYMBOL_FATARROW = 88,                  /* FATARROW  */
  YYSYMBOL_QUESTION = 89,                  /* QUESTION  */
  YYSYMBOL_UNDERSCORE = 90,                /* UNDERSCORE  */
  YYSYMBOL_INT_LITERAL = 91,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 92,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 93,            /* STRING_LITERAL  */
  YYSYMBOL_IDENTIFIER = 94,                /* IDENTIFIER  */
  YYSYMBOL_NAMESPACE_ID = 95,              /* NAMESPACE_ID  */
  YYSYMBOL_YYACCEPT = 96,                  /* $accept  */
  YYSYMBOL_program = 97,                   /* program  */
  YYSYMBOL_statement_list = 98,            /* statement_list  */
  YYSYMBOL_statement = 99,                 /* statement  */
  YYSYMBOL_import_statement = 100,         /* import_statement  */
  YYSYMBOL_class_declaration = 101,        /* class_declaration  */
  YYSYMBOL_class_body = 102,               /* class_body  */
  YYSYMBOL_class_member_list = 103,        /* class_member_list  */
  YYSYMBOL_class_member = 104,             /* class_member  */
  YYSYMBOL_function_declaration = 105,     /* function_declaration  */
  YYSYMBOL_context_function_declaration = 106, /* context_function_declaration  */
  YYSYMBOL_decorator_list = 107,           /* decorator_list  */
  YYSYMBOL_decorator = 108,                /* decorator  */
  YYSYMBOL_parameter_list = 109,           /* parameter_list  */
  YYSYMBOL_parameter = 110,                /* parameter  */
  YYSYMBOL_type_annotation = 111,          /* type_annotation  */
  YYSYMBOL_optional_type_annotation = 112, /* optional_type_annotation  */
  YYSYMBOL_block = 113,                    /* block  */
  YYSYMBOL_variable_decl_base = 114,       /* variable_decl_base  */
  YYSYMBOL_variable_declaration = 115,     /* variable_declaration  */
  YYSYMBOL_lvalue = 116,                   /* lvalue  */
  YYSYMBOL_assignment_base = 117,          /* assignment_base  */
  YYSYMBOL_assignment = 118,               /* assignment  */
  YYSYMBOL_if_statement = 119,             /* if_statement  */
  YYSYMBOL_while_statement = 120,          /* while_statement  */
  YYSYMBOL_for_statement = 121,            /* for_statement  */
  YYSYMBOL_return_statement = 122,         /* return_statement  */
  YYSYMBOL_break_statement = 123,          /* break_statement  */
  YYSYMBOL_continue_statement = 124,       /* continue_statement  */
  YYSYMBOL_expression = 125,               /* expression  */
  YYSYMBOL_binary_expr = 126,              /* binary_expr  */
  YYSYMBOL_unary_expr = 127,               /* unary_expr  */
  YYSYMBOL_primary_expr = 128,             /* primary_expr  */
  YYSYMBOL_function_call = 129,            /* function_call  */
  YYSYMBOL_argument_list = 130,            /* argument_list  */
  YYSYMBOL_literal = 131,                  /* literal  */
  YYSYMBOL_array_literal = 132,            /* array_literal  */
  YYSYMBOL_dict_literal = 133,             /* dict_literal  */
  YYSYMBOL_match_expr = 134,               /* match_expr  */
  YYSYMBOL_match_arms = 135,               /* match_arms  */
  YYSYMBOL_match_arm = 136,                /* match_arm  */
  YYSYMBOL_match_pattern = 137             /* match_pattern  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  107
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1591

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  152
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  323

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   350


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   163,   163,   167,   168,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   190,
     194,   202,   208,   209,   213,   214,   218,   219,   224,   227,
     233,   237,   244,   245,   249,   250,   251,   255,   256,   260,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   281,   282,   286,   287,   292,   295,   298,   304,
     309,   310,   311,   315,   318,   321,   327,   332,   335,   338,
     344,   350,   353,   356,   362,   365,   368,   371,   377,   380,
     386,   390,   395,   396,   397,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   424,   425,   426,   427,   428,
     429,   430,   431,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   450,   453,   456,   460,   464,
     467,   472,   478,   479,   483,   484,   485,   486,   487,   488,
     492,   495,   501,   508,   514,   515,   519,   522,   525,   528,
     534,   535,   536
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FUNC", "RETURN", "IF",
  "ELSE", "WHILE", "FOR", "FOREACH", "IN", "RANGE", "BREAK", "CONTINUE",
  "LET", "AUTO", "MATCH", "TRUE", "FALSE", "NULL_KW", "CLASS", "NEW",
  "THIS", "IMPORT", "FROM", "TRY", "CATCH", "FINALLY", "THROW", "ANY",
  "INT_TYPE", "FLOAT_TYPE", "STRING_TYPE", "BOOL_TYPE",
  "CONTEXT_DECORATOR", "CACHED_DECORATOR", "INLINE_DECORATOR", "LLM",
  "EMBED", "THRESHOLD", "AI_ASK", "AI_GENERATE", "AI_ANALYZE", "AI_EMBED",
  "AI_CLASSIFY", "PROMPT_TYPE", "AIRESPONSE_TYPE", "MODEL_TYPE",
  "SEMANTIC_EQ", "SEMANTIC_IMPLIES", "PLUS", "MINUS", "STAR", "SLASH",
  "PERCENT", "POWER", "EQ", "NE", "LT", "GT", "LE", "GE", "AND", "OR",
  "NOT", "ASSIGN", "PLUS_ASSIGN", "MINUS_ASSIGN", "STAR_ASSIGN",
  "SLASH_ASSIGN", "AMPERSAND", "PIPE", "CARET", "LSHIFT", "RSHIFT",
  "TILDE", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
  "COMMA", "COLON", "SEMICOLON", "DOT", "DOTDOT", "ARROW", "FATARROW",
  "QUESTION", "UNDERSCORE", "INT_LITERAL", "FLOAT_LITERAL",
  "STRING_LITERAL", "IDENTIFIER", "NAMESPACE_ID", "$accept", "program",
  "statement_list", "statement", "import_statement", "class_declaration",
  "class_body", "class_member_list", "class_member",
  "function_declaration", "context_function_declaration", "decorator_list",
  "decorator", "parameter_list", "parameter", "type_annotation",
  "optional_type_annotation", "block", "variable_decl_base",
  "variable_declaration", "lvalue", "assignment_base", "assignment",
  "if_statement", "while_statement", "for_statement", "return_statement",
  "break_statement", "continue_statement", "expression", "binary_expr",
  "unary_expr", "primary_expr", "function_call", "argument_list",
  "literal", "array_literal", "dict_literal", "match_expr", "match_arms",
  "match_arm", "match_pattern", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-205)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-63)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     472,   -76,   552,   893,   893,   -53,   -31,   -23,   -11,   -20,
     -10,   893,  -205,  -205,  -205,     7,    11,  -205,    18,    77,
    -205,  -205,    65,    78,   893,   893,   893,   893,   893,   893,
     893,   893,   893,    90,   632,  -205,  -205,  -205,  -205,   112,
      80,   183,   472,  -205,  -205,  -205,  -205,  -205,    36,  -205,
     109,  -205,   166,   126,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  1045,  -205,  -205,    19,  -205,  -205,  -205,  -205,  -205,
     116,  -205,    21,  1082,    61,  1368,  1368,   143,   201,   206,
    -205,  -205,    -6,   155,  1399,   144,   150,    -8,   145,   158,
     893,  1490,  1490,  1490,  1490,  1490,   189,  -205,  -205,  1430,
    -205,  -205,  1490,    58,   698,   159,   763,  -205,  -205,   160,
    -205,  -205,  -205,   893,   893,   893,  -205,   893,   893,   893,
     893,   893,   893,   893,   893,   893,   893,   893,   893,   893,
     893,   893,   893,   893,   893,   893,   893,  -205,   893,   161,
     -28,  -205,   893,   164,   286,   222,  -205,   893,   176,   177,
      19,   893,   893,   893,    22,   893,    17,   134,   828,   170,
    -205,   188,   190,  1460,  -205,  -205,   893,  -205,   105,   182,
    -205,   107,   194,  1490,  1490,  1490,   223,   223,   189,   189,
     217,   217,   217,   217,   281,   281,   121,   121,   121,   121,
     527,  1517,   972,   607,   149,   149,  1300,   181,   198,   203,
     108,  -205,  1334,  -205,  -205,   379,     4,  1119,   893,   893,
    1368,  1006,  1490,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,    22,  -205,   -25,  1490,    -5,  -205,  -205,  -205,     2,
    -205,   224,   231,   134,  -205,  -205,  -205,  -205,   114,   227,
     219,   893,  -205,  1490,  -205,   220,  -205,   219,   184,    22,
     237,    22,   198,   219,  -205,  -205,  -205,  -205,   958,  1156,
    1193,  -205,   893,  -205,   -33,   893,    22,  -205,   228,  -205,
    -205,   893,  -205,  -205,  -205,  -205,   135,   136,   241,   147,
     -14,  -205,   -14,   237,  -205,   242,   924,   958,  1368,  -205,
    1490,   229,   893,  1230,   198,  -205,   893,   198,  -205,   237,
     237,   248,   261,  -205,  1265,  -205,   265,   148,   266,  -205,
    -205,   237,   237,  -205,   252,  -205,   253,  -205,  -205,   268,
     269,  -205,  -205
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   137,   138,   139,     0,     0,   115,     0,    34,
      35,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,   134,   135,   136,   114,
       0,     0,     2,     3,     5,    16,     6,     7,     0,    32,
       0,     8,     0,     0,     9,    10,    11,    12,    13,    14,
      15,     0,    82,    83,    84,   116,   113,   117,   118,   119,
       0,    79,   114,     0,    84,     0,     0,     0,     0,     0,
      80,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   106,   105,   107,     0,
     142,   141,   132,     0,     0,     0,     0,     1,     4,     0,
      34,    33,    59,     0,     0,     0,    66,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,    78,     0,     0,     0,    67,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,     0,     0,
      19,     0,     0,     0,   120,   140,     0,   126,     0,     0,
     128,     0,     0,    63,    64,    65,    99,   100,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   101,   102,   103,   104,     0,   121,    53,     0,
       0,    37,     0,   121,    55,     0,     0,     0,     0,     0,
       0,     0,    57,    45,    41,    42,    43,    44,    46,    47,
      48,     0,    40,     0,    58,     0,   150,   152,   151,     0,
     144,     0,     0,    23,    24,    27,    26,   124,     0,     0,
       0,     0,   131,   133,   125,     0,   127,     0,   122,     0,
       0,     0,    53,     0,   122,    54,    68,    69,     0,     0,
       0,    71,     0,    72,     0,     0,     0,    50,     0,   143,
     145,     0,    21,    25,   123,    20,     0,     0,     0,     0,
      52,    29,    39,     0,    38,     0,     0,     0,     0,    49,
      56,    51,     0,   149,    53,   129,     0,    53,    28,     0,
       0,     0,     0,    73,   148,   147,     0,     0,     0,    76,
      77,     0,     0,   146,     0,   130,     0,    74,    75,     0,
       0,    31,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -205,  -205,   205,   -35,  -205,  -205,  -205,  -205,   118,  -142,
    -205,  -205,   304,  -203,   100,  -204,  -194,   -43,   279,  -135,
    -205,   -72,  -205,   151,  -205,  -205,  -205,  -205,  -205,     0,
    -205,  -205,     1,  -205,   -98,  -146,  -205,  -205,  -205,  -205,
     129,   138
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    41,    42,    43,    44,    45,   232,   233,   234,    46,
      47,    48,    49,   200,   201,   223,   250,   145,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   102,
      62,    63,    74,    65,   103,    66,    67,    68,    69,   229,
     230,   231
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    64,    73,    75,    76,   149,   168,   108,   171,     3,
     228,    84,    12,    13,    14,   235,   159,   264,    70,    12,
      13,    14,   236,    77,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   146,    12,    13,    14,   276,   266,   109,
     265,    78,    61,    64,   279,   280,   266,   282,   289,   198,
     225,   213,   214,   215,   216,   217,   267,   266,   283,   153,
     238,    80,   291,    79,   267,   225,   199,   218,   219,   220,
     110,    20,    21,    81,    82,   267,   160,   154,   150,   228,
      88,   269,   144,   228,    83,   226,    36,    37,    38,   227,
     163,   235,   226,    36,    37,    38,   227,   104,   236,   138,
     306,    85,   221,   308,   139,    86,   105,   226,    36,    37,
      38,   227,    87,   173,   174,   175,   222,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,     1,   196,   165,
     166,   142,   202,   277,    61,    64,   143,   207,     9,    10,
      89,   210,   211,   212,    90,   224,   106,     9,    10,    11,
      12,    13,    14,   256,    16,    17,   243,   261,   263,   100,
     108,   119,   120,   121,   122,   123,   124,   -60,   -60,   -60,
      22,    23,   244,   107,   246,   252,   285,   166,   104,   166,
     253,   274,   140,   112,   135,   136,   166,   105,   307,   119,
     120,   121,   122,   123,   124,    61,    64,   281,   259,   260,
     116,   151,   294,   295,   301,   302,   152,   253,   166,    32,
     155,    33,   157,    34,   297,   315,   158,   147,   206,   253,
     166,   113,   114,   115,    36,    37,    38,    39,    40,   161,
     298,   121,   122,   123,   124,   303,   -61,   -61,   -61,   -62,
     -62,   -62,   162,   169,   172,   197,   309,   310,   203,   150,
     208,   209,   288,   239,   240,   290,   241,   245,   317,   318,
     247,   293,   124,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   249,   251,   150,   150,     1,
       2,     3,   304,     4,     5,     6,   135,   136,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
     272,   275,   271,   199,   278,   144,   292,   296,   267,   299,
      19,    20,    21,    22,    23,   311,    24,    25,    26,    27,
      28,   119,   120,   121,   122,   123,   124,    29,   312,   127,
     128,   129,   130,   314,   316,   319,   320,   321,   322,   205,
      30,   273,   111,   284,   135,   136,   148,   257,   270,     0,
       0,    31,    32,   268,    33,   204,    34,     0,     0,     0,
      35,     0,     0,     0,     0,     0,     0,    36,    37,    38,
      39,    40,     1,     2,     3,     0,     4,     5,     6,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,    20,    21,    22,    23,     0,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
      29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,    33,   255,    34,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,    40,     1,     2,     3,     0,     4,
       5,     6,     0,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,    20,    21,    22,
      23,     0,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,     0,    34,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,    36,    37,    38,    39,    40,    11,    12,
      13,    14,     0,    16,    17,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,    22,
      23,     0,    24,    25,    26,    27,    28,   133,     0,   134,
     135,   136,     0,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,     0,    34,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,    36,    37,    38,    72,    40,    11,    12,
      13,    14,     0,    16,    17,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,    22,
      23,     0,    24,    25,    26,    27,    28,   133,     0,     0,
     135,   136,     0,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,     0,    34,   101,    11,    12,    13,    14,     0,    16,
      17,     0,     0,    36,    37,    38,    72,    40,     0,     0,
       0,     0,     0,     0,     0,    22,    23,     0,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,   167,    33,     0,    34,    11,
      12,    13,    14,     0,    16,    17,     0,     0,     0,    36,
      37,    38,    72,    40,     0,     0,     0,     0,     0,     0,
      22,    23,     0,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
     170,    33,     0,    34,    11,    12,    13,    14,     0,    16,
      17,     0,     0,     0,    36,    37,    38,    72,    40,     0,
       0,     0,     0,     0,     0,    22,    23,     0,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,   237,    33,     0,    34,    11,
      12,    13,    14,     0,    16,    17,     0,     0,     0,    36,
      37,    38,    72,    40,     0,     0,     0,     0,     0,     0,
      22,    23,     0,    24,    25,    26,    27,    28,     0,     0,
      11,    12,    13,    14,    29,    16,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,     0,
       0,    22,    23,     0,     0,     0,     0,     0,    31,    32,
       0,    33,     0,    34,    11,    12,    13,    14,     0,    16,
      17,     0,     0,     0,    36,    37,    38,    72,    40,     0,
       0,     0,     0,     0,     0,    22,    23,     0,     0,     0,
      32,   300,    33,     0,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,    39,    40,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,    32,     0,    33,     0,    34,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,    36,
      37,    38,    39,    40,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,     0,     0,   133,     0,   134,   135,
     136,     0,     0,     0,   144,     0,     0,     0,     0,     0,
       0,     0,   262,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,     0,
       0,     0,     0,     0,     0,   133,     0,   134,   135,   136,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
       0,     0,   133,     0,   134,   135,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   141,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,     0,     0,     0,     0,     0,     0,   133,
       0,   134,   135,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   258,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,     0,     0,   133,     0,   134,   135,
     136,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     286,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,     0,     0,     0,
       0,     0,     0,   133,     0,   134,   135,   136,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   287,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,   134,   135,   136,     0,     0,     0,     0,     0,
       0,     0,   305,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,     0,
       0,     0,     0,     0,     0,   133,     0,   134,   135,   136,
       0,     0,     0,     0,     0,     0,     0,   313,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,   134,   135,   136,     0,     0,     0,     0,     0,
       0,   248,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,     0,     0,
       0,     0,     0,     0,   133,     0,   134,   135,   136,     0,
       0,     0,     0,     0,     0,   254,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,     0,     0,     0,     0,     0,     0,   133,     0,
     134,   135,   136,     0,     0,     0,   144,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,     0,     0,     0,     0,     0,     0,   133,
       0,   134,   135,   136,     0,     0,     0,   156,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,   134,   135,   136,     0,     0,   164,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,   134,   135,   136,     0,     0,   242,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,   134,   135,   136,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
       0,     0,     0,     0,     0,     0,     0,   133,     0,   134,
     135,   136
};

static const yytype_int16 yycheck[] =
{
       0,     0,     2,     3,     4,    77,   104,    42,   106,     5,
     156,    11,    17,    18,    19,   157,    24,   221,    94,    17,
      18,    19,   157,    76,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    76,    17,    18,    19,   240,    71,     3,
      65,    94,    42,    42,   247,   249,    71,   251,    81,    77,
      48,    29,    30,    31,    32,    33,    89,    71,   252,    65,
     158,    84,   266,    94,    89,    48,    94,    45,    46,    47,
      34,    35,    36,    84,    94,    89,    84,    83,    77,   225,
       3,    79,    78,   229,    94,    90,    91,    92,    93,    94,
      90,   233,    90,    91,    92,    93,    94,    76,   233,    80,
     294,    94,    80,   297,    85,    94,    85,    90,    91,    92,
      93,    94,    94,   113,   114,   115,    94,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     3,   138,    81,
      82,    80,   142,   241,   144,   144,    85,   147,    14,    15,
      85,   151,   152,   153,    76,   155,    76,    14,    15,    16,
      17,    18,    19,   206,    21,    22,   166,   210,   211,    79,
     205,    50,    51,    52,    53,    54,    55,    65,    66,    67,
      37,    38,    77,     0,    77,    77,   258,    82,    76,    82,
      82,    77,    76,    84,    73,    74,    82,    85,   296,    50,
      51,    52,    53,    54,    55,   205,   205,   250,   208,   209,
      84,    10,    77,    77,   286,   287,    10,    82,    82,    76,
      65,    78,    78,    80,    77,    77,    76,    84,     6,    82,
      82,    65,    66,    67,    91,    92,    93,    94,    95,    94,
     283,    52,    53,    54,    55,   288,    65,    66,    67,    65,
      66,    67,    94,    94,    94,    94,   299,   300,    94,   258,
      84,    84,   262,    93,    76,   265,    76,    85,   311,   312,
      76,   271,    55,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    87,    83,   286,   287,     3,
       4,     5,   292,     7,     8,     9,    73,    74,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      79,    84,    88,    94,    94,    78,    88,    76,    89,    77,
      34,    35,    36,    37,    38,    77,    40,    41,    42,    43,
      44,    50,    51,    52,    53,    54,    55,    51,    77,    58,
      59,    60,    61,    78,    78,    93,    93,    79,    79,   144,
      64,   233,    48,   253,    73,    74,    77,   206,   229,    -1,
      -1,    75,    76,   225,    78,    79,    80,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,
      94,    95,     3,     4,     5,    -1,     7,     8,     9,    -1,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    -1,    78,    79,    80,
      -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    93,    94,    95,     3,     4,     5,    -1,     7,
       8,     9,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      78,    -1,    80,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    92,    93,    94,    95,    16,    17,
      18,    19,    -1,    21,    22,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    37,
      38,    -1,    40,    41,    42,    43,    44,    70,    -1,    72,
      73,    74,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      78,    -1,    80,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    92,    93,    94,    95,    16,    17,
      18,    19,    -1,    21,    22,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    37,
      38,    -1,    40,    41,    42,    43,    44,    70,    -1,    -1,
      73,    74,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      78,    -1,    80,    81,    16,    17,    18,    19,    -1,    21,
      22,    -1,    -1,    91,    92,    93,    94,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    -1,    80,    16,
      17,    18,    19,    -1,    21,    22,    -1,    -1,    -1,    91,
      92,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    -1,    80,    16,    17,    18,    19,    -1,    21,
      22,    -1,    -1,    -1,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    -1,    80,    16,
      17,    18,    19,    -1,    21,    22,    -1,    -1,    -1,    91,
      92,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      16,    17,    18,    19,    51,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    75,    76,
      -1,    78,    -1,    80,    16,    17,    18,    19,    -1,    21,
      22,    -1,    -1,    -1,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,
      76,    77,    78,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    76,    -1,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    91,
      92,    93,    94,    95,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,
      74,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      72,    73,    74,    -1,    -1,    -1,    78,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    72,    73,    74,    -1,    -1,    -1,    78,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    -1,    -1,    77,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    -1,    -1,    77,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,
      73,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    34,
      35,    36,    37,    38,    40,    41,    42,    43,    44,    51,
      64,    75,    76,    78,    80,    84,    91,    92,    93,    94,
      95,    97,    98,    99,   100,   101,   105,   106,   107,   108,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   131,   132,   133,   134,
      94,    84,    94,   125,   128,   125,   125,    76,    94,    94,
      84,    84,    94,    94,   125,    94,    94,    94,     3,    85,
      76,   125,   125,   125,   125,   125,   125,   125,   125,   125,
      79,    81,   125,   130,    76,    85,    76,     0,    99,     3,
      34,   108,    84,    65,    66,    67,    84,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    70,    72,    73,    74,    84,    80,    85,
      76,    84,    80,    85,    78,   113,   113,    84,   114,   117,
     128,    10,    10,    65,    83,    65,    78,    78,    76,    24,
      84,    94,    94,   125,    77,    81,    82,    77,   130,    94,
      77,   130,    94,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,    94,    77,    94,
     109,   110,   125,    94,    79,    98,     6,   125,    84,    84,
     125,   125,   125,    29,    30,    31,    32,    33,    45,    46,
      47,    80,    94,   111,   125,    48,    90,    94,   131,   135,
     136,   137,   102,   103,   104,   105,   115,    77,   130,    93,
      76,    76,    77,   125,    77,    85,    77,    76,    81,    87,
     112,    83,    77,    82,    81,    79,   113,   119,    84,   125,
     125,   113,    86,   113,   111,    65,    71,    89,   137,    79,
     136,    88,    79,   104,    77,    84,   109,   130,    94,   109,
     111,   113,   111,   112,   110,   117,    84,    84,   125,    81,
     125,   111,    88,   125,    77,    77,    76,    77,   113,    77,
      77,   117,   117,   113,   125,    82,   112,   130,   112,   113,
     113,    77,    77,    82,    78,    77,    78,   113,   113,    93,
      93,    79,    79
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    96,    97,    98,    98,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     100,   101,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   106,   107,   107,   108,   108,   108,   109,   109,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   112,   112,   113,   113,   114,   114,   114,   115,
     116,   116,   116,   117,   117,   117,   118,   119,   119,   119,
     120,   121,   121,   121,   121,   121,   121,   121,   122,   122,
     123,   124,   125,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   129,   129,   129,   129,   129,
     129,   129,   130,   130,   131,   131,   131,   131,   131,   131,
     132,   132,   133,   134,   135,   135,   136,   136,   136,   136,
     137,   137,   137
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     3,
       5,     5,     0,     1,     1,     2,     1,     1,     7,     6,
      10,    10,     1,     2,     1,     1,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     3,     2,     0,     3,     2,     6,     4,     4,     2,
       1,     3,     4,     3,     3,     3,     2,     3,     5,     5,
       3,     5,     5,     7,     9,     9,     8,     8,     3,     2,
       2,     2,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     4,     5,     4,     4,     3,     4,     3,     6,
       8,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     5,     1,     2,     5,     4,     4,     3,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statement_list  */
#line 163 "./src/parser/parser.y"
                     { root = (yyvsp[0].node); }
#line 1763 "./build/parser.tab.c"
    break;

  case 3: /* statement_list: statement  */
#line 167 "./src/parser/parser.y"
                { (yyval.node) = create_statement_list((yyvsp[0].node)); }
#line 1769 "./build/parser.tab.c"
    break;

  case 4: /* statement_list: statement_list statement  */
#line 168 "./src/parser/parser.y"
                               { (yyval.node) = append_statement((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1775 "./build/parser.tab.c"
    break;

  case 17: /* statement: expression SEMICOLON  */
#line 184 "./src/parser/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1781 "./build/parser.tab.c"
    break;

  case 18: /* statement: SEMICOLON  */
#line 185 "./src/parser/parser.y"
                { (yyval.node) = create_empty_statement(); }
#line 1787 "./build/parser.tab.c"
    break;

  case 19: /* import_statement: IMPORT IDENTIFIER SEMICOLON  */
#line 190 "./src/parser/parser.y"
                                  {
        // Simple import: import llm;
        (yyval.node) = create_empty_statement();  // For now, just parse it
    }
#line 1796 "./build/parser.tab.c"
    break;

  case 20: /* import_statement: IMPORT IDENTIFIER FROM STRING_LITERAL SEMICOLON  */
#line 194 "./src/parser/parser.y"
                                                      {
        // Named import: import llm from "module";
        (yyval.node) = create_empty_statement();
    }
#line 1805 "./build/parser.tab.c"
    break;

  case 21: /* class_declaration: CLASS IDENTIFIER LBRACE class_body RBRACE  */
#line 202 "./src/parser/parser.y"
                                                {
        (yyval.node) = create_class_node((yyvsp[-3].string_val), (yyvsp[-1].node));
    }
#line 1813 "./build/parser.tab.c"
    break;

  case 22: /* class_body: %empty  */
#line 208 "./src/parser/parser.y"
                  { (yyval.node) = NULL; }
#line 1819 "./build/parser.tab.c"
    break;

  case 23: /* class_body: class_member_list  */
#line 209 "./src/parser/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1825 "./build/parser.tab.c"
    break;

  case 24: /* class_member_list: class_member  */
#line 213 "./src/parser/parser.y"
                   { (yyval.node) = create_statement_list((yyvsp[0].node)); }
#line 1831 "./build/parser.tab.c"
    break;

  case 25: /* class_member_list: class_member_list class_member  */
#line 214 "./src/parser/parser.y"
                                     { (yyval.node) = append_statement((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1837 "./build/parser.tab.c"
    break;

  case 28: /* function_declaration: FUNC IDENTIFIER LPAREN parameter_list RPAREN optional_type_annotation block  */
#line 224 "./src/parser/parser.y"
                                                                                  {
        (yyval.node) = create_function_node((yyvsp[-5].string_val), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node), 0);
    }
#line 1845 "./build/parser.tab.c"
    break;

  case 29: /* function_declaration: FUNC IDENTIFIER LPAREN RPAREN optional_type_annotation block  */
#line 227 "./src/parser/parser.y"
                                                                   {
        (yyval.node) = create_function_node((yyvsp[-4].string_val), NULL, (yyvsp[-1].node), (yyvsp[0].node), 0);
    }
#line 1853 "./build/parser.tab.c"
    break;

  case 30: /* context_function_declaration: decorator_list FUNC IDENTIFIER LPAREN parameter_list RPAREN optional_type_annotation LBRACE STRING_LITERAL RBRACE  */
#line 233 "./src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string_val), (yyvsp[-5].node), (yyvsp[-3].node), NULL, 1);
        set_function_docstring((yyval.node), (yyvsp[-1].string_val));
    }
#line 1862 "./build/parser.tab.c"
    break;

  case 31: /* context_function_declaration: CONTEXT_DECORATOR FUNC IDENTIFIER LPAREN parameter_list RPAREN optional_type_annotation LBRACE STRING_LITERAL RBRACE  */
#line 237 "./src/parser/parser.y"
                                                                                                                           {
        (yyval.node) = create_function_node((yyvsp[-7].string_val), (yyvsp[-5].node), (yyvsp[-3].node), NULL, 1);
        set_function_docstring((yyval.node), (yyvsp[-1].string_val));
    }
#line 1871 "./build/parser.tab.c"
    break;

  case 34: /* decorator: CONTEXT_DECORATOR  */
#line 249 "./src/parser/parser.y"
                        { (yyval.node) = create_decorator_node("context"); }
#line 1877 "./build/parser.tab.c"
    break;

  case 35: /* decorator: CACHED_DECORATOR  */
#line 250 "./src/parser/parser.y"
                       { (yyval.node) = create_decorator_node("cached"); }
#line 1883 "./build/parser.tab.c"
    break;

  case 36: /* decorator: INLINE_DECORATOR  */
#line 251 "./src/parser/parser.y"
                       { (yyval.node) = create_decorator_node("inline"); }
#line 1889 "./build/parser.tab.c"
    break;

  case 37: /* parameter_list: parameter  */
#line 255 "./src/parser/parser.y"
                { (yyval.node) = create_parameter_list((yyvsp[0].node)); }
#line 1895 "./build/parser.tab.c"
    break;

  case 38: /* parameter_list: parameter_list COMMA parameter  */
#line 256 "./src/parser/parser.y"
                                     { (yyval.node) = append_parameter((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1901 "./build/parser.tab.c"
    break;

  case 39: /* parameter: IDENTIFIER COLON type_annotation  */
#line 260 "./src/parser/parser.y"
                                       {
        (yyval.node) = create_parameter_node((yyvsp[-2].string_val), (yyvsp[0].node));
    }
#line 1909 "./build/parser.tab.c"
    break;

  case 40: /* type_annotation: IDENTIFIER  */
#line 266 "./src/parser/parser.y"
                 { (yyval.node) = create_type_node((yyvsp[0].string_val)); }
#line 1915 "./build/parser.tab.c"
    break;

  case 41: /* type_annotation: INT_TYPE  */
#line 267 "./src/parser/parser.y"
               { (yyval.node) = create_type_node("int"); }
#line 1921 "./build/parser.tab.c"
    break;

  case 42: /* type_annotation: FLOAT_TYPE  */
#line 268 "./src/parser/parser.y"
                 { (yyval.node) = create_type_node("float"); }
#line 1927 "./build/parser.tab.c"
    break;

  case 43: /* type_annotation: STRING_TYPE  */
#line 269 "./src/parser/parser.y"
                  { (yyval.node) = create_type_node("string"); }
#line 1933 "./build/parser.tab.c"
    break;

  case 44: /* type_annotation: BOOL_TYPE  */
#line 270 "./src/parser/parser.y"
                { (yyval.node) = create_type_node("bool"); }
#line 1939 "./build/parser.tab.c"
    break;

  case 45: /* type_annotation: ANY  */
#line 271 "./src/parser/parser.y"
          { (yyval.node) = create_type_node("any"); }
#line 1945 "./build/parser.tab.c"
    break;

  case 46: /* type_annotation: PROMPT_TYPE  */
#line 272 "./src/parser/parser.y"
                  { (yyval.node) = create_type_node("prompt"); }
#line 1951 "./build/parser.tab.c"
    break;

  case 47: /* type_annotation: AIRESPONSE_TYPE  */
#line 273 "./src/parser/parser.y"
                      { (yyval.node) = create_type_node("airesponse"); }
#line 1957 "./build/parser.tab.c"
    break;

  case 48: /* type_annotation: MODEL_TYPE  */
#line 274 "./src/parser/parser.y"
                 { (yyval.node) = create_type_node("model"); }
#line 1963 "./build/parser.tab.c"
    break;

  case 49: /* type_annotation: LBRACKET type_annotation RBRACKET  */
#line 275 "./src/parser/parser.y"
                                        { (yyval.node) = create_array_type_node((yyvsp[-1].node)); }
#line 1969 "./build/parser.tab.c"
    break;

  case 50: /* type_annotation: type_annotation QUESTION  */
#line 276 "./src/parser/parser.y"
                               { (yyval.node) = create_optional_type_node((yyvsp[-1].node)); }
#line 1975 "./build/parser.tab.c"
    break;

  case 51: /* type_annotation: type_annotation PIPE type_annotation  */
#line 277 "./src/parser/parser.y"
                                           { (yyval.node) = create_union_type_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1981 "./build/parser.tab.c"
    break;

  case 52: /* optional_type_annotation: ARROW type_annotation  */
#line 281 "./src/parser/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1987 "./build/parser.tab.c"
    break;

  case 53: /* optional_type_annotation: %empty  */
#line 282 "./src/parser/parser.y"
                  { (yyval.node) = NULL; }
#line 1993 "./build/parser.tab.c"
    break;

  case 54: /* block: LBRACE statement_list RBRACE  */
#line 286 "./src/parser/parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 1999 "./build/parser.tab.c"
    break;

  case 55: /* block: LBRACE RBRACE  */
#line 287 "./src/parser/parser.y"
                    { (yyval.node) = create_empty_statement(); }
#line 2005 "./build/parser.tab.c"
    break;

  case 56: /* variable_decl_base: LET IDENTIFIER COLON type_annotation ASSIGN expression  */
#line 292 "./src/parser/parser.y"
                                                             {
        (yyval.node) = create_variable_node((yyvsp[-4].string_val), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2013 "./build/parser.tab.c"
    break;

  case 57: /* variable_decl_base: LET IDENTIFIER ASSIGN expression  */
#line 295 "./src/parser/parser.y"
                                       {
        (yyval.node) = create_variable_node((yyvsp[-2].string_val), NULL, (yyvsp[0].node));
    }
#line 2021 "./build/parser.tab.c"
    break;

  case 58: /* variable_decl_base: AUTO IDENTIFIER ASSIGN expression  */
#line 298 "./src/parser/parser.y"
                                        {
        (yyval.node) = create_variable_node((yyvsp[-2].string_val), create_type_node("auto"), (yyvsp[0].node));
    }
#line 2029 "./build/parser.tab.c"
    break;

  case 59: /* variable_declaration: variable_decl_base SEMICOLON  */
#line 304 "./src/parser/parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 2035 "./build/parser.tab.c"
    break;

  case 60: /* lvalue: IDENTIFIER  */
#line 309 "./src/parser/parser.y"
                 { (yyval.node) = create_identifier_node((yyvsp[0].string_val)); }
#line 2041 "./build/parser.tab.c"
    break;

  case 61: /* lvalue: primary_expr DOT IDENTIFIER  */
#line 310 "./src/parser/parser.y"
                                  { (yyval.node) = create_member_access_node((yyvsp[-2].node), (yyvsp[0].string_val)); }
#line 2047 "./build/parser.tab.c"
    break;

  case 62: /* lvalue: primary_expr LBRACKET expression RBRACKET  */
#line 311 "./src/parser/parser.y"
                                                { (yyval.node) = create_subscript_node((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2053 "./build/parser.tab.c"
    break;

  case 63: /* assignment_base: lvalue ASSIGN expression  */
#line 315 "./src/parser/parser.y"
                               {
        (yyval.node) = create_assignment_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2061 "./build/parser.tab.c"
    break;

  case 64: /* assignment_base: lvalue PLUS_ASSIGN expression  */
#line 318 "./src/parser/parser.y"
                                    {
        (yyval.node) = create_compound_assignment_node((yyvsp[-2].node), "+=", (yyvsp[0].node));
    }
#line 2069 "./build/parser.tab.c"
    break;

  case 65: /* assignment_base: lvalue MINUS_ASSIGN expression  */
#line 321 "./src/parser/parser.y"
                                     {
        (yyval.node) = create_compound_assignment_node((yyvsp[-2].node), "-=", (yyvsp[0].node));
    }
#line 2077 "./build/parser.tab.c"
    break;

  case 66: /* assignment: assignment_base SEMICOLON  */
#line 327 "./src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 2083 "./build/parser.tab.c"
    break;

  case 67: /* if_statement: IF expression block  */
#line 332 "./src/parser/parser.y"
                          {
        (yyval.node) = create_if_node((yyvsp[-1].node), (yyvsp[0].node), NULL);
    }
#line 2091 "./build/parser.tab.c"
    break;

  case 68: /* if_statement: IF expression block ELSE block  */
#line 335 "./src/parser/parser.y"
                                     {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2099 "./build/parser.tab.c"
    break;

  case 69: /* if_statement: IF expression block ELSE if_statement  */
#line 338 "./src/parser/parser.y"
                                            {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2107 "./build/parser.tab.c"
    break;

  case 70: /* while_statement: WHILE expression block  */
#line 344 "./src/parser/parser.y"
                             {
        (yyval.node) = create_while_node((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2115 "./build/parser.tab.c"
    break;

  case 71: /* for_statement: FOR IDENTIFIER IN expression block  */
#line 350 "./src/parser/parser.y"
                                         {
        (yyval.node) = create_for_node((yyvsp[-3].string_val), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2123 "./build/parser.tab.c"
    break;

  case 72: /* for_statement: FOREACH IDENTIFIER IN expression block  */
#line 353 "./src/parser/parser.y"
                                             {
        (yyval.node) = create_for_node((yyvsp[-3].string_val), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2131 "./build/parser.tab.c"
    break;

  case 73: /* for_statement: FOREACH IDENTIFIER IN expression DOTDOT expression block  */
#line 356 "./src/parser/parser.y"
                                                               {
        // Syntactic sugar: create range node from e1..e2
        ASTNode* range = create_binary_op_node("..", (yyvsp[-3].node), (yyvsp[-1].node));
        (yyval.node) = create_for_node((yyvsp[-5].string_val), range, (yyvsp[0].node));
    }
#line 2141 "./build/parser.tab.c"
    break;

  case 74: /* for_statement: FOR LPAREN variable_decl_base SEMICOLON expression SEMICOLON assignment_base RPAREN block  */
#line 362 "./src/parser/parser.y"
                                                                                                {
        (yyval.node) = create_c_style_for_node((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2149 "./build/parser.tab.c"
    break;

  case 75: /* for_statement: FOR LPAREN assignment_base SEMICOLON expression SEMICOLON assignment_base RPAREN block  */
#line 365 "./src/parser/parser.y"
                                                                                             {
        (yyval.node) = create_c_style_for_node((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2157 "./build/parser.tab.c"
    break;

  case 76: /* for_statement: FOR LPAREN SEMICOLON expression SEMICOLON assignment_base RPAREN block  */
#line 368 "./src/parser/parser.y"
                                                                             {
        (yyval.node) = create_c_style_for_node(NULL, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2165 "./build/parser.tab.c"
    break;

  case 77: /* for_statement: FOR LPAREN variable_decl_base SEMICOLON expression SEMICOLON RPAREN block  */
#line 371 "./src/parser/parser.y"
                                                                                {
        (yyval.node) = create_c_style_for_node((yyvsp[-5].node), (yyvsp[-3].node), NULL, (yyvsp[0].node));
    }
#line 2173 "./build/parser.tab.c"
    break;

  case 78: /* return_statement: RETURN expression SEMICOLON  */
#line 377 "./src/parser/parser.y"
                                  {
        (yyval.node) = create_return_node((yyvsp[-1].node));
    }
#line 2181 "./build/parser.tab.c"
    break;

  case 79: /* return_statement: RETURN SEMICOLON  */
#line 380 "./src/parser/parser.y"
                       {
        (yyval.node) = create_return_node(NULL);
    }
#line 2189 "./build/parser.tab.c"
    break;

  case 80: /* break_statement: BREAK SEMICOLON  */
#line 386 "./src/parser/parser.y"
                      { (yyval.node) = create_break_node(); }
#line 2195 "./build/parser.tab.c"
    break;

  case 81: /* continue_statement: CONTINUE SEMICOLON  */
#line 390 "./src/parser/parser.y"
                         { (yyval.node) = create_continue_node(); }
#line 2201 "./build/parser.tab.c"
    break;

  case 85: /* binary_expr: expression PLUS expression  */
#line 401 "./src/parser/parser.y"
                                 { (yyval.node) = create_binary_op_node("+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2207 "./build/parser.tab.c"
    break;

  case 86: /* binary_expr: expression MINUS expression  */
#line 402 "./src/parser/parser.y"
                                  { (yyval.node) = create_binary_op_node("-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2213 "./build/parser.tab.c"
    break;

  case 87: /* binary_expr: expression STAR expression  */
#line 403 "./src/parser/parser.y"
                                 { (yyval.node) = create_binary_op_node("*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2219 "./build/parser.tab.c"
    break;

  case 88: /* binary_expr: expression SLASH expression  */
#line 404 "./src/parser/parser.y"
                                  { (yyval.node) = create_binary_op_node("/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2225 "./build/parser.tab.c"
    break;

  case 89: /* binary_expr: expression PERCENT expression  */
#line 405 "./src/parser/parser.y"
                                    { (yyval.node) = create_binary_op_node("%", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2231 "./build/parser.tab.c"
    break;

  case 90: /* binary_expr: expression POWER expression  */
#line 406 "./src/parser/parser.y"
                                  { (yyval.node) = create_binary_op_node("**", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2237 "./build/parser.tab.c"
    break;

  case 91: /* binary_expr: expression EQ expression  */
#line 407 "./src/parser/parser.y"
                               { (yyval.node) = create_binary_op_node("==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2243 "./build/parser.tab.c"
    break;

  case 92: /* binary_expr: expression NE expression  */
#line 408 "./src/parser/parser.y"
                               { (yyval.node) = create_binary_op_node("!=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2249 "./build/parser.tab.c"
    break;

  case 93: /* binary_expr: expression LT expression  */
#line 409 "./src/parser/parser.y"
                               { (yyval.node) = create_binary_op_node("<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2255 "./build/parser.tab.c"
    break;

  case 94: /* binary_expr: expression GT expression  */
#line 410 "./src/parser/parser.y"
                               { (yyval.node) = create_binary_op_node(">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2261 "./build/parser.tab.c"
    break;

  case 95: /* binary_expr: expression LE expression  */
#line 411 "./src/parser/parser.y"
                               { (yyval.node) = create_binary_op_node("<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2267 "./build/parser.tab.c"
    break;

  case 96: /* binary_expr: expression GE expression  */
#line 412 "./src/parser/parser.y"
                               { (yyval.node) = create_binary_op_node(">=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2273 "./build/parser.tab.c"
    break;

  case 97: /* binary_expr: expression AND expression  */
#line 413 "./src/parser/parser.y"
                                { (yyval.node) = create_binary_op_node("&&", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2279 "./build/parser.tab.c"
    break;

  case 98: /* binary_expr: expression OR expression  */
#line 414 "./src/parser/parser.y"
                               { (yyval.node) = create_binary_op_node("||", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2285 "./build/parser.tab.c"
    break;

  case 99: /* binary_expr: expression SEMANTIC_EQ expression  */
#line 415 "./src/parser/parser.y"
                                        { (yyval.node) = create_binary_op_node("~=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2291 "./build/parser.tab.c"
    break;

  case 100: /* binary_expr: expression SEMANTIC_IMPLIES expression  */
#line 416 "./src/parser/parser.y"
                                             { (yyval.node) = create_binary_op_node("~>", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2297 "./build/parser.tab.c"
    break;

  case 101: /* binary_expr: expression AMPERSAND expression  */
#line 417 "./src/parser/parser.y"
                                      { (yyval.node) = create_binary_op_node("&", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2303 "./build/parser.tab.c"
    break;

  case 102: /* binary_expr: expression CARET expression  */
#line 418 "./src/parser/parser.y"
                                  { (yyval.node) = create_binary_op_node("^", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2309 "./build/parser.tab.c"
    break;

  case 103: /* binary_expr: expression LSHIFT expression  */
#line 419 "./src/parser/parser.y"
                                   { (yyval.node) = create_binary_op_node("<<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2315 "./build/parser.tab.c"
    break;

  case 104: /* binary_expr: expression RSHIFT expression  */
#line 420 "./src/parser/parser.y"
                                   { (yyval.node) = create_binary_op_node(">>", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2321 "./build/parser.tab.c"
    break;

  case 105: /* unary_expr: NOT expression  */
#line 424 "./src/parser/parser.y"
                     { (yyval.node) = create_unary_op_node("!", (yyvsp[0].node)); }
#line 2327 "./build/parser.tab.c"
    break;

  case 106: /* unary_expr: MINUS expression  */
#line 425 "./src/parser/parser.y"
                       { (yyval.node) = create_unary_op_node("-", (yyvsp[0].node)); }
#line 2333 "./build/parser.tab.c"
    break;

  case 107: /* unary_expr: TILDE expression  */
#line 426 "./src/parser/parser.y"
                       { (yyval.node) = create_unary_op_node("~", (yyvsp[0].node)); }
#line 2339 "./build/parser.tab.c"
    break;

  case 108: /* unary_expr: AI_ASK expression  */
#line 427 "./src/parser/parser.y"
                        { (yyval.node) = create_ai_ask_node((yyvsp[0].node)); }
#line 2345 "./build/parser.tab.c"
    break;

  case 109: /* unary_expr: AI_GENERATE expression  */
#line 428 "./src/parser/parser.y"
                             { (yyval.node) = create_ai_generate_node((yyvsp[0].node)); }
#line 2351 "./build/parser.tab.c"
    break;

  case 110: /* unary_expr: AI_ANALYZE expression  */
#line 429 "./src/parser/parser.y"
                            { (yyval.node) = create_ai_analyze_node((yyvsp[0].node)); }
#line 2357 "./build/parser.tab.c"
    break;

  case 111: /* unary_expr: AI_EMBED expression  */
#line 430 "./src/parser/parser.y"
                          { (yyval.node) = create_ai_embed_node((yyvsp[0].node)); }
#line 2363 "./build/parser.tab.c"
    break;

  case 112: /* unary_expr: AI_CLASSIFY expression  */
#line 431 "./src/parser/parser.y"
                             { (yyval.node) = create_ai_classify_node((yyvsp[0].node)); }
#line 2369 "./build/parser.tab.c"
    break;

  case 114: /* primary_expr: IDENTIFIER  */
#line 436 "./src/parser/parser.y"
                 { (yyval.node) = create_identifier_node((yyvsp[0].string_val)); }
#line 2375 "./build/parser.tab.c"
    break;

  case 115: /* primary_expr: THIS  */
#line 437 "./src/parser/parser.y"
           { (yyval.node) = create_identifier_node("this"); }
#line 2381 "./build/parser.tab.c"
    break;

  case 120: /* primary_expr: LPAREN expression RPAREN  */
#line 442 "./src/parser/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2387 "./build/parser.tab.c"
    break;

  case 121: /* primary_expr: primary_expr DOT IDENTIFIER  */
#line 443 "./src/parser/parser.y"
                                  { (yyval.node) = create_member_access_node((yyvsp[-2].node), (yyvsp[0].string_val)); }
#line 2393 "./build/parser.tab.c"
    break;

  case 122: /* primary_expr: primary_expr LBRACKET expression RBRACKET  */
#line 444 "./src/parser/parser.y"
                                                { (yyval.node) = create_subscript_node((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2399 "./build/parser.tab.c"
    break;

  case 123: /* primary_expr: NEW IDENTIFIER LPAREN argument_list RPAREN  */
#line 445 "./src/parser/parser.y"
                                                 { (yyval.node) = create_new_node((yyvsp[-3].string_val), (yyvsp[-1].node)); }
#line 2405 "./build/parser.tab.c"
    break;

  case 124: /* primary_expr: NEW IDENTIFIER LPAREN RPAREN  */
#line 446 "./src/parser/parser.y"
                                   { (yyval.node) = create_new_node((yyvsp[-2].string_val), NULL); }
#line 2411 "./build/parser.tab.c"
    break;

  case 125: /* function_call: IDENTIFIER LPAREN argument_list RPAREN  */
#line 450 "./src/parser/parser.y"
                                             {
        (yyval.node) = create_function_call_node((yyvsp[-3].string_val), (yyvsp[-1].node));
    }
#line 2419 "./build/parser.tab.c"
    break;

  case 126: /* function_call: IDENTIFIER LPAREN RPAREN  */
#line 453 "./src/parser/parser.y"
                               {
        (yyval.node) = create_function_call_node((yyvsp[-2].string_val), NULL);
    }
#line 2427 "./build/parser.tab.c"
    break;

  case 127: /* function_call: NAMESPACE_ID LPAREN argument_list RPAREN  */
#line 456 "./src/parser/parser.y"
                                               {
        // namespace.function(args) - parse and create appropriate call
        (yyval.node) = create_function_call_node((yyvsp[-3].string_val), (yyvsp[-1].node));
    }
#line 2436 "./build/parser.tab.c"
    break;

  case 128: /* function_call: NAMESPACE_ID LPAREN RPAREN  */
#line 460 "./src/parser/parser.y"
                                 {
        // namespace.function() - no args
        (yyval.node) = create_function_call_node((yyvsp[-2].string_val), NULL);
    }
#line 2445 "./build/parser.tab.c"
    break;

  case 129: /* function_call: LLM DOT IDENTIFIER LPAREN argument_list RPAREN  */
#line 464 "./src/parser/parser.y"
                                                     {
        (yyval.node) = create_llm_call_node((yyvsp[-3].string_val), (yyvsp[-1].node));
    }
#line 2453 "./build/parser.tab.c"
    break;

  case 130: /* function_call: IDENTIFIER DOT IDENTIFIER DOT IDENTIFIER LPAREN argument_list RPAREN  */
#line 467 "./src/parser/parser.y"
                                                                           {
        char buffer[256];
        sprintf(buffer, "%s.%s.%s", (yyvsp[-7].string_val), (yyvsp[-5].string_val), (yyvsp[-3].string_val));
        (yyval.node) = create_function_call_node(buffer, (yyvsp[-1].node));
    }
#line 2463 "./build/parser.tab.c"
    break;

  case 131: /* function_call: EMBED LPAREN expression RPAREN  */
#line 472 "./src/parser/parser.y"
                                     {
        (yyval.node) = create_embed_call_node((yyvsp[-1].node));
    }
#line 2471 "./build/parser.tab.c"
    break;

  case 132: /* argument_list: expression  */
#line 478 "./src/parser/parser.y"
                 { (yyval.node) = create_argument_list((yyvsp[0].node)); }
#line 2477 "./build/parser.tab.c"
    break;

  case 133: /* argument_list: argument_list COMMA expression  */
#line 479 "./src/parser/parser.y"
                                     { (yyval.node) = append_argument((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2483 "./build/parser.tab.c"
    break;

  case 134: /* literal: INT_LITERAL  */
#line 483 "./src/parser/parser.y"
                  { (yyval.node) = create_int_literal_node((yyvsp[0].int_val)); }
#line 2489 "./build/parser.tab.c"
    break;

  case 135: /* literal: FLOAT_LITERAL  */
#line 484 "./src/parser/parser.y"
                    { (yyval.node) = create_float_literal_node((yyvsp[0].float_val)); }
#line 2495 "./build/parser.tab.c"
    break;

  case 136: /* literal: STRING_LITERAL  */
#line 485 "./src/parser/parser.y"
                     { (yyval.node) = create_string_literal_node((yyvsp[0].string_val)); }
#line 2501 "./build/parser.tab.c"
    break;

  case 137: /* literal: TRUE  */
#line 486 "./src/parser/parser.y"
           { (yyval.node) = create_bool_literal_node(1); }
#line 2507 "./build/parser.tab.c"
    break;

  case 138: /* literal: FALSE  */
#line 487 "./src/parser/parser.y"
            { (yyval.node) = create_bool_literal_node(0); }
#line 2513 "./build/parser.tab.c"
    break;

  case 139: /* literal: NULL_KW  */
#line 488 "./src/parser/parser.y"
              { (yyval.node) = create_null_literal_node(); }
#line 2519 "./build/parser.tab.c"
    break;

  case 140: /* array_literal: LBRACKET argument_list RBRACKET  */
#line 492 "./src/parser/parser.y"
                                      {
        (yyval.node) = create_array_literal_node((yyvsp[-1].node));
    }
#line 2527 "./build/parser.tab.c"
    break;

  case 141: /* array_literal: LBRACKET RBRACKET  */
#line 495 "./src/parser/parser.y"
                        {
        (yyval.node) = create_array_literal_node(NULL);
    }
#line 2535 "./build/parser.tab.c"
    break;

  case 142: /* dict_literal: LBRACE RBRACE  */
#line 501 "./src/parser/parser.y"
                    {
        (yyval.node) = create_dict_literal_node(NULL);
    }
#line 2543 "./build/parser.tab.c"
    break;

  case 143: /* match_expr: MATCH expression LBRACE match_arms RBRACE  */
#line 508 "./src/parser/parser.y"
                                                {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2551 "./build/parser.tab.c"
    break;

  case 144: /* match_arms: match_arm  */
#line 514 "./src/parser/parser.y"
                { (yyval.node) = create_statement_list((yyvsp[0].node)); }
#line 2557 "./build/parser.tab.c"
    break;

  case 145: /* match_arms: match_arms match_arm  */
#line 515 "./src/parser/parser.y"
                           { (yyval.node) = append_statement((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2563 "./build/parser.tab.c"
    break;

  case 146: /* match_arm: SEMANTIC_EQ match_pattern FATARROW expression COMMA  */
#line 519 "./src/parser/parser.y"
                                                          {
        (yyval.node) = create_match_arm_node((yyvsp[-3].node), (yyvsp[-1].node), 1); /* semantic = 1 */
    }
#line 2571 "./build/parser.tab.c"
    break;

  case 147: /* match_arm: match_pattern FATARROW expression COMMA  */
#line 522 "./src/parser/parser.y"
                                              {
        (yyval.node) = create_match_arm_node((yyvsp[-3].node), (yyvsp[-1].node), 0); /* literal = 0 */
    }
#line 2579 "./build/parser.tab.c"
    break;

  case 148: /* match_arm: SEMANTIC_EQ match_pattern FATARROW expression  */
#line 525 "./src/parser/parser.y"
                                                    {
        (yyval.node) = create_match_arm_node((yyvsp[-2].node), (yyvsp[0].node), 1); /* last arm without comma */
    }
#line 2587 "./build/parser.tab.c"
    break;

  case 149: /* match_arm: match_pattern FATARROW expression  */
#line 528 "./src/parser/parser.y"
                                        {
        (yyval.node) = create_match_arm_node((yyvsp[-2].node), (yyvsp[0].node), 0); /* last arm without comma */
    }
#line 2595 "./build/parser.tab.c"
    break;

  case 150: /* match_pattern: UNDERSCORE  */
#line 534 "./src/parser/parser.y"
                 { (yyval.node) = create_wildcard_node(); }
#line 2601 "./build/parser.tab.c"
    break;

  case 151: /* match_pattern: literal  */
#line 535 "./src/parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2607 "./build/parser.tab.c"
    break;

  case 152: /* match_pattern: IDENTIFIER  */
#line 536 "./src/parser/parser.y"
                 { (yyval.node) = create_identifier_node((yyvsp[0].string_val)); }
#line 2613 "./build/parser.tab.c"
    break;


#line 2617 "./build/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 539 "./src/parser/parser.y"


extern FILE *yyin;
extern int yylineno;
ASTNode* root = NULL; // Global root AST node

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}

