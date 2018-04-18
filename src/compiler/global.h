#ifndef GLOBAL_H_
#define GLOBAL_H_

int errorOccur = 0;
extern int yylineno;//行号
extern char* yytext;//词

/*tree node definition*/

struct ast_node {
    int line;
    char* name;
    char *instructor;
    char* type;
    struct ast_node *left;
    struct ast_node *right;
};

typedef sturct ast_node AST_NODE;
typedef AST_NODE *AST_TREE;







//for function
struct ast_function_node // for function calls
{
    int node_type;
    char* name;
    char* type;
    struct ast_node * arguments;
    
    struct symbol_node * symbol;
};

struct number_node{
    int line;
    char* name;
}







#endif // GLOBAL_H_
