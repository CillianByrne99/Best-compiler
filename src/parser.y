%{
	#include "ToY.c"
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	extern FILE *yyin;
	extern FILE *yyout;
	extern int lineno;
	extern int yylex();
	void yyerror();
%}



/* tokens */
%token NOT
%token ADD SUB
%token RELATIONAL
%token EQUAL EQUALS

%token MULTIPLY DIVIDE OR AND MOD
%token INTEGER IF THEN ELSE FOR  VOID RETURN BOOL TRU FAL STRUCT
%token LBRACKET RBRACKET LBRACE RBRACE SEMICOLON DOT COMMA PRINT
%token ID ICONST STRING SCONST

%left NOT SUB ADD MULTIPLY DIVIDE
%nonassoc EQUALS RELATIONAL
%left DOT

%start compiler
 
/* exp rules */
 
%%
 
compiler: run_decs ;
 
run_decs: run_dec_rules run_decs |  ;

run_dec_rules: 
	return_t_rules ID LBRACKET decs_x LBRACE statements RBRACE | 
	return_t_rules ID LBRACKET RBRACKET LBRACE statements RBRACE |
	STRUCT ID LBRACKET decs_y 
;

statements: statement statements | ;
 
statement:
	if_rule | for_loop_rules | assign_rules | print_rules | dec_rules | procedure_rules
	| RETURN return_rules SEMICOLON 

dec_rules: exp_t_rule ID SEMICOLON;

decs_x: dec_x COMMA decs_x | dec_x RBRACKET;
decs_y: dec_x COMMA decs_y | dec_x RBRACKET;

dec_x: exp_t_rule ID;


procedure_rules: 
	ID LBRACKET exp_rule RBRACKET SEMICOLON | 
	ID EQUAL ID LBRACKET exp_rule RBRACKET SEMICOLON 
;


exp_rule: exp_rule exp | ;
exp:
	ICONST |
	SCONST |
	TRU |
	FAL |
	exp OPERATOR exp |
    LBRACKET exp RBRACKET |
	sign ICONST |
    NOT exp |
	ID |
	ID DOT ID
	
;
 

exp_t_rule: INTEGER | STRING | BOOL;

print_rules: PRINT LBRACKET SCONST RBRACKET SEMICOLON ;

return_rules:
	ID | ICONST | SCONST | VOID | ;

return_t_rules:
	INTEGER | STRING | BOOL | VOID;

assign_rules:  ID EQUAL VOID SEMICOLON | ID EQUAL exp SEMICOLON ; 

left_exp_rule : ID | ID DOT ID | 

if_rule: if_rule if_rules | ;

if_rules: IF LBRACKET boolean_rules RBRACKET THEN LBRACE statements RBRACE else_rules;
 
else_rules: ELSE LBRACE statements RBRACE | ; 
 
for_loop_rules: FOR LBRACKET assign_rules cond_rules SEMICOLON cond_rules RBRACKET LBRACE statements RBRACE;

boolean_rules : cond_rules | ID | TRU | FAL ;

cond_rules:
	exp EQUALS exp |
    exp RELATIONAL exp |
	NOT exp |
	exp OR exp  |
	exp AND exp |
	ID EQUAL exp 

sign: ADD | SUB;
OPERATOR : ADD | SUB | MULTIPLY | DIVIDE |MOD | AND | OR | NOT | EQUALS | RELATIONAL ;

%%
 
void yyerror (){
   fprintf(stderr, "ERROR: cannot compile line- \n");
}


int main (int argc, char *argv[]){
	table();
	int parse;
	yyin = fopen(argv[1], "r");
	parse = yyparse();
	fclose(yyin);
	yyout = fopen("ToY_dump.out", "w");
	fclose(yyout);
	printf("\nCompile: ",parse);
	if(parse == 0){printf("VALID: compilation successful");}
	else{printf("ERROR: compilation failed");}
	return parse;
}