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

int hash(char* literal, char* identifier);
hash_t* hash_find(char* literal, char* identifier);
void hash_insert(hash_t* hash);

hash_t* hash_table[HASH_SIZE];


int hash(char* literal, char* identifier) {
    int i;
    int sum = 0;
    for (i = 0; i < strlen(literal); i++) {
        sum += (i+1) * (literal[i]);
    }

    for (i = 0; i < strlen(identifier); i++) {
        sum += (i+1) * (identifier[i]);
    }


    return sum % HASH_SIZE;
}

hash_t* hash_find(char* literal, char* identifier) {
    int pos = hash(literal, identifier);
    //fprintf(stderr, "Fetching from at %d\n", pos);

    hash_t* item = hash_table[pos];
    if (item == NULL) {
        return NULL;
    }

    if (item->next == NULL) {
        return item;
    }

    while(1) {
        if (item->next == NULL) {
            return item;
        }

        item = item->next;
    }

    return NULL;
}

int hash_exists(char* literal, char* identifier) {
    return hash_find(literal, identifier) != NULL;
}

void hash_insert(hash_t* item) {
    int pos = hash(item->literal, item->identifier);
    //fprintf(stderr, "Inserting at from %d\n", pos);
    
    int exists = hash_exists(item->literal, item->identifier);
    if (exists) {
        hash_t* current_item = hash_table[pos];
        while (current_item->next != NULL) {
            current_item = current_item->next;
        }
        current_item->next = (hash_t*) calloc(1, sizeof(hash_t));
        current_item->next = item;
        return;
    }

    hash_table[pos] = (hash_t*) calloc(1, sizeof(hash_t));
    hash_table[pos] = item;
}