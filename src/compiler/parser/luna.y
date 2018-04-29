%{/* luna.y
 *
 * Luna grammar in Yacc format, based originally on
 * BNF of Luna language
 */
#include "macros.h"
#include "common.h"
#include "symbolTable.h"
#include <stdio.h>

#define WIDTH (4)
#define HEIGHT (0)

extern int openFile(int argc, char** argv);
int errorOccur;
int currentline = 0;
int yyerror(char *s);
int yylex();

TreeNode *tree = NULL;
void releaseNode(TreeNode *);
void printTree(TreeNode *, int);

void printAncestor(int *uncle, int level);
void printThisTree(TreeNode * t, int *uncle, int level);
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

file : functiondef_list MAIN LPAREN variable COMMA variable RPAREN block END {
	if ($1!=NULL){
	  TreeNode *temp = makeNewNode();
	  temp->nodeKind = functiondef_list_NodeKind;
	  temp->child = $1;
	  temp->line_no = $1->line_no;
	  $$ = makeNewNode();
	  $$->nodeKind = file_NodeKind;
	  $$->child = temp;
	  temp = makeNewNode();
	  temp->nodeKind = main_function_NodeKind;
	  temp->child = $4;
	  temp->line_no = $2->line_no;
	  $4->sibling = $6;
	  $6->sibling = $8;
	  $$->child->sibling = temp;
	} else {
	  $$ = makeNewNode();
	  $$->nodeKind = file_NodeKind;
	  TreeNode *temp = makeNewNode();
	  temp->nodeKind = main_function_NodeKind;
	  temp->line_no = $2->line_no;
	  temp->child = $4;
	  $4->sibling = $6;
	  $6->sibling = $8;
	  $$->child = temp;
	}
	tree = $$;
	releaseNode($2);
	releaseNode($3);
	releaseNode($5);
	releaseNode($7);
	releaseNode($9);
	}|
	functiondef_list MAIN LPAREN RPAREN block END{
	if ($1!=NULL){
	  TreeNode *temp = makeNewNode();
	  temp->nodeKind = functiondef_list_NodeKind;
	  temp->child = $1;
	  temp->line_no = $1->line_no;
	  $$ = makeNewNode();
	  $$->nodeKind = file_NodeKind;
	  $$->child = temp;
	  temp = makeNewNode();
	  temp->nodeKind = main_function_NodeKind;
	  temp->line_no = $2->line_no;
	  temp->child = $5;
	  $$->child->sibling = temp;
	} else {
	  $$ = makeNewNode();
	  $$->nodeKind = file_NodeKind;
	  TreeNode *temp = makeNewNode();
	  temp->nodeKind = main_function_NodeKind;
	  temp->line_no = $2->line_no;
	  temp->child = $5;
	  $$->child = temp;
	}
	tree = $$;
	releaseNode($2);
	releaseNode($3);
	releaseNode($4);
	releaseNode($6);
	}
	;

block : statement_list {
	$$ = makeNewNode();
	$$->nodeKind = block_NodeKind;
	$$->child = $1;
	$$->line_no = $1->line_no;
	}|
	;

statement_list : statement_list statement {
	if ($1!=NULL){
	  TreeNode *temp = $1;
	  while(temp->sibling!=NULL){
	    temp = temp->sibling;
	  }
	  temp->sibling = $2;
	  $$ = $1;
	} else {
	  $$ = $2;
	}
	}|
	statement{
	$$ = $1;
	}
	;

statement : assign_statement {
	$$ = $1;
	}|
	functioncall {
	$$ = $1;
	}|
	do_statement {
	$$ = $1;
	}|
	loop_statement {
	$$ = $1;
	}|
	if_statement {
	$$ = $1;
	}|
        return_statement{
        $$ = $1;
        }|
	error {
	  printf("statement error detected\n");
	  printf("line number: %d\n", $$->line_no);
	}
	;

do_statement : DO block END{
	$$ = makeNewNode();
	$$->nodeKind = do_statement_NodeKind;
	$$->child = $2;
	$$->line_no = $1->line_no;
	releaseNode($1);
	releaseNode($3);
	}
	;

loop_statement : WHILE LPAREN bool_expression RPAREN DO block END {
	$$ = makeNewNode();
	$$->nodeKind = while_statement_NodeKind;
	$$->child = $3;
	$3->sibling = $6;
	$$->line_no = $1->line_no;
	releaseNode($1);
	releaseNode($2);
	releaseNode($4);
	releaseNode($5);
	releaseNode($7);
	}|
	FOR identifier for_statement{
	$$ = makeNewNode();
	$$->nodeKind = for_statement_NodeKind;
	$$->child = $2;
	$2->sibling = $3;
	$$->line_no = $1->line_no;
	releaseNode($1);
	}
	;

for_statement : ASSIGNMENT int_num COMMA int_num COMMA int_num DO block END {
	$$ = $2;
	$2->sibling = $4;
	$4->sibling = $6;
	$6->sibling = $8;
	releaseNode($1);
	releaseNode($3);
	releaseNode($5);
	releaseNode($7);
	releaseNode($9);
	}|
	IN list_expression DO block END {
	$$ = $2;
	$2->sibling = $4;
	releaseNode($1);
	releaseNode($3);
	releaseNode($5);
	}|
	IN identifier DO block END{
	$$ = $2;
	$2->sibling = $4;
	releaseNode($1);
	releaseNode($3);
	releaseNode($5);
	}
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
	  if ($6!=NULL) $5->sibling = $6;
	} else {
          if ($6!=NULL) temp->sibling = $6;
	}
	releaseNode($1);
	releaseNode($2);
	releaseNode($4);
	releaseNode($7);
	}
	;

