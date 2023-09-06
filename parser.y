//%define parse.error verbose

%{
#include "hash.h"
#include "ast_types.h"
#include "ast.h"    
#include "semantic.h"
#include "tac.h"
#include "asmgen.h"
int SyntaxErrors = 0;
int optimize = 0;
%}

%union{
    HASH* symbol; 
    AST *ast;
}


%token KW_CHAR 
%token KW_INT
%token KW_REAL 
%token KW_BOOL 

%token KW_IF 
%token KW_ELSE 
%token KW_LOOP 
%token KW_INPUT
%token KW_OUTPUT 
%token KW_RETURN 

%token OPERATOR_LE 
%token OPERATOR_GE 
%token OPERATOR_EQ 
%token OPERATOR_DIF

%token<symbol> TK_IDENTIFIER 

%token<symbol> LIT_INT 
%token<symbol> LIT_REAL
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token TOKEN_ERROR 

%type<ast> cmd_list
%type<ast> cmd
%type<ast> body
%type<ast> expr
%type<ast> if_body
%type<ast> if_statement
%type<ast> parameter_list
%type<ast> parameter_list_aux
%type<ast> var_attrib
%type<ast> parameter
%type<ast> func_declaration
%type<ast> vec_declaration
%type<ast> vec_init_opt
%type<ast> func_call
%type<ast> expr_list
%type<ast> expr_list_aux
%type<ast> return_cmd
%type<ast> input_expr
%type<ast> output_cmd
%type<ast> output_param_list
%type<ast> var_declaration
//%type<ast> declaration
%type<ast> declaration_list
%type<ast> program
%type<ast> vec_attrib

%left '&' '|'
%left '~' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '>' '<'
%left '+' '-'
%left '*' '/'

%%

program: declaration_list   { 
                              
                                    root = astCreate(AST_PROGRAM, NULL, $1, NULL, NULL, NULL, getLineNumber()); $1 = root; $$ = $1;
                                   
                                    set_param_list_item_function(root);
                                    set_expr_list_item_function(root);
                                    check_and_set_declarations($1);
                                    check_undeclared();
                                    
                                    check_operands($1);
                                    
                                    check_assignments($1);	
                                        
                                    check_return($1);
                                        
                                    check_function_call($1);
                                    
                                    check_conditional_stmts($1);


                                    if (SyntaxErrors == 0 && SemanticErrors == 0) {
                                       
                                        if (optimize) {
                                            fprintf(stderr, "Generating optimized code...\n");
                                            ast_collect_loop_elements($1);
                                            ast_collect_loop_conditions($1);
                                            ast_collect_loop_variables($1);
                                            // ast_collect_has_dependencies($1);
                                           
                                            ast_collect_varies($1);
                                            
                                            ast_set_dependencies($1);

                                            ast_set_varies($1);
                                            ast_set_order_dependencies($1);
                                     
                                           // ast_print_cond_list();
                                        
                                            ast_optimize($1);
                                            if (optimized > 0) {
                                                ast_handle_marked_assignments($1);
                                                ast_add_assignment_conds($1);
                                                fprintf(stderr, "Optimization done!\n");
                                            } else {
                                                fprintf(stderr, "No optimization done!\n");
                                            }
                                            
                                        } else {
                                            fprintf(stderr, "Generating unoptimized code...\n");
                                        }
                                      
                                        TAC * code = generate_code($1);
                                        code = generate_code($1);
                                        //tac_print_backwards(code);
                                        generate_asm(code);
                                        
                                    }
                                

                                
                                //astPrint($1, 0);
                                /*AST * test = $1;
                                test = test->son[0]->son[1]->son[0]->son[1]->son[0]->son[0]->son[0];
                                int typecheck_result = expression_typecheck(test);
                                fprintf(stderr, "typecheck result: %d\n", typecheck_result);*/

                               
                            }
    ;

