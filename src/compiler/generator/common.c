#include "common.h"
TreeNode *makeNewNode(){
  TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
  if (t == NULL) {
    fprintf (stderr, "out of memory during parsing\n");
    exit(1);
  }

  t->child = NULL;
  t->sibling = NULL;
  t->line_no = 0;
  t->literal = NULL;
  t->label = NULL;

  t->size = 0;
  t->level = 0;
  t->leveltofather = 0;

  t->computable = 0;
  t->result = 0;
  t->type = 0;

  t->start_ins_line = -1;
  t->end_ins_line = -1;
  return t;
}

void releaseNode(TreeNode *t) {
  if (t == NULL) {
    return;
  }

  if (t->literal != NULL) {
    free(t->literal);
  }
  if (t->label != NULL) {
    free(t->label);
  }

  releaseNode(t->sibling);
  releaseNode(t->child);

  free(t);
}

char nodeKindStr[][40] = {
  "variable", "int", "double", "list",
  "bool", "id", "equal_expression",
  "greater_equal", "less_equal", "greater_than",
  "less_than", "not_equal", "increase_one",
  "decrease_one", "divide_op", "mul_op",
  "plus_op", "minus_op", "return",
  "function_body", "parameter_list", "functiondef",
  "num_id", "term", "list_expression",
  "false", "true", "bool_expression", "brac",
  "expression", "argument_list", "functioncall",
  "define_assign", "identifier_assign", "unary_assign", 
  "else_statement", "if_statement", 
  "math_expression", "functiondef_list",
  "file", "main_function", "block",
  "do_statement", "while_statement", "for_statement"
};

int errorOccur = 0;
