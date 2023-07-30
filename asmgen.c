#include "asmgen.h"
#include "hash.h"

char * print_registers[2] = {
    "esi", "edi"
};

void generate_asm(TAC *first)
{
    int print_param_count = 0;
    char *print_formatting_str = (char*) calloc(1, sizeof(char) * 100);
    print_formatting_str = strdup("");
    FILE *fout;
    fout = fopen("out.s", "w");

    TAC *tac = tac_reverse(first);

    HASH * hash_item = hash_table[0];
    for (int i = 0; i < HASH_SIZE; i++)
    {
        if (hash_item)
        {
            switch (hash_item->type) {
                case SYMBOL_FUNCTION:
                {
                    fprintf(fout, ".%s:\n\t.text\n\t.globl	%s\n\t.type	%s, @function\n", hash_item->text, hash_item->text, hash_item->text);
                    break;
                }
                case SYMBOL_LIT_INTEGER:
                case SYMBOL_LIT_CHAR:
                {
                    fprintf(fout, "_%s: .long %s\n", hash_item->text, hash_item->text);
                    break;
                }
                case SYMBOL_IDENTIFIER:
                {
                    fprintf(fout, "_%s: .long 0\n", hash_item->text);
                }
            }
        }
        hash_item = hash_table[i];
    }

    do
    {
        switch (tac->type)
        {
        case TAC_VARDEC:
        {
            fprintf(fout, "%s: .long %s\n", tac->res->text, tac->op1->text);
            break;
        }
        case TAC_BEGINFUN:
        {
            fprintf(fout, "%s:\n\tpushq	%%rbp\n\tmovq	%%rsp, %%rbp\n", tac->res->text);
            break;
        }
        case TAC_RET:
        {
            fprintf(fout, "\tmovl	$%s, %%eax\n", tac->res->text);
            break;
        }
        case TAC_ENDFUN:
        {
                fprintf(fout, "\tpopq	%%rbp\n\tret\n");
                break;
        }
        case TAC_PRINT_ARG:
        {
            
            switch (tac->res->datatype) {
                case DATATYPE_INT: 
                {
                    strcat(print_formatting_str, "%d ");
                    break;
                }
                case DATATYPE_REAL:
                {
                    strcat(print_formatting_str, "%f ");
                }
                case DATATYPE_CHAR:
                {
                    strcat(print_formatting_str, "%c ");
                }
            }

            fprintf(fout, "\tmovl %s(%%rip), %%%s\n", tac->res->text, print_registers[print_param_count]);

            print_param_count++;
            break;
        }
        case TAC_PRINT: {
            fprintf(fout, "\tleaq	.print_str(%%rip), %%rax\n");
            fprintf(fout, "\tmovq	%%rax, %%rdi\n\tcall	printf@PLT\n");

            print_param_count = 0;
            print_formatting_str = "";



            break;
        }
        }
        tac = tac->next;
    } while (tac);

    fclose(fout);
}