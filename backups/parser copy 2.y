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

variable_declaration: KW_INT TK_IDENTIFIER '=' LIT_INT
    | KW_INT TK_IDENTIFIER '=' LIT_CHAR
    | KW_INT TK_IDENTIFIER '=' LIT_REAL

    | KW_CHAR TK_IDENTIFIER '=' LIT_INT
    | KW_CHAR TK_IDENTIFIER '=' LIT_CHAR
    | KW_CHAR TK_IDENTIFIER '=' LIT_REAL

    | KW_REAL TK_IDENTIFIER '=' LIT_INT
    | KW_REAL TK_IDENTIFIER '=' LIT_CHAR
    | KW_REAL TK_IDENTIFIER '=' LIT_REAL

    | KW_BOOL TK_IDENTIFIER '=' LIT_INT
    | KW_BOOL TK_IDENTIFIER '=' LIT_CHAR
    | KW_BOOL TK_IDENTIFIER '=' LIT_REAL
    ;


vector_initialization: LIT_CHAR vector_initialization
    | LIT_INT vector_initialization
    | LIT_REAL vector_initialization
    |
    ;

vector_declaration: KW_INT TK_IDENTIFIER '[' LIT_INT ']'
    | KW_CHAR TK_IDENTIFIER '[' LIT_INT ']'
    | KW_REAL TK_IDENTIFIER '[' LIT_INT ']'
    ;

function_argument: KW_INT TK_IDENTIFIER
    | KW_CHAR TK_IDENTIFIER
    | KW_REAL TK_IDENTIFIER
    ;

function_argument_list: function_argument
    | function_argument ',' function_argument_list
    ;

function_arguments: function_argument_list
    |
    ;

function_declaration: KW_INT TK_IDENTIFIER '(' function_arguments ')' block
;

function_call_argument_list: expr
    | expr ',' function_argument_list
    | 
    ;


function_call: TK_IDENTIFIER '(' function_call_argument_list ')'
    ;

input_call: KW_INPUT '(' KW_INT ')'
    | KW_INPUT '(' KW_CHAR ')'
    | KW_INPUT '(' KW_REAL ')'


expr: TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']'
    | LIT_INT
    | LIT_CHAR
    | LIT_REAL
    | function_call
    | input_call
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | expr '&' expr
    | expr '|' expr
    | expr '~' expr
    | '(' expr ')' 
    ;

cmd_attrib: TK_IDENTIFIER '=' expr
    | TK_IDENTIFIER '[' expr ']' '=' expr
    ;

output_arguments: LIT_STRING
    | expr
    | LIT_STRING ',' output_arguments
    | expr ',' output_arguments



cmd: cmd_attrib
    | KW_OUTPUT output_arguments
    | KW_RETURN expr
    |
    ;

cmd_list: cmd ';'
    | cmd ';' cmd_list
    | block
    | block cmd_list
    | flow_control
    | flow_control cmd_list
    ;

block: '{' cmd_list '}'
    ;

flow_control: KW_IF '(' expr ')' cmd_list
    | KW_IF '(' expr ')' cmd_list KW_ELSE cmd_list
    | KW_IF '(' expr ')' KW_LOOP cmd_list

declaration: variable_declaration ';'
    | vector_declaration vector_initialization ';'
    | function_declaration
    ;

declaration_list: declaration declaration_list
    | declaration
    |
    ;



%%

#include "definitions.h" // yyparse() is defined here