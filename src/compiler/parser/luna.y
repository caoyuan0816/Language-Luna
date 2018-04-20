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
int yyerror(char *s);
int yylex();
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
file : functiondef_list MAIN LPAREN variable COMMA variable RPAREN block END |
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
	  printf("line number: %d\n", $$->line_no);
	}
	;

do_statement : DO block END{
    
    }
	;

loop_statement : WHILE LPAREN bool_expression RPAREN DO block END |
	FOR identifier for_statement
	;

for_statement : ASSIGNMENT int_num COMMA int_num COMMA int_num DO block END |
	IN list_expression DO block END |
	IN identifier DO block END
	;


if_statement : IF LPAREN bool_expression RPAREN block else_statement END{
	$$ = makeNewNode();
	$$->nodeKind = if_statement_NodeKind;
	TreeNode *temp = $3;
	$$->child = temp;
	currentline = $1->line_no;
	$$->line_no = currentline;
	if($5 != NULL){
	  temp->sibling = $5;
	  $5->sibling = $6;
	} else {
          temp->sibling = $6;
	}
	free($1);
	free($2);
	free($4);
	free($7);
	}
	;

else_statement : ELSE block {
	$$ = makeNewNode();
	$$->nodeKind = else_statement_NodeKind;
	$$->child = $2;
	currentline = $$->line_no;
	free($1);
	}|
	;

assign_statement : define_assign {
	$$ = $1;
	}|
identifier_assign{
	$$ = $1;
	}|
unary_assign{
	$$ = $1; 
	}
	;

unary_assign : identifier unaryop{
	$$ = makeNewNode();
	$$->nodeKind = unary_assign_NodeKind;
	$$->child = $2;
	$2->sibling = $1;
	currentline = $$->line_no;
	}
	;

identifier_assign : identifier ASSIGNMENT assign_type{
	$$ = makeNewNode();
	$$->nodeKind = identifier_assign_NodeKind;
	$$->child = $1;
	$1->sibling = $3;
	currentline = $$->line_no;
	free($2);
	}
	;

define_assign : variable ASSIGNMENT assign_type{
	$$ = makeNewNode();
	$$->nodeKind = define_assign_NodeKind;
	$$->child = $1;
	$1->sibling = $3;
	currentline = $$->line_no;
	free($2);
	}
	;

assign_type : expression {
	$$ = $1;
	}|
	TRUE{
	$$ = $1;
	$$->nodeKind = true_NodeKind;
        currentline = $$->line_no;
	} |	
	FALSE{
	$$ = $1;
	$$->nodeKind = false_NodeKind;
	currentline = $$->line_no;
	} |
	list_expression{
	$$ = $1;
	}
	;

variable : type identifier {
	$$ = makeNewNode();
	$$->nodeKind = variable_NodeKind;
	$$->child = $1;
	$1->sibling = $2;
	currentline = $$->line_no;
	printf("child: %s\tsibling: %s\n", $1->literal, $1->sibling->literal);
	} |
	error {
	  printf("variable definition error in line :%d\n",$$->line_no);
	}
	;

functioncall : identifier argument_list{
	$$ = makeNewNode();
	$$->nodeKind = functioncall_NodeKind;
	$$->child = $1;
	$1->sibling = $2;
	currentline = $$->line_no;
	}
	;

argument_list : LPAREN RPAREN{
	$$ = makeNewNode();
	$$->nodeKind = argument_list_NodeKind;
	currentline = $$->line_no;
	free($1);
	free($2);
	}|
	LPAREN expression_list RPAREN{
	$$ = makeNewNode();
	$$->nodeKind = argument_list_NodeKind;
	$$->child = $2;
	currentline = $$->line_no;
	free($1);
	free($3);
	}
	;

expression_list : expression_list COMMA expression{
	TreeNode *temp = $1;
	while(temp->sibling != NULL){
          temp = temp->sibling;
	}
	temp->sibling = $3;
	$$ = $1;
	free($2);
	} |
	expression{
	$$ = $1;
	}
	;

