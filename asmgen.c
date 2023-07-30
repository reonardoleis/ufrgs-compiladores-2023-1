#include "asmgen.h"
#include "hash.h"

char *print_registers[2] = {
    "esi", "edi"};

char *get_string_name(int string_id);
char *get_string_name(int string_id)
{
    char *string_name = (char *)calloc(1, sizeof(char) * 100);
    sprintf(string_name, "string_%d", string_id);
    return string_name;
}

void generate_asm(TAC *first)
{
    int print_param_count = 0;
    char *print_formatting_str = (char *)calloc(1, sizeof(char) * 100);
    print_formatting_str = strdup("");
    FILE *fout;
    fout = fopen("out.s", "w");

    fprintf(fout, ".section .data\n\n");
    fprintf(fout, "print_str_int:\n\t.string	\"%%d\"\nprint_str_real:\n\t.string	\"%%f\"\nprint_str_char:\n\t.string	\"%%c\"\n");

    TAC *tac = tac_reverse(first);

    HASH *hash_item = hash_table[0];
    for (int i = 0; i < HASH_SIZE; i++)
    {
        if (hash_item)
        {
            switch (hash_item->type)
            {
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
            case SYMBOL_LIT_STRING:
            {
                if (hash_item->string_id == 0)
                {
                    break;
                }
                char *string_name = get_string_name(hash_item->string_id);
                fprintf(fout, "_%s: .string %s\n", string_name, hash_item->text);
                break;
            }
            }
        }
        hash_item = hash_table[i];
    }

    TAC *origin = tac;

    do
    {
        if (tac->type == TAC_VARDEC)
        {
            switch (tac->res->datatype)
            {
            case DATATYPE_INT:
            case DATATYPE_CHAR:
            {
                fprintf(fout, "_%s: .long %s\n", tac->res->text, tac->op1->text);
                break;
            }
            case DATATYPE_REAL:
            {
                fprintf(fout, "_%s: .float %s\n", tac->res->text, tac->op1->text);
                break;
            }
            }
        }
        tac = tac->next;
    } while (tac);

    tac = origin;

    fprintf(fout, "\n.section .text\n\n");
    do
    {
        switch (tac->type)
        {
        case TAC_BEGINFUN:
        {
            fprintf(fout, ".%s:\n\t.text\n\t.globl	%s\n\t.type	%s, @function\n", tac->res->text, tac->res->text, tac->res->text);
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
            switch (tac->res->datatype)
            {
            case DATATYPE_INT:
            {
                fprintf(fout, "\tmovl _%s(%%rip), %%esi\n", tac->res->text);
                fprintf(fout, "\tleaq	print_str_int(%%rip), %%rax\n\tmovq	%%rax, %%rdi\n\tcall	printf@PLT\n");
                break;
            }
            case DATATYPE_REAL:
            {
                fprintf(fout, "\tmovss _%s(%%rip), %%xmm0\n\tpxor %%xmm1, %%xmm1\n\tcvtss2sd	%%xmm0, %%xmm1\n\tmovq %%xmm1, %%rax\n\tmovq %%rax, %%xmm0\n", tac->res->text);
                fprintf(fout, "\tleaq	print_str_real(%%rip), %%rax\n\tmovq	%%rax, %%rdi\n\tcall	printf@PLT\n");
                break;
            }
            case DATATYPE_CHAR:
            {
                fprintf(fout, "\tmovl _%s(%%rip), %%esi\n", tac->res->text);
                fprintf(fout, "\tleaq	print_str_char(%%rip), %%rax\n\tmovq	%%rax, %%rdi\n\tcall	printf@PLT\n");
                break;
            }
            default:
            {
                fprintf(fout, "\tleaq _%s(%%rip), %%rax\n\tmovq	%%rax, %%rdi\n\tcall	printf@PLT\n", get_string_name(tac->res->string_id));
                break;
            }
            }
            break;
        }
        case TAC_ADD:
        {
            fprintf(stderr, "DATATYPE: %s\n", datatype_str[tac->res->datatype]);
            if (tac->res->datatype == DATATYPE_INT)
            {
                fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n", tac->op1->text);
                fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n", tac->op2->text);
                fprintf(fout, "\taddl	%%eax, %%edx\n");
                fprintf(fout, "\tmovl	%%edx, _%s(%%rip)\n", tac->res->text);
            }
            else
            {
                fprintf(fout, "\tmovss	_%s(%%rip), %%xmm1\n", tac->op1->text);
                fprintf(fout, "\tmovss	_%s(%%rip), %%xmm0\n", tac->op2->text);
                fprintf(fout, "\taddss	%%xmm1, %%xmm0\n");
                fprintf(fout, "\tmovss	%%xmm0, _%s(%%rip)\n", tac->res->text);
            }
            break;
        }
        case TAC_SUB:
        {
            if (tac->res->datatype == DATATYPE_INT)
            {
                fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n", tac->op1->text);
                fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n", tac->op2->text);
                fprintf(fout, "\tsubl	%%eax, %%edx\n");
                fprintf(fout, "\tmovl	%%edx, _%s(%%rip)\n", tac->res->text);
            }
            else
            {
                fprintf(fout, "\tmovss	_%s(%%rip), %%xmm1\n", tac->op1->text);
                fprintf(fout, "\tmovss	_%s(%%rip), %%xmm0\n", tac->op2->text);
                fprintf(fout, "\tsubss	%%xmm0, %%xmm1\n");
                fprintf(fout, "\tmovss	%%xmm1, _%s(%%rip)\n", tac->res->text);
            }

            break;
        }
        case TAC_COPY:
        {
            fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op1->text);
            fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
            break;
        }
        }
        tac = tac->next;
    } while (tac);

    fclose(fout);
}