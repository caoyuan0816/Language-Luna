#include "global.h"

int errorOccur = 0;

ast_node newast(int line. char* name, AST_TREE n1, AST_TREE n2){
    ast_node t ;
    t = (ast_node)malloc(sizeof(AST_NODE));
    t->line = line;
    strcpy(t->name, name);
    t->left = n1;
    t-> rigth = n2;
    return (t);
}
