#pragma once
#include "hash.h"

#define MAX_SONS 4

extern int SemanticErrors;

extern int ast_node_id;

typedef struct ast_node
{
    int id;
    int type;
    HASH *symbol;
    int typechecked;
    int result_datatype;
    int line_number;
    struct ast_node *son[MAX_SONS];
} AST;

AST *root;

AST *astCreate(int type, HASH *symbol, AST *s0, AST *s1, AST *s2, AST *s3, int line_number);
void astPrint(AST *node, int level);
char *astToCode(AST *node);
char *handleVecOptInitialization(AST *vec_init_opt_root_node);
char *handleFunctinDeclarationParams(AST *func_decl_params_root_node);
int isLeaf(AST *node);
int is_input_cmd(AST *node);
int get_input_cmd_type(AST *node);