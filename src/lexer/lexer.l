%{
/*
 * LazyA Lexer - Flex Specification
 * Tokenizes LazyA source code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

void yyerror(const char* s);

/* Helper function to process escape sequences in strings */
char* process_escape_sequences(const char* str) {
    char* result = (char*)malloc(strlen(str) + 1);
    char* dst = result;
    const char* src = str;
    
    while (*src) {
        if (*src == '\\' && *(src + 1)) {
            src++; // Skip backslash
            switch (*src) {
                case 'n':  *dst++ = '\n'; break;
                case 't':  *dst++ = '\t'; break;
                case 'r':  *dst++ = '\r'; break;
                case '\\': *dst++ = '\\'; break;
                case '"':  *dst++ = '"';  break;
                case '0':  *dst++ = '\0'; break;
                default:   
                    *dst++ = '\\';
                    *dst++ = *src;
                    break;
            }
            src++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    return result;
}
%}

%option noyywrap
%option yylineno

/* Patterns */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*
NAMESPACE_ID {IDENTIFIER}(\.{IDENTIFIER})+
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+\.{DIGIT}+
STRING      \"([^\\\"]|\\.)*\"
WHITESPACE  [ \t\r]+
NEWLINE     \n

%%

    /* Keywords */
"func"          { return FUNC; }
"return"        { return RETURN; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"in"            { return IN; }
"let"           { return LET; }
"auto"          { return AUTO; }
"foreach"       { return FOREACH; }
"range"         { return RANGE; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"match"         { return MATCH; }
"true"          { return TRUE; }
"false"         { return FALSE; }
"null"          { return NULL_KW; }
"import"        { return IMPORT; }
"from"          { return FROM; }
"try"           { return TRY; }
"catch"         { return CATCH; }
"finally"       { return FINALLY; }
"throw"         { return THROW; }
"any"           { return ANY; }
"int"           { return INT_TYPE; }
"float"         { return FLOAT_TYPE; }
"string"        { return STRING_TYPE; }
"bool"          { return BOOL_TYPE; }

"class"         { return CLASS; }
"new"           { return NEW; }
"this"          { return THIS; }

    /* AI-specific keywords */
"@context"      { return CONTEXT_DECORATOR; }
"@cached"       { return CACHED_DECORATOR; }
"@inline"       { return INLINE_DECORATOR; }
"llm"           { return LLM; }
"embed"         { return EMBED; }
"threshold"     { return THRESHOLD; }

    /* AI Operator Keywords */
"@ask"          { return AI_ASK; }
"@generate"     { return AI_GENERATE; }
"@analyze"      { return AI_ANALYZE; }
"@embed"        { return AI_EMBED; }
"@classify"     { return AI_CLASSIFY; }

    /* AI Type Keywords */
"prompt"        { return PROMPT_TYPE; }
"airesponse"    { return AIRESPONSE_TYPE; }
"model"         { return MODEL_TYPE; }

    /* AI Operators */
"~="            { return SEMANTIC_EQ; }
"~>"            { return SEMANTIC_IMPLIES; }

    /* Standard Operators */
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return STAR; }
"/"             { return SLASH; }
"%"             { return PERCENT; }
"**"            { return POWER; }

    /* Bitwise operators */
"&"             { return AMPERSAND; }
"|"             { return PIPE; }
"^"             { return CARET; }
"<<"            { return LSHIFT; }
">>"            { return RSHIFT; }
"~"             { return TILDE; }

"=="            { return EQ; }
"!="            { return NE; }
"<"             { return LT; }
">"             { return GT; }
"<="            { return LE; }
">="            { return GE; }

"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }

"="             { return ASSIGN; }
"+="            { return PLUS_ASSIGN; }
"-="            { return MINUS_ASSIGN; }
"*="            { return STAR_ASSIGN; }
"/="            { return SLASH_ASSIGN; }

    /* Delimiters */
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
","             { return COMMA; }
":"             { return COLON; }
";"             { return SEMICOLON; }
"."             { return DOT; }
".."            { return DOTDOT; }
"->"            { return ARROW; }
"=>"            { return FATARROW; }
"?"             { return QUESTION; }
"_"             { return UNDERSCORE; }

    /* Literals */
{INTEGER}       { 
                    yylval.int_val = atoi(yytext); 
                    return INT_LITERAL; 
                }

{FLOAT}         { 
                    yylval.float_val = atof(yytext); 
                    return FLOAT_LITERAL; 
                }

{STRING}        { 
                    /* Remove quotes and process escape sequences */
                    char* raw_str = strdup(yytext + 1);
                    raw_str[strlen(raw_str) - 1] = '\0';
                    yylval.string_val = process_escape_sequences(raw_str);
                    free(raw_str);
                    return STRING_LITERAL; 
                }

{NAMESPACE_ID}  {
                    /* namespace.function syntax */
                    yylval.string_val = strdup(yytext);
                    return NAMESPACE_ID;
                }

{IDENTIFIER}    { 
                    yylval.string_val = strdup(yytext); 
                    return IDENTIFIER; 
                }

    /* Comments */
"//"[^\n]*      { /* Single-line comment, ignore */ }

"/*"            { 
                    /* Multi-line comment */
                    int c;
                    while ((c = input()) != 0) {
                        if (c == '*') {
                            if ((c = input()) == '/') {
                                break;
                            }
                            unput(c);
                        }
                    }
                }

    /* Whitespace */
{WHITESPACE}    { /* Ignore whitespace */ }
{NEWLINE}       { /* Track line numbers */ }

    /* Unknown character */
.               { 
                    char msg[100];
                    sprintf(msg, "Unknown character: %s", yytext);
                    yyerror(msg);
                }

%%

