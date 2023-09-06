// Leonardo Reis da Silva

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbols.h"
#include "ast_types.h"
#include "debug.h"
#define HASH_SIZE 997

#define DATATYPE_INT 1
#define DATATYPE_REAL 2
#define DATATYPE_BOOL 3
#define DATATYPE_CHAR 4


char* datatype_str[] = { "invalid", "int",  "real", "bool", "char" };

int string_id = 1;
int function_id = 1;

typedef struct STRING_LIST
{
    char *text;
    struct STRING_LIST *next;
} STRING_LIST;

typedef struct HASH
{
    int type; 
    int datatype;
    char *text;
    int line_number;
    struct HASH *next;
    int* params;
    int param_count;
    int is_vector;
    int is_function;
    int string_id;
    int function_id;
    int is_label;
    int is_temp;
    STRING_LIST *param_list;
    struct HASH *beginfun_label;    
} HASH;



int hash(char *key);
HASH *hash_find(char *key);
HASH *hash_insert(char *text, int type, int line_number);
char *get_key(HASH *hash);
void hash_print();
int hash_check_undeclared(void);
int ast_type_to_datatype(int ast_type);
HASH *make_temp(int datatype);
HASH *make_label(int type);
HASH *make_missing(int datatype);
HASH *make_value(int ty);

HASH *hash_table[HASH_SIZE];

void initMe(void)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
    {
        hash_table[i] = 0;
    }
}

int hash(char *text)
{
    int i;
    int hash_val = 1;
    for (i = 0; i < strlen(text); i++)
    {
        hash_val = (hash_val * text[i]) % HASH_SIZE + 1;
    }

    return hash_val - 1;
}

char *get_key(HASH *hash)
{
    return hash->text;
}

HASH *hash_find(char *key)
{
    int pos = hash(key);

    HASH *item = hash_table[pos];
    if (item == NULL)
    {
        return NULL;
    }

    if (item->next == NULL)
    {
        return item;
    }

    item = item->next;
    while (item != NULL)
    {
        char *item_key = get_key(item);
        if (strcmp(key, item_key))
        {
            return item;
        }

        item = item->next;
    }

    return NULL;
}

HASH *set_function_id(HASH *hash);
HASH *set_function_id(HASH *hash) {
    hash->function_id = function_id;
    function_id++;
    return hash;
}

void hash_append_param_list(HASH *hash, HASH *param);
void hash_append_param_list(HASH *hash, HASH *param) {
    if (!param || !param->text) {
        return;
    }
    // param list is on hash->param_list of type STRING_LIST
    // param is of type HASH
    STRING_LIST *new_param = (STRING_LIST *)calloc(1, sizeof(STRING_LIST));
    new_param->text = (char *)calloc(strlen(param->text) + 1, sizeof(char));
    strcpy(new_param->text, param->text);

    if (!hash->param_list) {
        hash->param_list = new_param;
        return;
    }

    STRING_LIST *current_param = hash->param_list;
    while (current_param->next != NULL) {
        current_param = current_param->next;
    }

    current_param->next = new_param;

   
}

HASH *hash_insert(char *text, int type, int datatype)
{
    HASH *item = (HASH *)calloc(1, sizeof(HASH));
    item->type = type;
    item->text = (char *)calloc(strlen(text) + 1, sizeof(char));
    item->line_number = line_number;
    item->datatype = datatype;
    item->params = (int *)calloc(100, sizeof(int));
    item->param_count = 0;
    item->is_vector = 0;
    item->is_function = 0;
    item->beginfun_label = (HASH *)calloc(1, sizeof(HASH));
    item->beginfun_label = NULL;
    item->string_id = 0;
    item->param_list = NULL;
    item->is_temp = 0;

    if (strstr(text, "label") != NULL) {
        item->is_label = 1;
    } else {
        item->is_label = 0;
    }

    if (type == SYMBOL_LIT_STRING) {
        item->string_id = string_id++;
    }

    
    strcpy(item->text, text);

    char *key = get_key(item);
    int pos = hash(key);

    debug_printf("hash.h: INSERTING WITH KEY %s ON POS %d", key, pos);

    if (hash_table[pos])
    {
        debug_printf("hash.h: COLLISION ON POS %d", pos);
        HASH *current_item = hash_table[pos];
        HASH *prev_item = NULL;
        while (current_item != NULL)
        {
            if (strcmp(get_key(current_item), key) == 0 /* current_item_key != key */)
            {
                return current_item;
            }

            prev_item = current_item;
            current_item = current_item->next;
        }

        debug_printf("hash.h: DIFFERENT KEY ON POS %d", pos);
        prev_item->next = (HASH *)calloc(1, sizeof(HASH));
        debug_printf("hash.h: LINKED LIST %d", pos);
        prev_item->next = item;
        return prev_item->next;
    }

    hash_table[pos] = (HASH *)calloc(1, sizeof(HASH));
    hash_table[pos] = item;

    return hash_table[pos];
}

