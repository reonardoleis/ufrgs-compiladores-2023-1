#pragma once
#include "ast.h"
#include "hash.h"

char *appeared_right_side[1000];
int appeared_right_side_index = 0;

char *appeared_left_side[1000];
int appeared_left_side_index = 0;

char *loop_expr_vars[1000];
int loop_expr_vars_index = 0;

int optimization_depends_on_itself(HASH * variable, AST * attrib, AST * last_cmd_list);
int optimization_appears_in_right_side(HASH * variable, AST * attrib, AST * last_cmd_list);
void optimization_collect_right_side(AST * last_cmd_list);
int optimization_appears_in_left_side(HASH * variable, AST * attrib, AST * last_cmd_list);
void optimization_collect_left_side(AST * last_cmd_list);
void optimization_reset_step();
void optimization_collect_loop_expr_vars(AST * loop_expr);
int optimization_is_loop_expr_var(char * var_name);
int optimization_optimize(HASH * variable, AST * attrib, AST * last_cmd_list);
int optimization_verify_right_side(AST * attrib);