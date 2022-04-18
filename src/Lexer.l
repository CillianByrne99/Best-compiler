%option noyywrap
 
%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "ToY.h"
	#include "parser.tab.h"
	extern FILE *yyin;
	extern FILE *yyout;
 
	void ret_print(char *token_type);
	void yyerror();
%}
 
%x ML_COMMENT
 
Int				  [0-9]
DecInt 	   		  [1-9]{Int}* 
MinusInt   		  [-]({Int}|{DecInt})
Integer   		  {Int}|{DecInt}|{MinusInt}

Comment    	   	  ([//]|[##])

LineTerminator    \r|\n|\r\n
WhiteSpace        [ \t\f]

Alpha 			  [a-zA-Z_]
Alnum			  {Alpha}|{Int}
Identifier        {Alpha}+{Alnum}*

String 			  \"([^"\\])*\"
 
%%
 
{Comment}				{ } 
 

"struct"			    { return STRUCT;} 
"int"					{ return INTEGER; }
"string"				{ return STRING; }
"void"					{ return VOID; }
"return"				{ return RETURN; }
"printf"			    { return PRINT;}
"bool"					{ return BOOL; }
"true"			        { return TRU; }
"false"			        { return FAL;} 
"for"					{ return FOR; }
"if"					{ return IF; }
"else"					{ return ELSE; }
"then"					{ return THEN; } 
 
"+"						{ return ADD; }
"-"						{ return SUB; }
"*"						{ return MULTIPLY; }
"/"						{ return DIVIDE; }
"or"					{ return OR; }
"not"|"!"				{ return NOT; }
"and"					{ return AND; }
"mod"					{ return MOD; }
"=="|"!="				{ return EQUALS; }
">"|"<"|">="|"<="		{ return RELATIONAL; }
","						{ return COMMA; }
 
 
"("				{ return LBRACKET; }
")"				{ return RBRACKET; }
"{"				{ return LBRACE; }
"}"				{ return RBRACE; }
";"				{ return SEMICOLON; }
"."				{ return DOT; }
"="				{ return EQUAL; }

{LineTerminator}	    { yylineno++; } 
{WhiteSpace}            { /* ignore */ }

{Integer} 		{
						yylval = atoi(yytext) ;
						if(  yylval > 32767 )
						{
							yyerror("ERROR: Integer OOB") ;
				//			return INVALID;
							
						}
						else if (yylval < -32768){
							yyerror("ERROR: Integer OOB") ;
				//			return INVALID;
						}
						else
						{
							return ICONST; 
						} 
				}

				

{String} 		{ 
					int present = 0;
					for(int i = 0; yytext[i] != '\0'; i++)
				  	{
						if(yytext[i] == '\\')
							present = 1;
				  	}
					if(present == 1)
						yyerror("ERROR: STRING OOB");
					//	return INVALID;
					else
					{
                    	return SCONST; 
					} 
				}
{Identifier} 			{
					insert(yytext, strlen(yytext), UNDEF, yylineno);
					return ID;
				}


.				{ yyerror("Unrecognized character"); }

%%