//%define parse.error verbose
%token KW_CHAR 
%token KW_INT
%token KW_REAL 
%token KW_BOOL 

%token KW_IF 
%token KW_THEN 
%token KW_ELSE 
%token KW_LOOP 
%token KW_INPUT
%token KW_OUTPUT 
%token KW_RETURN 

%token OPERATOR_LE 
%token OPERATOR_GE 
%token OPERATOR_EQ 
%token OPERATOR_DIF

%token TK_IDENTIFIER 

%token LIT_INT 
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR 


%left '*' '/' '+' '-' '~' '&' '|' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '>' '<';
%%

program: declaration_list
    ;

declaration_list: declaration declaration_list
    |
    ;

declaration: var_declaration ';'
    |        vec_declaration vec_init ';'
    |        func_declaration

type: KW_INT | KW_CHAR | KW_REAL | KW_BOOL;
literal: LIT_INT | LIT_CHAR | LIT_REAL;

var_declaration: type TK_IDENTIFIER '=' literal;

vec_init: literal
    |     literal vec_init
    |
    ;

vec_declaration: type TK_IDENTIFIER '[' LIT_INT ']';

parameter: type TK_IDENTIFIER;

parameter_list: parameter
    |           parameter ',' parameter_list
    |
    ;

func_declaration: type TK_IDENTIFIER '(' parameter_list ')' body;

body: '{' cmd_list '}';

cmd_list: cmd ';' cmd_list
    |     ';' cmd_list
    |     body cmd_list
    |     conditional_cmd cmd_list
    |
    ;

cmd:  var_attrib
    | vec_attrib
    | output_cmd
    | return_cmd
    | 
    ;

var_attrib: TK_IDENTIFIER '=' expr;

vec_attrib: TK_IDENTIFIER '[' expr ']' '=' expr;

output_cmd: KW_OUTPUT output_param_list;

output_param_list: LIT_STRING ',' output_param_list
    |              expr ',' output_param_list
    |              LIT_STRING
    |              expr
    ;

return_cmd: KW_RETURN expr;

conditional_cmd: KW_IF '(' expr ')' cmd_list
    |            KW_IF '(' expr ')' cmd_list KW_ELSE cmd_list
    |            KW_IF '(' expr ')' KW_LOOP cmd_list
    ;
    
input_expr: KW_INPUT '(' type ')';

vec_access: TK_IDENTIFIER '[' expr ']';

expr: TK_IDENTIFIER
    | vec_access
    | literal
    | input_expr
    | func_call
    | expr '*' expr
    | expr '/' expr
    | expr '+' expr
    | expr '-' expr
    | '-' expr
    | '~' expr
    | expr '&' expr
    | expr '|' expr
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | expr '>' expr
    | expr '<' expr
    | '(' expr ')'

func_call: TK_IDENTIFIER '(' expr_list ')';

expr_list:  expr
    |       expr ',' expr_list
    |
    ;

%%

#include "definitions.h" // yyparse() is defined here