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

    int i;
    for (i = 0; i < HASH_SIZE; i++)
    {
        if (hash_table[i])
        {
            HASH *node = hash_table[i];
            while (node)
            {
                if (node->is_vector)
                {
                    node = node->next;
                    continue;
                }
                switch (node->type)
                {
                case SYMBOL_LIT_INTEGER:
                case SYMBOL_LIT_CHAR:
                {
                    fprintf(fout, "_%s: .long %s\n", node->text, node->text);
                    break;
                }
                case SYMBOL_IDENTIFIER:
                {
                    fprintf(fout, "_%s: .long 0\n", node->text);
                    break;
                }
                case SYMBOL_LIT_REAL:
                {
                    fprintf(fout, "_%s: .float %s\n", remove_decimal_point(node->text), node->text);
                    break;
                }
                case SYMBOL_LIT_STRING:
                {
                    if (node->string_id == 0)
                    {
                        break;
                    }
                    char *string_name = get_string_name(node->string_id);
                    fprintf(fout, "_%s: .string %s\n", string_name, node->text);
                    break;
                }
                case SYMBOL_VARIABLE:
                {
                    if (node->datatype != DATATYPE_INT && node->datatype != DATATYPE_CHAR && node->datatype != DATATYPE_REAL)
                    {
                        fprintf(fout, "_%s: .long 0\n", node->text);
                    }

                    break;
                }
                default:
                {
                    if (!node->is_function && !node->is_label)
                    {
                        switch (node->datatype)
                        {
                        case DATATYPE_INT:
                        case DATATYPE_CHAR:
                        case DATATYPE_BOOL:
                        {
                            fprintf(fout, "_%s: .long 0\n", node->text);
                            break;
                        }
                        case DATATYPE_REAL:
                        {
                            fprintf(fout, "_%s: .float 0.0\n", node->text);
                            break;
                        }
                        }
                    }
                }
                }
                node = node->next;
            }
        }
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
        fprintf(fout, "\t# %s\n", tac_type_str[tac->type]);
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
            fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->res->text);
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
            case DATATYPE_BOOL:
            {
                fprintf(fout, "\tmovl _%s(%%rip), %%esi\n", tac->res->text);
                fprintf(fout, "\tleaq	print_str_int(%%rip), %%rax\n\tmovq	%%rax, %%rdi\n\tcall	printf@PLT\n");
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
        case TAC_SUB:
        case TAC_MUL:
        {
            if (tac->res->datatype == DATATYPE_INT)
            {
                fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n", tac->op1->text);
                fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n", tac->op2->text);
                fprintf(fout, "\t%sl	%%eax, %%edx\n", arithmetic_tac_to_asm(tac));
                fprintf(fout, "\tmovl	%%edx, _%s(%%rip)\n", tac->res->text);
            }
            else
            {
                fprintf(stderr, "IDENTIFIER ERRADO: %s\n", datatype_str[tac->op1->datatype]);
                fprintf(stderr, "TEXT OF: %s\n", tac->op1->text);
                fprintf(fout, "\tmovss	_%s(%%rip), %%xmm0\n", remove_decimal_point(tac->op1->text));
                fprintf(fout, "\tmovss	_%s(%%rip), %%xmm1\n", remove_decimal_point(tac->op2->text));
                fprintf(fout, "\t%sss	%%xmm1, %%xmm0\n", arithmetic_tac_to_asm(tac));
                fprintf(fout, "\tmovss	%%xmm0, _%s(%%rip)\n", tac->res->text);
            }
            break;
        }
        case TAC_DIV:
        {
            if (tac->res->datatype == DATATYPE_INT)
            {
                fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op1->text);
                fprintf(fout, "\tmovl _%s(%%rip), %%ecx\n", tac->op2->text);
                fprintf(fout, "\tcltd\n");
                fprintf(fout, "\tidivl %%ecx\n");
                fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
            }
            else
            {
                fprintf(fout, "\tmovss	_%s(%%rip), %%xmm0\n", remove_decimal_point(tac->op1->text));
                fprintf(fout, "\tmovss	_%s(%%rip), %%xmm1\n", remove_decimal_point(tac->op2->text));
                fprintf(fout, "\tdivss	%%xmm1, %%xmm0\n");
                fprintf(fout, "\tmovss	%%xmm0, _%s(%%rip)\n", tac->res->text);
            }
            break;
        }
        case TAC_LE:
        case TAC_GE:
        case TAC_LT:
        case TAC_GT:
        case TAC_EQ:
        case TAC_DIF:
        {
            if (tac->res->datatype == DATATYPE_INT)
            {
                fprintf(fout, "\tmovl _%s(%%rip), %%edx\n", tac->op1->text);
                fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op2->text);
                fprintf(fout, "\tcmpl %%eax, %%edx\n");
                fprintf(fout, "\t%s %%al\n", logic_tac_to_asm(tac));
                fprintf(fout, "\tmovzbl %%al, %%eax\n");
                fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
            }
            else
            {
                switch (tac->type)
                {
                case TAC_LT:
                {
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm1\n", remove_decimal_point(tac->op1->text));
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm0\n", remove_decimal_point(tac->op2->text));
                    fprintf(fout, "\tcomiss %%xmm1, %%xmm0\n");
                    fprintf(fout, "\tseta %%al\n");
                    fprintf(fout, "\tmovzbl %%al, %%eax\n");
                    fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
                    break;
                }
                case TAC_GT:
                {
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm0\n", remove_decimal_point(tac->op1->text));
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm1\n", remove_decimal_point(tac->op2->text));
                    fprintf(fout, "\tcomiss %%xmm1, %%xmm0\n");
                    fprintf(fout, "\tseta %%al\n");
                    fprintf(fout, "\tmovzbl %%al, %%eax\n");
                    fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
                    break;
                }
                case TAC_LE:
                {
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm1\n", remove_decimal_point(tac->op1->text));
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm0\n", remove_decimal_point(tac->op2->text));
                    fprintf(fout, "\tcomiss %%xmm1, %%xmm0\n");
                    fprintf(fout, "\tsetnb %%al\n");
                    fprintf(fout, "\tmovzbl %%al, %%eax\n");
                    fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);

                    break;
                }
                case TAC_GE:
                {
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm0\n", remove_decimal_point(tac->op1->text));
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm1\n", remove_decimal_point(tac->op2->text));
                    fprintf(fout, "\tcomiss %%xmm1, %%xmm0\n");
                    fprintf(fout, "\tsetnb %%al\n");
                    fprintf(fout, "\tmovzbl %%al, %%eax\n");
                    fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);

                    break;
                }
                case TAC_EQ:
                case TAC_DIF:
                {
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm0\n", remove_decimal_point(tac->op1->text));
                    fprintf(fout, "\tmovss _%s(%%rip), %%xmm1\n", remove_decimal_point(tac->op2->text));
                    fprintf(fout, "\tucomiss %%xmm1, %%xmm0\n");
                    fprintf(fout, "\tsetnp %%al\n");
                    fprintf(fout, "\tmovl $%d, %%edx\n", tac->type == TAC_EQ ? 0 : 1);
                    fprintf(fout, "\tucomiss %%xmm1, %%xmm0\n");
                    fprintf(fout, "\tcmovne %%edx, %%eax\n");
                    fprintf(fout, "\tmovzbl %%al, %%eax\n");
                    fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
                    break;
                }
                }
            }
            break;
        }
        case TAC_OR:
        case TAC_AND:
        {

            fprintf(fout, "\tmovl _%s(%%rip), %%edx\n", tac->op1->text);
            fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op2->text);
            fprintf(fout, "\t%s %%edx, %%eax\n", logic_tac_to_asm(tac));
            fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);

            break;
        }
        case TAC_NOT:
        {

            fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op1->text);
            fprintf(fout, "\ttestl %%eax, %%eax\n");
            fprintf(fout, "\tsete %%al\n");
            fprintf(fout, "\tmovzbl %%al, %%eax\n");
            fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);

            break;
        }
        case TAC_COPY:
        case TAC_ARG:
        {
            if (tac->res->is_vector)
            {
                if (tac->op1->type == SYMBOL_VARIABLE || 
                    tac->op1->type == SYMBOL_IDENTIFIER ||
                    tac->op1->type == SYMBOL_PARAMETER)
                {


                    fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op1->text);
                    fprintf(fout, "\tcltq\n");
                    fprintf(fout, "\tleaq	0(,%%rax,4), %%rdx\n");
                    fprintf(fout, "\tleaq _%s(%%rip), %%rax\n", tac->res->text);
                    fprintf(fout, "\tmovl _%s(%%rip), %%ecx\n", tac->op2->text);
                    fprintf(fout, "\tmovl %%ecx, (%%rdx,%%rax)\n");

                }
                else
                {
                    int index = 4 * atoi(tac->op1->text);
                    fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", remove_decimal_point(tac->op2->text));
                    fprintf(fout, "\tmovl %%eax, %d+_%s(%%rip)\n", index, tac->res->text);
                }
            }
            else if (tac->op1->is_vector)
            {
                if (tac->op2->type == SYMBOL_VARIABLE || 
                    tac->op2->type == SYMBOL_IDENTIFIER ||
                    tac->op2->type == SYMBOL_PARAMETER)
                {
                    fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "\tcltq\n");
                    fprintf(fout, "\tleaq 0(,%%rax,4), %%rdx\n");
                    fprintf(fout, "\tleaq _%s(%%rip), %%rax\n", tac->op1->text);
                    fprintf(fout, "\tmovl (%%rdx,%%rax), %%eax\n");
                    fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
                }
                else
                {
                    int index = 4 * atoi(tac->op2->text);
                    fprintf(fout, "\tmovl %d+_%s(%%rip), %%eax\n", index, tac->op1->text);
                    fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
                }
            }
            else
            {
                fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op1->text);
                fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
            }

            break;
        }
        case TAC_LABEL:
        {
            fprintf(fout, "_%s:\n", tac->res->text);
            break;
        }
        case TAC_JFALSE:
        {
            fprintf(fout, "\tmovl _%s(%%rip), %%eax\n", tac->op1->text);
            fprintf(fout, "\ttestl %%eax, %%eax\n");
            fprintf(fout, "\tje _%s\n", tac->res->text);
            break;
        }
        case TAC_JUMP:
        {
            fprintf(fout, "\tjmp _%s\n", tac->res->text);
            break;
        }
        case TAC_CALL:
        {
            fprintf(fout, "\tcall %s\n", tac->op1->text);
            fprintf(fout, "\tmovl %%eax, _%s(%%rip)\n", tac->res->text);
            break;
        }
        case TAC_READ:
        {
            fprintf(fout, "\tleaq _%s(%%rip), %%rax\n", tac->res->text);
            fprintf(fout, "\tmovq %%rax, %%rsi\n");
            fprintf(fout, "\tleaq print_str_int(%%rip), %%rax\n");
            fprintf(fout, "\tmovq %%rax, %%rdi\n");
            fprintf(fout, "\tmovl $0, %%eax\n");
            fprintf(fout, "\tcall __isoc99_scanf@PLT\n");

            break;
        }
        case TAC_VECDEC:
        {

            /*.globl	vec
    .data
    .align 8
    .type	vec, @object
    .size	vec, 12*/

            fprintf(fout, "\t.globl\t_%s\n", tac->res->text);
            fprintf(fout, "\t.data\n");
            fprintf(fout, "\t.align 8\n");
            fprintf(fout, "\t.type\t_%s, @object\n", tac->res->text);
            fprintf(fout, "\t.size\t_%s, %d\n", tac->res->text, 4 * atoi(tac->op1->text));

            fprintf(fout, "_%s:\n", tac->res->text);

            TAC *first_vec_item = tac->next;
            while (first_vec_item && first_vec_item->type == TAC_SYMBOL)
            {
                fprintf(fout, "\t.long %s\n", first_vec_item->res->text);
                first_vec_item = first_vec_item->next;
            }

            break;
        }
        }
        tac = tac->next;
    } while (tac);

    fclose(fout);
}