else_statement : ELSE block {
	$$ = makeNewNode();
	$$->nodeKind = else_statement_NodeKind;
	$$->child = $2;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	releaseNode($1);
	}| {
	$$ = NULL;
	}
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
	$$->line_no = $1->line_no;
	}
	;

identifier_assign : identifier ASSIGNMENT assign_type{
	$$ = makeNewNode();
	$$->nodeKind = identifier_assign_NodeKind;
	$$->child = $1;
	$1->sibling = $3;
	$$->line_no = $1->line_no;
	releaseNode($2);
	}
	;

define_assign : variable ASSIGNMENT assign_type{
	$$ = makeNewNode();
	$$->nodeKind = define_assign_NodeKind;
	$$->child = $1;
	$1->sibling = $3;
	$$->line_no = $1->line_no;
	releaseNode($2);
	}
	;

assign_type : expression {
	$$ = $1;
	}|
	TRUE{
	$$ = $1;
	$$->nodeKind = true_NodeKind;
        $$->line_no = $1->line_no;
	} |	
	FALSE{
	$$ = $1;
	$$->nodeKind = false_NodeKind;
	$$->line_no = $1->line_no;
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
	currentline = $1->line_no;
	$$->line_no = currentline;
	//printf("%d child: %s\tsibling: %s\n",$1->line_no, $1->literal, $1->sibling->literal);
	//printf("variable_NodeKind: %d\n", variable_NodeKind);
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
	$$->line_no = $1->line_no;
	}
	;

argument_list : LPAREN RPAREN{
	$$ = makeNewNode();
	$$->nodeKind = argument_list_NodeKind;
	$$->line_no = $1->line_no;
	releaseNode($1);
	releaseNode($2);
	}|
	LPAREN expression_list RPAREN{
	$$ = makeNewNode();
	$$->nodeKind = argument_list_NodeKind;
	$$->child = $2;
	$$->line_no = $1->line_no;
	releaseNode($1);
	releaseNode($3);
	}
	;

expression_list : expression_list COMMA expression{
	TreeNode *temp = $1;
	while(temp->sibling != NULL){
          temp = temp->sibling;
	}
	temp->sibling = $3;
	$$ = $1;
	releaseNode($2);
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
	$$->line_no = $1->line_no;
	$$->child = $1;
	} |
	error {
	  printf("expression error detected!\n");
	}
	;

