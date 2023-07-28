#pragma once

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MUL 4
#define TAC_DIV 5
#define TAC_NEG 6
#define TAC_NOT 7
#define TAC_AND 8
#define TAC_OR 9
#define TAC_LE 10
#define TAC_GE 11
#define TAC_EQ 12
#define TAC_DIF 13
#define TAC_GT 14
#define TAC_LT 15
#define TAC_VAR_ATTRIB 16
#define TAC_JFALSE 17
#define TAC_LABEL 18
#define TAC_JTRUE 19

#define TAC_TYPE_COUNT ((sizeof(tac_type_str)/sizeof(tac_type_str[0])) + 1)

typedef struct tac_node {
    int type;
    hash_t * res;
    hash_t * op1;
    hash_t * op2;
    struct tac_node * prev;
    struct tac_node * next;
} TAC;


// TAC methods
TAC * tac_create(int type, hash_t * res, hash_t * op1, hash_t * op2);
void tac_print(TAC * tac);
void tac_print_backwards(TAC * tac);
TAC * tac_join(TAC * l1, TAC * l2);

// Code Generation
TAC * generate_code(AST * node);
TAC * make_binary_operation(int type, TAC * code0, TAC * code1);
TAC * make_if(TAC * code0, TAC * code1);
TAC * make_if_else(TAC * code0, TAC * code1, TAC * code2);
TAC * make_loop(TAC * code0, TAC * code1);
TAC * make_unary_operation(int type, TAC * code0);
int get_tac_type_from_ast(int type);
