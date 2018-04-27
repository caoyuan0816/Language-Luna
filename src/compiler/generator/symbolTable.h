#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "common.h"

typedef struct VarTable{
  struct VarTable *child;
  struct VarTable *sibling;
  struct VarTable *father;
  NodeKind varType;
  TreeNode *var;
  int line_no;
} VarTable;

typedef struct BlockTable{
  struct BlockTable *child;
  struct BlockTable *sibling;
  struct BlockTable *father;
  struct VarTable *varTable;

  int size;
  int line_no;
} BlockTable;

typedef struct FuncTable{
  struct FuncTable *sibling;
  struct FuncTable *head;
  struct BlockTable *blockTable;
  struct VarTable *paramTable;

  TreeNode *returnNode;
  int line_no;
} FuncTable;

VarTable *makeNewVarTable();
BlockTable *makeNewBlockTable();
FuncTable *makeNewFuncTable();

void funcGen(TreeNode *, FuncTable *, int *line);
void codeGen(TreeNode *, FuncTable *, int *line);

void releaseVarTable(VarTable *);
void releaseBlockTable(BlockTable *);
void releaseFuncTable(FuncTable *);
#endif
