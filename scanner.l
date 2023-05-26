%{

#include "tokens.h"
#include "definitions.h"

%}

%s MULTI_LINE_COMMENT

%%


<MULTI_LINE_COMMENT>"\/\/\/"            { BEGIN(0); }
<MULTI_LINE_COMMENT>[^\n]*              { }
<MULTI_LINE_COMMENT>\n                   { }

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

[0-9]+        { return LIT_INT; }
\'.\'    { return LIT_CHAR; }
[0-9]+\.([0-9]+)       { return LIT_REAL; }
(\"[^\"]*\")                  { return LIT_STRING; }

[a-zA-z._]* { return TK_IDENTIFIER; }
[",;()\[\]{}=+\-*/%><&|~] { return yytext[0]; }

.             { }






%%

#include "hash.h"
#include "main.c"