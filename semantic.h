#pragma once
#include "ast.h"
#include "hash.h"
#include "symbols.h"

int SemanticErrors = 0;

void check_and_set_declarations(AST *node);
void check_undeclared(void);

void check_and_set_declarations(AST *node) {
    int i;


    if (!node) return;

    switch (node->type) {
        case AST_VAR_DECL_INT:
        case AST_VAR_DECL_CHAR:
        case AST_VAR_DECL_REAL:
        case AST_VAR_DECL_BOOL:
        {
            if (node->symbol) {
                if (node->symbol->type != SYMBOL_IDENTIFIER) {
                    fprintf(stderr, "Semantic Error: variable %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                }

                 node->symbol->type = SYMBOL_VARIABLE;
            }

            break;
        }
        case AST_VEC_DECL_INT:
        case AST_VEC_DECL_CHAR:
        case AST_VEC_DECL_REAL:
        case AST_VEC_DECL_BOOL:
        {
            if (node->symbol) {
                if (node->symbol->type != SYMBOL_IDENTIFIER) {
                    fprintf(stderr, "Semantic Error: vector %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                }

                 node->symbol->type = SYMBOL_VECTOR;
            }

            break;
        }
        case AST_FUNC_DECL_INT:
        case AST_FUNC_DECL_CHAR:
        case AST_FUNC_DECL_REAL:
        case AST_FUNC_DECL_BOOL:
        {
            if (node->symbol) {
                if (node->symbol->type != SYMBOL_IDENTIFIER) {
                    fprintf(stderr, "Semantic Error: function %s already declared\n", node->symbol->text);
                    SemanticErrors++;
                }

                 node->symbol->type = SYMBOL_FUNCTION;
            }

            break;
        }

    }

    for (i = 0; i < MAX_SONS; i++) {
        check_and_set_declarations(node->son[i]);
    }

}