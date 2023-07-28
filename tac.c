#include "tac.h"

char *tac_type_str[] = {
    "",
    "TAC_SYMBOL",
    "TAC_ADD",
    "TAC_SUB",
    "TAC_MUL",
    "TAC_DIV",
    "TAC_NEG",
    "TAC_NOT",
    "TAC_AND",
    "TAC_OR",
    "TAC_LE",
    "TAC_GE",
    "TAC_EQ",
    "TAC_DIF",
    "TAC_GT",
    "TAC_LT",
    "TAC_VAR_ATTRIB",
    "TAC_JFALSE",
    "TAC_LABEL",
    "TAC_JTRUE"};

// TAC methods
TAC *tac_create(int type, hash_t *res, hash_t *op1, hash_t *op2)
{
    TAC *tac = NULL;
    tac = (TAC *)calloc(1, sizeof(TAC));

    tac->type = type;
    tac->res = res;
    tac->op1 = op1;
    tac->op2 = op2;
    tac->prev = NULL;
    tac->next = NULL;

    return tac;
}

void tac_print(TAC *tac)
{
    if (tac == NULL || (tac && tac->type == TAC_SYMBOL))
        return;
    fprintf(
        stderr, "TAC(%s, %s, %s, %s)\n",
        tac->type < TAC_TYPE_COUNT ? tac_type_str[tac->type] : "TAC_UNKNOWN",
        tac->res && tac->res->text ? tac->res->text : "0",
        tac->op1 && tac->op1->text ? tac->op1->text : "0",
        tac->op2 && tac->op2->text ? tac->op2->text : "0");
    tac_print(tac->next);
}

void tac_print_backwards(TAC *tac)
{
    if (tac == NULL)
        return;

    tac_print_backwards(tac->prev);
    tac_print(tac);
}

TAC *tac_join(TAC *l1, TAC *l2)
{
    TAC *tac = NULL;
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    for (tac = l2; tac->prev != NULL; tac = tac->prev)
        ;
    tac->prev = l1;
    return l2;
}

// Code Generation

TAC *make_binary_operation(int type, TAC *code0, TAC *code1)
{
    return tac_join(tac_join(code0, code1), tac_create(TAC_ADD, make_temp(), code0 ? code0->res : NULL, code1 ? code1->res : NULL));
}

TAC *make_if(TAC *code0, TAC *code1)
{
    TAC *jumptac = NULL;
    TAC *labeltac = NULL;
    hash_t *newlabel = NULL;

    newlabel = make_label(CONDITIONAL_IF);

    jumptac = tac_create(TAC_JFALSE, newlabel, code0 ? code0->res : NULL, NULL);
    jumptac->prev = code0;
    labeltac = tac_create(TAC_LABEL, newlabel, NULL, NULL);
    labeltac->prev = code1;

    return tac_join(jumptac, labeltac);
}

TAC *make_if_else(TAC *code0, TAC *code1, TAC *code2)
{
    TAC *jumptac = NULL;
    TAC *labeltac = NULL;

    hash_t *newlabel = NULL;

    newlabel = make_label(CONDITIONAL_ELSE);

    jumptac = tac_create(TAC_JFALSE, newlabel, code0 ? code0->res : NULL, NULL);
    jumptac->prev = code0;
    labeltac = tac_create(TAC_LABEL, newlabel, NULL, NULL);
    labeltac->prev = code1;

    return tac_join(tac_join(jumptac, labeltac), code2);
}

TAC *make_loop(TAC *code0, TAC *code1)
{
    TAC *jumptac = NULL;
    TAC *labeltac = NULL;
    hash_t *newlabel = NULL;

    newlabel = make_label(CONDITIONAL_LOOP);

    jumptac = tac_create(TAC_JFALSE, newlabel, code0 ? code0->res : NULL, NULL);
    jumptac->prev = code0;
    labeltac = tac_create(TAC_LABEL, newlabel, NULL, NULL);
    labeltac->prev = code1;

    return tac_join(jumptac, labeltac);
}

TAC *make_unary_operation(int type, TAC *code0)
{
    return tac_join(code0, tac_create(type, make_temp(), code0 ? code0->res : NULL, NULL));
}

TAC *generate_code(AST *node)
{
    if (node == NULL)
        return NULL;
    int i;
    TAC *result = NULL;
    TAC *code[MAX_SONS];

    for (i = 0; i < MAX_SONS; i++)
    {
        code[i] = generate_code(node->son[i]);
    }

    switch (node->type)
    {
    case AST_IDENTIFIER:
    case AST_LIT_INT:
    case AST_LIT_REAL:
    case AST_LIT_CHAR:
    {
        result = tac_create(TAC_SYMBOL, node->symbol, NULL, NULL);
        break;
    }
    case AST_ADD:
    case AST_SUB:
    case AST_MUL:
    case AST_DIV:
    case AST_AND:
    case AST_OR:
    case AST_LE:
    case AST_GE:
    case AST_EQ:
    case AST_DIF:
    case AST_GT:
    case AST_LT:
    {
        int tac_type = get_tac_type_from_ast(node->type);
        result = make_binary_operation(tac_type, code[0], code[1]);
        break;
    }
    case AST_NEG:
    case AST_NOT:
    {
        int tac_type = get_tac_type_from_ast(node->type);
        result = make_unary_operation(tac_type, code[0]);
        break;
    }
    case AST_VAR_ATTRIB:
    {
        result = tac_join(code[0], tac_create(TAC_VAR_ATTRIB, node->symbol, code[0] ? code[0]->res : NULL, NULL));
        break;
    }
    case AST_IF:
    {
        result = make_if(code[0], code[1]);
        break;
    }
    case AST_IF_ELSE:
    {
        result = make_if_else(code[0], code[1], code[2]);
        break;
    }
    case AST_LOOP:
    {
        result = make_loop(code[0], code[1]);
        break;
    }
    default:
    {
        result = tac_join(code[0], tac_join(code[1], tac_join(code[2], code[3])));
        break;
    }
    }

    return result;
}

int get_tac_type_from_ast(int type)
{
    switch (type)
    {
    case AST_ADD:
        return TAC_ADD;
    case AST_SUB:
        return TAC_SUB;
    case AST_MUL:
        return TAC_MUL;
    case AST_DIV:
        return TAC_DIV;
    case AST_AND:
        return TAC_AND;
    case AST_OR:
        return TAC_OR;
    case AST_LE:
        return TAC_LE;
    case AST_GE:
        return TAC_GE;
    case AST_EQ:
        return TAC_EQ;
    case AST_DIF:
        return TAC_DIF;
    case AST_GT:
        return TAC_GT;
    case AST_LT:
        return TAC_LT;
    case AST_NEG:
        return TAC_NEG;
    case AST_NOT:
        return TAC_NOT;
    default:
        return -1;
    }
}