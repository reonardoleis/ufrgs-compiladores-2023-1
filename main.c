// Leonardo Reis da Silva

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"

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
        return 0;
    }

    char *input_file_name = argv[1];
    char* output_file_name = argv[2];

    if (!(yyin = fopen(input_file_name, "r")))
    {
        fprintf(stderr, "could not open input file\n");
        return 0;
    }

    FILE *output_file;
    if (!(output_file = fopen(output_file_name, "w")))
    {
        fprintf(stderr, "could not open output file\n");
        return 0;
    }


    int token = 0;
    yyparse();

    fprintf(stderr, "Successful compilation. Program had %d lines.", getLineNumber());

    fprintf(output_file, "%s", astToCode(root));
    exit(0);
}