#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define AST_SYMBOL 1
#define AST_IDENTIFIER 34
#define AST_LIT_INT 35
#define AST_LIT_REAL 36
#define AST_LIT_CHAR 37
#define AST_LIT_STRING 38
#define AST_PARAM_LIST 39
#define AST_FUNC_DECL_INT 40
#define AST_FUNC_DECL_REAL 41
#define AST_FUNC_DECL_CHAR 42
#define AST_FUNC_DECL_BOOL 43
#define AST_PARAM_INT 44
#define AST_PARAM_REAL 45
#define AST_PARAM_CHAR 46
#define AST_PARAM_BOOL 47
#define AST_ADD 2
#define AST_SUB 3
#define AST_MUL 4
#define AST_DIV 5
#define AST_NEG 6
#define AST_NOT 7
#define AST_AND 8
#define AST_OR 9
#define AST_LE 10
#define AST_GE 11
#define AST_EQ 12
#define AST_DIF 13
#define AST_GT 14
#define AST_LT 15
#define AST_PROGRAM 16
#define AST_DECLARATION_LIST 17
#define AST_DECLARATION 18
#define AST_PARAMETER_LIST 21
#define AST_PARAMETER 22
#define AST_FUNC_DECLARATION 23
#define AST_BODY 24
#define AST_CMD_LIST 25
#define AST_CMD 26
#define AST_VAR_ATTRIB 27
#define AST_OUTPUT_CMD 28
#define AST_OUTPUT_PARAM_LIST 29
#define AST_RETURN_CMD 30
#define AST_IF 31
#define AST_IF_ELSE 32
#define AST_LOOP 33

#define AST_VEC_ATTRIB 48
#define AST_VEC_DECL_INT 50
#define AST_VEC_DECL_REAL 51
#define AST_VEC_DECL_CHAR 52
#define AST_VEC_DECL_BOOL 53
#define AST_VEC_INIT_OPT_INT 54
#define AST_VEC_INIT_OPT_REAL 55
#define AST_VEC_INIT_OPT_CHAR 56

#define AST_EXPR_LIST 57
#define AST_FUNC_CALL 58
#define AST_INPUT_EXPR_INT 63
#define AST_INPUT_EXPR_REAL 64
#define AST_INPUT_EXPR_CHAR 65
#define AST_INPUT_EXPR_BOOL 66
#define AST_VAR_DECL_INT 67
#define AST_VAR_DECL_REAL 68
#define AST_VAR_DECL_CHAR 69
#define AST_VAR_DECL_BOOL 70
#define AST_DECL_LIST 71
#define AST_VEC_INIT 72
#define AST_NESTED_EXPR 73
#define AST_INPUT_EXPR 74
#define AST_VEC_ACCESS 75
#define AST_CONDITIONAL_STATEMENT 76
#define AST_EMPTY_PARAM_LIST 77

