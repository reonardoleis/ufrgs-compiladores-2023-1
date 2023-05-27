#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 997

typedef struct hash_t {
    int type;
    char* text;
    struct hash_t* next;
} hash_t;

int hash(char *key);
hash_t* hash_find(char *key);
hash_t* hash_insert(char *text, int type);
char* get_key(hash_t* hash);

hash_t* hash_table[HASH_SIZE];


void initMe() {}

int hash(char *text) {
    int i;
    int hash_val = 1;
    for (i = 0; i < strlen(text); i++) {
        hash_val = (hash_val * text[i]) % HASH_SIZE + 1;
    }

    return hash_val - 1;
}

char* get_key(hash_t* hash) {
    return hash->text;
}

hash_t* hash_find(char *key) {
    int pos = hash(key);

    hash_t* item = hash_table[pos];
    if (item == NULL) {
        return NULL;
    }

    if (item->next == NULL) {
        return item;
    }

    item = item->next;
    while(item != NULL) {
        char* item_key = get_key(item);
        if (strcmp(key, item_key)) {
            return item;
        }

        item = item->next;
    }

    return NULL;
}

hash_t* hash_insert(char *text, int type) {
    hash_t* item = (hash_t*) calloc(1, sizeof(hash_t));
    item->type = type;
    item->text = (char*) calloc(strlen(text) + 1, sizeof(char));
    strcpy(item->text, text);
    
    char* key = get_key(item);
    int pos = hash(key);

    int exists = hash_table[pos] != NULL;
    if (exists) {
        hash_t* current_item = hash_table[pos];
        while (current_item->next != NULL) {
            if (strcmp(get_key(current_item), key)) {
                return current_item;
            }
            current_item = current_item->next;
        }
        current_item->next = (hash_t*) calloc(1, sizeof(hash_t));
        current_item->next = item;
        return current_item->next;
    }

    hash_table[pos] = (hash_t*) calloc(1, sizeof(hash_t));
    hash_table[pos] = item;

    return hash_table[pos];
}