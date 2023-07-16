#pragma once
#include "ast.h"
#include "hash.h"

int is_arithmetic(AST *node);
int is_numeric(AST *node);
int is_logic(AST *node);
int is_unary(AST *node);
int is_binary(AST *node);
int is_func_declaration(AST *node);
int validate_return_type(AST * func, AST * return_cmd);

int is_arithmetic(AST *node) {
    if (!node) return 0;

    switch (node->type) {
        case AST_MUL:
        case AST_DIV:
        case AST_ADD:
        case AST_SUB:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
        case AST_GT:
        case AST_LT:
            return 1;
        default:
            return 0;
    }
}

int is_numeric(AST *node) {
    if (!node) return 0;

    switch (node->type) {
        case AST_LIT_INT:
        case AST_LIT_REAL:
        case AST_LIT_CHAR:
            return 1;
        case AST_VEC_ACCESS:
            {
                if (node->symbol->type == SYMBOL_VECTOR) {
                    if (node->symbol->datatype == DATATYPE_INT 
                    ||  node->symbol->datatype == DATATYPE_REAL
                    ||  node->symbol->datatype == DATATYPE_CHAR) {
                        return 1;
                    }
                }
                return 0;
            }
        case AST_FUNC_CALL: 
            {
                if (node->symbol->type == SYMBOL_FUNCTION) {
                    if (node->symbol->datatype == DATATYPE_INT 
                    ||  node->symbol->datatype == DATATYPE_REAL
                    ||  node->symbol->datatype == DATATYPE_CHAR) {
                        return 1;
                    }
                }
                return 0;    
            }
        default:
            return 0;
    }
}

int is_logic(AST *node) {
    if (!node) return 0;

    switch (node->type) {
        case AST_AND:
        case AST_OR:
        case AST_NOT:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
        case AST_GT:
        case AST_LT:
            return 1;
        case AST_IDENTIFIER:
            return node->symbol->datatype == DATATYPE_BOOL;
        case AST_VEC_ACCESS:
            {
                if (node->symbol->type == SYMBOL_VECTOR) {
                    if (node->symbol->datatype == DATATYPE_BOOL) {
                        return 1;
                    }
                }
                return 0;
            }
        case AST_FUNC_CALL:
            {
                if (node->symbol->type == SYMBOL_FUNCTION) {
                    if (node->symbol->datatype == DATATYPE_BOOL) {
                        return 1;
                    }
                }
                return 0;
            }
        default:
            return 0;
    }
}

int is_bool(AST *node) {
    return node->type == AST_IDENTIFIER && node->symbol->datatype == DATATYPE_BOOL;
}

int is_unary(AST *node) {
    if (!node) return 0;

    switch (node->type) {
        case AST_NOT:
        case AST_SUB:
            return 1;
        default:
            return 0;
    }
}

int is_binary(AST *node) {
    if (!node) return 0;

    switch (node->type) {
        case AST_MUL:
        case AST_DIV:
        case AST_ADD:
        case AST_SUB:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
        case AST_GT:
        case AST_LT:
        case AST_AND:
        case AST_OR:
            return 1;
        default:
            return 0;
    }
}

int is_func_declaration(AST *node) {
    if (!node) return 0;

    return node->type == AST_FUNC_DECL_INT || node->type == AST_FUNC_DECL_REAL || node->type == AST_FUNC_DECL_CHAR || node->type == AST_FUNC_DECL_BOOL;
}

int validate_return_type(AST * func, AST * return_cmd) {
    
    if (!func || !return_cmd) return 0;



    return 
        (return_cmd->symbol->datatype == func->symbol->datatype) ||
        (return_cmd->type == AST_LIT_INT && func->symbol->datatype == DATATYPE_INT) ||
        (return_cmd->type == AST_LIT_CHAR && func->symbol->datatype == DATATYPE_INT) ||
        (return_cmd->type == AST_LIT_INT && func->symbol->datatype == DATATYPE_CHAR) ||
        (return_cmd->type == AST_LIT_CHAR && func->symbol->datatype == DATATYPE_CHAR) ||
        (return_cmd->type == AST_LIT_REAL && func->symbol->datatype == DATATYPE_REAL);
}