list_expression : LBRAC int_list RBRAC{
	$$ = makeNewNode();
	$$->nodeKind = list_expression_NodeKind;
	$$->line_no = $1->line_no;
	$$->child = $2;
	releaseNode($1);
	releaseNode($3);
	}|
	LBRAC RBRAC{
	$$ = makeNewNode();
	$$->nodeKind = list_expression_NodeKind;
	$$->line_no = $1->line_no;
        releaseNode($1);
        releaseNode($2);
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
	$$->line_no = $1->line_no;
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
	} |
	num_id {
	$$ = $1;
	} |
        functioncall{
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
	} | {
	$$ = NULL;
	}
	;

functiondef : FUNCTION variable funcbody{
	$$ = makeNewNode();
	$$->nodeKind = functiondef_NodeKind;
	$$->child = $2;
	$2->sibling = $3;
	currentline = $1->line_no;
	$$->line_no = currentline;
	releaseNode($1);
	}
	;

funcbody : LPAREN paramlist RPAREN block END {
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
	}
	releaseNode($1);
	releaseNode($3);
	releaseNode($5);
	}|
	LPAREN RPAREN block END{
	$$ = makeNewNode();
	$$->nodeKind = function_body_NodeKind;
	TreeNode *temp = makeNewNode();
	$$->child = temp;
	temp->nodeKind = parameter_list_NodeKind;
	currentline = $1->line_no;
	$$->line_no = currentline;
	if ($3!=NULL){
	  temp->sibling = $3;
	}
	releaseNode($1);
	releaseNode($2);
	releaseNode($4);
	}
	;

return_statement : RETURN expression {
	$$ = makeNewNode();
	$$->nodeKind = return_NodeKind;
	$$->child = $2;
	$$->line_no = $1->line_no;
	releaseNode($1);
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
	releaseNode($2);
	}|
	variable {
	$$ = $1;
	}
	;

addop : PLUS {
	$$ = $1;
	$$->nodeKind = plus_op_NodeKind;
	$$->line_no = $1->line_no;
	}|
	MINUS {
	$$ = $1;
	$$->nodeKind = minus_op_NodeKind;
	$$->line_no = $1->line_no;
	}
	; 

mulop : STAR {
	$$ = $1;
	$$->nodeKind = mul_op_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}|
	SLASH {
	$$->nodeKind = divide_op_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}
	;

unaryop : INCO {
	$$ = $1;
	$$->nodeKind = increase_one_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}|
	DECO {
	$$ = $1;
	$$->nodeKind = decrease_one_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}
	;

boolop : EQUAL {
	$$ = $1;
	$$->nodeKind = equal_expression_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}|
	GE {
	$$ = $1;
	$$->nodeKind = greater_equal_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}|
	LE {
	$$ = $1;
	$$->nodeKind = less_equal_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}|
	LT {
	$$ = $1;
	$$->nodeKind = less_than_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}|
	GT {
	$$ = $1;
	$$->nodeKind = greater_than_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}|	
	NOTEQUAL {
	$$ = $1;
	$$->nodeKind = not_equal_NodeKind;
	$$->line_no = $1->line_no;
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
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}
	;

int_type : INT {
	$$ = $1;
	$$->nodeKind = int_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}
	;

double_type : DOUBLE {
	$$ = $1;
	$$->nodeKind = double_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}
	;

list_type : LIST {
	$$ = $1;
	$$->nodeKind = list_NodeKind;
	$$->line_no = $1->line_no;
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
	releaseNode($2);
	}|
	int_num {
	$$ = $1;
	}
	;

real_num :MINUS REALNUMBER {
	$$ = $2;
	$$->nodeKind = double_NodeKind;
	$$->line_no = $1->line_no;
        int len = strlen($$->literal);
        char *temp = (char *)malloc((len+2)*sizeof(char));
        temp[0]='-';
        strcpy(&temp[1], $$->literal);
        free($$->literal);
	$$->literal = temp;
      //TODO: add minus to the string of number
	currentline = $$->line_no;
	releaseNode($1);
	}|
	REALNUMBER {
	$$ = $1;
	$$->nodeKind = double_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}
	;

