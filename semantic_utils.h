#pragma once
#include "ast.h"
#include "hash.h"

int is_arithmetic(AST *node);
int is_numeric(AST *node);
int is_logic(AST *node);
int is_unary(AST *node);
int is_binary(AST *node);
int is_func_declaration(AST *node);
int validate_return_type(int required_return_datatype, AST * return_cmd);
int verify_literal_compatibility(int lit_type1, int lit_type2);

int is_arithmetic(AST *node) {
    if (!node) return 0;

    switch (node->type) {
        case AST_MUL:
        case AST_DIV:
        case AST_ADD:
        case AST_SUB:
        case AST_NESTED_EXPR:
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
        case AST_IDENTIFIER:
            return node->symbol->datatype == DATATYPE_INT 
                || node->symbol->datatype == DATATYPE_REAL
                || node->symbol->datatype == DATATYPE_CHAR;
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
        case AST_NEG:
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

int validate_return_type(int required_return_type, AST * return_cmd) {

    if (!return_cmd) return 0;


    int compatible_char_int = 0;

    int datatype = 0;

    if (return_cmd->symbol) {
        datatype = return_cmd->symbol->datatype;
    } else {
        datatype = return_cmd->result_datatype;
    }

    if (datatype == DATATYPE_CHAR && required_return_type == DATATYPE_INT) {
        compatible_char_int = 1;
    }

   


    if (datatype == DATATYPE_INT && required_return_type == DATATYPE_CHAR) {
        compatible_char_int = 1;
    }


    return 
        compatible_char_int ||
        (datatype == required_return_type) ||
        (return_cmd->type == AST_LIT_INT && required_return_type == DATATYPE_INT) ||
        (return_cmd->type == AST_LIT_CHAR && required_return_type == DATATYPE_INT) ||
        (return_cmd->type == AST_LIT_INT && required_return_type == DATATYPE_CHAR) ||
        (return_cmd->type == AST_LIT_CHAR && required_return_type == DATATYPE_CHAR) ||
        (return_cmd->type == AST_LIT_REAL && required_return_type == DATATYPE_REAL);
}

int compare_datatypes(int a, int b) {
    int compatible_char_int = 0;
    if (a == DATATYPE_CHAR && b == DATATYPE_INT) {
        compatible_char_int = 1;
    }

    if (a == DATATYPE_INT && b == DATATYPE_CHAR) {
        compatible_char_int = 1;
    }

    return compatible_char_int || a == b;
}


int verify_literal_compatibility(int lit_type1, int lit_type2) {
    if (lit_type1 == lit_type2) {
        return 1;
    }

    if (lit_type1 == AST_LIT_CHAR && lit_type2 == AST_LIT_INT) {
        return 1;
    }

    if (lit_type1 == AST_LIT_INT && lit_type2 == AST_LIT_CHAR) {
        return 1;
    }

    return 0;
}