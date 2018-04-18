%{
/*
 * grammar.y
 *
 * Luna grammar in Yacc format, based originally on
 * BNF of Luna language
 */
#include "global.h"
#include <stdio.h>
extern int openFile(int argc, char** argv);
int errorOccur;
%}
%union{
struct ast* node;
}
%token <node> LIST ASSIGNMENT COLON COMMA DIGSEQ
%token <node> DO ELSE END EQUAL FOR FUNCTION RETURN
%token <node> GE GT IDENTIFIER IF IN LBRAC LE LPAREN LT MINUS
%token <node> NOTEQUAL PFILE PLUS MAIN RBRAC
%token <node> REALNUMBER RPAREN SEMICOLON SLASH STAR THEN
%token <node> INT DOUBLE BOOL WHILE
%token <node> INCO DECO
%token <node> FALSE TRUE

%type <node> file block 
%type <node> statement_list  statement do_statement loop_statement  for_statement if_statement else_statement 
%type <node> functioncall assign_statement unary_assign identifier_assign  define_assign 
%type <node> assign_type  variable argument_list 
%type <node> expression_list bool_expression expression  list_expression math_expression 
%type <node> term functiondef_list functiondef funcbody return_statement
%type <node> paramlist addop mulop unaryop boolop 
%type <node> type bool_type int_type double_type list_type num_id num int_list int_num identifier comma 

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
file : 
		functiondef_list MAIN LPAREN variable comma variable RPAREN block END {$$=newast("file",9,$1,$2,$3,$4,$5,$6.$7,$8,$9);} 
	|	functiondef_list MAIN LPAREN RPAREN block END {$$=newast("file",6,$1,$2,$3,$4,$5,$6);} 
	; 

block : 
		statement_list {$$=newast("block",1,$1);}
	|	{$$=newast("statement_list",0,-1);}
	;

statement_list : 
		statement_list statement{$$=newast("statement_list",2,$1,$2);} 
	|	statement{$$=newast("statement_list",1,$1);}
	;

statement : 
		assign_statement {$$=newast("statement",1,$1);}  
	|	functioncall {$$=newast("statement",1,$1);}  
	|	do_statement {$$=newast("statement",1,$1);}  
	|	loop_statement {$$=newast("statement",1,$1);}  
	|	if_statement {$$=newast("statement",1,$1);}  
	|	error {
			printf("statement error detected\n");
		}
	;

do_statement : 
		DO block END {$$=newast("do_statement",3,$1,$2,$3);}
	;

loop_statement : 
		WHILE LPAREN bool_expression RPAREN DO block END {$$=newast("loop_statement",7,$1,$2,$3,$4,$5,$6,$7);}
	|	FOR identifier for_statement {$$=newast("loop_statement",3,$1,$2,$3);}
	;

for_statement : 
		ASSIGNMENT int_num comma int_num comma int_num DO block END {$$=newast("for_statement",9,$1,$2,$3,$4,$5,$6,$7,$8,$9);}
	|	IN list_expression DO block END {$$=newast("for_statement",5,$1,$2,$3,$4,$5);}
	|	IN identifier DO block END {$$=newast("for_statement",5,$1,$2,$3,$4,$5);}
	;


if_statement : IF LPAREN bool_expression RPAREN block else_statement END {$$=newast("if_statement",7,$1,$2,$3,$4,$5,$6,$7);}
	;

else_statement : 
		ELSE block {$$=newast("else_statement",2,$1,$2);}
	|
	;

assign_statement : 
		define_assign {$$=newast("assign_statement",1,$1);}
	|	identifier_assign {$$=newast("assign_statement",1,$1);}
	|	unary_assign {$$=newast("assign_statement",1,$1);}
	;

unary_assign : 
		identifier unaryop {$$=newast("unary_assign",2,$1,$2);}
	;

identifier_assign : 
		identifier ASSIGNMENT assign_type {$$=newast("identifier_assign",3,$1,$2,$3);}
	;

define_assign : 
		variable ASSIGNMENT assign_type {$$=newast("define_assign",3,$1,$2,$3);}
	;

assign_type : 
		expression {$$=newast("assign_type",1,$1);}
	|	TRUE {$$=newast("assign_type",1,$1);}
	|	FALSE {$$=newast("assign_type",1,$1);}
	|	list_expression {$$=newast("assign_type",1,$1);}
	;

variable : 
		type identifier {$$=newast("variable",1,$1);}
	|	error {
			printf("variable definition error\n");
		}
	;

