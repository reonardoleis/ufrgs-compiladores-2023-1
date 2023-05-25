#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}