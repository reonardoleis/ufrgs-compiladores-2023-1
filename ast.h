#pragma once
#include "hash.h"

#define MAX_SONS 4
#define COND_LIST_SIZE 10000000
#define VARIABLE_LIST_SIZE 10000
extern int SemanticErrors;

extern int ast_node_id;
extern int ast_loop_id;
extern int ast_subloop_id;

typedef struct variable
{
    HASH* symbol;
    int varies;
    int is_loop_var;
} VARIABLE;

typedef struct node_list
{
    char *left_side_vars[1000];
    char *right_side_vars[1000];
    char *loop_vars[1000];

    VARIABLE *variables[VARIABLE_LIST_SIZE];
    VARIABLE *attribs[VARIABLE_LIST_SIZE];

    int left_side_vars_count;
    int right_side_vars_count;
    int loop_vars_count;
    int subloop_id;
    struct ast_node *node;
    struct node_list *next;
} NODE_LIST;

typedef struct ast_node
{
    int id;
    int type;
    HASH *symbol;
    int typechecked;
    int result_datatype;
    int line_number;
    struct ast_node *son[MAX_SONS];
    char* func_param;
    
    // optimization-related fields
    int has_dependencies;
    int loop_id;
    int subloop_id;
    int remove_assignment;
    int varies;
} AST;

int optimized = 0;
AST *root;
NODE_LIST *cond_list[COND_LIST_SIZE];

AST *astCreate(int type, HASH *symbol, AST *s0, AST *s1, AST *s2, AST *s3, int line_number);
void astPrint(AST *node, int level);
char *astToCode(AST *node);
char *handleVecOptInitialization(AST *vec_init_opt_root_node);
char *handleFunctinDeclarationParams(AST *func_decl_params_root_node);
int isLeaf(AST *node);
int is_input_cmd(AST *node);
int get_input_cmd_type(AST *node);
void set_expr_list_item_function(AST *node);
void set_param_list_item_function(AST *node);


int ast_mark_loop_elements(AST *loop, int id, int subloop_id);
int ast_collect_loop_elements(AST *node);
void ast_collect_loop_conditions(AST *node);
NODE_LIST *ast_cond_list_insert_at(int index, int subloop_id, AST *node);
void ast_print_cond_list();

void ast_collect_loop_variables(AST *node);
void ast_set_cond_list_loop_variables(int id, AST *node);
int ast_appears_on_right_side(char * text, int loop_id);
int ast_appears_on_left_side(char * text, int loop_id);
void ast_collect_has_dependencies(AST *node);
void ast_set_cond_list_has_dependencies(int id, AST *node);


void ast_optimize(AST *node);
void ast_move_constant_assignments_out_of_loop(AST *cmdlist_before, AST *node);
void ast_handle_marked_assignments(AST *node);
void ast_remove_marked_assignments(AST *node);
void ast_add_assignment_conds(AST *node);
int ast_has_left_side_dependencies(AST *node);

void ast_collect_varies(AST *node);
void ast_collect_varies_aux(AST *node, int loop_id);
int ast_variable_changes(AST *node, HASH *symbol);
void ast_insert_variable(HASH * symbol, int loop_id);
void ast_insert_attrib(HASH * symbol, int loop_id);


void ast_set_dependencies(AST *node);
void ast_set_dependencies_handle_loop(AST *node, int loop_id);
void ast_set_dependencies_handle_attrib(AST *node, int loop_id);

int ast_variable_varies(HASH *symbol, int loop_id);
void ast_update_variable_varies(HASH *symbol, int loop_id, int varies);

void ast_set_varies(AST *node);
void ast_set_varies_handle_loop(AST *node, int loop_id);
void ast_set_varies_handle_attrib(AST *attrib, AST *node, int loop_id);

int ast_identifiers_of_attrib_varies(AST *node);

void ast_set_order_dependencies(AST *node);
void ast_set_order_dependencies_handle_loop(AST *node, int loop_id);
void ast_set_order_dependencies_handle_attrib(AST *attrib, AST *node, int loop_id);