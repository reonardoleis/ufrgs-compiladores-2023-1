%{

#include "tokens.h"

%}

%%

"char"        { return LIT_CHAR; }
"int"         { return LIT_INT; }
"real"        { return LIT_REAL; }
"bool"        { return KW_BOOL; }
"if"          { return KW_IF; }
"then"        { return KW_THEN; }
"else"        { return KW_ELSE; }
"loop"        { return KW_LOOP; }
"input"       { return KW_INPUT; }
"output"      { return KW_OUTPUT; }
"return"     { return KW_RETURN; }
"<="          { fprintf(stderr, "OPERATOR_LE FOUND"); return OPERATOR_LE; }
">="          { return OPERATOR_GE; }
"=="          { return OPERATOR_EQ; }
"!="          { return OPERATOR_DIF; }
[a-zA-z._]* { fprintf(stderr, "TK_IDENTIFIER FOUND"); return TK_IDENTIFIER; }

[",;()\[\]{}=+\-*/%><&|~] { return yytext[0]; }

%%

#include "hash.h"
#include "main.c"