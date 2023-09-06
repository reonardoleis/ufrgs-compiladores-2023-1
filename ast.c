#include "hash.h"
#include "ast_types.h"
#include "ast.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

AST *root;
int ast_node_id = 0;
int ast_loop_id = 0;
int ast_subloop_id = 0;

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
    // ast->optimized = 0;
    ast->has_dependencies = 0;
    ast->id = ++ast_node_id;
    ast->remove_assignment = 0;
    ast->varies = 0;

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

    if (ast->result_datatype && !ast->has_dependencies)
    {
        fprintf(stderr, "AST[t:%s, l:%d, s:%d](", datatype_str[ast->result_datatype], ast->loop_id, ast->subloop_id);
    }
    else if (ast->result_datatype && ast->has_dependencies)
    {
        fprintf(stderr, "AST[t:%s, l:%d, s:%d, d:%d](", datatype_str[ast->result_datatype], ast->loop_id, ast->subloop_id, ast->has_dependencies);
    }
    else
    {
        fprintf(stderr, "AST[l:%d, s:%d, d:%d](", ast->loop_id, ast->subloop_id, ast->has_dependencies);
    }

    char *debug = getenv("DEBUG");
    if (debug != NULL && strcmp(debug, "1") == 0)
    {
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

    switch (node->type)
    {
    case AST_PROGRAM:
    {
        return astToCode(node->son[0]);
    }
    case AST_DECL_LIST:
    {
        sprintf(code, "%s%s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    // variable declarations
    case AST_VAR_DECL_INT:
    {
        sprintf(code, "int %s = %s;\n", node->symbol->text, node->son[0]->symbol->text);
        return strdup(code);
    }
    case AST_VAR_DECL_CHAR:
    {
        sprintf(code, "char %s = %s;\n", node->symbol->text, node->son[0]->symbol->text);
        return strdup(code);
    }
    case AST_VAR_DECL_REAL:
    {
        sprintf(code, "real %s = %s;\n", node->symbol->text, node->son[0]->symbol->text);
        return strdup(code);
    }
    case AST_VAR_DECL_BOOL:
    {
        sprintf(code, "bool %s = %s;\n", node->symbol->text, node->son[0]->symbol->text);
        return strdup(code);
    }

    // vector declarations
    case AST_VEC_DECL_INT:
    {
        sprintf(code, "int %s[%s]%s;\n", node->symbol->text, node->son[0]->symbol->text, astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_VEC_DECL_CHAR:
    {
        sprintf(code, "char %s[%s]%s;\n", node->symbol->text, node->son[0]->symbol->text, astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_VEC_DECL_REAL:
    {
        sprintf(code, "real %s[%s]%s;\n", node->symbol->text, node->son[0]->symbol->text, astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_VEC_DECL_BOOL:
    {
        sprintf(code, "bool %s[%s]%s;\n", node->symbol->text, node->son[0]->symbol->text, astToCode(node->son[1]));
        return strdup(code);
    }

    // vector opt init
    case AST_VEC_INIT_OPT_INT:
    case AST_VEC_INIT_OPT_CHAR:
    case AST_VEC_INIT_OPT_REAL:
    {
        sprintf(code, " %s%s", node->son[0]->symbol->text, astToCode(node->son[1]));
        return strdup(code);
    }

    // func declarations
    case AST_FUNC_DECL_INT:
    {
        sprintf(code, "int %s(%s)%s\n\n", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_FUNC_DECL_CHAR:
    {
        sprintf(code, "char %s(%s)%s\n\n", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_FUNC_DECL_REAL:
    {
        sprintf(code, "real %s(%s)%s\n\n", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_FUNC_DECL_BOOL:
    {
        sprintf(code, "bool %s(%s)%s\n\n", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }

    // func decl parameters
    case AST_PARAM_LIST:
    {
        if (node->son[1] != NULL)
        {
            sprintf(code, "%s %s, %s", ast_func_param_type_str(node->son[0]->type), node->son[0]->symbol->text, astToCode(node->son[1]));
        }
        else
        {
            sprintf(code, "%s %s", ast_func_param_type_str(node->son[0]->type), node->son[0]->symbol->text);
        }

        return strdup(code);
    }

    case AST_BODY:
    {
        sprintf(code, "{%s\n}%s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }

    case AST_CMD_LIST:
    {
        sprintf(code, "%s%s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }

    case AST_VAR_ATTRIB:
    {
        sprintf(code, "\n\t%s = %s;", node->symbol->text, astToCode(node->son[0]));
        return strdup(code);
    }

    case AST_VEC_ATTRIB:
    {
        sprintf(code, "\n\t%s[%s] = %s;", node->symbol->text, astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }

    case AST_OUTPUT_CMD:
    {
        sprintf(code, "\n\toutput %s;", astToCode(node->son[0]));
        return strdup(code);
    }

    case AST_OUTPUT_PARAM_LIST:
    {
        if (node->son[1] != NULL)
        {
            sprintf(code, "%s,%s", astToCode(node->son[0]), astToCode(node->son[1]));
        }
        else
        {
            sprintf(code, "%s", astToCode(node->son[0]));
        }

        return strdup(code);
    }

    // literals (covers expr literals)
    case AST_LIT_INT:
    case AST_LIT_REAL:
    case AST_LIT_CHAR:
    case AST_LIT_STRING:
    {
        sprintf(code, "%s", node->symbol->text);
        return strdup(code);
    }

    // expr
    case AST_IDENTIFIER:
    {
        sprintf(code, "%s", node->symbol->text);
        return strdup(code);
    }

    case AST_MUL:
    {
        sprintf(code, "%s * %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_DIV:
    {
        sprintf(code, "%s / %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_ADD:
    {
        sprintf(code, "%s + %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_SUB:
    {
        sprintf(code, "%s - %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_NEG:
    {
        sprintf(code, "-%s", astToCode(node->son[0]));
        return strdup(code);
    }
    case AST_NOT:
    {
        sprintf(code, "~%s", astToCode(node->son[0]));
        return strdup(code);
    }
    case AST_AND:
    {
        sprintf(code, "%s & %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_OR:
    {
        sprintf(code, "%s | %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_LE:
    {
        sprintf(code, "%s <= %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_GE:
    {
        sprintf(code, "%s >= %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_EQ:
    {
        sprintf(code, "%s == %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_DIF:
    {
        sprintf(code, "%s != %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_GT:
    {
        sprintf(code, "%s > %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_LT:
    {
        sprintf(code, "%s < %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }

    case AST_NESTED_EXPR:
    {
        sprintf(code, "(%s)", astToCode(node->son[0]));
        return strdup(code);
    }

    case AST_VEC_ACCESS:
    {
        sprintf(code, "%s[%s]", node->symbol->text, astToCode(node->son[0]));
        return strdup(code);
    }

    case AST_INPUT_EXPR_INT:
    {
        sprintf(code, "input(int)");
        return strdup(code);
    }
    case AST_INPUT_EXPR_CHAR:
    {
        sprintf(code, "input(char)");
        return strdup(code);
    }
    case AST_INPUT_EXPR_REAL:
    {
        sprintf(code, "tinput(real)");
        return strdup(code);
    }
    case AST_INPUT_EXPR_BOOL:
    {
        sprintf(code, "input(bool)");
        return strdup(code);
    }

    case AST_FUNC_CALL:
    {

        sprintf(code, "%s(%s)", node->symbol->text, astToCode(node->son[0]));
        return strdup(code);
    }

    case AST_EXPR_LIST:
    {
        if (node->son[1] != NULL)
        {
            sprintf(code, "%s, %s", astToCode(node->son[0]), astToCode(node->son[1]));
        }
        else
        {
            sprintf(code, "%s", astToCode(node->son[0]));
        }

        return strdup(code);
    }

    case AST_RETURN_CMD:
    {
        sprintf(code, "\n\treturn %s;", astToCode(node->son[0]));
        return strdup(code);
    }

        // ifs

    case AST_IF:
    {
        sprintf(code, "\n\tif (%s) %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_IF_ELSE:
    {
        sprintf(code, "\n\tif (%s) %s else %s", astToCode(node->son[0]), astToCode(node->son[1]), astToCode(node->son[2]));
        return strdup(code);
    }
    case AST_LOOP:
    {
        sprintf(code, "\n\tif (%s) loop %s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }
    case AST_CONDITIONAL_STATEMENT:
    {
        sprintf(code, "%s%s", astToCode(node->son[0]), astToCode(node->son[1]));
        return strdup(code);
    }

    default:
    {
        return strdup("");
    }
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

int get_input_cmd_type(AST *node)
{
    if (node->type == AST_INPUT_EXPR_INT)
    {
        return DATATYPE_INT;
    }
    else if (node->type == AST_INPUT_EXPR_REAL)
    {
        return DATATYPE_REAL;
    }
    else if (node->type == AST_INPUT_EXPR_CHAR)
    {
        return DATATYPE_CHAR;
    }
    else if (node->type == AST_INPUT_EXPR_BOOL)
    {
        return DATATYPE_BOOL;
    }
    else
    {
        return -1;
    }
}

void set_expr_list_item_function(AST *node)
{
    int i;
    if (!node)
        return;

    if (node->type == AST_FUNC_CALL)
    {
        AST *expr_list = node->son[0];
        STRING_LIST *param = node->symbol->param_list;
        while (expr_list != NULL && param != NULL)
        {
            expr_list->func_param = param->text;
            expr_list = expr_list->son[1];
            param = param->next;
        }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        set_expr_list_item_function(node->son[i]);
    }
}

void set_param_list_item_function(AST *node)
{
    int i;
    if (!node)
        return;

    if (node->type == AST_FUNC_DECL_INT || node->type == AST_FUNC_DECL_REAL || node->type == AST_FUNC_DECL_BOOL)
    {
        AST *param_list = node->son[0];
        while (param_list != NULL)
        {
            hash_append_param_list(node->symbol, param_list->son[0] ? param_list->son[0]->symbol : NULL);
            param_list = param_list->son[1];
        }
    }

    for (i = 0; i < MAX_SONS; i++)
    {
        set_param_list_item_function(node->son[i]);
    }
}

int ast_mark_loop_elements(AST *loop, int id, int subloop_id)
{
    if (loop == NULL)
    {
        return 0;
    }

    loop->loop_id = id;

    if (loop->type == AST_LOOP && loop->subloop_id == 0)
    {
        subloop_id = subloop_id + 1;
    }

    loop->subloop_id = subloop_id;

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_mark_loop_elements(loop->son[i], id, subloop_id);
    }
}

int ast_collect_loop_elements(AST *node)
{
    if (node == NULL)
    {
        return 0;
    }

    if (node->type == AST_CMD_LIST && node->son[0] && node->son[0]->type == AST_LOOP && node->loop_id == 0)
    {
        int id = ast_loop_id + 1;
        node->loop_id = id;
        node->subloop_id = 1;
        node->son[0]->subloop_id = 1;
        ast_mark_loop_elements(node->son[0], id, 1);

        ast_loop_id++;
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_collect_loop_elements(node->son[i]);
    }
}

void ast_collect_loop_conditions(AST *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_LOOP)
    {
        AST *condition = node->son[0];
        int id = node->loop_id;
        int subloop_id = node->subloop_id;
        //fprintf(stderr, "Inserting on condition list with loop_id %d and subloop_id %d\n", id, subloop_id);
        ast_cond_list_insert_at(id, subloop_id, condition);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_collect_loop_conditions(node->son[i]);
    }
}

NODE_LIST *ast_cond_list_insert_at(int index, int subloop_id, AST *node)
{
    NODE_LIST *new_node = (NODE_LIST *)calloc(1, sizeof(NODE_LIST));
    new_node->node = node;
    new_node->subloop_id = subloop_id;
    new_node->next = NULL;
    int i;
    for (i = 0; i < VARIABLE_LIST_SIZE; i++) {
        new_node->variables[i] = (VARIABLE*) calloc(1, sizeof(VARIABLE));
        new_node->attribs[i] = (VARIABLE*) calloc(1, sizeof(VARIABLE));
    }

    if (index == 0)
    {
        return new_node;
    }

    if (cond_list[index] == NULL)
    {
        cond_list[index] = new_node;
    }
    else
    {
        NODE_LIST *current = cond_list[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }

    return cond_list[index];
}

void ast_collect_loop_variables(AST *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_LOOP)
    {
        node->has_dependencies = 1;
        int id = node->loop_id;
        ast_set_cond_list_loop_variables(id, node->son[1]);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_collect_loop_variables(node->son[i]);
    }
}

void ast_insert_variable(HASH * symbol, int loop_id) {
    NODE_LIST* current = cond_list[loop_id];
    if (current == NULL) {
        return;
    }

    
    int i;
    for (i = 0; i < VARIABLE_LIST_SIZE; i++) {
        if (current->variables[i]->symbol == NULL) {
            current->variables[i]->symbol = symbol;
            return;
        }

        if (current->variables[i]->symbol != NULL && current->variables[i]->symbol == symbol) {
            return;
        }
    }
}

void ast_insert_attrib(HASH * symbol, int loop_id) {
    NODE_LIST* current = cond_list[loop_id];
    if (current == NULL) {
        return;
    }

    
    int i;
    for (i = 0; i < VARIABLE_LIST_SIZE; i++) {
        if (current->attribs[i]->symbol == NULL) {
           // fprintf(stderr, "Inserindo variavel %s\n", symbol->text);
            current->attribs[i]->symbol = symbol;
            return;
        }

        if (current->attribs[i]->symbol != NULL && current->attribs[i]->symbol == symbol) {
            return;
        }
    }
}

void ast_set_cond_list_loop_variables(int id, AST *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_IDENTIFIER)
    {
        NODE_LIST *current = cond_list[id];
        current->right_side_vars[current->right_side_vars_count++] = node->symbol->text;
        ast_insert_variable(node->symbol, id);
    }

    if (node->type == AST_VAR_ATTRIB)
    {
        NODE_LIST *current = cond_list[id];
        current->left_side_vars[current->left_side_vars_count++] = node->symbol->text;
        ast_insert_variable(node->symbol, id);
        ast_insert_attrib(node->symbol, id);
    }

    int i;
    for (i = MAX_SONS-1; i >= 0; i--)
    {
        ast_set_cond_list_loop_variables(id, node->son[i]);
    }
}

int ast_appears_on_right_side(char *text, int loop_id)
{
    NODE_LIST *current = cond_list[loop_id];
    int i;
    for (i = 0; i < current->right_side_vars_count; i++)
    {
        if (strcmp(current->right_side_vars[i], text) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void ast_print_cond_list()
{

    int i;
    for (i = 0; i < COND_LIST_SIZE; i++)
    {
        if (cond_list[i] != NULL)
        {
            fprintf(stderr, "cond_list[%d]:\n", i);
            NODE_LIST *current = cond_list[i];

            int j;
            for (j = 0; j < VARIABLE_LIST_SIZE; j++) {
                if (current->variables[j]->symbol != NULL) {
                    fprintf(stderr, "loop %d has variable %s\n", i, current->variables[j]->symbol->text);
                }
            }

            while (current != NULL)
            {
                fprintf(stderr, "subloop id: %d\n", current->subloop_id);
                // fprintf(stderr, "cond type: %s\n", ast_type_str(current->node->type));
                current = current->next;
            }
        }
    }
}

void ast_collect_has_dependencies(AST *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_LOOP)
    {
        int id = node->loop_id;
        ast_set_cond_list_has_dependencies(id, node->son[1]);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_collect_has_dependencies(node->son[i]);
    }
}

int ast_appears_on_left_side(char *text, int loop_id)
{
    NODE_LIST *current = cond_list[loop_id];
    int i;
    int c = 0;
    for (i = 0; i < current->left_side_vars_count; i++)
    {
        if (strcmp(current->left_side_vars[i], text) == 0)
        {
            c++;
        }
    }

    return c;
}

int ast_has_left_side_dependencies(AST *node)
{
    if (node == NULL)
    {
        return 0;
    }

    if (node->type == AST_IDENTIFIER)
    {
        int id = node->loop_id;
        if (ast_appears_on_left_side(node->symbol->text, id))
        {
            return 1;
        }
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        if (ast_has_left_side_dependencies(node->son[i]))
        {
            return 1;
        }
    }
}

void ast_set_cond_list_has_dependencies(int id, AST *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_VAR_ATTRIB)
    {
        if (ast_appears_on_right_side(node->symbol->text, id))
        {
            node->has_dependencies = 1;
        }

        if (ast_has_left_side_dependencies(node))
        {
            node->has_dependencies = 1;
        }
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_cond_list_has_dependencies(id, node->son[i]);
    }
}

void ast_move_constant_assignments_out_of_loop(AST *cmdlist_before, AST *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_VAR_ATTRIB && node->loop_id != 0)
    {
        // fprintf(stderr, "found variable %s\n", node->symbol->text);
        AST * current = node;
        int depends = ast_variable_varies(current->symbol, current->loop_id) || ast_identifiers_of_attrib_varies(node);
        node->has_dependencies = depends;
        if (!node->has_dependencies)
        {
           // fprintf(stderr, "variable %s has no dependencies\n", node->symbol->text);
            optimized = 1;
            node->remove_assignment = 1;
            AST *loop = cmdlist_before->son[0];
            AST *rest = cmdlist_before->son[1];
            cmdlist_before->son[0] = astCreate(AST_CMD_LIST, 0, node, loop, 0, 0, 0);
            cmdlist_before->son[1] = rest;
        } else {
            //fprintf(stderr, "variable %s has dependencies\n", node->symbol->text);
        }
    }

    int i;
    for (i = MAX_SONS-1; i >= 0; i--)
    {
        ast_move_constant_assignments_out_of_loop(cmdlist_before, node->son[i]);
    }
}

void ast_optimize(AST *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_CMD_LIST && node->son[0] && node->son[0]->type == AST_LOOP)
    {
        int id = node->loop_id;
        ast_move_constant_assignments_out_of_loop(node, node->son[0]);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_optimize(node->son[i]);
    }
}

void ast_handle_marked_assignments(AST *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_LOOP)
    {
        ast_remove_marked_assignments(node->son[1]);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_handle_marked_assignments(node->son[i]);
    }
}

void ast_remove_marked_assignments(AST *node)
{
    if (node == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_remove_marked_assignments(node->son[i]);
    }

    if (node->type == AST_CMD_LIST)
    {
        if (node->son[0] && node->son[0]->remove_assignment)
        {
            node->son[0] = NULL;
        }
    }
}

void ast_add_assignment_conds(AST *node)
{
    if (node == NULL)
    {
        return;
    }

    AST *parent = node;
    AST *current = node->son[0];
    if (current != NULL && current->type == AST_VAR_ATTRIB && current->loop_id != 0 && !current->has_dependencies)
    {
        NODE_LIST *current_cond = cond_list[node->son[0]->loop_id];
        AST *linked = NULL;
        AST *last = NULL;
        while (current_cond != NULL)
        {

            if (current->subloop_id >= current_cond->subloop_id)
            {
                if (linked == NULL)
                {
                    linked = astCreate(AST_CMD_LIST, 0, 0, 0, 0, 0, 0);
                    linked->son[0] = astCreate(AST_IF, 0, current_cond->node, astCreate(AST_BODY, 0, 0, 0, 0, 0, 0), 0, 0, 0);

                    last = linked->son[0]->son[1];
                }
                else
                {

                    last->son[0] = astCreate(AST_CMD_LIST, 0, 0, 0, 0, 0, 0);
                    last->son[0] = astCreate(AST_IF, 0, current_cond->node, astCreate(AST_BODY, 0, 0, 0, 0, 0, 0), 0, 0, 0);
                    last = last->son[0]->son[1];
                }
            }

            current_cond = current_cond->next;
        }

        current->loop_id = 0;
        last->son[0] = current;

        parent->son[0] = linked;
        // astPrint(linked, 0);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_add_assignment_conds(node->son[i]);
    }
}

void ast_collect_varies(AST *node) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_LOOP)
    {
        int id = node->loop_id;
        ast_collect_varies_aux(node->son[1], id);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_collect_varies(node->son[i]);
    }
}

void ast_collect_varies_aux(AST *node, int loop_id) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_VAR_ATTRIB)
    {
        node->varies = ast_variable_changes(node, node->symbol);
        if (node->varies) {
            ast_update_variable_varies(node->symbol, loop_id, 1);
           // fprintf(stderr, "variable %s varies\n", node->symbol->text);
        } else {
          //  fprintf(stderr, "variable %s does not vary\n", node->symbol->text);
        }
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_collect_varies_aux(node->son[i], loop_id);
    }
}

int ast_variable_changes(AST *node, HASH *symbol) {
    if (node == NULL)
    {
        return 0;
    }

    if (node->type == AST_IDENTIFIER)
    {
        if (strcmp(node->symbol->text, symbol->text) == 0) {
            return 1;
        }
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        return ast_variable_changes(node->son[i], symbol);
    }

    return 0;
}

void ast_set_dependencies(AST *node) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_LOOP)
    {
        int id = node->loop_id;
        ast_set_dependencies_handle_loop(node->son[1], id);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_dependencies(node->son[i]);
    }
}

void ast_set_dependencies_handle_loop(AST *node, int loop_id) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_VAR_ATTRIB)
    {
        //fprintf(stderr, "Handling %s attribution on loop %d\n", node->symbol->text, loop_id);
        ast_set_dependencies_handle_attrib(node, loop_id);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_dependencies_handle_loop(node->son[i], loop_id);
    }
}



void ast_set_dependencies_handle_attrib(AST *node, int loop_id) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_IDENTIFIER)
    {
        //fprintf(stderr, "Verifying identifier %s on loop %d\n", node->symbol->text, loop_id);
        if (ast_variable_varies(node->symbol, loop_id)) {
            //fprintf(stderr, "%s varies on %d\n", node->symbol->text, loop_id);
            node->has_dependencies = 1;
        }
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_dependencies_handle_attrib(node->son[i], loop_id);
    }
}

void ast_update_variable_varies(HASH *symbol, int loop_id, int varies) {
    NODE_LIST* current = cond_list[loop_id];
    if (current == NULL) {
        return;
    }

    int i;
    for (i = 0; i < VARIABLE_LIST_SIZE; i++) {
        if (current->variables[i]->symbol != NULL && current->variables[i]->symbol == symbol) {
            current->variables[i]->varies = varies;
            return;
        }
    }
}

int ast_identifiers_of_attrib_varies(AST *node) {
    if (node == NULL)
    {
        return 0;
    }

    if (node->type == AST_IDENTIFIER)
    {
        return ast_variable_varies(node->symbol, node->loop_id);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        return ast_identifiers_of_attrib_varies(node->son[i]);
    }

    return 0;
}

int ast_variable_varies(HASH *symbol, int loop_id) {
   
    NODE_LIST* current = cond_list[loop_id];
    if (current == NULL) {
     
        return 0;
    }


    
    int i;
    for (i = 0; i < VARIABLE_LIST_SIZE; i++) {
        if (current->variables[i]->symbol != NULL && current->variables[i]->symbol == symbol) {
            //fprintf(stderr, "%s on %d varies? %s\n", symbol->text, loop_id, current->variables[i]->varies ? "yes" : "no");
            return current->variables[i]->varies;
        }
    }

    return 0;
}

void ast_set_varies(AST *node) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_LOOP)
    {
        int id = node->loop_id;
        ast_set_varies_handle_loop(node->son[1], id);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_varies(node->son[i]);
    }
}

void ast_set_varies_handle_loop(AST *node, int loop_id) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_VAR_ATTRIB)
    {
        ast_set_varies_handle_attrib(node, node->son[0], loop_id);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_varies_handle_loop(node->son[i], loop_id);
    }
}

void ast_set_varies_handle_attrib(AST *attrib, AST *node, int loop_id) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_IDENTIFIER)
    {
    
        if (strcmp(node->symbol->text, attrib->symbol->text) == 0 || ast_variable_varies(node->symbol, loop_id)) {
            ast_update_variable_varies(attrib->symbol, loop_id, 1);
            attrib->varies = 1 ;
            return;
        }
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_varies_handle_attrib(attrib, node->son[i], loop_id);
    }
}

void ast_set_order_dependencies(AST *node) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_LOOP)
    {
        int id = node->loop_id;
        ast_set_order_dependencies_handle_loop(node->son[1], id);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_order_dependencies(node->son[i]);
    }
}

void ast_set_order_dependencies_handle_loop(AST *node, int loop_id) {
    if (node == NULL)
    {
        return;
    }

    if (node->type == AST_VAR_ATTRIB)
    {
        ast_set_order_dependencies_handle_attrib(node, node, loop_id);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_order_dependencies_handle_loop(node->son[i], loop_id);
    }
}

void ast_set_order_dependencies_handle_attrib(AST *attrib, AST *node, int loop_id) {
    if (node == NULL)
    {
        return;
    }


    if (node->type == AST_IDENTIFIER)
        {
            VARIABLE **attribs = cond_list[loop_id]->attribs;
            int mypos, theirpos;
            int i;
            for (i = 0; i < VARIABLE_LIST_SIZE; i++) {
                if (attribs[i]->symbol != NULL && attribs[i]->symbol == attrib->symbol) {
                    mypos = i;
                }

                if (attribs[i]->symbol != NULL && attribs[i]->symbol == node->symbol) {
                  
                    theirpos = i;
                }
            }

           // fprintf(stderr, "Attrib %s | Id %s:  mypos: %d theirpos: %d\n", attrib->symbol->text, node->symbol->text, mypos, theirpos);

            // remember that the variable list is in reverse order
            if (mypos > theirpos && attrib->varies) {
             
                ast_update_variable_varies(node->symbol, loop_id, 1);
            }
            
        }
    

    int i;
    for (i = 0; i < MAX_SONS; i++)
    {
        ast_set_order_dependencies_handle_attrib(attrib, node->son[i], loop_id);
    }
}