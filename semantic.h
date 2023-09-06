#pragma once
#include "ast.h"

void check_and_set_declarations(AST *node);
void check_undeclared(void);
void check_operands(AST *node);
int expression_typecheck(AST *node);
int find_first_datatype(AST *node);
int check_assignments(AST *node);
void check_return(AST *node);
int check_return_aux(AST *node, int required_datatype);
void check_conditional_stmts(AST *node);
void check_function_call(AST *node);