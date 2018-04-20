#ifndef COMMON_H_
#define COMMON_H_

/*tree node definition*/
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define YYSTYPE TreeNode *

typedef enum {
  variable_NodeKind, int_NodeKind, double_NodeKind, list_NodeKind, bool_NodeKind, id_NodeKind
} NodeKind;

typedef enum {
  _integer, _double, _boolean, _list
} TableNodeType;

typedef struct treeNode {
  struct treeNode *child;
  struct treeNode *sibling;
  int line_no;
  char *literal;
  NodeKind nodeKind;

  char *label;
  int size;
  int level;
  int leveltofather;

  int computable;
  int result;
  int type;

  TableNodeType tableType;
} TreeNode;

TreeNode *makeNewNode();
void releaseNode(TreeNode *t);

#endif // GLOBAL_H_
