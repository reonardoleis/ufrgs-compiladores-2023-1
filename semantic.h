#pragma once
#include "ast.h"
#include "ast_types.h"
#include "hash.h"
#include "symbols.h"
#include "debug.h"
#include "semantic_utils.h"

int SemanticErrors = 0;

void check_and_set_declarations(AST *node);
void check_undeclared(void);
void check_operands(AST *node);
int expression_typecheck(AST *node);
int find_first_datatype(AST *node);
int check_attributions(AST *node);
int check_return(AST *node);

void check_and_set_declarations(AST *node)
{
    int i;

    if (!node)
        return;

    switch (node->type)
    {
    case AST_VAR_DECL_INT:
    case AST_VAR_DECL_CHAR:
    case AST_VAR_DECL_REAL:
    case AST_VAR_DECL_BOOL:
    {
        if (node->symbol)
        {
            if (node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic Error: identifier %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }

            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = ast_type_to_datatype(node->type);
        }

        break;
    }
    case AST_VEC_DECL_INT:
    case AST_VEC_DECL_CHAR:
    case AST_VEC_DECL_REAL:
    case AST_VEC_DECL_BOOL:
    {
        if (node->symbol)
        {
            if (node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic Error: identifier %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }

            node->symbol->type = SYMBOL_VECTOR;
            node->symbol->datatype = ast_type_to_datatype(node->type);
        }

        break;
    }
    case AST_FUNC_DECL_INT:
    case AST_FUNC_DECL_CHAR:
    case AST_FUNC_DECL_REAL:
    case AST_FUNC_DECL_BOOL:
    {
        if (node->symbol)
        {
            if (node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic Error: identifier %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }

            node->symbol->type = SYMBOL_FUNCTION;
            node->symbol->datatype = ast_type_to_datatype(node->type);
        }

        break;
    }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        check_and_set_declarations(node->son[i]);
    }
}

void check_undeclared(void)
{
    SemanticErrors += hash_check_undeclared();
}

void check_operands(AST *node)
{
    int i;

    if (!node)
        return;

    switch (node->type)
    {
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
    {
        debug_printf("node->type: %s\n", ast_type_str(node->type));
        AST *left_operand = node->son[0];
        AST *right_operand = node->son[1];

        if (!(left_operand->type == AST_NESTED_EXPR) && !is_numeric(left_operand) && !is_arithmetic(left_operand))
        {
            fprintf(stderr, "Semantic Error: invalid left operand\n");
            ++SemanticErrors;
        }

        if (!(right_operand->type == AST_NESTED_EXPR) && !is_numeric(right_operand) && !is_arithmetic(right_operand))
        {
            fprintf(stderr, "Semantic Error: invalid right operand\n");
            ++SemanticErrors;
        }

        if (!expression_typecheck(node))
        {
            fprintf(stderr, "Semantic Error: invalid resulting expression type %s\n", ast_type_str(node->type));
            ++SemanticErrors;
        }
        else
        {
            node->result_datatype = find_first_datatype(node);
        }

        break;
    }

    case AST_NEG:
    {
        AST *operand = node->son[0];
        if (!(operand->type == AST_NESTED_EXPR) && !is_numeric(operand) && !is_arithmetic(operand))
        {
            fprintf(stderr, "Semantic Error: invalid unary arithmetic/numeric operand\n");
            ++SemanticErrors;
        }

        if (!expression_typecheck(node))
        {
            fprintf(stderr, "Semantic Error: invalid resulting expression type %s\n", ast_type_str(node->type));
            ++SemanticErrors;
        }
        else
        {
            node->result_datatype = find_first_datatype(node);
        }
        break;
    }

    case AST_AND:
    case AST_OR:
    {
        AST *left_operand = node->son[0];
        AST *right_operand = node->son[1];

        if (!is_bool(left_operand) && !(left_operand->type == AST_NESTED_EXPR) && !is_logic(left_operand))
        {
            fprintf(stderr, "Semantic Error: invalid left operand for %s\n", ast_type_str(node->type));
            ++SemanticErrors;
        }

        if (!is_bool(right_operand) && !(right_operand->type == AST_NESTED_EXPR) && !is_logic(right_operand))
        {
            fprintf(stderr, "Semantic Error: invalid right operand for %s\n", ast_type_str(node->type));
            ++SemanticErrors;
        }

        if (!expression_typecheck(node))
        {
            fprintf(stderr, "Semantic Error: invalid resulting expression type %s\n", ast_type_str(node->type));
            ++SemanticErrors;
        }
        else
        {
            node->result_datatype = find_first_datatype(node);
        }

        break;
    }

    case AST_NOT:
    {
        AST *operand = node->son[0];
        if (!(operand->type == AST_NESTED_EXPR) && !is_logic(operand) && !is_bool(operand))
        {
            fprintf(stderr, "Semantic Error: invalid unary logical operand (%s)\n", datatype_str[operand->symbol->datatype]);
            ++SemanticErrors;
        }

        if (!expression_typecheck(node))
        {
            fprintf(stderr, "Semantic Error: invalid resulting expression type %s\n", ast_type_str(node->type));
            ++SemanticErrors;
        }
        else
        {
            node->result_datatype = find_first_datatype(node);
        }

        break;
    }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        check_operands(node->son[i]);
    }
}

