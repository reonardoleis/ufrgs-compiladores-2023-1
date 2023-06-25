#pragma once
#include "hash.h"
#include "ast_types.h"
#include <string.h>
#include <stdio.h>

#define MAX_SONS 4

typedef struct ast_node
{
    int type;
    hash_t *symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST *root;

AST *astCreate(int type, hash_t *symbol, AST *s0, AST *s1, AST *s2, AST *s3);
void astPrint(AST *node, int level);
char *astToCode(AST *node, char *code);
char *handleVecOptInitialization(AST *vec_init_opt_root_node);
char *handleFunctinDeclarationParams(AST *func_decl_params_root_node);
int isLeaf(AST *node);

AST *astCreate(int type, hash_t *symbol, AST *s0, AST *s1, AST *s2, AST *s3)
{
    // fprintf(stderr, "astCreate(%s)\n", ast_type_str(type));
    AST *ast = (AST *)calloc(1, sizeof(AST));
    ast->type = type;
    ast->symbol = symbol;
    ast->son[0] = s0;
    ast->son[1] = s1;
    ast->son[2] = s2;
    ast->son[3] = s3;

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

    fprintf(stderr, "AST(");
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

char *astToCode(AST *node, char *code)
{
    if (node == 0)
    {
        return code;
    }

    // fprintf(stderr, "Node %s with value %s\n\n", ast_type_str(node->type), node->symbol->text);

    if (isLeaf(node))
    {
        return node->symbol->text;
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        AST *current_node = node->son[i];
        if (current_node != NULL)
        {

            switch (node->son[i]->type)
            {

            // variable declaration
            case AST_VAR_DECL_INT:
            {
                sprintf(code, "%sint %s = %s;\n", code, current_node->symbol->text, astToCode(current_node, code));
                break;
            }
            case AST_VAR_DECL_REAL:
            {
                sprintf(code, "%sreal %s = %s;\n", code, current_node->symbol->text, astToCode(current_node, code));
                break;
            }
            case AST_VAR_DECL_CHAR:
            {
                sprintf(code, "%schar %s = %s;\n", code, current_node->symbol->text, astToCode(current_node, code));
                break;
            }
            case AST_VAR_DECL_BOOL:
            {
                sprintf(code, "%sbool %s = %s;\n", code, current_node->symbol->text, astToCode(current_node, code));
                break;
            }

            // vector declaration
            case AST_VEC_DECL_INT:
            {
                sprintf(code, "%sint %s[%s]%s\n", code, current_node->symbol->text, astToCode(current_node, code), handleVecOptInitialization(current_node->son[1]));
                break;
            }
            case AST_VEC_DECL_REAL:
            {
                sprintf(code, "%sreal %s[%s]%s\n", code, current_node->symbol->text, astToCode(current_node, code), handleVecOptInitialization(current_node->son[1]));
                break;
            }
            case AST_VEC_DECL_CHAR:
            {
                sprintf(code, "%schar %s[%s]%s\n", code, current_node->symbol->text, astToCode(current_node, code), handleVecOptInitialization(current_node->son[1]));
                break;
            }
            case AST_VEC_DECL_BOOL:
            {
                sprintf(code, "%sbool %s[%s]%s\n", code, current_node->symbol->text, astToCode(current_node, code), handleVecOptInitialization(current_node->son[1]));
                break;
            }

            // function declaration
            case AST_FUNC_DECL_INT:
            {
                sprintf(code, "%sint %s(%s)%s\n", code, current_node->symbol->text, handleFunctinDeclarationParams(current_node->son[0]), astToCode(current_node->son[1], code));
                break;
            }
            case AST_FUNC_DECL_REAL:
            {
                sprintf(code, "%sreal %s(%s)%s\n", code, current_node->symbol->text, handleFunctinDeclarationParams(current_node->son[0]), astToCode(current_node->son[1], code));
                break;
            }
            case AST_FUNC_DECL_CHAR:
            {
                sprintf(code, "%schar %s(%s)%s\n", code, current_node->symbol->text, handleFunctinDeclarationParams(current_node->son[0]), astToCode(current_node->son[1], code));
                break;
            }
            case AST_FUNC_DECL_BOOL:
            {
                sprintf(code, "%sbool %s(%s)%s\n", code, current_node->symbol->text, handleFunctinDeclarationParams(current_node->son[0]), astToCode(current_node->son[1], code));
                break;
            }

            // body
            case AST_CMD_LIST:
            {
                sprintf(code, "%s{\n%s\n}\n", code, astToCode(current_node->son[0], code));
                break;
            }

            // var attrib
            case AST_VAR_ATTRIB:
            {
                return astToCode(current_node, code);
            }

            default:
            {
                return astToCode(current_node, code);
            }
            }
        }
    }

    fprintf(stderr, "\n%s\n", code);

    return code;
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