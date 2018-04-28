#include "symbolTable.h"

#define NULL_ERROR {printf("error null in line: %d\n", tree->line_no); exit(1); }

FILE *out_fp;

#ifdef _LUNAC_DEBUG_

#define OUTPUT_CMD(X) {if (checkFlag==0) {fprintf(out_fp, "%d ", (*line)); (*line)++; fprintf(out_fp, X); fprintf(out_fp, "\n");} else (*line)++;}
#define OUTPUT_CMD_P(X,Y) {if (checkFlag==0){fprintf(out_fp, "%d ", *line); (*line)++; fprintf(out_fp, X, Y); fprintf(out_fp, "\n");} else (*line)++;}
#define COMPILE_ERROR(X,Y) {fprintf(out_fp, "error: line %d ", Y); fprintf(out_fp, X); fprintf(out_fp, "\n");}
#define FUNC_CALL_CMD(X,Y) {if (checkFlag==0){fprintf(out_fp, "%d ", *line); (*line)++; fprintf(out_fp, "CALL "); fprintf(out_fp, "%s %d\n", X, Y);} else (*line)++;}
#define UNRESOLVED_REF(X, Y){ fprintf(stderr, "error line %d: unresolved reference %s\n", Y, X);}
#define DULP_DEF_ERROR(X, Y){ fprintf(stderr, "error line %d: dulplicate definition of %s\n", Y, X);}

#else

#define OUTPUT_CMD(X) {if (checkFlag==0) { (*line)++; fprintf(out_fp, X); fprintf(out_fp, "\n");} else (*line)++;}
#define OUTPUT_CMD_P(X,Y) {if (checkFlag==0){ (*line)++; fprintf(out_fp, X, Y); fprintf(out_fp, "\n");} else (*line)++;}
#define COMPILE_ERROR(X,Y) {fprintf(out_fp, "error: line %d ", Y); fprintf(out_fp, X); fprintf(out_fp, "\n");}
#define FUNC_CALL_CMD(X,Y) {if (checkFlag==0){ (*line)++; fprintf(out_fp, "CALL "); fprintf(out_fp, "%s %d\n", X, Y);} else (*line)++;}
#define UNRESOLVED_REF(X, Y){ fprintf(stderr, "error line %d: unresolved reference %s\n", Y, X);}
#define DULP_DEF_ERROR(X, Y){ fprintf(stderr, "error line %d: dulplicate definition of %s\n", Y, X);}

#endif
#include <stdbool.h>

void blockGen(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag);
void expression(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag);

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

  t->id = NULL;
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

bool inVarTable(const char *id, const VarTable *varTable){
  if (varTable==NULL) return false;
  if (strcmp(varTable->id, id)==0||inVarTable(id, varTable->sibling)) return true;
  return false;
}

bool inBlockTable(const char *id, const BlockTable *blockTable){
  if (blockTable==NULL) return false;
  if (inVarTable(id, blockTable->varTable)) return true;
  return false;
}

bool inFuncTable(const char *id, const FuncTable *funcTable){
  if (funcTable==NULL) return false;
  if (inVarTable(id, funcTable->paramTable)) return true;
  return false;
}

void addVarBlockTable(char *id, BlockTable *blockTable){
  VarTable *temp = makeNewVarTable();
  temp->id = id;
  temp->sibling = blockTable->varTable;
  blockTable->varTable = temp;
}

void checkIdentifier(const char *id, const FuncTable *funcTable, int line_no, int checkFlag){
  if (checkFlag==0) return;
  if (funcTable==NULL||funcTable->blockTable==NULL) UNRESOLVED_REF(id, line_no);
  if (inFuncTable(id, funcTable)) return;
  if (inBlockTable(id, funcTable->blockTable)) return;
  UNRESOLVED_REF(id, line_no);
}

void addParam(TreeNode *tree, FuncTable *funcTable, int checkFlag) {
  TreeNode *temp = tree->child;
  while (temp){
    if (checkFlag==0){
      fprintf(out_fp, " %s", temp->child->sibling->literal);
    } else {
      if (inFuncTable(temp->child->sibling->literal, funcTable)){
        DULP_DEF_ERROR(temp->child->sibling->literal, temp->child->sibling->line_no);
      } else {
        VarTable *varTableTemp = makeNewVarTable();
        varTableTemp->id = temp->child->sibling->literal;
        varTableTemp->sibling = funcTable->paramTable;
        funcTable->paramTable = varTableTemp;
      }
    }
    temp = temp->sibling;
  }
  if (checkFlag==0) fprintf(out_fp, "\n");
}

