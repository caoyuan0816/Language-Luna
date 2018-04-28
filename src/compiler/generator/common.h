#ifndef COMMON_H_
#define COMMON_H_

/*tree node definition*/
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "macros.h"

#define YYSTYPE TreeNode *

typedef enum {
  variable_NodeKind, int_NodeKind, double_NodeKind, list_NodeKind,
  bool_NodeKind, id_NodeKind, equal_expression_NodeKind,
  greater_equal_NodeKind, less_equal_NodeKind, greater_than_NodeKind,
  less_than_NodeKind, not_equal_NodeKind, increase_one_NodeKind,
  decrease_one_NodeKind, divide_op_NodeKind, mul_op_NodeKind,
  plus_op_NodeKind, minus_op_NodeKind, return_NodeKind,
  function_body_NodeKind, parameter_list_NodeKind, functiondef_NodeKind,
  num_id_NodeKind, term_NodeKind, list_expression_NodeKind, false_NodeKind,
  true_NodeKind, bool_expression_NodeKind, brac_NodeKind, expression_NodeKind,
  argument_list_NodeKind, functioncall_NodeKind, define_assign_NodeKind,
  identifier_assign_NodeKind, unary_assign_NodeKind, else_statement_NodeKind,
  if_statement_NodeKind, math_expression_NodeKind, functiondef_list_NodeKind,
  file_NodeKind, main_function_NodeKind, block_NodeKind,
  do_statement_NodeKind, while_statement_NodeKind, for_statement_NodeKind
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

  int start_ins_line;
  int end_ins_line;

  TableNodeType tableType;
} TreeNode;

TreeNode *makeNewNode();
void releaseNode(TreeNode *t);

extern char nodeKindStr[][40];

#endif
