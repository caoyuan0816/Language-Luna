%{/* luna.y
 *
 * Luna grammar in Yacc format, based originally on
 * BNF of Luna language
 */
#include "common.h"
#include <stdio.h>
extern int openFile(int argc, char** argv);
int errorOccur;
int currentline = 0;
%}

%token LIST ASSIGNMENT COLON COMMA INTNUM
%token DO ELSE END EQUAL FOR FUNCTION RETURN
%token GE GT IDENTIFIER IF IN LBRAC LE LPAREN LT MINUS
%token NOTEQUAL PFILE PLUS MAIN RBRAC //TODO: MAIN
%token REALNUMBER RPAREN SEMICOLON SLASH STAR THEN
%token INT DOUBLE BOOL WHILE
%token INCO DECO
%token FALSE TRUE

%%
//TODO: MAIN
file : functiondef_list MAIN LPAREN variable comma variable RPAREN block END |
	functiondef_list MAIN LPAREN RPAREN block END
	; 

block : statement_list |
	;

statement_list : statement_list statement |
	statement
	;

statement : assign_statement |
	functioncall |
	do_statement |
	loop_statement |
	if_statement |
	error {
	  printf("statement error detected\n");
	}
	;

do_statement : DO block END
	;

loop_statement : WHILE LPAREN bool_expression RPAREN DO block END |
	FOR identifier for_statement
	;

for_statement : ASSIGNMENT int_num comma int_num comma int_num DO block END |
	IN list_expression DO block END |
	IN identifier DO block END
	;


if_statement : IF LPAREN bool_expression RPAREN block else_statement END
	;

else_statement : ELSE block |
	;

assign_statement : define_assign |
	identifier_assign |
	unary_assign
	;

unary_assign : identifier unaryop
	;

identifier_assign : identifier ASSIGNMENT assign_type
	;

define_assign : variable ASSIGNMENT assign_type
	;

assign_type : expression |
	TRUE |
	FALSE |
	list_expression
	;

variable : type identifier {

	} |
	error {
	  printf("variable definition error\n");
	}
	;

functioncall : identifier argument_list
	;

argument_list : LPAREN RPAREN |
	LPAREN expression_list RPAREN
	;

expression_list : expression_list comma expression |
	expression
	;

bool_expression : FALSE |
	TRUE |
	expression boolop expression
	;

expression : math_expression {
	} |
	functioncall |
	error {
	  printf("expression error detected!\n");
	}
	;

list_expression : LBRAC int_list RBRAC |
	LBRAC RBRAC
	;

math_expression : math_expression addop term |
	term
	;

term : term mulop num_id |
	num_id {
	}
	;

functiondef_list : functiondef_list functiondef|
	;

functiondef : FUNCTION variable funcbody{
	
	}
	;

funcbody : LPAREN paramlist RPAREN block return_statement END
	;

return_statement : RETURN num_id {
	
	}
	;

paramlist : paramlist comma type identifier |
	type identifier |
	;

addop : PLUS |
	MINUS
	; 

mulop : STAR |
	SLASH
	;

unaryop : INCO |
	DECO
	;

boolop : EQUAL |
	GE |
	LE |
	LT |
	NOTEQUAL |
	GT
	;

type : bool_type |
	int_type |
	double_type |
	list_type
	;

bool_type : BOOL
	;

int_type : INT
	;

double_type : DOUBLE
	;

list_type : LIST
	;

num_id : identifier |
	num
	;

num : MINUS INTNUM |
	INTNUM |
	MINUS REALNUMBER |
	REALNUMBER
	;

int_list : int_list comma int_num |
	int_num
	;

int_num : MINUS INTNUM |
	INTNUM
	;

identifier : IDENTIFIER
	;

comma : COMMA
	;
%%

int main(int argc, char** argv){
  errorOccur = 0;
  errorOccur = openFile(argc, argv);
  return yyparse();
}

int yyerror(char *s){
  fprintf(stderr, "%s\n", s);
  errorOccur++;
  return 0;
}
