// Leonardo Reis da Silva

#pragma once
#include <stdio.h>
#include <stdlib.h>

int is_running = 1;
int line_number = 1;

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
    fprintf(stderr, "Error: %s at line %d\n", s, getLineNumber());
    exit(3);
}