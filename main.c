#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main() {
    hash_t* element1 = (hash_t*) calloc(1, sizeof(hash_t));
    hash_t* element2 = (hash_t*) calloc(1, sizeof(hash_t));
    hash_t* element3 = (hash_t*) calloc(1, sizeof(hash_t));

    element1->identifier = "a";
    element1->literal = "int";

    element2->identifier = "b";
    element2->literal = "int";

    element3->identifier = "a";
    element3->literal = "real";

    hash_insert(element1);
    hash_insert(element2);
    hash_insert(element3);

    hash_t* found = (hash_t*) calloc(1, sizeof(hash_t));
    found = hash_find("intb");
    if (found != NULL) {
        fprintf(stderr, "Found %s %s", found->literal, found->identifier);
    }
 
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}