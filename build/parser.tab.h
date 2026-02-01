/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_DALETH_ESCRITORIO_LAZY_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_HOME_DALETH_ESCRITORIO_LAZY_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FUNC = 258,                    /* FUNC  */
    RETURN = 259,                  /* RETURN  */
    IF = 260,                      /* IF  */
    ELSE = 261,                    /* ELSE  */
    WHILE = 262,                   /* WHILE  */
    FOR = 263,                     /* FOR  */
    FOREACH = 264,                 /* FOREACH  */
    IN = 265,                      /* IN  */
    RANGE = 266,                   /* RANGE  */
    BREAK = 267,                   /* BREAK  */
    CONTINUE = 268,                /* CONTINUE  */
    LET = 269,                     /* LET  */
    AUTO = 270,                    /* AUTO  */
    MATCH = 271,                   /* MATCH  */
    TRUE = 272,                    /* TRUE  */
    FALSE = 273,                   /* FALSE  */
    NULL_KW = 274,                 /* NULL_KW  */
    CLASS = 275,                   /* CLASS  */
    NEW = 276,                     /* NEW  */
    THIS = 277,                    /* THIS  */
    IMPORT = 278,                  /* IMPORT  */
    FROM = 279,                    /* FROM  */
    TRY = 280,                     /* TRY  */
    CATCH = 281,                   /* CATCH  */
    FINALLY = 282,                 /* FINALLY  */
    THROW = 283,                   /* THROW  */
    ANY = 284,                     /* ANY  */
    INT_TYPE = 285,                /* INT_TYPE  */
    FLOAT_TYPE = 286,              /* FLOAT_TYPE  */
    STRING_TYPE = 287,             /* STRING_TYPE  */
    BOOL_TYPE = 288,               /* BOOL_TYPE  */
    CONTEXT_DECORATOR = 289,       /* CONTEXT_DECORATOR  */
    CACHED_DECORATOR = 290,        /* CACHED_DECORATOR  */
    INLINE_DECORATOR = 291,        /* INLINE_DECORATOR  */
    LLM = 292,                     /* LLM  */
    EMBED = 293,                   /* EMBED  */
    THRESHOLD = 294,               /* THRESHOLD  */
    AI_ASK = 295,                  /* AI_ASK  */
    AI_GENERATE = 296,             /* AI_GENERATE  */
    AI_ANALYZE = 297,              /* AI_ANALYZE  */
    AI_EMBED = 298,                /* AI_EMBED  */
    AI_CLASSIFY = 299,             /* AI_CLASSIFY  */
    PROMPT_TYPE = 300,             /* PROMPT_TYPE  */
    AIRESPONSE_TYPE = 301,         /* AIRESPONSE_TYPE  */
    MODEL_TYPE = 302,              /* MODEL_TYPE  */
    SEMANTIC_EQ = 303,             /* SEMANTIC_EQ  */
    SEMANTIC_IMPLIES = 304,        /* SEMANTIC_IMPLIES  */
    PLUS = 305,                    /* PLUS  */
    MINUS = 306,                   /* MINUS  */
    STAR = 307,                    /* STAR  */
    SLASH = 308,                   /* SLASH  */
    PERCENT = 309,                 /* PERCENT  */
    POWER = 310,                   /* POWER  */
    EQ = 311,                      /* EQ  */
    NE = 312,                      /* NE  */
    LT = 313,                      /* LT  */
    GT = 314,                      /* GT  */
    LE = 315,                      /* LE  */
    GE = 316,                      /* GE  */
    AND = 317,                     /* AND  */
    OR = 318,                      /* OR  */
    NOT = 319,                     /* NOT  */
    ASSIGN = 320,                  /* ASSIGN  */
    PLUS_ASSIGN = 321,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 322,            /* MINUS_ASSIGN  */
    STAR_ASSIGN = 323,             /* STAR_ASSIGN  */
    SLASH_ASSIGN = 324,            /* SLASH_ASSIGN  */
    AMPERSAND = 325,               /* AMPERSAND  */
    PIPE = 326,                    /* PIPE  */
    CARET = 327,                   /* CARET  */
    LSHIFT = 328,                  /* LSHIFT  */
    RSHIFT = 329,                  /* RSHIFT  */
    TILDE = 330,                   /* TILDE  */
    LPAREN = 331,                  /* LPAREN  */
    RPAREN = 332,                  /* RPAREN  */
    LBRACE = 333,                  /* LBRACE  */
    RBRACE = 334,                  /* RBRACE  */
    LBRACKET = 335,                /* LBRACKET  */
    RBRACKET = 336,                /* RBRACKET  */
    COMMA = 337,                   /* COMMA  */
    COLON = 338,                   /* COLON  */
    SEMICOLON = 339,               /* SEMICOLON  */
    DOT = 340,                     /* DOT  */
    DOTDOT = 341,                  /* DOTDOT  */
    ARROW = 342,                   /* ARROW  */
    FATARROW = 343,                /* FATARROW  */
    QUESTION = 344,                /* QUESTION  */
    UNDERSCORE = 345,              /* UNDERSCORE  */
    INT_LITERAL = 346,             /* INT_LITERAL  */
    FLOAT_LITERAL = 347,           /* FLOAT_LITERAL  */
    STRING_LITERAL = 348,          /* STRING_LITERAL  */
    IDENTIFIER = 349,              /* IDENTIFIER  */
    NAMESPACE_ID = 350             /* NAMESPACE_ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 81 "/home/daleth/Escritorio/lazy/src/parser/parser.y"

    int int_val;
    double float_val;
    char* string_val;
    void* node;  /* Changed from ASTNode* to void* for C compatibility */

#line 166 "/home/daleth/Escritorio/lazy/build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_DALETH_ESCRITORIO_LAZY_BUILD_PARSER_TAB_H_INCLUDED  */
