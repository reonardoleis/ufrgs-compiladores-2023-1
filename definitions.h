// Leonardo Reis da Silva

#pragma once
#include <stdio.h>
#include <stdlib.h>

int is_running = 1;
int line_number = 1;

int errored_line = 0;

int getLineNumber()
{
    return line_number;
}

void increment_line_number()
{
    line_number++;
}

int yywrap(void)
{
    is_running = 0;
    return 1;
}

int isRunning(void)
{
    return is_running;
}

int yyerror(char *s)
{

    if (errored_line == 0) {
        fprintf(stderr, "Error: %s at line %d\n", s, getLineNumber());
    }

    errored_line = 0;
    
    
    
    //exit(3);
}