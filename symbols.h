#pragma once

#define SYMBOL_IDENTIFIER 0
#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_VARIABLE 5
#define SYMBOL_FUNCTION 6
#define SYMBOL_VECTOR 7
#define SYMBOL_PARAMETER 8

char* symbol_type_str(int symbol_type);
char* symbol_type_str(int symbol_type) {
    static char* symbols_str[] = {
        "SYMBOL_IDENTIFIER",
        "SYMBOL_LIT_INTEGER",
        "SYMBOL_LIT_REAL",
        "SYMBOL_LIT_CHAR",
        "SYMBOL_LIT_STRING",
        "SYMBOL_VARIABLE",
        "SYMBOL_FUNCTION",
        "SYMBOL_VECTOR"
    };
    

    if (symbol_type > 7) return strdup("UNKNOWN");

    return symbols_str[symbol_type];
}

