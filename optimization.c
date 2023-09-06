#include "optimization.h"


void optimization_reset_step() {
    appeared_right_side_index = 0;
    loop_expr_vars_index = 0;
    for (int i = 0; i < 1000; i++) {
        appeared_right_side[i] = NULL;
        loop_expr_vars[i] = NULL;
    }
}

int optimization_is_loop_expr_var(char * var_name) {
    for (int i = 0; i < loop_expr_vars_index; i++) {
        if (strcmp(loop_expr_vars[i], var_name) == 0) {
            return 1;
        }
    }
    return 0;
}

void optimization_collect_loop_expr_vars(AST * loop_expr) {
    if (loop_expr == NULL)
        return;

    if (loop_expr->type == AST_IDENTIFIER) {
        loop_expr_vars[loop_expr_vars_index] = loop_expr->symbol->text;
        loop_expr_vars_index++;
    }

    for (int i = 0; i < MAX_SONS; i++) {
        optimization_collect_loop_expr_vars(loop_expr->son[i]);
    }
}

void optimization_collect_right_side(AST *last_cmd_list)
{
    if (last_cmd_list == NULL)
        return;

    if (last_cmd_list->type == AST_IDENTIFIER)
    {
        appeared_right_side[appeared_right_side_index] = last_cmd_list->symbol->text;
        appeared_right_side_index++;
    }

    for (int i = 0; i < MAX_SONS; i++)
    {
        optimization_collect_right_side(last_cmd_list->son[i]);
    }
}

int optimization_depends_on_itself(HASH *variable, AST *attrib, AST *last_cmd_list)
{

    if (attrib == NULL)
        return 0;

    if (attrib->type == AST_IDENTIFIER)
    {
        if (strcmp(attrib->symbol->text, variable->text) == 0)
        {
            return 1;
        }
    }

    for (int i = 0; i < MAX_SONS; i++)
    {
        if (optimization_depends_on_itself(variable, attrib->son[i], last_cmd_list))
            return 1;
    }

    return 0;
}

int optimization_appears_in_right_side(HASH * variable, AST * attrib, AST * last_cmd_list) {
    if (last_cmd_list == NULL)
        return 0;

    if (last_cmd_list->type == AST_IDENTIFIER) {
        if (strcmp(last_cmd_list->symbol->text, variable->text) == 0) {
            return 1;
        }
    }

    for (int i = 0; i < MAX_SONS; i++) {
        if (optimization_appears_in_right_side(variable, attrib, last_cmd_list->son[i]))
            return 1;
    }

    return 0;
}


int optimization_appears_in_left_side(HASH * variable, AST * attrib, AST * last_cmd_list) {
    if (last_cmd_list == NULL)
        return 0;

    if (last_cmd_list->type == AST_IDENTIFIER) {
        if (strcmp(last_cmd_list->symbol->text, variable->text) == 0) {
            return 1;
        }
    }

    for (int i = 0; i < MAX_SONS; i++) {
        if (optimization_appears_in_left_side(variable, attrib, last_cmd_list->son[i]))
            return 1;
    }

    return 0;
}

void optimization_collect_left_side(AST * last_cmd_list) {
    if (last_cmd_list == NULL)
        return;
    if (last_cmd_list->type == AST_VAR_ATTRIB) {
       
        appeared_left_side[appeared_left_side_index] = last_cmd_list->symbol->text;
        appeared_left_side_index++;
    }

    for (int i = 0; i < MAX_SONS; i++) {
        optimization_collect_left_side(last_cmd_list->son[i]);
    }
}

int optimization_verify_right_side(AST * attrib) {
    if (attrib == NULL) {
        return 0;
    }

    if (attrib->type == AST_IDENTIFIER) {
        for (int i = 0; i < appeared_left_side_index; i++) {
            if (strcmp(attrib->symbol->text, appeared_left_side[i]) == 0) {
                return 1;
            }
        }
    }

    for (int i = 0; i < MAX_SONS; i++) {
        if (optimization_verify_right_side(attrib->son[i])) {
            return 1;
        }
    }

    return 0;
}

int optimization_optimize(HASH * variable, AST * attrib, AST * last_cmd_list) {
    int depends_on_itself = optimization_depends_on_itself(variable, attrib, last_cmd_list);
    int appears_in_right_side = optimization_appears_in_right_side(variable, attrib, last_cmd_list);
    int appears_in_left_side = optimization_appears_in_left_side(variable, attrib, last_cmd_list);


    if (depends_on_itself || appears_in_right_side || appears_in_left_side) {
        return 1;
    }

    return 0 || optimization_verify_right_side(attrib);
}