bool_expression : FALSE {
	$$ = $1;
	$$->nodeKind = false_NodeKind;
	currentline = $$->line_no;
	}|
	TRUE {
	$$ = $1;
	$$->nodeKind = true_NodeKind;
	currentline = $$->line_no;
	}|
	expression boolop expression {
	$$ = makeNewNode();
	$$->nodeKind = bool_expression_NodeKind;
	$$->child = $2;
	currentline = $2->line_no;
	$$->line_no = currentline;
	$2->sibling = $1;
	$1->sibling = $3;
	}
	;

expression : math_expression {
	$$ = makeNewNode();
	$$->nodeKind = math_expression_NodeKind;
	$$->child = $1;
	} |
	functioncall{
	$$ = $1;
	} |
	error {
	  printf("expression error detected!\n");
	}
	;

list_expression : LBRAC int_list RBRAC{
	$$ = makeNewNode();
	$$->nodeKind = list_expression_NodeKind;
	$$->child = $2;
	free($1);
	free($3);
	}|
	LBRAC RBRAC{
	$$ = makeNewNode();
	$$->nodeKind = list_expression_NodeKind;
        free($1);
        free($2);
	}
	;

//TODO: reconsider
math_expression : math_expression addop term{
	TreeNode *temp = makeNewNode();
	temp->nodeKind = term_NodeKind;
	temp->child = $3;
	$2->sibling = temp;
	temp->sibling = $1;
	$$ = $2;
	}|
	term{
	$$ = makeNewNode();
	$$->nodeKind = term_NodeKind;
        $$->child = $1;
	}
	;

//TODO: reconsider
term : term mulop num_id {
	TreeNode *temp = $2;
	if (temp->sibling!=NULL){
	  printf("%d The operator %s already has a sibling: %s\n", temp->line_no, temp->literal, temp->sibling->literal);
	}
	temp->sibling = $3;
	if ($3->sibling!=NULL){
	  printf("%d The number %s already has a sibling: %s\n", temp->line_no, temp->literal, temp->sibling->literal);
	}
	$3->sibling = $1;
	$$ = $2;
	}
	|
	num_id {
	$$ = $1;
	}
	;

functiondef_list : functiondef_list functiondef{
	if ($1!=NULL){
	  TreeNode *temp = $1;
	  while(temp->sibling != NULL){
	    temp = temp->sibling;
	  }
	  temp->sibling = $2;
	  $$ = $1;
	} else {
	  $$ = $2;
	}
	}|
	;

functiondef : FUNCTION variable funcbody{
	$$ = makeNewNode();
	$$->nodeKind = functiondef_NodeKind;
	$$->child = $2;
	$2->sibling = $3;
	currentline = $$->line_no;
	free($1);
	}
	;

funcbody : LPAREN paramlist RPAREN block return_statement END {
	$$ = makeNewNode();
	$$->nodeKind = function_body_NodeKind;
	TreeNode *temp = makeNewNode();
	$$->child = temp;
	temp->nodeKind = parameter_list_NodeKind;
        temp->child = $2;
	currentline = $1->line_no;
	$$->line_no = currentline;
	if ($4!=NULL){
        temp->sibling = $4;
	  $4->sibling = $5;
	} else {
	  temp->sibling = $5;
	}
	free($1);
	free($3);
	free($6);
	}|
	LPAREN RPAREN block return_statement END{
	$$ = makeNewNode();
	$$->nodeKind = function_body_NodeKind;
	TreeNode *temp = makeNewNode();
	$$->child = temp;
	temp->nodeKind = parameter_list_NodeKind;
	currentline = $1->line_no;
	$$->line_no = currentline;
	if ($3!=NULL){
	  temp->sibling = $3;
	  $3->sibling = $4;
	} else {
	  temp->sibling = $4;
	}
	free($1);
	free($2);
	free($5);
	}
	;

return_statement : RETURN num_id {
	$$ = makeNewNode();
	$$->nodeKind = return_NodeKind;
	$$->child = $2;
	free($1);
	}
	;

paramlist : paramlist COMMA variable {
	if ($1!=NULL){
	  TreeNode *temp = $1;
	  while (temp->sibling!=NULL){
	    temp = temp->sibling;
	  }
	  temp->sibling = $3;
	  $$ = $1;
	} else {
	  $$ = $3;
	}
	free($2);
	}|
	variable {
	$$ = $1;
	}
	;

