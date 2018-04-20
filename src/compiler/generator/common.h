#ifndef COMMON_H_
#define COMMON_H_

/*tree node definition*/
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define YYSTYPE TreeNode *

typedef enum {
  variable_NodeKind, int_NodeKind, double_NodeKind, list_NodeKind,
  bool_NodeKind, id_NodeKind, equal_expression_NodeKind,
  greater_equal_NodeKind, less_equal_NodeKind, greater_than_NodeKind,
  less_than_NodeKind, not_equal_NodeKind, increase_one_NodeKind,
  decrease_one_NodeKind, divide_op_NodeKind, mul_op_NodeKind,
  plus_op_NodeKind, minus_op_NodeKind, return_NodeKind,
  function_body_NodeKind, parameter_list_NodeKind，functiondef_NodeKind,
    functiondef_list_NodeKind, term_KindNode
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
