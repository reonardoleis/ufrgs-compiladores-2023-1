#include "hash.h"
#include "ast_types.h"
#include "ast.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

AST *root;
int ast_node_id = 0;

AST *astCreate(int type, HASH *symbol, AST *s0, AST *s1, AST *s2, AST *s3, int line_number)
{
    // fprintf(stderr, "astCreate(%s)\n", ast_type_str(type));
    AST *ast = (AST *)calloc(1, sizeof(AST));
    ast->type = type;
    ast->typechecked = 0;
    ast->symbol = symbol;
    ast->line_number = line_number;
    ast->son[0] = s0;
    ast->son[1] = s1;
    ast->son[2] = s2;
    ast->son[3] = s3;

    ast->id = ast_node_id++;

    return ast;
}

void astPrint(AST *ast, int level)
{
    if (ast == 0)
    {
        return;
    }

    int i;
    for (int i = 0; i < level; i++)
    {
        fprintf(stderr, "  ");
    }


    if (ast->result_datatype) {
        fprintf(stderr, "AST[%s](", datatype_str[ast->result_datatype]);
    } else {
        fprintf(stderr, "AST(");
    }

    char * debug = getenv("DEBUG");
    if (debug != NULL && strcmp(debug, "1") == 0) {
        fprintf(stderr, "<%d>,", ast->id);
    }
    
    fprintf(stderr, "%s", ast_type_str(ast->type));

    if (ast->symbol != 0)
    {
        fprintf(stderr, ",%s\n", ast->symbol->text);
    }
    else
    {
        fprintf(stderr, ",0\n");
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        astPrint(ast->son[i], level + 1);
    }
}

int isLeaf(AST *node)
{
    return node->son[0] == 0 && node->son[1] == 0 && node->son[2] == 0 && node->son[3] == 0;
}