char *arithmetic_tac_to_asm(TAC *tac)
{
    switch (tac->type)
    {
    case TAC_ADD:
        return strdup("add");
    case TAC_SUB:
        return strdup("sub");
    case TAC_MUL:
    {
        if (tac->res->datatype == DATATYPE_INT)
            return strdup("imul");
        else
            return strdup("mul");
    }
    case TAC_DIV:
        return strdup("idiv");
    }
}

char *remove_decimal_point(char *str)
{
    // copy str to a new string
    char *copy = strdup(str);
    // split  string on "." and create "before" and "after"
    char *before = strtok(copy, ".");
    char *after = strtok(NULL, ".");

    char *result = (char *)calloc(100, sizeof(char));

    // if there was a decimal point, concatenate the two parts
    strcat(result, before);
    if (after)
    {
        strcat(result, "f");
        strcat(result, after);
    }

    return result;
}

char *logic_tac_to_asm(TAC *tac)
{

    switch (tac->type)
    {
    case TAC_LE:
        return strdup("setle");
    case TAC_GE:
        return strdup("setge");
    case TAC_EQ:
        return strdup("sete");
    case TAC_DIF:
        return strdup("setne");
    case TAC_LT:
        return strdup("setl");
    case TAC_GT:
        return strdup("setg");
    case TAC_OR:
        return strdup("orl");
    case TAC_AND:
        return strdup("andl");
    }

    return strdup("ERROR");
}