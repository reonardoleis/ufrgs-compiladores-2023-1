#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 997

typedef struct hash_t {
    char* literal;
    char* identifier;
    struct hash_t* next;
} hash_t;

int hash(char *key);
hash_t* hash_find(char *key);
void hash_insert(hash_t* hash);
char* get_key(hash_t* hash);

hash_t* hash_table[HASH_SIZE];


void initMe() {}

int hash(char *key) {
    int i;
    int sum = 0;
    for (i = 0; i < strlen(key); i++) {
        sum += (i+1) * (key[i]);
    }

    return sum % HASH_SIZE;
}

char* get_key(hash_t* hash) {
    char* key = hash->identifier;
    key = strcat(key, hash->literal);

    return key;
}

hash_t* hash_find(char *key) {
    int pos = hash(key);
    //fprintf(stderr, "Fetching from at %d\n", pos);

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

void hash_insert(hash_t* item) {
    char* key = (char*) calloc(1, sizeof(item->literal) + sizeof(item->identifier));
    strcpy(key, item->literal);
    key = strcat(key, item->identifier);
    int pos = hash(key);

    
    int exists = hash_table[pos] != NULL;
    if (exists) {
        hash_t* current_item = hash_table[pos];
        while (current_item->next != NULL) {
            if (strcmp(get_key(current_item), key)) {
                return;
            }
            current_item = current_item->next;
        }
        current_item->next = (hash_t*) calloc(1, sizeof(hash_t));
        current_item->next = item;
        return;
    }

    hash_table[pos] = (hash_t*) calloc(1, sizeof(hash_t));
    hash_table[pos] = item;
}