int_num : MINUS INTNUM {
	$$ = $2;
	$$->nodeKind = int_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	int len = strlen($$->literal);
        char *temp = (char *)malloc((len+2)*sizeof(char));
        temp[0]='-';
        strcpy(&temp[1], $$->literal);
        free($$->literal);
	$$->literal = temp;
	releaseNode($1);
	} |
	INTNUM {
	$$ = $1;
	$$->nodeKind = int_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
        }
	;

identifier : IDENTIFIER {
	$$ = $1;
	$$->nodeKind = id_NodeKind;
	$$->line_no = $1->line_no;
	currentline = $$->line_no;
	}
	;
%%

void printTree(TreeNode *root, int bias){
  if (root==NULL) return;
  if (root->child!=NULL) printTree(root->child, bias+1);
  else printf("\n");
  char buffer[10];
  sprintf(buffer, "\r%%%ds ", bias*24);
  printf(buffer, nodeKindStr[root->nodeKind]);
  printf(" %d", root->line_no);
  TreeNode *temp = root;
  while(temp->sibling){
    printTree(temp->sibling, bias);
    temp = temp->sibling;
  }
}

int yyerror(char *s){
  fprintf(stderr, "%s\n", s);
  errorOccur++;
  return 0;
}

void printAncestor(int *uncle, int level) {
  int i = 0;
  for (; i < level - 1; ++i) {
    if (uncle[i] == 1) {
      printf("|");
    } else {
      printf(" ");
    }
    int j = 0;
    for (; j < WIDTH - 1; ++j)    {
      printf(" ");
    }
  }
}

void printThisTree(TreeNode * t, int *uncle, int level) {
  if (t == NULL)
    return;

  printAncestor(uncle, level);
  if (level != 0) {
    printf("|");
    int i = 0;
    for (; i < WIDTH - 1; ++i) {
      printf("-");
    }
  }

  if (t->literal) {
    printf("%s-%s\n", t->literal, nodeKindStr[t->nodeKind]);
  } else {
    printf("%s%d\n", nodeKindStr[t->nodeKind], t->line_no);
  }

  TreeNode * k = t->child;
  while (k != NULL) {
    if (k->sibling) {
      uncle[level] = 1;
    } else {
      uncle[level] = 0;
    }

    for (int i = 0; i < HEIGHT; i++) {
      printAncestor(uncle, level + 1);
      printf("|\n");
    }

    printThisTree(k, uncle, level + 1);

    k = k->sibling;
  }
}

int main(int argc, char** argv){

	//Checking arguments number
	if (argc != 2){
	    printf("Cannot find input file\n");
	    printf("Usage: lunac [input_file.lu]\n");
	    exit(1);
  	}

  	//Checking file name
  	if(strlen(argv[1]) <= 3){
  		printf("Suffix of input file must be *.lu\n");
  		printf("Please check your input file format.\n");
  		exit(1);
  	}else{
  		char file_suf[4];
	  	memcpy(file_suf, &(argv[1][strlen(argv[1])-3]), 3);
	  	file_suf[3] = '\0';
	  	if(strcmp(file_suf, ".lu") != 0){
	  		printf("Suffix of input file must be *.lu\n");
	  		printf("Please check your input file format.\n");
	  		exit(1);
	  	}
  	}

  	#ifdef _LUNAC_DEBUG_
  		printf("Loading from :%s\n", argv[1]);
  	#endif

  	//Parsing
	errorOccur = 0;
	errorOccur = openFile(argc, argv);
	yyparse();
	int uncle[200]={0};

	//Debug information
	#ifdef _LUNAC_DEBUG_
	    printThisTree(tree, uncle, 0);
	#endif

	//Byte code generating
	FuncTable *funcTable = makeNewFuncTable();
	int line =0;
	codeGen(tree, funcTable, &line, argv[1]);
	return 0;
}