addop : PLUS {
	$$ = $1;
	$$->nodeKind = plus_op_NodeKind;
	currentline = $$->line_no;
	}|
	MINUS {
	$$ = $1;
	$$->nodeKind = minus_op_NodeKind;
	currentline = $$->line_no;
	}
	; 

mulop : STAR {
	$$ = $1;
	$$->nodeKind = mul_op_NodeKind;
	currentline = $$->line_no;
	}|
	SLASH {
	$$->nodeKind = divide_op_NodeKind;
	currentline = $$->line_no;
	}
	;

unaryop : INCO {
	$$ = $1;
	$$->nodeKind = increase_one_NodeKind;
	currentline = $$->line_no;
	}|
	DECO {
	$$ = $1;
	$$->nodeKind = decrease_one_NodeKind;
	currentline = $$->line_no;
	}
	;

boolop : EQUAL {
	$$ = $1;
	$$->nodeKind = equal_expression_NodeKind;
	currentline = $$->line_no;
	}|
	GE {
	$$ = $1;
	$$->nodeKind = greater_equal_NodeKind;
	currentline = $$->line_no;
	}|
	LE {
	$$ = $1;
	$$->nodeKind = less_equal_NodeKind;
	currentline = $$->line_no;
	}|
	LT {
	$$ = $1;
	$$->nodeKind = less_than_NodeKind;
	currentline = $$->line_no;
	}|
	GT {
	$$ = $1;
	$$->nodeKind = greater_than_NodeKind;
	currentline = $$->line_no;
	}|	
	NOTEQUAL {
	$$ = $1;
	$$->nodeKind = not_equal_NodeKind;
	currentline = $$->line_no;
	}
	;

type : bool_type {
	$$ = $1;
	currentline = $$->line_no;
	} |
	int_type {
	$$ = $1;
	currentline = $$->line_no;
	} |
	double_type {
	$$ = $1;
	currentline = $$->line_no;
	}|
	list_type{
	$$ = $1;
	currentline = $$->line_no;
	}
	;

bool_type : BOOL {
	$$ = $1;
	$$->nodeKind = bool_NodeKind;
	currentline = $$->line_no;
	}
	;

int_type : INT {
	$$ = $1;
	$$->nodeKind = int_NodeKind;
	currentline = $$->line_no;
	}
	;

double_type : DOUBLE {
	$$ = $1;
	$$->nodeKind = double_NodeKind;
	currentline = $$->line_no;
	}
	;

list_type : LIST {
	$$ = $1;
	$$->nodeKind = list_NodeKind;
	currentline = $$->line_no;
	}
	;

num_id : identifier {
	$$ = $1;
	}|
	num {
	$$ = $1;
	}
	;

num :   int_num {
	$$ = $1;
	}|
	real_num {
	$$ = $1;
	}
	;

int_list : int_list COMMA int_num {
	$$ = makeNewNode();
	$$->nodeKind = int_NodeKind;
	if ($1!=NULL){
	  TreeNode *temp = $1;
	  while (temp->sibling!=NULL){
	    temp = temp->sibling;
	  }
	  temp->sibling = $3;
	  $$ = $1;
	} else {
	  $$ = $3;
	}
	free($2);
	}|
	int_num {
	$$ = $1;
	}
	;

real_num :MINUS REALNUMBER {
	$$ = $2;
	$$->nodeKind = double_NodeKind;
	currentline = $$->line_no;
	free($1);
	}|
	REALNUMBER {
	$$ = $1;
	$$->nodeKind = double_NodeKind;
	currentline = $$->line_no;
//	printf("double: %s\n", $$->literal);
	}
	;

int_num : MINUS INTNUM {
	$$ = $2;
	$$->nodeKind = int_NodeKind;
	currentline = $$->line_no;
//	printf("negative int: %c%s\n", '-', $$->literal);
	free($1);
	} |
	INTNUM {
	$$ = $1;
	$$->nodeKind = int_NodeKind;
	currentline = $$->line_no;
//	printf("int number: %s\n", $$->literal);
	}
	;

identifier : IDENTIFIER {
	$$ = $1;
	$$->nodeKind = id_NodeKind;
	currentline = $$->line_no;
	}
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