void addVar(TreeNode *tree, VarTable *varTable) {
  if (tree == NULL) return;
  // TODO: add type check if still have time
  if (tree->nodeKind==variable_NodeKind){
    TreeNode *temp = tree->child;
    VarTable *table = varTable;
    while (temp!=NULL){
      if(table->id==NULL){
        table->id = temp->sibling->literal;
      } else{

      }
    }
  }
}

void expressionList(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag, int *paramNum){
  if (tree==NULL) return;
  (*paramNum)++;
  expressionList(tree->sibling, funcTable, blockTable, line, checkFlag, paramNum);
  expression(tree, funcTable, blockTable, line, checkFlag);
}

void functioncall(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  //TODO: variable number and type check
  int paramNum = 0;
  TreeNode *temp = tree->child->sibling;
  if (temp->nodeKind==argument_list_NodeKind){
    temp = temp->child;
    expressionList(temp, funcTable, blockTable, line, checkFlag, &paramNum);
  }

  FUNC_CALL_CMD(tree->child->literal, paramNum);
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

    case functioncall_NodeKind:
      mathExpression(tree->sibling, funcTable, blockTable, line, checkFlag);
      functioncall(tree, funcTable, blockTable, line, checkFlag);
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
  checkIdentifier(identifier->literal, funcTable, identifier->line_no, checkFlag);
  switch (assign->nodeKind){
    case true_NodeKind:
      OUTPUT_CMD("LDC true");
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case false_NodeKind:
      OUTPUT_CMD("LDC false");
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case math_expression_NodeKind:
      mathExpression(assign->child, funcTable, blockTable, line, checkFlag);
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
  if (checkFlag){
    if (inBlockTable(identifier->literal, blockTable)){
      DULP_DEF_ERROR(identifier->literal, identifier->line_no);
    } else {
      addVarBlockTable(identifier->literal, blockTable);
    }
  }
  switch (assign->nodeKind){
    case true_NodeKind:
      OUTPUT_CMD("LDC true");
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case false_NodeKind:
      OUTPUT_CMD("LDC false");
      OUTPUT_CMD_P("ASN %s", identifier->literal);
      break;

    case math_expression_NodeKind:
      mathExpression(assign->child, funcTable, blockTable, line, checkFlag);
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

    default:
      printf("line %d : unresolved expression\n", tree->line_no);
  }
}

void boolExpression(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  if (tree == NULL || funcTable == NULL || blockTable==NULL) NULL_ERROR
  switch(tree->nodeKind){
    case true_NodeKind:
      OUTPUT_CMD("LDC true");
      break;

    case false_NodeKind:
      OUTPUT_CMD("LDC false");
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
          OUTPUT_CMD("GT");
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

void whileStatement(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  if (checkFlag==1){
    tree->child->start_ins_line = *line;
  }
  boolExpression(tree->child, funcTable, blockTable, line, checkFlag);
  OUTPUT_CMD_P("JZ %d", tree->child->sibling->end_ins_line);
  blockGen(tree->child->sibling, funcTable, blockTable, line, checkFlag);
  OUTPUT_CMD_P("JMP %d", tree->child->start_ins_line);
  if (checkFlag==1){
    tree->child->sibling->end_ins_line = *line;
  }
}

void forStatement(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  if (tree == NULL || funcTable == NULL || blockTable==NULL) NULL_ERROR
  TreeNode *temp = tree->child;
  switch(temp->sibling->nodeKind){
    case int_NodeKind:
      OUTPUT_CMD_P("LDC %s", temp->sibling->literal);
      if (checkFlag == 1){
         temp->start_ins_line = *line;
      }
      OUTPUT_CMD_P("ASN %s", temp->literal);
      OUTPUT_CMD_P("LDV %s", temp->literal);
      OUTPUT_CMD_P("LDC %s", temp->sibling->sibling->literal);
      OUTPUT_CMD("LT");
      OUTPUT_CMD_P("JZ %d", temp->end_ins_line);
      blockGen(temp->sibling->sibling->sibling->sibling, funcTable, blockTable, line, checkFlag);
      OUTPUT_CMD_P("LDV %s", temp->literal);
      OUTPUT_CMD_P("LDC %s", temp->sibling->sibling->sibling->literal);
      OUTPUT_CMD("ADD");
      OUTPUT_CMD_P("JMP %d", temp->start_ins_line);
      if (checkFlag == 1){
        temp->end_ins_line = *line;
      }

      break;

    case list_expression_NodeKind:
      break;

    case id_NodeKind:
      break;

    default:
      printf("line %d unresolved for statement\n", temp->line_no);
  }
}

void returnStatement(const TreeNode *tree, const FuncTable *funcTable, BlockTable *blockTable, int *line, int checkFlag){
  TreeNode *temp = tree->child;
  mathExpression(temp->child, funcTable, blockTable, line, checkFlag);
  OUTPUT_CMD("RET");
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
        OUTPUT_CMD_P("LDV %s", temp->child->sibling->literal);
        if (temp->child->nodeKind==increase_one_NodeKind){
          OUTPUT_CMD("LDC 1");
        } else if (temp->child->nodeKind==decrease_one_NodeKind){
          OUTPUT_CMD("LDC -1");
        }
        OUTPUT_CMD("ADD");
        OUTPUT_CMD_P("ASN %s", temp->child->sibling->literal);
        break;

      case define_assign_NodeKind:
        //TODO: type check
        defineAssign(temp, funcTable, blockTable, line, checkFlag);
        break;

      case if_statement_NodeKind:
        ifStatement(temp, funcTable, blockTable, line, checkFlag);
        break;

      case for_statement_NodeKind:
        forStatement(temp, funcTable, blockTable, line, checkFlag);
        break;

      case while_statement_NodeKind:
        whileStatement(temp, funcTable, blockTable, line, checkFlag);
        break;

      case do_statement_NodeKind:
        blockGen(temp->child, funcTable, blockTable, line, checkFlag);
        break;

      case functioncall_NodeKind:
        functioncall(temp, funcTable, blockTable, line, checkFlag);
        break;

      case return_NodeKind:
        returnStatement(temp, funcTable, blockTable, line, checkFlag);
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
    if (checkFlag==0) fprintf(out_fp, "%s",funcTable->returnNode->child->sibling->literal);
    TreeNode *temp = tree->child->sibling;
    // temp is funcbody
    if (temp->nodeKind == function_body_NodeKind){
      if (temp->child->nodeKind==parameter_list_NodeKind){
        addParam(temp->child, funcTable, checkFlag);
        temp = temp->child->sibling;
        if (temp->nodeKind!=block_NodeKind) printf("error detecting block: %d\n", temp->line_no);
        if (funcTable->blockTable==NULL) funcTable->blockTable = makeNewBlockTable();
        blockGen(temp, funcTable, funcTable->blockTable, line, checkFlag);
      }
    } else {
      NULL_ERROR
    }
  }
}

void codeGen(TreeNode *tree, FuncTable *funcTable, int *line, char *inputFilePath) {
  //Setting output file path
  //Will automatically generate output file to input file's directory
  char outputFilePath[256];
  memcpy(outputFilePath, &inputFilePath[0], strlen(inputFilePath)-3);
  memcpy(outputFilePath + strlen(inputFilePath)-3, ".luo", 4);
  outputFilePath[strlen(inputFilePath)+1] = '\0';
  #ifdef _LUNAC_DEBUG_
  printf("Saving to :%s\n", outputFilePath);
  #endif

  out_fp = fopen(outputFilePath, "w");
  if(out_fp == NULL){
    printf("Output file cannot be opened. Please check your file path.\n");
    exit(1);
  }

  if (tree == NULL|| tree->nodeKind!=file_NodeKind) return;
  TreeNode *root = tree;
  root = root->child;
  FuncTable *f_tail = funcTable;
  while (root) {
    if (root->nodeKind == main_function_NodeKind) {
      fprintf(out_fp, "main\n");
      int start_line = *line;
      if (f_tail->blockTable==NULL)
        f_tail->blockTable = makeNewBlockTable();
      blockGen(root->child, f_tail, f_tail->blockTable, line, 1);
      *line = start_line;
      blockGen(root->child, f_tail, f_tail->blockTable, line, 0);

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
  fprintf(out_fp, "HALT\n");

  //Closing output file
  fclose(out_fp);
  return;
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
