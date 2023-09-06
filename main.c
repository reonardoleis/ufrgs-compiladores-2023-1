// Leonardo Reis da Silva



#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"

#include "ast.h"
#include "ast.c"

#include "tac.h"
#include  "tac.c"

#include "semantic.h"
#include "semantic.c"

#include "asmgen.h"
#include "asmgen.c"

#include "optimization.h"
#include "optimization.c"


int isRunning();
int getLineNumber();
void initMe();

int yylex();
extern char *yytext;
extern FILE *yyin;


int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "usage: ./a.out input.txt output.txt\n");
        exit(1);
    }

    if (argc == 3) {
        if (strcmp(argv[2], "-o") == 0) {
            optimize = 1;
            fprintf(stderr, "Optimization = %d\n", optimize);
        }
    }

   
    char *input_file_name = argv[1];

    if (!(yyin = fopen(input_file_name, "r")))
    {
        fprintf(stderr, "could not open input file\n");
        exit(2);
    }

    char *output_file_name = "out.decomp";
    FILE *output_file;
    if (!(output_file = fopen(output_file_name, "w")))
    {
        fprintf(stderr, "could not open output file\n");
        exit(2);
    }


    int token = 0;
    yyparse();


    if (SyntaxErrors > 0) {
        fprintf(stderr, "\n\nCompilation failed with %d syntax errors. Program had %d lines.\n\n", SyntaxErrors, getLineNumber());
        exit(3);
    }

    if (SemanticErrors == 0) {
        fprintf(stderr, "\n\nSuccessful compilation. Program had %d lines.\n\n", getLineNumber());
    } else {
        fprintf(stderr, "\n\nCompilation failed with %d Semantic errors. Program had %d lines.\n\n", SemanticErrors, getLineNumber());
        exit(4);
    }
     
   // hash_print();
    fprintf(output_file, "%s", astToCode(root));
    exit(0);
}