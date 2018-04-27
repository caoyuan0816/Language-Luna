#include "symbolTable.h"

#define NULL_ERROR {printf("error null in line: %d\n", tree->line_no); exit(1); }
#define OUTPUT_CMD(X) {printf("%d ", *line); (*line)++; printf(X); printf("\n");} 
#define OUTPUT_CMD_P(X,Y) {printf("%d ", *line); (*line)++; printf(X, Y); printf("\n");} 
#define COMPILE_ERROR(X,Y) {printf("error: line %d ", Y); printf(X); printf("\n");}

VarTable *makeNewVarTable(){
  VarTable *t = (VarTable *)malloc(sizeof(VarTable));

  if (t == NULL){
    fprintf(stderr, "out of memory during allocate variable table\n");
    exit(1);
  }

  t->child = NULL;
  t->sibling = NULL;
  t->father = NULL;

  t->varType = variable_NodeKind;

  t->var = NULL;
  t->line_no = 0;

  return t;
}

BlockTable *makeNewBlockTable(){
  BlockTable *t = (BlockTable *)malloc(sizeof(BlockTable));

  if (t == NULL){
    fprintf(stderr, "out of memory during allocate block table\n");
    exit(1);
  }

  t->child = NULL;
  t->sibling = NULL;
  t->father = NULL;

  t->varTable = NULL;

  t->size = 0;
  t->line_no = 0;

  return t;
}

FuncTable *makeNewFuncTable(){
  FuncTable *t = (FuncTable *)malloc(sizeof(FuncTable));

  if (t == NULL){
    fprintf(stderr, "out of memory during allocate function table\n");
    exit(1);
  }

  t->sibling = NULL;
  t->head = NULL;

  t->blockTable = NULL;
  t->paramTable = NULL;

  t->line_no = 0;

  return t;
}

void addParam(TreeNode *tree, VarTable *varTable) {
  
}

void addVar(TreeNode *tree, VarTable *varTable) {
  if (tree == NULL) return;
  // TODO: add type check if still have time
  if (tree->nodeKind==variable_NodeKind){
    TreeNode *temp = tree;
    VarTable *table = varTable;
    while (temp!=NULL){
      if(table->var==NULL){
        table->var = temp;
      } else{
        
      }
    }
  }
}

void functioncall(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line){

}

void math_expression(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line){
  if (tree == NULL) return;
  switch (tree->nodeKind){
    case term_NodeKind:
      math_expression(tree->sibling, funcTable, blockTable, line);
      math_expression(tree->child, funcTable, blockTable, line);
      break;

    case plus_op_NodeKind:
      math_expression(tree->sibling, funcTable, blockTable, line);
      OUTPUT_CMD("ADD");
      break;

    case minus_op_NodeKind:
      math_expression(tree->sibling, funcTable, blockTable, line);
      OUTPUT_CMD("SUB");
      break;

    case double_NodeKind:
    case int_NodeKind:
      math_expression(tree->sibling, funcTable, blockTable, line);
      OUTPUT_CMD_P("LDC %s", tree->literal);
      break;

    case id_NodeKind:
      math_expression(tree->sibling, funcTable, blockTable, line);
      OUTPUT_CMD_P("LDV %s", tree->literal);
      break;

    case mul_op_NodeKind:
      math_expression(tree->sibling, funcTable, blockTable, line);
      OUTPUT_CMD("MUL");
      break;

    case divide_op_NodeKind:
      math_expression(tree->sibling, funcTable, blockTable, line);
      OUTPUT_CMD("DIV");
      break;

    default:
      COMPILE_ERROR("unknow math expression", tree->line_no);
  }  
}

void identifier_assign(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line) {
  if (tree == NULL || funcTable == NULL || blockTable==NULL) NULL_ERROR
  // TODO: type check and symbol table check
  TreeNode *identifier = tree->child;
  TreeNode *assign = identifier->sibling;
  switch (assign->nodeKind){
    case true_NodeKind:
      OUTPUT_CMD("LDC 1");
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case false_NodeKind:
      OUTPUT_CMD("LDC 0");
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case math_expression_NodeKind:
      math_expression(assign->child, funcTable, blockTable, line);
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;
    
    case functioncall_NodeKind:
      functioncall(assign, funcTable, blockTable, line);
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case list_expression_NodeKind:

      break;

    default:
      printf("unresolved assign to the identifier in line: %d\n", assign->line_no);
  }
}

void blockGen(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line){
  if (tree == NULL || funcTable == NULL || blockTable==NULL) NULL_ERROR
  TreeNode *temp = tree->child;
  while (temp){
    switch(temp->nodeKind){
      case identifier_assign_NodeKind:
        identifier_assign(temp, funcTable, blockTable, line);
        break;

      case unary_assign_NodeKind:

        break;

      case define_assign_NodeKind:

        break;

      case if_statement_NodeKind:

        break;

      case for_statement_NodeKind:

        break;

      case while_statement_NodeKind:

        break;

      case do_statement_NodeKind:

        break;

      case functioncall_NodeKind:

        break;

      default:
        printf("unresolved statement type in line: %d\n", temp->line_no);
    }
    temp = temp->sibling;
  }
}

void funcGen(TreeNode *tree, FuncTable *funcTable, int *line) {
  if (tree == NULL || funcTable == NULL) NULL_ERROR
  if (tree->nodeKind == functiondef_NodeKind){
    //TODO: dulplicate function def check
    funcTable->returnNode = tree->child;
    printf("function :%s ",funcTable->returnNode->child->sibling->literal);
    TreeNode *temp = tree->child->sibling;
    // temp is funcbody
    if (temp->nodeKind == function_body_NodeKind){
      if (temp->child->nodeKind==parameter_list_NodeKind){
        if (funcTable->paramTable==NULL){
          addParam(temp->child, funcTable->paramTable);
        }
        temp = temp->child->sibling;
        if (temp!=block_NodeKind) printf("error detecting block: %d\n", temp->line_no);
        funcTable->blockTable = makeNewBlockTable();
        blockGen(temp, funcTable, funcTable->blockTable, line);
      }
    } else {
      NULL_ERROR
    }  
  }
}

void codeGen(TreeNode *tree, FuncTable *funcTable, int *line) {
  printf("tree: %s\n", nodeKindStr[tree->nodeKind]);
    if (tree == NULL|| tree->nodeKind!=file_NodeKind) return;
  TreeNode *root = tree;
  root = root->child;
  FuncTable *f_tail = funcTable;
  while (root) {
    if (root->nodeKind == main_function_NodeKind) {
      break;
    } else if (root->nodeKind == functiondef_list_NodeKind) {
      TreeNode *funcList = root->child;
      root = root->sibling;
      while(funcList) {
        funcGen(funcList, f_tail, line);
        FuncTable *temp = makeNewFuncTable();
        f_tail->sibling = temp;
        temp->head = funcTable;
        f_tail = temp;
        funcList = funcList->sibling;
        //TODO: has an additional empty funcTable;
      }
    }
  }
}

int codeGenBlock(TreeNode *tree, FuncTable *funcTable, BlockTable *blockTable){
  
}

void releaseVarTable(VarTable *t){

}

void releaseBlockTable(BlockTable *t){

}

void releaseFuncTable(FuncTable *t){

}