char *ast_type_str(int type);
char *ast_func_param_type_str(int type);
char* ast_type_str(int type) {
    switch (type) {
        case AST_SYMBOL:
            return strdup("AST_SYMBOL");
        case AST_IDENTIFIER:
            return strdup("AST_IDENTIFIER");
        case AST_LIT_INT:
            return strdup("AST_LIT_INT");
        case AST_LIT_REAL:
            return strdup("AST_LIT_REAL");
        case AST_LIT_CHAR:
            return strdup("AST_LIT_CHAR");
        case AST_LIT_STRING:
            return strdup("AST_LIT_STRING");
        case AST_PARAM_LIST:
            return strdup("AST_PARAM_LIST");
        case AST_FUNC_DECL_INT:
            return strdup("AST_FUNC_DECL_INT");
        case AST_FUNC_DECL_REAL:
            return strdup("AST_FUNC_DECL_REAL");
        case AST_FUNC_DECL_CHAR:
            return strdup("AST_FUNC_DECL_CHAR");
        case AST_FUNC_DECL_BOOL:
            return strdup("AST_FUNC_DECL_BOOL");
        case AST_PARAM_INT:
            return strdup("AST_PARAM_INT");
        case AST_PARAM_REAL:
            return strdup("AST_PARAM_REAL");
        case AST_PARAM_CHAR:
            return strdup("AST_PARAM_CHAR");
        case AST_PARAM_BOOL:
            return strdup("AST_PARAM_BOOL");
        case AST_ADD:
            return strdup("AST_ADD");
        case AST_SUB:
            return strdup("AST_SUB");
        case AST_MUL:
            return strdup("AST_MUL");
        case AST_DIV:
            return strdup("AST_DIV");
        case AST_NEG:
            return strdup("AST_NEG");
        case AST_NOT:
            return strdup("AST_NOT");
        case AST_AND:
            return strdup("AST_AND");
        case AST_OR:
            return strdup("AST_OR");
        case AST_LE:
            return strdup("AST_LE");
        case AST_GE:
            return strdup("AST_GE");
        case AST_EQ:
            return strdup("AST_EQ");
        case AST_DIF:
            return strdup("AST_DIF");
        case AST_GT:
            return strdup("AST_GT");
        case AST_LT:
            return strdup("AST_LT");
        case AST_PROGRAM:
            return strdup("AST_PROGRAM");
        case AST_DECLARATION_LIST:
            return strdup("AST_DECLARATION_LIST");
        case AST_DECLARATION:
            return strdup("AST_DECLARATION");
        case AST_PARAMETER_LIST:
            return strdup("AST_PARAMETER_LIST");
        case AST_PARAMETER:
            return strdup("AST_PARAMETER");
        case AST_FUNC_DECLARATION:
            return strdup("AST_FUNC_DECLARATION");
        case AST_BODY:
            return strdup("AST_BODY");
        case AST_CMD_LIST:
            return strdup("AST_CMD_LIST");
        case AST_CMD:
            return strdup("AST_CMD");
        case AST_VAR_ATTRIB:
            return strdup("AST_VAR_ATTRIB");
        case AST_OUTPUT_CMD:
            return strdup("AST_OUTPUT_CMD");
        case AST_OUTPUT_PARAM_LIST:
            return strdup("AST_OUTPUT_PARAM_LIST");
        case AST_RETURN_CMD:
            return strdup("AST_RETURN_CMD");
        case AST_IF:
            return strdup("AST_IF");
        case AST_IF_ELSE:
            return strdup("AST_IF_ELSE");
        case AST_LOOP:
            return strdup("AST_LOOP");
        case AST_VEC_ATTRIB:
            return strdup("AST_VEC_ATTRIB");
        case AST_VEC_DECL_INT:
            return strdup("AST_VEC_DECL_INT");
        case AST_VEC_DECL_REAL:
            return strdup("AST_VEC_DECL_REAL");
        case AST_VEC_DECL_CHAR:
            return strdup("AST_VEC_DECL_CHAR");
        case AST_VEC_DECL_BOOL:
            return strdup("AST_VEC_DECL_BOOL");
        case AST_VEC_INIT_OPT_INT:
            return strdup("AST_VEC_INIT_OPT_INT");
        case AST_VEC_INIT_OPT_REAL:
            return strdup("AST_VEC_INIT_OPT_REAL");
        case AST_VEC_INIT_OPT_CHAR:
            return strdup("AST_VEC_INIT_OPT_CHAR");
        case AST_EXPR_LIST:
            return strdup("AST_EXPR_LIST");
        case AST_FUNC_CALL:
            return strdup("AST_FUNC_CALL");
        case AST_INPUT_EXPR_INT:
            return strdup("AST_INPUT_EXPR_INT");
        case AST_INPUT_EXPR_REAL:
            return strdup("AST_INPUT_EXPR_REAL");
        case AST_INPUT_EXPR_CHAR:
            return strdup("AST_INPUT_EXPR_CHAR");
        case AST_INPUT_EXPR_BOOL:
            return strdup("AST_INPUT_EXPR_BOOL");
        case AST_VAR_DECL_INT:
            return strdup("AST_VAR_DECL_INT");
        case AST_VAR_DECL_REAL:
            return strdup("AST_VAR_DECL_REAL");
        case AST_VAR_DECL_CHAR:
            return strdup("AST_VAR_DECL_CHAR");
        case AST_VAR_DECL_BOOL:
            return strdup("AST_VAR_DECL_BOOL");
        case AST_DECL_LIST:
            return strdup("AST_DECL_LIST");
        case AST_VEC_INIT:
            return strdup("AST_VEC_INIT");
        case AST_NESTED_EXPR:
            return strdup("AST_NESTED_EXPR");
        case AST_VEC_ACCESS:
            return strdup("AST_VEC_ACCESS");
        case AST_INPUT_EXPR:
            return strdup("AST_INPUT_EXPR");
        case AST_CONDITIONAL_STATEMENT:
            return strdup("AST_CONDITIONAL_STATEMENT");
        case AST_EMPTY_PARAM_LIST:
            return strdup("AST_EMPTY_PARAM_LIST");
        default: {
            char* unknown = (char*) calloc(1, sizeof(char) * 100);
            sprintf(unknown, "AST_TYPE_UNKNOWN(%d)", type);
            return unknown;
        }
    }
}


char *ast_func_param_type_str(int type)
{
    switch (type)
    {
    case AST_PARAM_INT:
        return strdup("int");
    case AST_PARAM_REAL:
        return strdup("real");
    case AST_PARAM_CHAR:
        return strdup("char");
    case AST_PARAM_BOOL:
        return strdup("bool");
    default: {
        char *unknown = (char *)calloc(1, sizeof(char) * 100);
        sprintf(unknown, "unknown(%d)", type);
        return unknown;
    }
    }
}