char code[50000000];
inline char *astToCode(AST *node)
{
    if (node == 0)
    {
        return strdup("");
    }

    switch (node->type) {
        case AST_PROGRAM:       {  return astToCode(node->son[0]); }
        case AST_DECL_LIST:     { sprintf(code, "%s%s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        // variable declarations
        case AST_VAR_DECL_INT:  { sprintf(code, "int %s = %s;\n", node->symbol->text, node->son[0]->symbol->text); return strdup(code); }
        case AST_VAR_DECL_CHAR: { sprintf(code, "char %s = %s;\n", node->symbol->text, node->son[0]->symbol->text); return strdup(code); }
        case AST_VAR_DECL_REAL: { sprintf(code, "real %s = %s;\n", node->symbol->text, node->son[0]->symbol->text); return strdup(code); }
        case AST_VAR_DECL_BOOL: { sprintf(code, "bool %s = %s;\n", node->symbol->text, node->son[0]->symbol->text); return strdup(code); }

        // vector declarations
        case AST_VEC_DECL_INT:  { sprintf(code, "int %s[%s]%s;\n", node->symbol->text, node->son[0]->symbol->text, astToCode(node->son[1])); return strdup(code); }
        case AST_VEC_DECL_CHAR:  { sprintf(code, "char %s[%s]%s;\n", node->symbol->text, node->son[0]->symbol->text, astToCode(node->son[1])); return strdup(code); }
        case AST_VEC_DECL_REAL:  { sprintf(code, "real %s[%s]%s;\n", node->symbol->text, node->son[0]->symbol->text, astToCode(node->son[1])); return strdup(code); }
        case AST_VEC_DECL_BOOL:  { sprintf(code, "bool %s[%s]%s;\n", node->symbol->text, node->son[0]->symbol->text, astToCode(node->son[1])); return strdup(code); }


        // vector opt init
        case AST_VEC_INIT_OPT_INT:
        case AST_VEC_INIT_OPT_CHAR: 
        case AST_VEC_INIT_OPT_REAL: { sprintf(code, " %s%s", node->son[0]->symbol->text, astToCode(node->son[1])); return strdup(code); }

        // func declarations
        case AST_FUNC_DECL_INT: { sprintf(code, "int %s(%s)%s\n\n", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_FUNC_DECL_CHAR: { sprintf(code, "char %s(%s)%s\n\n", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_FUNC_DECL_REAL: { sprintf(code, "real %s(%s)%s\n\n", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_FUNC_DECL_BOOL: { sprintf(code, "bool %s(%s)%s\n\n", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }

        // func decl parameters
        case AST_PARAM_LIST: 
        { 
            if (node->son[1] != NULL) {
                sprintf(code, "%s %s, %s", ast_func_param_type_str(node->son[0]->type), node->son[0]->symbol->text, astToCode(node->son[1]));
            } else {
                sprintf(code, "%s %s", ast_func_param_type_str(node->son[0]->type), node->son[0]->symbol->text);
            }

            return strdup(code);
        }

        case AST_BODY: { sprintf(code, "{%s\n}%s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }

        case AST_CMD_LIST: { sprintf(code, "%s%s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }

        case AST_VAR_ATTRIB: { sprintf(code, "\n\t%s = %s;", node->symbol->text, astToCode(node->son[0])); return strdup(code); }

        case AST_VEC_ATTRIB: { sprintf(code, "\n\t%s[%s] = %s;", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }

        case AST_OUTPUT_CMD: { sprintf(code, "\n\toutput %s;", astToCode(node->son[0])); return strdup(code); }

        case AST_OUTPUT_PARAM_LIST: { 
            if (node->son[1] != NULL) {
                sprintf(code, "%s,%s", astToCode(node->son[0]), astToCode(node->son[1]));
            } else {
                sprintf(code, "%s", astToCode(node->son[0]));
            }

            return strdup(code);
        }

        // literals (covers expr literals)
        case AST_LIT_INT:
        case AST_LIT_REAL: 
        case AST_LIT_CHAR: 
        case AST_LIT_STRING: { sprintf(code, "%s", node->symbol->text); return strdup(code); }

        // expr
        case AST_IDENTIFIER: { sprintf(code, "%s", node->symbol->text); return strdup(code); }
        
        case AST_MUL: { sprintf(code, "%s * %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_DIV: { sprintf(code, "%s / %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_ADD: { sprintf(code, "%s + %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_SUB: { sprintf(code, "%s - %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_NEG: { sprintf(code, "-%s", astToCode(node->son[0])); return strdup(code); }
        case AST_NOT: { sprintf(code, "~%s", astToCode(node->son[0])); return strdup(code); }
        case AST_AND: { sprintf(code, "%s & %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_OR: { sprintf(code, "%s | %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_LE: { sprintf(code, "%s <= %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_GE: { sprintf(code, "%s >= %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_EQ: { sprintf(code, "%s == %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_DIF: { sprintf(code, "%s != %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_GT: { sprintf(code, "%s > %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_LT: { sprintf(code, "%s < %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        
        case AST_NESTED_EXPR: { sprintf(code, "(%s)", astToCode(node->son[0])); return strdup(code); }

        case AST_VEC_ACCESS:  { sprintf(code, "%s[%s]", node->symbol->text, astToCode(node->son[0])); return strdup(code); }

        case AST_INPUT_EXPR_INT: { sprintf(code, "input(int)"); return strdup(code); }
        case AST_INPUT_EXPR_CHAR: { sprintf(code, "input(char)"); return strdup(code); }
        case AST_INPUT_EXPR_REAL: { sprintf(code, "tinput(real)"); return strdup(code); }
        case AST_INPUT_EXPR_BOOL: { sprintf(code, "input(bool)"); return strdup(code); }

        case AST_FUNC_CALL: { sprintf(code, "%s(%s)", node->symbol->text, astToCode(node->son[0])); return strdup(code); }

        case AST_EXPR_LIST: { 
            if (node->son[1] != NULL) {
                sprintf(code, "%s, %s", astToCode(node->son[0]), astToCode(node->son[1]));
            } else {
                sprintf(code, "%s", astToCode(node->son[0]));
            }

            return strdup(code);
        }

        case AST_RETURN_CMD: { sprintf(code, "\n\treturn %s;", astToCode(node->son[0])); return strdup(code); }


        // ifs

        case AST_IF: { sprintf(code, "\n\tif (%s) %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_IF_ELSE: { sprintf(code, "\n\tif (%s) %s else %s", astToCode(node->son[0]), astToCode(node->son[1]), astToCode(node->son[2])); return strdup(code);}
        case AST_LOOP: { sprintf(code, "\n\tif (%s) loop %s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }
        case AST_CONDITIONAL_STATEMENT: { sprintf(code, "%s%s", astToCode(node->son[0]), astToCode(node->son[1])); return strdup(code); }

        default: { return strdup(""); }
    }
    

    return strdup(code);
}

char *handleVecOptInitialization(AST *vec_init_opt_root_node)
{
    if (vec_init_opt_root_node == NULL)
    {
        return ";";
    }
    char *out = (char *)calloc(1, sizeof(char));
    AST *current_opt = vec_init_opt_root_node;

    while (current_opt->son[1] != NULL)
    {
        // copy out to temp var, reallocate out to new size, copy temp var to out, strcat out with current_opt->son[0]->symbol->text
        char *temp = (char *)calloc(strlen(out), sizeof(char));
        strcpy(temp, out);
        out = (char *)realloc(out, strlen(out) + strlen(current_opt->son[0]->symbol->text) + 1);
        strcpy(out, temp);
        strcat(out, " ");
        strcat(out, current_opt->son[0]->symbol->text);
        current_opt = current_opt->son[1];
    }

    char *temp = (char *)calloc(strlen(out), sizeof(char));
    strcpy(temp, out);
    out = (char *)realloc(out, strlen(out) + strlen(current_opt->son[0]->symbol->text) + 2);
    strcpy(out, temp);
    strcat(out, " ");
    strcat(out, current_opt->son[0]->symbol->text);
    strcat(out, ";");

    return out;
}

char *handleFunctinDeclarationParams(AST *func_decl_params_root_node)
{
    if (func_decl_params_root_node == NULL)
    {
        return "";
    }
    char *out = (char *)calloc(1, sizeof(char));
    AST *current_opt = func_decl_params_root_node;
    char *param_type;
    while (current_opt->son[1] != NULL)
    {
        
        param_type = ast_func_param_type_str(current_opt->son[0]->type);

        char *temp = (char *)calloc(strlen(out), sizeof(char));
        strcpy(temp, out);
        out = (char *)realloc(out, strlen(out) + strlen(param_type) + strlen(current_opt->son[0]->symbol->text) + 4);
        strcpy(out, temp);
        strcat(out, param_type);
        strcat(out, " ");
        strcat(out, current_opt->son[0]->symbol->text);
        strcat(out, ", ");


        current_opt = current_opt->son[1];
    }

    param_type = ast_func_param_type_str(current_opt->son[0]->type);
    char *temp = (char *)calloc(strlen(out), sizeof(char));
    strcpy(temp, out);
    out = (char *)realloc(out, strlen(out) + strlen(param_type) + strlen(current_opt->son[0]->symbol->text) + 3);
    strcpy(out, temp);
    strcat(out, param_type);
    strcat(out, " ");
    strcat(out, current_opt->son[0]->symbol->text);

    return out;
}

int is_input_cmd(AST *node)
{
    return node->type == AST_INPUT_EXPR_INT || node->type == AST_INPUT_EXPR_REAL || node->type == AST_INPUT_EXPR_CHAR || node->type == AST_INPUT_EXPR_BOOL;
}

int get_input_cmd_type(AST *node) {
    if (node->type == AST_INPUT_EXPR_INT) {
        return DATATYPE_INT;
    } else if (node->type == AST_INPUT_EXPR_REAL) {
        return DATATYPE_REAL;
    } else if (node->type == AST_INPUT_EXPR_CHAR) {
        return DATATYPE_CHAR;
    } else if (node->type == AST_INPUT_EXPR_BOOL) {
        return DATATYPE_BOOL;
    } else {
        return -1;
    }
}