declaration_list: var_declaration ';' declaration_list  { $$ = astCreate(AST_DECL_LIST, NULL, $1, $3, NULL, NULL, getLineNumber()); }
    | vec_declaration ';' declaration_list  { $$ = astCreate(AST_DECL_LIST, NULL, $1, $3, NULL, NULL, getLineNumber()); }
    | func_declaration declaration_list  { $$ = astCreate(AST_DECL_LIST, NULL, $1, $2, NULL, NULL, getLineNumber()); }
    
    //errors
    |              var_declaration error declaration_list { $$ = astCreate(AST_DECL_LIST, NULL, $1, $3, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ; on end of variable declaration\n"); SyntaxErrors++; }
    |              vec_declaration error declaration_list { $$ = astCreate(AST_DECL_LIST, NULL, $1, $3, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ; on end of vector declaration\n"); SyntaxErrors++; }
    |            { $$ = 0; }
    ;


var_declaration: KW_INT TK_IDENTIFIER '=' LIT_INT   { $$ = astCreate(AST_VAR_DECL_INT, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_CHAR TK_IDENTIFIER '=' LIT_INT  { $$ = astCreate(AST_VAR_DECL_CHAR, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_REAL TK_IDENTIFIER '=' LIT_INT    { $$ = astCreate(AST_VAR_DECL_REAL, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_BOOL TK_IDENTIFIER '=' LIT_INT  { $$ = astCreate(AST_VAR_DECL_BOOL, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    
    |            KW_INT TK_IDENTIFIER '=' LIT_CHAR  { $$ = astCreate(AST_VAR_DECL_INT, $2, astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_CHAR TK_IDENTIFIER '=' LIT_CHAR { $$ = astCreate(AST_VAR_DECL_CHAR, $2,astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_REAL TK_IDENTIFIER '=' LIT_CHAR  { $$ = astCreate(AST_VAR_DECL_REAL, $2, astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_BOOL TK_IDENTIFIER '=' LIT_CHAR  { $$ = astCreate(AST_VAR_DECL_BOOL, $2, astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }

    |            KW_INT TK_IDENTIFIER '=' LIT_REAL { $$ = astCreate(AST_VAR_DECL_INT, $2, astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_CHAR TK_IDENTIFIER '=' LIT_REAL { $$ = astCreate(AST_VAR_DECL_CHAR, $2, astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_REAL TK_IDENTIFIER '=' LIT_REAL      { $$ = astCreate(AST_VAR_DECL_REAL, $2, astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |            KW_BOOL TK_IDENTIFIER '=' LIT_REAL     { $$ = astCreate(AST_VAR_DECL_BOOL, $2, astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    // errors
    |            KW_INT error '='  LIT_INT { $$ = astCreate(AST_VAR_DECL_INT, make_missing(DATATYPE_INT), astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_CHAR error '=' LIT_INT { $$ = astCreate(AST_VAR_DECL_CHAR, make_missing(DATATYPE_CHAR), astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_REAL error '=' LIT_INT { $$ = astCreate(AST_VAR_DECL_REAL, make_missing(DATATYPE_REAL), astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_BOOL error '=' LIT_INT { $$ = astCreate(AST_VAR_DECL_BOOL, make_missing(DATATYPE_BOOL), astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }

    |            KW_INT error '='  LIT_CHAR { $$ = astCreate(AST_VAR_DECL_INT, make_missing(DATATYPE_INT), astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_CHAR error '=' LIT_CHAR { $$ = astCreate(AST_VAR_DECL_CHAR, make_missing(DATATYPE_CHAR), astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_REAL error '=' LIT_CHAR { $$ = astCreate(AST_VAR_DECL_REAL, make_missing(DATATYPE_REAL), astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_BOOL error '=' LIT_CHAR { $$ = astCreate(AST_VAR_DECL_BOOL, make_missing(DATATYPE_BOOL), astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }

    |            KW_INT error '='  LIT_REAL { $$ = astCreate(AST_VAR_DECL_INT, make_missing(DATATYPE_INT), astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_CHAR error '=' LIT_REAL { $$ = astCreate(AST_VAR_DECL_CHAR, make_missing(DATATYPE_CHAR), astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_REAL error '=' LIT_REAL { $$ = astCreate(AST_VAR_DECL_REAL, make_missing(DATATYPE_REAL), astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }
    |            KW_BOOL error '=' LIT_REAL { $$ = astCreate(AST_VAR_DECL_BOOL, make_missing(DATATYPE_BOOL), astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected identifier on variable declaration\n"); SyntaxErrors++; }


    |           KW_INT TK_IDENTIFIER error LIT_INT  { $$ = astCreate(AST_VAR_DECL_INT, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_CHAR TK_IDENTIFIER error LIT_INT { $$ = astCreate(AST_VAR_DECL_CHAR, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_REAL TK_IDENTIFIER error LIT_INT { $$ = astCreate(AST_VAR_DECL_REAL, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_BOOL TK_IDENTIFIER error LIT_INT { $$ = astCreate(AST_VAR_DECL_BOOL, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    
    |KW_INT TK_IDENTIFIER error LIT_CHAR  { $$ = astCreate(AST_VAR_DECL_INT, $2, astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_CHAR TK_IDENTIFIER error LIT_CHAR { $$ = astCreate(AST_VAR_DECL_CHAR, $2, astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_REAL TK_IDENTIFIER error LIT_CHAR { $$ = astCreate(AST_VAR_DECL_REAL, $2, astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_BOOL TK_IDENTIFIER error LIT_CHAR { $$ = astCreate(AST_VAR_DECL_BOOL, $2, astCreate(AST_LIT_CHAR, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }

    |KW_INT TK_IDENTIFIER error LIT_REAL  { $$ = astCreate(AST_VAR_DECL_INT, $2, astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_CHAR TK_IDENTIFIER error LIT_REAL { $$ = astCreate(AST_VAR_DECL_CHAR, $2, astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_REAL TK_IDENTIFIER error LIT_REAL { $$ = astCreate(AST_VAR_DECL_REAL, $2, astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }
    |KW_BOOL TK_IDENTIFIER error LIT_REAL { $$ = astCreate(AST_VAR_DECL_BOOL, $2, astCreate(AST_LIT_REAL, $4, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected = on variable declaration\n"); SyntaxErrors++; }


    |KW_INT TK_IDENTIFIER '=' error  { $$ = astCreate(AST_VAR_DECL_INT, $2, astCreate(AST_LIT_REAL, make_value(SYMBOL_LIT_INTEGER), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expected literal as value on variable declaration\n"); SyntaxErrors++; }
    |KW_CHAR TK_IDENTIFIER '=' error { $$ = astCreate(AST_VAR_DECL_CHAR, $2, astCreate(AST_LIT_REAL, make_value(SYMBOL_LIT_CHAR), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected literal as value on variable declaration\n"); SyntaxErrors++; }
    |KW_REAL TK_IDENTIFIER '=' error { $$ = astCreate(AST_VAR_DECL_REAL, $2, astCreate(AST_LIT_REAL, make_value(SYMBOL_LIT_REAL), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected literal as value on variable declaration\n"); SyntaxErrors++; }
    |KW_BOOL TK_IDENTIFIER '=' error { $$ = astCreate(AST_VAR_DECL_BOOL, $2, astCreate(AST_LIT_REAL, make_value(SYMBOL_LIT_INTEGER), NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber());  fprintf(stderr, "Expected literal as value on variable declaration\n"); SyntaxErrors++; }
  
    ;

vec_init_opt: LIT_INT vec_init_opt { $$ = astCreate(AST_VEC_INIT_OPT_INT, NULL, astCreate(AST_LIT_INT, $1, NULL, NULL, NULL, NULL, getLineNumber()), $2, NULL, NULL, getLineNumber());}
    |     LIT_REAL vec_init_opt    { $$ = astCreate(AST_VEC_INIT_OPT_REAL, NULL, astCreate(AST_LIT_REAL, $1, NULL, NULL, NULL, NULL, getLineNumber()), $2, NULL, NULL, getLineNumber()); }
    |     LIT_CHAR vec_init_opt     { $$ = astCreate(AST_VEC_INIT_OPT_CHAR, NULL, astCreate(AST_LIT_CHAR, $1, NULL, NULL, NULL, NULL, getLineNumber()), $2, NULL, NULL, getLineNumber()); }
    |     { $$ = 0; }
    ;

vec_declaration: KW_INT TK_IDENTIFIER '[' LIT_INT ']'  vec_init_opt  { $$ = astCreate(AST_VEC_DECL_INT, $2,  astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), $6, NULL, NULL, getLineNumber()); }
    |            KW_CHAR TK_IDENTIFIER '[' LIT_INT ']' vec_init_opt { $$ = astCreate(AST_VEC_DECL_CHAR, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), $6, NULL, NULL, getLineNumber()); }
    |            KW_REAL TK_IDENTIFIER '[' LIT_INT ']' vec_init_opt { $$ = astCreate(AST_VEC_DECL_REAL, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), $6, NULL, NULL, getLineNumber()); }
    |            KW_BOOL TK_IDENTIFIER '[' LIT_INT ']' vec_init_opt { $$ = astCreate(AST_VEC_DECL_BOOL, $2, astCreate(AST_LIT_INT, $4, NULL, NULL, NULL, NULL, getLineNumber()), $6, NULL, NULL, getLineNumber()); }
    
    // errors
    |            KW_INT TK_IDENTIFIER '[' error ']' vec_init_opt  { $$ = 0; fprintf(stderr, "Expected size on vector declaration\n"); SyntaxErrors++; }
    |            KW_CHAR TK_IDENTIFIER '[' error ']' vec_init_opt { $$ = 0;  fprintf(stderr, "Expected size on vector declaration\n"); SyntaxErrors++; }
    |            KW_REAL TK_IDENTIFIER '[' error ']' vec_init_opt  { $$ = 0;  fprintf(stderr, "Expected size on vector declaration\n"); SyntaxErrors++; }
    |            KW_BOOL TK_IDENTIFIER '[' error ']' vec_init_opt  { $$ = 0;  fprintf(stderr, "Expected size on vector declaration\n"); SyntaxErrors++; }
    
    |            KW_INT TK_IDENTIFIER '[' LIT_INT ']' error  { $$ = 0; fprintf(stderr, "Expected literal list on vector declaration opt\n"); SyntaxErrors++; }
    |            KW_CHAR TK_IDENTIFIER '[' LIT_INT ']' error { $$ = 0;  fprintf(stderr, "Expected literal list on vector declaration opt\n"); SyntaxErrors++; }
    |            KW_REAL TK_IDENTIFIER '[' LIT_INT ']' error  { $$ = 0;  fprintf(stderr, "Expected literal list on vector declaration opt\n"); SyntaxErrors++; }
    |            KW_BOOL TK_IDENTIFIER '[' LIT_INT ']' error  { $$ = 0;  fprintf(stderr, "Expected literal list on vector declaration opt\n"); SyntaxErrors++; }
    ;

parameter: KW_INT TK_IDENTIFIER     { $$ = astCreate(AST_PARAM_INT, $2, NULL, NULL, NULL, NULL, getLineNumber()); }
    |      KW_CHAR TK_IDENTIFIER    { $$ = astCreate(AST_PARAM_CHAR, $2, NULL, NULL, NULL, NULL, getLineNumber()); }
    |      KW_REAL TK_IDENTIFIER    { $$ = astCreate(AST_PARAM_REAL, $2, NULL, NULL, NULL, NULL, getLineNumber()); }
    |      KW_BOOL TK_IDENTIFIER    { $$ = astCreate(AST_PARAM_BOOL, $2, NULL, NULL, NULL, NULL, getLineNumber()); }
    ;

parameter_list: parameter parameter_list_aux { $$ = astCreate(AST_PARAM_LIST, NULL, $1, $2, NULL, NULL, getLineNumber()); }
    | { $$ = astCreate(AST_EMPTY_PARAM_LIST, NULL, NULL, NULL, NULL, NULL, getLineNumber());} 
    ;

parameter_list_aux: ',' parameter parameter_list_aux { $$ = astCreate(AST_PARAM_LIST, NULL, $2, $3, NULL, NULL, getLineNumber()); }
    | { $$ = 0; }
    ;

func_declaration: KW_INT TK_IDENTIFIER '(' parameter_list ')' body      { $$ = astCreate(AST_FUNC_DECL_INT, $2, $4, $6, NULL, NULL, getLineNumber()); }
    |             KW_CHAR TK_IDENTIFIER '(' parameter_list ')' body     { $$ = astCreate(AST_FUNC_DECL_CHAR, $2, $4, $6, NULL, NULL, getLineNumber()); }
    |             KW_REAL TK_IDENTIFIER '(' parameter_list ')' body     { $$ = astCreate(AST_FUNC_DECL_REAL, $2, $4, $6, NULL, NULL, getLineNumber()); }
    |             KW_BOOL TK_IDENTIFIER '(' parameter_list ')' body     { $$ = astCreate(AST_FUNC_DECL_BOOL, $2, $4, $6, NULL, NULL, getLineNumber()); }
    ;

body: '{' cmd_list '}' { $$ = astCreate(AST_BODY, NULL, $2, NULL, NULL, NULL, getLineNumber()); }

    //| error cmd_list '}' { $$ = astCreate(AST_BODY, NULL, $2, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting { on start of block\n"); SyntaxErrors++; }
   // | '{' cmd_list error { $$ = astCreate(AST_BODY, NULL, $2, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting } on end of block\n"); SyntaxErrors++; }
    ;

cmd_list: cmd ';' cmd_list { $$ = astCreate(AST_CMD_LIST, 0, $1, $3, NULL, NULL, getLineNumber()); }
    |     body cmd_list    { $$ = astCreate(AST_CMD_LIST, 0, $1, $2, NULL, NULL, getLineNumber()); }
    |     if_statement cmd_list     { $$ = astCreate(AST_CMD_LIST, 0, $1, $2, NULL, NULL, getLineNumber()); }
    
    |   cmd error cmd_list { $$ = astCreate(AST_CMD_LIST, 0, $1, $3, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ; on end of command\n"); SyntaxErrors++; }

    |     { $$ = 0; }
    ;

if_body: body { $$ = $1; } 
    |    cmd ';' { $$ = $1; }
    ;

if_statement: KW_IF '(' expr ')' if_body           { $$ = astCreate(AST_IF, 0, $3, $5, NULL, NULL, getLineNumber()); }
    | KW_IF '(' expr ')' if_body KW_ELSE if_body   { $$ = astCreate(AST_IF_ELSE, 0, $3, $5, $7, NULL, getLineNumber()); }
    | KW_IF '(' expr ')' KW_LOOP if_body           { $$ = astCreate(AST_LOOP, 0, $3, $6, NULL, NULL, getLineNumber()); }

    // errors
   // | KW_IF '(' expr ')' if_body KW_ELSE error   { $$ = astCreate(AST_IF_ELSE, 0, $3, $5, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting else body\n"); SyntaxErrors++; }
    | KW_IF '(' expr ')' KW_LOOP error           { $$ = astCreate(AST_LOOP, 0, $3, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting loop body\n"); SyntaxErrors++; }
     
    | KW_IF error expr ')' if_body           { $$ = astCreate(AST_IF, 0, $3, $5, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( at the start of if condition\n"); SyntaxErrors++; }
    | KW_IF '(' expr error if_body           { $$ = astCreate(AST_IF, 0, $3, $5, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) at the end of if condition\n"); SyntaxErrors++; }
    | KW_IF error expr ')' if_body KW_ELSE if_body   { $$ = astCreate(AST_IF_ELSE, 0, $3, $5, $7, NULL, getLineNumber()); fprintf(stderr, "Expecting ( at the start of if condition\n"); SyntaxErrors++; }
    | KW_IF '(' expr error if_body KW_ELSE if_body   { $$ = astCreate(AST_IF_ELSE, 0, $3, $5, $7, NULL, getLineNumber()); fprintf(stderr, "Expecting ) at the end of if condition\n"); SyntaxErrors++; }
    | KW_IF error expr ')' KW_LOOP if_body           { $$ = astCreate(AST_LOOP, 0, $3, $6, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( at the start of loop condition\n"); SyntaxErrors++;}
    | KW_IF '(' expr error KW_LOOP if_body           { $$ = astCreate(AST_LOOP, 0, $3, $6, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) at the end of loop condition\n"); SyntaxErrors++;}

    | KW_IF error expr error if_body           { $$ = astCreate(AST_IF, 0, $3, $5, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting if condition to be inside (...)\n"); SyntaxErrors++; }
    | KW_IF error expr error if_body KW_ELSE if_body   { $$ = astCreate(AST_IF_ELSE, 0, $3, $5, $7, NULL, getLineNumber()); fprintf(stderr, "Expecting if condition to be inside (...)\n"); SyntaxErrors++; }
    | KW_IF error expr error KW_LOOP if_body           { $$ = astCreate(AST_LOOP, 0, $3, $6, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting loop condition to be inside (...)\n"); SyntaxErrors++;}
    ;

cmd:  var_attrib {  $$ = $1; }
    | vec_attrib { $$ = $1; }
    | output_cmd { $$ = $1; }
    | return_cmd { $$ = $1; }
    | { $$ = 0; }
    ;

var_attrib: TK_IDENTIFIER '=' expr { $$ = astCreate(AST_VAR_ATTRIB, $1, $3, NULL, NULL, NULL, getLineNumber());  }
    | TK_IDENTIFIER error expr { $$ = astCreate(AST_VAR_ATTRIB, $1, $3, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting = on variable assignment\n"); SyntaxErrors++;  }
    ;

vec_attrib: TK_IDENTIFIER '[' expr ']' '=' expr { $$ = astCreate(AST_VEC_ATTRIB, $1, $3, $6, NULL, NULL, getLineNumber()); }
    | TK_IDENTIFIER '[' expr ']' error expr { $$ = astCreate(AST_VEC_ATTRIB, $1, $3, $6, NULL, NULL, getLineNumber());  fprintf(stderr, "Expecting = on vector assignment\n"); SyntaxErrors++; }
    ;

output_cmd: KW_OUTPUT output_param_list { $$ = astCreate(AST_OUTPUT_CMD, 0, $2, NULL, NULL, NULL, getLineNumber()); }
    ;

output_param_list: LIT_STRING ',' output_param_list     { $$ = astCreate(AST_OUTPUT_PARAM_LIST, NULL, astCreate(AST_LIT_STRING, $1, NULL, NULL, NULL, NULL, getLineNumber()), $3, NULL, NULL, getLineNumber()); }
    |              expr ',' output_param_list           { $$ = astCreate(AST_OUTPUT_PARAM_LIST, 0, $1, $3, NULL, NULL, getLineNumber()); }
    |              LIT_STRING                           { $$ = astCreate(AST_OUTPUT_PARAM_LIST, NULL, astCreate(AST_LIT_STRING, $1, NULL, NULL, NULL, NULL, getLineNumber()), NULL, NULL, NULL, getLineNumber()); }
    |              expr                                 { $$ = astCreate(AST_OUTPUT_PARAM_LIST, NULL, $1,  NULL, NULL, NULL, getLineNumber()); }

    // errors
    |LIT_STRING error output_param_list     { $$ = astCreate(AST_OUTPUT_PARAM_LIST, NULL, astCreate(AST_LIT_STRING, $1, NULL, NULL, NULL, NULL, getLineNumber()), $3, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting , on output command\n"); SyntaxErrors++; }
    |expr error output_param_list           { $$ = astCreate(AST_OUTPUT_PARAM_LIST, 0, $1, $3, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting , on output command\n"); SyntaxErrors++; }
    |              { $$ = 0; }
    ;

return_cmd: KW_RETURN expr { $$ = astCreate(AST_RETURN_CMD, 0, $2, NULL, NULL, NULL, getLineNumber()); }
    // errors
    // | KW_RETURN error { $$ = astCreate(AST_RETURN_CMD, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting expression on return command\n"); SyntaxErrors++; }
    ;
    
input_expr: KW_INPUT '(' KW_INT ')'  { $$ = astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); }
    |       KW_INPUT '(' KW_CHAR ')' { $$ = astCreate(AST_INPUT_EXPR_CHAR, 0, NULL, NULL, NULL, NULL, getLineNumber()); }
    |       KW_INPUT '(' KW_REAL ')' { $$ = astCreate(AST_INPUT_EXPR_REAL, 0, NULL, NULL, NULL, NULL, getLineNumber()); }
    |       KW_INPUT '(' KW_BOOL ')' { $$ = astCreate(AST_INPUT_EXPR_BOOL, 0, NULL, NULL, NULL, NULL, getLineNumber()); }

    // errors
    |       KW_INPUT '(' error ')' { $$ = astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting type on input command\n"); SyntaxErrors++; }
    |       KW_INPUT error {  $$ =  astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting (type) on input command\n"); SyntaxErrors++; }

    |       KW_INPUT error KW_INT ')' { $$ =  astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( after input command type, it should be input(int) instead\n"); SyntaxErrors++; }
    |       KW_INPUT '(' KW_INT error {  $$ =  astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) after input command type, it should be input(int) instead\n"); SyntaxErrors++; }
    |       KW_INPUT error KW_INT error {  $$ =  astCreate(AST_INPUT_EXPR_INT, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting input command type to be this way input(int)\n"); SyntaxErrors++; }

    |       KW_INPUT error KW_CHAR ')' {  $$ = astCreate(AST_INPUT_EXPR_CHAR, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( after input command type, it should be input(char) instead\n"); SyntaxErrors++; }
    |       KW_INPUT '(' KW_CHAR error {  $$ =  astCreate(AST_INPUT_EXPR_CHAR, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) after input command type, it should be input(char) instead\n"); SyntaxErrors++; }
    |       KW_INPUT error KW_CHAR error {  $$ =  astCreate(AST_INPUT_EXPR_CHAR, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting input command type to be this way input(char)\n"); SyntaxErrors++; }

    |       KW_INPUT error KW_REAL ')' {  $$ = astCreate(AST_INPUT_EXPR_REAL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( after input command type, it should be input(real) instead\n"); SyntaxErrors++; }
    |       KW_INPUT '(' KW_REAL error {  $$ =  astCreate(AST_INPUT_EXPR_REAL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) after input command type, it should be input(real) instead\n"); SyntaxErrors++; }
    |       KW_INPUT error KW_REAL error {  $$ =  astCreate(AST_INPUT_EXPR_REAL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting input command type to be this way input(real)\n"); SyntaxErrors++; }

    |       KW_INPUT error KW_BOOL ')' {  $$ = astCreate(AST_INPUT_EXPR_BOOL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( before input command type, it should be input(bool) instead\n"); SyntaxErrors++; }
    |       KW_INPUT '(' KW_BOOL error {  $$ =  astCreate(AST_INPUT_EXPR_BOOL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) after input command type, it should be input(bool) instead\n"); SyntaxErrors++; }
    |       KW_INPUT error KW_BOOL error {   $$ = astCreate(AST_INPUT_EXPR_BOOL, 0, NULL, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting input command type to be this way input(bool)\n"); SyntaxErrors++; }

    ;

expr: LIT_INT                               { $$ = astCreate(AST_LIT_INT, $1, NULL, NULL, NULL, NULL, getLineNumber()); }
    | TK_IDENTIFIER                         { $$ = astCreate(AST_IDENTIFIER, $1, NULL, NULL, NULL, NULL, getLineNumber());    }
    | LIT_CHAR                              { $$ = astCreate(AST_LIT_CHAR, $1, NULL, NULL, NULL, NULL, getLineNumber()); }
    | LIT_REAL                              { $$ = astCreate(AST_LIT_REAL, $1, NULL, NULL, NULL, NULL, getLineNumber()); }
    | TK_IDENTIFIER '[' expr ']'            { $$ = astCreate(AST_VEC_ACCESS, $1, $3, NULL, NULL, NULL, getLineNumber());   }
    | input_expr                            { $$ = $1;                                                 }
    | func_call                             { $$ = $1;                                                }
    | expr '*' expr                         { $$ = astCreate(AST_MUL, 0, $1, $3, NULL, NULL, getLineNumber());         }               
    | expr '/' expr                         { $$ = astCreate(AST_DIV, 0, $1, $3, NULL, NULL, getLineNumber());         }  
    | expr '+' expr                         { $$ = astCreate(AST_ADD, 0, $1, $3, NULL, NULL, getLineNumber());         }  
    | expr '-' expr                         { $$ = astCreate(AST_SUB, 0, $1, $3, NULL, NULL, getLineNumber());         }  
    | '-' expr                              { $$ = astCreate(AST_NEG, 0, $2, NULL, NULL, NULL, getLineNumber());       }  
    | '~' expr                              { $$ = astCreate(AST_NOT, 0, $2, NULL, NULL, NULL, getLineNumber());       }  
    | expr '&' expr                         { $$ = astCreate(AST_AND, 0, $1, $3, NULL, NULL, getLineNumber());         }  
    | expr '|' expr                         { $$ = astCreate(AST_OR, 0, $1, $3, NULL, NULL, getLineNumber());          }  
    | expr OPERATOR_LE expr                 { $$ = astCreate(AST_LE, 0, $1, $3, NULL, NULL, getLineNumber());          }  
    | expr OPERATOR_GE expr                 { $$ = astCreate(AST_GE, 0, $1, $3, NULL, NULL, getLineNumber());          }  
    | expr OPERATOR_EQ expr                 { $$ = astCreate(AST_EQ, 0, $1, $3, NULL, NULL, getLineNumber());          }  
    | expr OPERATOR_DIF expr                { $$ = astCreate(AST_DIF, 0, $1, $3, NULL, NULL, getLineNumber());         }  
    | expr '>' expr                         { $$ = astCreate(AST_GT, 0, $1, $3, NULL, NULL, getLineNumber());          }  
    | expr '<' expr                         { $$ = astCreate(AST_LT, 0, $1, $3, NULL, NULL, getLineNumber());          }  
    | '(' expr ')'                          { $$ = astCreate(AST_NESTED_EXPR, 0, $2, NULL, NULL, NULL, getLineNumber()); }   

   
    ;

func_call: TK_IDENTIFIER '(' expr_list ')' { $$ = astCreate(AST_FUNC_CALL, $1, $3, NULL, NULL, NULL, getLineNumber());  }
    // errors
    | TK_IDENTIFIER '(' expr_list error { $$ = astCreate(AST_FUNC_CALL, $1, $3, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ) on end of function call\n"); SyntaxErrors++; }
    | TK_IDENTIFIER error expr_list ')' { $$ = astCreate(AST_FUNC_CALL, $1, $3, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting ( on start of function call\n"); SyntaxErrors++; }		
    | TK_IDENTIFIER error expr_list error { $$ = astCreate(AST_FUNC_CALL, $1, $3, NULL, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting function parameters to be inside (...)\n"); SyntaxErrors++; }	
    ;

expr_list:  expr expr_list_aux        { $$ = astCreate(AST_EXPR_LIST, NULL, $1, $2, NULL, NULL, getLineNumber());}
    |                                 { $$ = 0; }
    ;

expr_list_aux: ',' expr expr_list_aux { $$ = astCreate(AST_EXPR_LIST, NULL, $2, $3, NULL, NULL, getLineNumber());}
    // errors
    | error expr expr_list_aux { $$ = astCreate(AST_EXPR_LIST, NULL, $2, $3, NULL, NULL, getLineNumber()); fprintf(stderr, "Expecting function parameters to be separated by a ,\n"); SyntaxErrors++; }
    |                                 { $$ = 0; }           
    ;


%%

#include "definitions.h" // yyparse() is defined here
