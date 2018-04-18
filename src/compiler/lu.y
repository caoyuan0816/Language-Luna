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
%type <node> term functiondef_list functiondef return_statement
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


if_statement : IF LPAREN bool_expression RPAREN block else_statement END {$$=newast("loop_statement",7,$1,$2,$3,$4,$5,$6,$7);}
	;

else_statement : ELSE block |
	;

assign_statement : 
		define_assign {$$=newast("assign_statement",1,$1);}
	|	identifier_assign {$$=newast("assign_statement",1,$1);}
	|	unary_assign {$$=newast("assign_statement",1,$1);}
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
	}|
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

addop : PLUS {$$ = newast("MINUS",0,yylineno} |
    MINUS {$$ = newast("MINUS",0,yylineno)}
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

num : MINUS DIGSEQ |
	DIGSEQ |
	MINUS REALNUMBER |
	REALNUMBER
	;

int_list : int_list comma int_num |
	int_num
	;

int_num : MINUS DIGSEQ |
	DIGSEQ
	;

identifier : IDENTIFIER
	;

comma : COMMA {$$ = newast("COMMA",0,yylineno)}
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
