#pragma once
#include "ast.h"
#include "ast_types.h"
#include "hash.h"
#include "symbols.h"
#include "debug.h"
#include "semantic_utils.h"

int SemanticErrors = 0;

// TODO: garantir que vetor sempre é usado com indice
// no typecheck, um acesso a vetor tem o tipo como seu tipo, entao se a é um vetor de int e b é um int, entao a[0] + b é valido

void check_and_set_declarations(AST *node);
void check_undeclared(void);
void check_operands(AST *node);
int expression_typecheck(AST *node);
int find_first_datatype(AST *node);
int check_assignments(AST *node);
int check_return(AST *node);
int check_return_aux(AST *node, int required_datatype);
int check_conditional_stmts(AST *node);

void check_and_set_declarations(AST *node)
{
    int i;
    int required_vec_type = 0;
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
                fprintf(stderr, "Semantic error: identifier %s already declared at line %d\n", node->symbol->text, node->line_number);
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
        int required_vec_type = 0;
        if (node->type == AST_VEC_DECL_INT)
            required_vec_type = AST_LIT_INT;
        else if (node->type == AST_VEC_DECL_CHAR)
            required_vec_type = AST_LIT_CHAR;
        else if (node->type == AST_VEC_DECL_REAL)
            required_vec_type = AST_LIT_REAL;

        if (node->symbol)
        {
            if (node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic error: identifier %s already declared at line %d\n", node->symbol->text, node->line_number);
                ++SemanticErrors;
            }

            node->symbol->type = SYMBOL_VECTOR;
            node->symbol->datatype = ast_type_to_datatype(node->type);
            node->symbol->is_vector = 1;
            int vec_size = atoi(node->son[0]->symbol->text);
            int initialization_count = 0;

            if (node->son[1] != NULL)
            {
                AST *initialization_item = node->son[1];
                while (initialization_item != NULL)
                {
                    if (!(verify_literal_compatibility(initialization_item->son[0]->type, required_vec_type)))
                    {
                        fprintf(stderr, "Semantic error: vector %s has initialization item with wrong type (expected type %s got %s) at line %d\n",
                                node->symbol->text, ast_type_str(required_vec_type),
                                ast_type_str(initialization_item->son[0]->type), node->line_number);
                        ++SemanticErrors;
                    }
                    initialization_item = initialization_item->son[1];
                    ++initialization_count;
                }

                if (initialization_count != vec_size)
                {
                    fprintf(stderr, "Semantic error: vector %s has %d initialization items, but its size is %d at line %d\n",
                            node->symbol->text, initialization_count, vec_size, node->line_number);
                    ++SemanticErrors;
                }
            }
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
                fprintf(stderr, "Semantic error: identifier %s already declared at line %d\n", node->symbol->text, node->line_number);
                ++SemanticErrors;
            }


            node->symbol->type = SYMBOL_FUNCTION;
            node->symbol->datatype = ast_type_to_datatype(node->type);
            node->symbol->is_function = 1;

        

            AST *param = node->son[0];
            int count = 0;
            while (param)
            {

                node->symbol->params[count] = ast_type_to_datatype(param->son[0]->type);
                param = param->son[1];
                ++count;
            }

            node->symbol->param_count = count;
        }

        break;
    }

    case AST_PARAM_INT:
    case AST_PARAM_CHAR:
    case AST_PARAM_REAL:
    case AST_PARAM_BOOL:
    {

        if (node->symbol)
        {
            if (node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic error: identifier %s already declared at line %d\n", node->symbol->text, node->line_number);
                ++SemanticErrors;
            }

            node->symbol->type = SYMBOL_PARAMETER;
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

    case AST_NESTED_EXPR:
    {
        int datatype = find_first_datatype(node);
        node->result_datatype = datatype;
        break;
    }

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

        if (left_operand->symbol != NULL && left_operand->symbol->is_vector && left_operand->type != AST_VEC_ACCESS)
        {
            fprintf(stderr, "Semantic error: invalid left operand (vector should be indexed) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (right_operand->symbol != NULL && right_operand->symbol->is_vector && right_operand->type != AST_VEC_ACCESS)
        {
            fprintf(stderr, "Semantic error: invalid right operand (vector should be indexed) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (left_operand->symbol != NULL && left_operand->symbol->is_function && left_operand->type != AST_FUNC_CALL)
        {
            fprintf(stderr, "Semantic error: invalid left operand (function should be called) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (right_operand->symbol != NULL && right_operand->symbol->is_function && right_operand->type != AST_FUNC_CALL)
        {
            fprintf(stderr, "Semantic error: invalid right operand (function should be called) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        int errored = 0;

        if (!(left_operand->type == AST_NESTED_EXPR) && !(left_operand->type == AST_NEG) && !is_numeric(left_operand) && !is_arithmetic(left_operand))
        {
            errored = 1;
            fprintf(stderr, "Semantic error: invalid left operand at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (!(right_operand->type == AST_NESTED_EXPR) && !(right_operand->type == AST_NEG) && !is_numeric(right_operand) && !is_arithmetic(right_operand))
        {
            errored = 1;
            fprintf(stderr, "Semantic error: invalid right operand at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (!errored)
        {
            int left_datatype = 0;
            int right_datatype = 0;

            if (left_operand->symbol)
            {
                left_datatype = left_operand->symbol->datatype;
            }

            if (right_operand->symbol)
            {
                right_datatype = right_operand->symbol->datatype;
            }

            if (left_operand->type == AST_NESTED_EXPR)
            {
                left_datatype = find_first_datatype(left_operand);
            }

            if (right_operand->type == AST_NESTED_EXPR)
            {
                right_datatype = find_first_datatype(right_operand);
            }


            if (left_operand->symbol && right_operand->symbol && left_datatype != right_datatype)
            {
                fprintf(stderr, "Semantic error: operands should have same type at line %d\n", node->line_number);
                ++SemanticErrors;
            }
        }

        if (!expression_typecheck(node))
        {
            fprintf(stderr, "Semantic error: invalid resulting expression type for %s at line %d\n", ast_type_str(node->type), node->line_number);
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

        if (operand->symbol && operand->symbol->is_vector && operand->type != AST_VEC_ACCESS)
        {
            fprintf(stderr, "Semantic error: invalid unary operand (vector should be indexed) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (operand->symbol &&operand->symbol->is_function && operand->type != AST_FUNC_CALL)
        {
            fprintf(stderr, "Semantic error: invalid unary operand (function should be called) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (!(operand->type == AST_NESTED_EXPR) && !is_numeric(operand) && !is_arithmetic(operand))
        {
            fprintf(stderr, "Semantic error: invalid unary arithmetic/numeric operand at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (!expression_typecheck(node))
        {
            fprintf(stderr, "Semantic error: invalid resulting expression type for %s at line %d\n", ast_type_str(node->type), node->line_number);
            ++SemanticErrors;
        }
        else
        {
            node->result_datatype = find_first_datatype(node);
            if (node->result_datatype == DATATYPE_BOOL) {
                fprintf(stderr, "Semantic error: invalid resulting expression type for %s (got bool, expected numeric-compatible type) at line %d\n", ast_type_str(node->type), node->line_number);
                ++SemanticErrors;
            }
        }
        break;
    }

    case AST_AND:
    case AST_OR:
    {
        AST *left_operand = node->son[0];
        AST *right_operand = node->son[1];

        if (left_operand->symbol && left_operand->symbol->is_vector && left_operand->type != AST_VEC_ACCESS)
        {
            fprintf(stderr, "Semantic error: invalid left operand (vector should be indexed) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (right_operand->symbol && right_operand->symbol->is_vector && right_operand->type != AST_VEC_ACCESS)
        {
            fprintf(stderr, "Semantic error: invalid right operand (vector should be indexed) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (left_operand->symbol && left_operand->symbol->is_function && left_operand->type != AST_FUNC_CALL)
        {
            fprintf(stderr, "Semantic error: invalid left operand (function should be called) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (right_operand->symbol && right_operand->symbol->is_function && right_operand->type != AST_FUNC_CALL)
        {
            fprintf(stderr, "Semantic error: invalid right operand (function should be called) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        int errored = 0;

        if (!is_bool(left_operand) && !(left_operand->type == AST_NESTED_EXPR) && !is_logic(left_operand))
        {
            fprintf(stderr, "Semantic error: invalid left operand for %s at line %d\n", ast_type_str(node->type), node->line_number);
            ++SemanticErrors;
        }

        if (!is_bool(right_operand) && !(right_operand->type == AST_NESTED_EXPR) && !is_logic(right_operand))
        {
            fprintf(stderr, "Semantic error: invalid right operand for %s at line %d\n", ast_type_str(node->type), node->line_number);
            ++SemanticErrors;
        }

        if (!errored)
        {
            int left_datatype = 0;
            int right_datatype = 0;

            if (left_operand->symbol)
            {
                left_datatype = left_operand->symbol->datatype;
            }

            if (right_operand->symbol)
            {
                right_datatype = right_operand->symbol->datatype;
            }

            if (left_operand->type == AST_NESTED_EXPR)
            {
                left_datatype = find_first_datatype(left_operand);
            }

            if (right_operand->type == AST_NESTED_EXPR)
            {
                right_datatype = find_first_datatype(right_operand);
            }


            if (left_operand->symbol && right_operand->symbol && left_datatype != right_datatype)
            {
                fprintf(stderr, "Semantic error: operands should have same type at line %d\n", node->line_number);
                ++SemanticErrors;
            }
        }

        if (!expression_typecheck(node))
        {
            fprintf(stderr, "Semantic error: invalid resulting expression type for %s at line %d\n", ast_type_str(node->type), node->line_number);
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

    
        if (operand->symbol && operand->symbol->is_vector && operand->type != AST_VEC_ACCESS)
        {
            fprintf(stderr, "Semantic error: invalid unary logical operand (vector should be indexed) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (operand->symbol && operand->symbol->is_function && operand->type != AST_FUNC_CALL)
        {
            fprintf(stderr, "Semantic error: invalid unary logical operand (function should be called) at line %d\n", node->line_number);
            ++SemanticErrors;
        }

        if (!(operand->type == AST_NESTED_EXPR) && !is_logic(operand) && !is_bool(operand))
        {
            fprintf(stderr, "Semantic error: invalid unary logical operand (%s) at line %d\n", datatype_str[operand->symbol->datatype], node->line_number);
            ++SemanticErrors;
        }

        if (!expression_typecheck(node))
        {
            fprintf(stderr, "Semantic error: invalid resulting expression type for %s at line %d\n", ast_type_str(node->type), node->line_number);
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

    if (node->type == AST_NESTED_EXPR)
    {
        return expression_typecheck(node->son[0]);
    }

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

            if (node->type == AST_LIT_INT)
                return DATATYPE_INT;
            if (node->type == AST_LIT_REAL)
                return DATATYPE_REAL;
            if (node->type == AST_LIT_CHAR)
                return DATATYPE_CHAR;

            return node->symbol->datatype;
        }
    }

    if (is_logic(node))
    {
        if (is_binary(node))
        {
            node->typechecked = 1;

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

    if (is_logic(node) && node->son[0] && node->son[0]->type != AST_NESTED_EXPR)
    {
        return DATATYPE_BOOL;
    }

    if (node->type == AST_NESTED_EXPR)
    {
        return find_first_datatype(node->son[0]);
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

int check_assignments(AST *node)
{
    int i;

    if (!node)
        return 0;

    if (node->type == AST_VAR_ATTRIB)
    {

        int expected_datatype = node->symbol->datatype;
        int resulting_datatype = node->son[0]->result_datatype;

        if (node->son[0]->type == AST_IDENTIFIER)
        {
            if (node->son[0]->symbol->is_vector && node->son[0]->type != AST_VEC_ACCESS)
            {
                fprintf(stderr, "Semantic error: invalid assignment of vector to scalar at line %d\n", node->line_number);
                ++SemanticErrors;
            }

            if (node->son[0]->symbol->is_function && node->son[0]->type != AST_FUNC_CALL)
            {
                fprintf(stderr, "Semantic error: invalid assignment of function to scalar at line %d\n", node->line_number);
                ++SemanticErrors;
            }
        }

        if (expected_datatype != resulting_datatype && resulting_datatype != 0)
        {
            fprintf(stderr, "Semantic error: invalid assignment of %s to %s at line %d\n", datatype_str[resulting_datatype], datatype_str[expected_datatype], node->line_number);
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
                    fprintf(stderr, "Semantic error: invalid vector indexer type (expected int or char, got %s -> %s) at line %d\n", 
                    ast_type_str(vec_indexer->type), datatype_str[func_datatype], node->line_number);
                    ++SemanticErrors;
                }
            }
            else
            {
                int vec_indexer_result_type = vec_indexer->result_datatype;
                if (vec_indexer_result_type != DATATYPE_INT && vec_indexer_result_type != DATATYPE_CHAR)
                {
                    fprintf(stderr, "Semantic error: invalid vector indexer type (expected int or char, got %s) at line %d\n", ast_type_str(node->type), node->line_number);
                    ++SemanticErrors;
                }
            }
        }

        int expected_datatype = node->symbol->datatype;
        int resulting_datatype = node->son[1]->result_datatype;

        if (node->son[1]->type == AST_IDENTIFIER)
        {
            if (node->son[1]->symbol->is_vector && node->son[1]->type != AST_VEC_ACCESS)
            {
                fprintf(stderr, "Semantic error: invalid assignment of vector to vector index at line %d\n", node->line_number);
                ++SemanticErrors;
            }

            if (node->son[1]->symbol->is_function && node->son[1]->type != AST_FUNC_CALL)
            {
                fprintf(stderr, "Semantic error: invalid assignment of function to vector index at line %d\n", node->line_number);
                ++SemanticErrors;
            }
        }

        if (expected_datatype != resulting_datatype && resulting_datatype != 0)
        {
            fprintf(stderr, "Semantic error: invalid assignment of %s to %s[] at line %d\n", datatype_str[resulting_datatype], datatype_str[expected_datatype], node->line_number);
            ++SemanticErrors;
        }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        check_assignments(node->son[i]);
    }
}


int check_return(AST *node) {
    int i;
    int required_vec_type = 0;
    if (!node)
        return 0;

    switch (node->type)
    {
    case AST_FUNC_DECL_INT:
    case AST_FUNC_DECL_CHAR:
    case AST_FUNC_DECL_REAL:
    case AST_FUNC_DECL_BOOL:
    {
        if (node->symbol)
        {
        
     
            if (!check_return_aux(node, node->symbol->datatype)) {
                fprintf(stderr, "Semantic error: function %s is missing return statement at line %d\n", node->symbol->text, node->line_number);
                ++SemanticErrors;
            }

            AST *param = node->son[0];
            int count = 0;
            while (param)
            {

                node->symbol->params[count] = ast_type_to_datatype(param->son[0]->type);
                param = param->son[1];
                ++count;
            }

            node->symbol->param_count = count;
        }

        break;
    }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        check_return(node->son[i]);
    }
}

int check_return_aux(AST *node, int required_datatype)
{
    int i;

    if (!node) return 0;

    int found = 0;

    if (node->type == AST_RETURN_CMD)
    {
        int return_datatype = node->son[0]->result_datatype;

        if (node->son[0]->symbol && node->son[0]->symbol->is_vector && node->son[0]->type != AST_VEC_ACCESS)
        {
            fprintf(stderr, "Semantic error: invalid return type (expected %s, got vector) at line %d\n", datatype_str[required_datatype], node->line_number);
            ++SemanticErrors;
        }

        if (node->son[0]->symbol && node->son[0]->symbol->is_function && node->son[0]->type != AST_FUNC_CALL)
        {
            fprintf(stderr, "Semantic error: invalid return type (expected %s, got function) at line %d\n", datatype_str[required_datatype], node->line_number);
            ++SemanticErrors;
        }

       
        if (return_datatype != required_datatype && !validate_return_type(required_datatype, node->son[0]))
        {
            if (return_datatype != 0) {
                fprintf(stderr, "Semantic error: invalid return type (expected %s, got %s) at line %d\n", datatype_str[required_datatype], datatype_str[return_datatype], node->line_number);
            } else {
                fprintf(stderr, "Semantic error: invalid return type (expected %s, got incompatible type) at line %d\n", datatype_str[required_datatype], node->line_number);
            }
            
            ++SemanticErrors;
        }

        found = 1;
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        found = found | check_return_aux(node->son[i], required_datatype);
    }

    return found;
}

int check_function_call(AST *node)
{
    int i;

    if (!node)
        return 0;

    if (node->type == AST_FUNC_CALL)
    {
        int parameter_count = 0;
        int found = 0;
        int error_in_number_of_params = 0;
        AST *expr_list = node->son[0];
        AST *expr_list_copy = expr_list;
        if (expr_list)
        {
            AST *expr = expr_list->son[0];
            int index = 0;
            while (expr)
            {
                int expected_datatype = node->symbol->params[index];
                int actual_datatype;

                if (expr->result_datatype != 0)
                {
                    actual_datatype = expr->result_datatype;
                }
                else
                {
                    actual_datatype = expr->symbol->datatype;
                }

                if (!compare_datatypes(expected_datatype, actual_datatype) && expected_datatype != 0)
                {
                    fprintf(stderr, "Semantic error: invalid parameter type (expected %s, got %s) at line %d\n", 
                    datatype_str[expected_datatype], datatype_str[actual_datatype], node->line_number);
                    ++SemanticErrors;
                }

                index++;
                if (expr_list->son[1] != NULL)
                {
                    expr_list = expr_list->son[1];
                    if (expr_list)
                        expr = expr_list->son[0];
                }
                else
                {
                    expr = NULL;
                }
            }

            expr = expr_list_copy->son[0];
          
            while (expr)
            {
                parameter_count++;
                if (expr_list_copy->son[1] != NULL)
                {
                    expr_list_copy = expr_list_copy->son[1];
                    if (expr_list_copy)
                        expr = expr_list_copy->son[0];
                }
                else
                {
                    expr = NULL;
                }
            }
        }

        if (parameter_count != node->symbol->param_count)
        {
            if (parameter_count == 0) {
                fprintf(stderr, "Semantic error: invalid number of parameters (expected %d, got none) at line %d\n", node->symbol->param_count, node->line_number);
            } else {
                fprintf(stderr, "Semantic error: invalid number of parameters (expected %d, got %d) at line %d\n", node->symbol->param_count, parameter_count, node->line_number);
            }
            
            ++SemanticErrors;
        }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        check_function_call(node->son[i]);
    }
}

int check_conditional_stmts(AST *node)
{
    int i;

    if (!node)
        return 0;

    if (node->type == AST_IF || node->type == AST_IF_ELSE || node->type == AST_LOOP)
    {
        if (node->son[0]->result_datatype != DATATYPE_BOOL && (node->son[0]->symbol && node->son[0]->symbol->datatype != DATATYPE_BOOL))
        {
            fprintf(stderr, "Semantic error: invalid conditional statement (expected bool, got %s) at line %d\n", datatype_str[node->son[0]->result_datatype], node->line_number);
            ++SemanticErrors;
        }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        check_conditional_stmts(node->son[i]);
    }
}