int expression_typecheck(AST *node)
{
    int i;

    if (!node)
        return 0;
    if (node->typechecked)
        return 1;

    if (node->type == AST_IDENTIFIER || node->type == AST_VEC_ACCESS || node->type == AST_FUNC_CALL ||
        node->type == AST_LIT_INT || node->type == AST_LIT_REAL || node->type == AST_LIT_CHAR)
    {
        if (node->symbol)
        {
            node->typechecked = 1;

            if (node->symbol->datatype == DATATYPE_CHAR)
            {
                return DATATYPE_INT;
            }
            return node->symbol->datatype;
        }
    }

    if (is_logic(node))
    {
        debug_printf("IS_LOGIC! %s\n", ast_type_str(node->type));
        if (is_binary(node))
        {
            node->typechecked = 1;

            debug_printf("son[0] logic (type = %s)? %d\n", ast_type_str(node->son[0]->type), is_logic(node->son[0]));
            debug_printf("son[1] logic (type = %s) ? %d\n", ast_type_str(node->son[1]->type), is_logic(node->son[1]));

            return ((node->son[0]->type == AST_NESTED_EXPR || is_logic(node->son[0])) && expression_typecheck(node->son[1])) ||
                   ((node->son[1]->type == AST_NESTED_EXPR || is_logic(node->son[1])) && expression_typecheck(node->son[0])) ||
                   (expression_typecheck(node->son[0]) && expression_typecheck(node->son[1]));
        }

        if (is_unary(node))
        {
            node->typechecked = 1;
            return (is_logic(node->son[0]) && expression_typecheck(node->son[0])) ||
                   (expression_typecheck(node->son[0]));
        }
    }

    if (is_binary(node))
    {
        node->typechecked = 1;
        return expression_typecheck(node->son[0]) == expression_typecheck(node->son[1]);
    }

    if (is_unary(node))
    {
        node->typechecked = 1;
        return expression_typecheck(node->son[0]);
    }
}

int find_first_datatype(AST *node)
{
    int i;

    if (!node)
        return 0;

    if (is_logic(node))
    {
        return DATATYPE_BOOL;
    }

    if (node->type == AST_IDENTIFIER || node->type == AST_VEC_ACCESS || node->type == AST_FUNC_CALL ||
        node->type == AST_LIT_INT || node->type == AST_LIT_REAL || node->type == AST_LIT_CHAR)
    {
        if (node->symbol)
        {
            return node->symbol->datatype;
        }
    }

    if (is_binary(node))
    {
        return find_first_datatype(node->son[0]);
    }

    if (is_unary(node))
    {
        return find_first_datatype(node->son[0]);
    }
}

