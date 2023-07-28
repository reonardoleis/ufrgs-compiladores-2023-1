// Leonardo Reis da Silva

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"
#include "tac.h"
#include  "tac.c"


int isRunning();
int getLineNumber();
void initMe();

int yylex();
extern char *yytext;
extern FILE *yyin;

int main(int argc, char **argv)
{

    if (argc < 3)
    {
        fprintf(stderr, "usage: ./a.out input.txt output.txt\n");
        exit(1);
    }

    char *input_file_name = argv[1];
    char* output_file_name = argv[2];

    if (!(yyin = fopen(input_file_name, "r")))
    {
        fprintf(stderr, "could not open input file\n");
        exit(2);
    }

    FILE *output_file;
    if (!(output_file = fopen(output_file_name, "w")))
    {
        fprintf(stderr, "could not open output file\n");
        return 0;
    }


    int token = 0;
    yyparse();

   // hash_print();

    if (SemanticErrors == 0) {
        fprintf(stderr, "\n\nSuccessful compilation. Program had %d lines.\n\n", getLineNumber());
    } else {
        fprintf(stderr, "\n\nCompilation failed with %d Semantic errors. Program had %d lines.\n\n", SemanticErrors, getLineNumber());
        exit(4);
    }
     


 
    fprintf(output_file, "%s", astToCode(root));
    exit(0);
}