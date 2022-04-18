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
//a lot to do here


/* token definition */
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

%start program
 
/* expression priorities and rules */
 
%%
 
program: procedure_declarations ;
 
procedure_declarations: procedure_declaration procedure_declarations |  ;

procedure_declaration: 
	return_type ID LBRACKET declarations_p LBRACE statements RBRACE | 
	return_type ID LBRACKET RBRACKET LBRACE statements RBRACE |
	STRUCT ID LBRACE declarations_s 
;

statements: statement statements | ;
 
statement:
	if_statements | for_statement | assignment | prints | declaration | procedure_calls
	| RETURN returns SEMICOLON

declaration: type ID SEMICOLON;

declarations_p: declaration_p COMMA declarations_p | declaration_p RBRACKET;
declarations_s: declaration_p COMMA declarations_s | declaration_p RBRACE;

declaration_p: type ID;


procedure_calls: 
	ID LBRACKET expressions RBRACKET SEMICOLON | 
	ID EQUAL ID LBRACKET expressions RBRACKET SEMICOLON 
;


expressions: expressions expression | ;
expression:
	ICONST |
	SCONST |
	TRU |
	FAL |
	expression OPERATOR expression |
    LBRACKET expression RBRACKET |
	sign ICONST |
    NOT expression |
	ID |
	ID DOT ID
	
;
 

type: INTEGER | STRING | BOOL;

prints: PRINT LBRACKET SCONST RBRACKET SEMICOLON ;

returns:
	ID | ICONST | SCONST | VOID | ;

return_type:
	INTEGER | STRING | BOOL | VOID;

assignment:  ID EQUAL VOID SEMICOLON | ID EQUAL expression SEMICOLON ; 

lexp : ID | ID DOT ID | 

if_statements: if_statements if_statement | ;

if_statement: IF LBRACKET bool_exp RBRACKET THEN LBRACE statements RBRACE else_part;
 
else_part: ELSE LBRACE statements RBRACE | ; 
 
for_statement: FOR LBRACKET assignment conditionals SEMICOLON conditionals RBRACKET LBRACE statements RBRACE;

bool_exp : conditionals | ID | TRU | FAL ;

conditionals:
	expression EQUALS expression |
    expression RELATIONAL expression |
	NOT expression |
	expression OR expression  |
	expression AND expression |
	ID EQUAL expression 

sign: ADD | SUB;
OPERATOR : ADD | SUB | MULTIPLY | DIVIDE |MOD | AND | OR | NOT | EQUALS | RELATIONAL ;

 
%%
 
void yyerror ()
{
   fprintf(stderr, "Syntax Error at line \n");
}


int main (int argc, char *argv[]){

	// initialize symbol table
	init_hash_table();
 
	// parsing
	int flag;
	yyin = fopen(argv[1], "r");
	flag = yyparse();
	fclose(yyin);
 
	// symbol table dump
	yyout = fopen("ToY_dump.out", "w");
	ToY_dump(yyout);
	fclose(yyout);

	printf("\n\nProgram: ",flag);

	if(flag == 0){
		printf("VALID\n\n\n");
	}
	else{
		printf("ERROR\n\n\n");
	}
	
	return flag;
}