int check_attributions(AST *node)
{
    int i;

    if (!node)
        return 0;

    if (node->type == AST_VAR_ATTRIB)
    {

        int expected_datatype = node->symbol->datatype;
        int resulting_datatype = node->son[0]->result_datatype;

        if (expected_datatype != resulting_datatype && resulting_datatype != 0)
        {
            fprintf(stderr, "Semantic Error: invalid attribution of %s to %s\n", datatype_str[resulting_datatype], datatype_str[expected_datatype]);
            ++SemanticErrors;
        }
    }

    if (node->type == AST_VEC_ATTRIB)
    {
        AST *vec_indexer = node->son[0];

        if (vec_indexer->type != AST_LIT_INT && vec_indexer->type != AST_LIT_CHAR)
        {

            if (vec_indexer->type == AST_FUNC_CALL)
            {
                int func_datatype = vec_indexer->symbol->datatype;
                if (func_datatype != DATATYPE_INT && func_datatype != DATATYPE_CHAR)
                {
                    fprintf(stderr, "Semantic Error: invalid vector indexer type (expected int or char, got %s -> %s)\n", ast_type_str(vec_indexer->type), datatype_str[func_datatype]);
                    ++SemanticErrors;
                }
            }
            else
            {
                int vec_indexer_result_type = vec_indexer->result_datatype;
                if (vec_indexer_result_type != DATATYPE_INT && vec_indexer_result_type != DATATYPE_CHAR)
                {
                    fprintf(stderr, "Semantic Error: invalid vector indexer type (expected int or char, got %s)\n", ast_type_str(node->type));
                    ++SemanticErrors;
                }
            }
        }

        int expected_datatype = node->symbol->datatype;
        int resulting_datatype = node->son[1]->result_datatype;

        if (expected_datatype != resulting_datatype && resulting_datatype != 0)
        {
            fprintf(stderr, "Semantic Error: invalid attribution of %s to %s[]\n", datatype_str[resulting_datatype], datatype_str[expected_datatype]);
            ++SemanticErrors;
        }

    }

    for (i = 0; i < MAX_SONS; i++)
    {
        check_attributions(node->son[i]);
    }
}

int check_return(AST *node)
{
    int i;

    if (!node)
        return 0;

    if (is_func_declaration(node))
    {
        int found = 0;
        AST * body = node->son[1];
        AST * cmd_list = body->son[0];
        if (cmd_list) {
            AST * cmd = cmd_list->son[0];
            while (cmd) {
                
                if (cmd->type == AST_RETURN_CMD) {
                    found = 1;
                    if (cmd->son[0]->result_datatype != node->symbol->datatype && !validate_return_type(node, cmd->son[0])) {
                        if (cmd->son[0]->result_datatype == 0) {
                            fprintf(stderr, "Semantic Error: invalid return type (expected %s, got %s -> %s)\n", datatype_str[node->symbol->datatype], ast_type_str(cmd->son[0]->type), datatype_str[cmd->son[0]->symbol->datatype]);
                        } else {
                            fprintf(stderr, "Semantic Error: invalid return type (expected %s, got %s)\n", datatype_str[node->symbol->datatype], datatype_str[cmd->son[0]->result_datatype]);
                        }
                        ++SemanticErrors;
                    }

                    break;
                }
                
                if (cmd_list->son[1] != NULL) {
                    cmd_list = cmd_list->son[1];
                    if (cmd_list) cmd = cmd_list->son[0];
                } else {
                    cmd = NULL;
                }
                
           
            }


            if (!found) {
                fprintf(stderr, "Semantic Error: missing return statement in function %s\n", node->symbol->text);
                ++SemanticErrors;
            }
        }
      
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        check_return(node->son[i]);
    }
}