void hash_print()
{
    if (hash_table == NULL)
    {
        return;
    }

    HASH* node;

    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        for (node = hash_table[i]; node; node = node->next) {
            printf("Table[%d] has %s with type %s of %s datatype", i, node->text, symbol_type_str(node->type), datatype_str[node->datatype]);
            if (hash_table[i]->type == SYMBOL_FUNCTION) {
                printf(" and params: ");
                int j;
                for (j = 0; j < 100; j++) {
                    if (node->params[j] == 0) {
                        break;
                    }

                    printf("%s ", datatype_str[node->params[j]]);
                }
            }

            printf("\n");
        }
    }
}

int hash_check_undeclared(void)
{
   if (hash == NULL)
    {
        return 0;
    }

    int undeclared = 0;

    HASH* node;

    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        for (node = hash_table[i]; node; node = node->next) {
            if (node->type == SYMBOL_IDENTIFIER) {
                fprintf(stderr, "Semantic error: Undeclared identifier %s\n", node->text);
                undeclared++;
            }

        }
    }

    return undeclared;
}

int ast_type_to_datatype(int ast_type) {
    switch (ast_type) {
        case AST_VAR_DECL_INT: return DATATYPE_INT;
        case AST_VAR_DECL_REAL: return DATATYPE_REAL;
        case AST_VAR_DECL_BOOL: return DATATYPE_BOOL;
        case AST_VAR_DECL_CHAR: return DATATYPE_CHAR;

        case AST_VEC_DECL_INT: return DATATYPE_INT;
        case AST_VEC_DECL_REAL: return DATATYPE_REAL;
        case AST_VEC_DECL_BOOL: return DATATYPE_BOOL;
        case AST_VEC_DECL_CHAR: return DATATYPE_CHAR;

        case AST_FUNC_DECL_INT: return DATATYPE_INT;
        case AST_FUNC_DECL_REAL: return DATATYPE_REAL;
        case AST_FUNC_DECL_BOOL: return DATATYPE_BOOL;
        case AST_FUNC_DECL_CHAR: return DATATYPE_CHAR;

        case AST_PARAM_INT: return DATATYPE_INT;
        case AST_PARAM_REAL: return DATATYPE_REAL;
        case AST_PARAM_BOOL: return DATATYPE_BOOL;
        case AST_PARAM_CHAR: return DATATYPE_CHAR;

        case AST_LIT_INT: return DATATYPE_INT;
        case AST_LIT_REAL: return DATATYPE_REAL;
        case AST_LIT_CHAR: return DATATYPE_CHAR;
       
    }

    return 0;
}

HASH *make_temp(int datatype) {
    static int serial = 0;
    char buffer[100];
    sprintf(buffer, "temp_%d", serial++);
    
    HASH * temp = hash_insert(buffer, SYMBOL_IDENTIFIER, datatype);
    temp->is_temp = 1;
    return temp;
}

HASH *make_missing(int datatype) {
    static int missing_serial = 0;
    char buffer[100];
    sprintf(buffer, "missing_%d", missing_serial++);

    HASH * missing = hash_insert(buffer, SYMBOL_IDENTIFIER, datatype);
    return missing;
}

HASH *make_value(int ty) {
    char *value = (char*) calloc(100, sizeof(char));
    int datatype = 0;
    switch (ty) {
        case SYMBOL_LIT_INTEGER:
        {
            datatype = DATATYPE_INT;
            value = "0";
            break;
        }
        case SYMBOL_LIT_REAL:
        {
            datatype = DATATYPE_REAL;
            value = "0.0";
            break;
        }
        case SYMBOL_LIT_CHAR:
        {
            datatype = DATATYPE_CHAR;
            value = "' '";
            break;
        }
        case SYMBOL_LIT_STRING:
        {
            datatype = DATATYPE_CHAR;
            value = "a";
            break;
        }
        default:
        {
            datatype = DATATYPE_INT;
            ty = SYMBOL_LIT_INTEGER;
            value = "0";
            break;
        }
    }

    HASH *val = hash_insert(value, ty, datatype);
}


#define CONDITIONAL_IF 0
#define CONDITIONAL_ELSE 1
#define LOOP_START 2
#define LOOP_END 3
#define CONDITIONAL_ENDIF 4
#define BEGINFUN 5
#define ENDFUN 6

HASH *make_label(int type) {
    static int serial = 0;
    char buffer[100];
   
    if (type == CONDITIONAL_IF) {
         sprintf(buffer, "if_label_%d", serial++);
    } else if (type == CONDITIONAL_ELSE) {
            sprintf(buffer, "else_label_%d", serial++);
    } else if (type == LOOP_START) {
            sprintf(buffer, "loop_start_label_%d", serial++);
    } else if (type == CONDITIONAL_ENDIF) {
            sprintf(buffer, "endif_label_%d", serial++);
    } else if (type == BEGINFUN) {
            sprintf(buffer, "beginfun_label_%d", serial++);
    } else if (type == ENDFUN) {
            sprintf(buffer, "endfun_label_%d", serial++);
    } else if (type == LOOP_END) {
            sprintf(buffer, "loop_end_label_%d", serial++);
    }

    return hash_insert(buffer, SYMBOL_LABEL, DATATYPE_INT);
}

HASH *make_missing_id() {
    static int serial = 0;
    char buffer[100];
    sprintf(buffer, "missing_id_%d", serial++);

    return hash_insert(buffer, SYMBOL_IDENTIFIER, 0);
}