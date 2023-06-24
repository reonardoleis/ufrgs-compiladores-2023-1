#pragma once
#include "hash.h"
#include "ast_types.h"
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
char* astToCode(AST *node, char *code);
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

char* astToCode(AST *node, char *code)
{
    if (node == 0)
    {
        return "";
    }

    int i;

    if (isLeaf(node))
    {
        return node->symbol->text;
    }
    else
    {   
        for (i = 0; i < MAX_SONS; i++)
        {
            if (node->son[i] != 0)
            {
                switch (node->type)
                {

                // variable declaration
                case AST_VAR_DECL_INT:      sprintf(code, "%sint %s = %s;\n", code, node->symbol->text,  astToCode(node->son[i], code)); return code;
                case AST_VAR_DECL_REAL:     sprintf(code, "%s float %s = %s;\n", code,  node->symbol->text,  astToCode(node->son[i], code)); return code;
                case AST_VAR_DECL_CHAR:     sprintf(code, "%schar %s = %s;\n", code, node->symbol->text,  astToCode(node->son[i], code)); return code;
                case AST_VAR_DECL_BOOL:     sprintf(code, "%sbool %s = %s;\n", code, node->symbol->text,  astToCode(node->son[i], code)); return code;
               
                // vector declaration
                case AST_VEC_DECL_INT:   sprintf(code, "%sint %s[%s]", code, node->symbol->text,  astToCode(node->son[i], code)); return code;
                case AST_VEC_DECL_REAL:  sprintf(code, "%sfloat %s[%s]", code, node->symbol->text,  astToCode(node->son[i], code)); return code;
                case AST_VEC_DECL_CHAR:  sprintf(code, "%schar %s[%s]", code, node->symbol->text,  astToCode(node->son[i], code)); return code;
                case AST_VEC_DECL_BOOL:  sprintf(code, "%sbool %s[%s]", code, node->symbol->text,  astToCode(node->son[i], code)); return code;

                default:
                    return astToCode(node->son[i], code);
                }
            }
        }
    }
}



