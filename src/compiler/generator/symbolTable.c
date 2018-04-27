#include "symbolTable.h"

#define NULL_ERROR {printf("error null in line: %d\n", tree->line_no); exit(1); }
#define OUTPUT_CMD(X) {if (checkFlag==0) {printf("%d ", *line); (*line)++; printf(X); printf("\n");} else (*line)++;}

#define OUTPUT_CMD_P(X,Y) {if (checkFlag==0){printf("%d ", *line); (*line)++; printf(X, Y); printf("\n");} else (*line)++;} 
#define COMPILE_ERROR(X,Y) {printf("error: line %d ", Y); printf(X); printf("\n");}

void blockGen(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag);

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

void functioncall(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){

}

void mathExpression(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  if (tree == NULL) return;
  switch (tree->nodeKind){
    case term_NodeKind:
      mathExpression(tree->sibling, funcTable, blockTable, line, checkFlag);
      mathExpression(tree->child, funcTable, blockTable, line, checkFlag);
      break;

    case plus_op_NodeKind:
      mathExpression(tree->sibling, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD("ADD");
      break;

    case minus_op_NodeKind:
      mathExpression(tree->sibling, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD("SUB");
      break;

    case double_NodeKind:
    case int_NodeKind:
      mathExpression(tree->sibling, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD_P("LDC %s", tree->literal);
      break;

    case id_NodeKind:
      mathExpression(tree->sibling, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD_P("LDV %s", tree->literal);
      break;

    case mul_op_NodeKind:
      mathExpression(tree->sibling, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD("MUL");
      break;

    case divide_op_NodeKind:
      mathExpression(tree->sibling, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD("DIV");
      break;

    default:
      COMPILE_ERROR("unknow math expression", tree->line_no);
  }  
}

void identifierAssign(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag) {
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
      mathExpression(assign->child, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;
    
    case functioncall_NodeKind:
      functioncall(assign, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case list_expression_NodeKind:

      break;

    default:
      printf("unresolved assign to the identifier in line: %d\n", assign->line_no);
  }
}

void defineAssign(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  if (tree == NULL || funcTable == NULL || blockTable==NULL) NULL_ERROR
  // TODO: type check and symbol table check
  TreeNode *identifier = tree->child->child->sibling;
  TreeNode *assign = tree->child->sibling;
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
      mathExpression(assign->child, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;
    
    case functioncall_NodeKind:
      functioncall(assign, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case list_expression_NodeKind:

      break;

    default:
      printf("unresolved assign to the identifier in line: %d\n", assign->line_no);
  }
}

void expression(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  if (tree == NULL || funcTable == NULL || blockTable==NULL) NULL_ERROR
  switch(tree->nodeKind){
    case math_expression_NodeKind:
      mathExpression(tree->child, funcTable, blockTable, line, checkFlag);
      break;

    case functioncall_NodeKind:
      functioncall(tree, funcTable, blockTable, line, checkFlag);
      break;

    default:
      printf("line %d : unresolved expression\n", tree->line_no);
  }
}

void boolExpression(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  if (tree == NULL || funcTable == NULL || blockTable==NULL) NULL_ERROR
  switch(tree->nodeKind){
    case true_NodeKind:
      OUTPUT_CMD("LDC 1");
      break;

    case false_NodeKind:
      OUTPUT_CMD("LDC 0");
      break;

    case bool_expression_NodeKind:
      expression(tree->child->sibling, funcTable, blockTable, line, checkFlag);
      expression(tree->child->sibling->sibling, funcTable, blockTable, line, checkFlag);
      switch(tree->child->nodeKind){
        case equal_expression_NodeKind:
          OUTPUT_CMD("EQ");
          break;

        case greater_equal_NodeKind:
          OUTPUT_CMD("GE");
          break;

        case less_equal_NodeKind:
          OUTPUT_CMD("LE");
          break;

        case less_than_NodeKind:
          OUTPUT_CMD("LT");
          break;

        case greater_than_NodeKind:
          OUTPUT_CMD("GE");
          break;

        case not_equal_NodeKind:
          OUTPUT_CMD("NEQ");
          break;

        default:
          printf("line %d :boolean operator undefined!\n", tree->child->line_no);
      }
      break;

    default:
      printf("bool expression generation failed: %d\n", tree->line_no);
  }
}

void ifStatement(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  TreeNode *temp = tree->child;
  boolExpression(temp, funcTable, blockTable, line, checkFlag);
  temp = temp->sibling;
  OUTPUT_CMD_P("JZ %d", temp->end_ins_line);
  blockGen(temp, funcTable, blockTable, line, checkFlag);
  if (checkFlag==1){
    temp->end_ins_line = *line;
  }
  if (temp->sibling&&temp->sibling->nodeKind==else_statement_NodeKind){
    blockGen(temp->sibling->child, funcTable, blockTable, line, checkFlag);
  }
}

void blockGen(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  if (tree == NULL || funcTable == NULL || blockTable==NULL) NULL_ERROR
  TreeNode *temp = tree->child;
  while (temp){
    switch(temp->nodeKind){
      case identifier_assign_NodeKind:
        //TODO: type check
        identifierAssign(temp, funcTable, blockTable, line, checkFlag);
        break;

      case unary_assign_NodeKind:
        
        break;

      case define_assign_NodeKind:
        //TODO: type check
        defineAssign(temp, funcTable, blockTable, line, checkFlag);
        break;

      case if_statement_NodeKind:
        ifStatement(temp, funcTable, blockTable, line, checkFlag);
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

void funcGen(TreeNode *tree, FuncTable *funcTable, int *line, int checkFlag) {
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
        if (temp->nodeKind!=block_NodeKind) printf("error detecting block: %d\n", temp->line_no);
        funcTable->blockTable = makeNewBlockTable();
        blockGen(temp, funcTable, funcTable->blockTable, line, checkFlag);
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
        int start_line = *line;
        funcGen(funcList, f_tail, line, 1);
        *line = start_line;
        funcGen(funcList, f_tail, line, 0);
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
  return 0;
}

void releaseVarTable(VarTable *t){

}

void releaseBlockTable(BlockTable *t){

}

void releaseFuncTable(FuncTable *t){

}
