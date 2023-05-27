%{

#include "tokens.h"
#include "definitions.h"
#include "hash.h"

%}

%s MULTI_LINE_COMMENT

%%


<MULTI_LINE_COMMENT>"\/\/\/"            { BEGIN(0); }
<MULTI_LINE_COMMENT>[^\n]*              { /* ignore */ }
<MULTI_LINE_COMMENT>\n                   { /* ignore */ }

(\\\\\\)            { BEGIN(MULTI_LINE_COMMENT); }

(\\\\)[^\\](.)*(\n)      { return SINGLE_LINE_COMMENT; }



"char"        { return KW_CHAR; }
"int"      { return KW_INT; }
"real"        { return KW_REAL; }
"bool"        { return KW_BOOL; }
"if"          { return KW_IF; }
"then"        { return KW_THEN; }
"else"        { return KW_ELSE; }
"loop"        { return KW_LOOP; }
"input"       { return KW_INPUT; }
"output"      { return KW_OUTPUT; }
"return"     { return KW_RETURN; }

"<="          { return OPERATOR_LE; }
">="          { return OPERATOR_GE; }
"=="          { return OPERATOR_EQ; }
"!="          { return OPERATOR_DIF; }

[0-9]+                  { hash_insert(yytext, LIT_INT); return LIT_INT; }
\'[^\']\'                   { hash_insert(yytext, LIT_CHAR); return LIT_CHAR; }
[0-9]+\.([0-9]+)        { hash_insert(yytext, LIT_REAL); return LIT_REAL; }
(\"[^\"]*\")            { hash_insert(yytext, LIT_STRING); return LIT_STRING; }

[a-zA-Z._]+ { hash_insert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; }
[,;()\[\]{}=+\-*/%<>&|~] { return yytext[0]; }

[\n\t ]       { /* ignore */ }

.             { return TOKEN_ERROR; }






%%

#include "hash.h"
#include "main.c"