functioncall : 
		identifier argument_list {$$=newast("functioncall",1,$1);}
	;

argument_list : 
		LPAREN RPAREN {$$=newast("argument_list",2,$1,$2);}
	|	LPAREN expression_list RPAREN {$$=newast("argument_list",3,$1,$2,$3);}
	;

expression_list : 
		expression_list comma expression {$$=newast("expression_list",3,$1,$2,$3);}
	|	expression {$$=newast("expression_list",1,$1);}
	;

bool_expression : 
		FALSE {$$=newast("bool_expression",1,$1);}
	|	TRUE {$$=newast("bool_expression",1,$1);}
	|	expression boolop expression {$$=newast("bool_expression",3,$1,$2,$3);}
	;

expression : 
		math_expression {$$=newast("expression",1,$1);} 
	|	functioncall {$$=newast("expression",1,$1);}
	|	error {
			printf("expression error detected!\n");
		}
	;

list_expression : 
		LBRAC int_list RBRAC {$$=newast("list_expression",3,$1,$2,$3);}
	|	LBRAC RBRAC {$$=newast("list_expression",2,$1,$2);}
	;

math_expression : 
		math_expression addop term {$$=newast("math_expression",3,$1,$2,$3);}
	|	term {$$=newast("math_expression",1,$1);}
	;

term : 
		term mulop num_id {$$=newast("term",3,$1,$2,$3);}
	|	num_id {} 
	;

functiondef_list : 
		functiondef_list functiondef {$$=newast("functiondef",2,$1,$2);}
	|
	;

functiondef : 
		FUNCTION variable funcbody{
	
	}
	;

funcbody : 
		LPAREN paramlist RPAREN block return_statement END {$$=newast("funcbody",6,$1,$2,$3,$4,$5,$6);}
	;

return_statement : 
		RETURN num_id {
	
	}
	;

paramlist : 
		paramlist comma type identifier {$$=newast("paramlist",4,$1,$2,$3,$4);}
	|	type identifier {$$=newast("paramlist",2,$1,$2);}
	|
	;

addop : 
		PLUS {$$=newast("addop",1,$1);}
	|	MINUS {$$=newast("addop",1,$1);}
	; 

mulop : 
		STAR {$$=newast("mulop",1,$1);}
	|	SLASH {$$=newast("mulop",1,$1);}
	;

unaryop : 
		INCO {$$=newast("unaryop",1,$1);}
	|	DECO {$$=newast("unaryop",1,$1);}
	;

boolop : 
		EQUAL {$$=newast("boolop",1,$1);}
	|	GE {$$=newast("boolop",1,$1);}
	|	LE {$$=newast("boolop",1,$1);}
	|	LT {$$=newast("boolop",1,$1);}
	|	NOTEQUAL {$$=newast("boolop",1,$1);}
	|	GT {$$=newast("boolop",1,$1);}
	;

type : 
		bool_type {$$=newast("type",1,$1);}
	|	int_type {$$=newast("type",1,$1);}
	|	double_type {$$=newast("type",1,$1);}
	|	list_type {$$=newast("type",1,$1);}
	;

bool_type : 
		BOOL {$$ = newast("bool_type",1,$1);}
	;

int_type : 
		INT {$$ = newast("int_type",1,$1); $$->type = "int";}
	;

double_type : 
		DOUBLE {$$ = newast("double_type",1,$1); $$->type = "double";}
	;

list_type : 
		LIST {$$=newast("list_type",1,$1);$$->type = "list";}
	;

num_id : 
		identifier {$$=newast("num_id",1,$1);}
	|	num {$$=newast("num_id",1,$1);}
	;

num : 
		MINUS DIGSEQ {$$=newast("num",2,$1,$2);}
	|	DIGSEQ {$$=newast("num",1,$1);}
	|	MINUS REALNUMBER {$$=newast("num",2,$1,$2);}
	|	REALNUMBER {$$=newast("num",1,$1);}
	;

int_list : 
		int_list comma int_num {$$=newast("num",3,$1,$2,$3);}
	|	int_num {$$=newast("num",1,$1);}
	;

int_num : 
		MINUS DIGSEQ {$$=newast("int_num",2,$1,$2);}
	|	DIGSEQ {$$=newast("int_num",1,$1);}
	;

identifier : 
		IDENTIFIER {$$=newast("identifier",1,$1);}
	;

comma : 
		COMMA {$$=newast("comma",1,$1);}
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
