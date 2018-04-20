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
  "varibale"
};

int errorOccur = 0;
