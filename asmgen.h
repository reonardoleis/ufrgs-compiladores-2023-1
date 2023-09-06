#pragma once
#include "tac.h"

char* arithmetic_tac_to_asm(TAC *tac);
char* logic_tac_to_asm(TAC *tac);
char* remove_decimal_point(char* str);
void generate_asm(TAC *first);