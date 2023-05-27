#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "tokens.h"

int isRunning();
int getLineNumber();
void initMe();
int is_running = 1;

int yylex();
extern char* yytext;
extern FILE* yyin;

int getLineNumber() {
    return 0;
}

int isRunning() {
    return is_running;
}

int main(int argc, char** argv) {
    
    if (argc < 3) {
        fprintf(stderr, "usage: ./a.out input.txt output.txt\n");
        return 0;
    }

    char* input_file_name = argv[1];
    char* output_file_name = argv[2];
    
    if (!(yyin = fopen(input_file_name, "r"))) {
        fprintf(stderr, "could not open input file\n");
        return 0;
    }


    int token = 0;
    while (isRunning()) {
        token = yylex();

        if (!isRunning()) {
            return 0;
        }

        switch (token) {
            case KW_CHAR:       { fprintf(stderr, "KW_CHAR\n"); break; }
            case KW_INT:        { fprintf(stderr, "KW_INT\n"); break;  }
            case KW_REAL:       { fprintf(stderr, "KW_REAL\n"); break;  }
            case KW_BOOL:       { fprintf(stderr, "KW_BOOL\n"); break;  }
            case KW_IF:         { fprintf(stderr, "KW_IF\n"); break;  }
            case KW_THEN:       { fprintf(stderr, "KW_THEN\n"); break;  }
            case KW_ELSE:       { fprintf(stderr, "KW_ELSE\n"); break;  }
            case KW_LOOP:       { fprintf(stderr, "KW_LOOP\n"); break;  }
            case KW_INPUT:      { fprintf(stderr, "KW_INPUT\n"); break;  }
            case KW_OUTPUT:     { fprintf(stderr, "KW_OUTPUT\n"); break;  }
            case KW_RETURN:     { fprintf(stderr, "KW_RETURN\n"); break;  }
            case OPERATOR_LE:   { fprintf(stderr, "OPERATOR_LE\n"); break;  }
            case OPERATOR_GE:   { fprintf(stderr, "OPERATOR_GE\n"); break;  }
            case OPERATOR_EQ:   { fprintf(stderr, "OPERATOR_EQ\n"); break;  }
            case OPERATOR_DIF:  { fprintf(stderr, "OPERATOR_DIF\n"); break;  }
            case LIT_INT:       { fprintf(stderr, "LIT_INT\n"); break;  }
            case LIT_CHAR:      { fprintf(stderr, "LIT_CHAR\n"); break;  }
            case LIT_REAL:      { fprintf(stderr, "LIT_REAL\n"); break;  }
            case LIT_STRING:    { fprintf(stderr, "LIT_STRING\n"); break;  }
            case TK_IDENTIFIER: { fprintf(stderr, "TK_IDENTIFIER\n"); break;  }
            case TOKEN_ERROR:   { fprintf(stderr, "TOKEN_ERROR\n"); break;  }
            default:            { fprintf(stderr, "OP %d\n", token);     break;}     
        }
    }

    return 0;
}

int yywrap() {
    is_running = 0;
    return 1;
}