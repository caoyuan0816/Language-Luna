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
  }#include "common.h"
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
    
    int seqNum = 0;
    void traversal(TreeNode *t){
        if(t->child != NULL ||t->sibling != NULL){
            switch (t->nodeKind) {
                case "greater_equal_NodeKind":
                    printf("%d %s", seqNum++, "ge" );
                    break;
                    
                case "functioncall_NodeKind":
                    seqNum = 0;
                    break;
                    
                case "not_equal_NodeKind":
                    printf("%d %s", seqNum++, "neq" );
                    break;
                    
                case "equal_NodeKind":
                    printf("%d %s", seqNum++, "eq" );
                    break;
                    
                case "less_equal_NodeKind":
                    printf("%d %s", seqNum++, "le" );
                    break;
                    
                case "greater_NodeKind":
                    printf("%d %s", seqNum++, "gt" );
                    break;
                    
                case "less_NodeKind":
                    printf("%d %s", seqNum++, "lt" );
                    break;
                    
                case "divide_op_NodeKind":
                    printf("%d %s", seqNum++, "div" );
                    break;
                case "mul_op_NodeKind":
                    printf("%d %s", seqNum++, "mul" );
                    break;
                case "plus_op_NodeKind":
                    printf("%d %s", seqNum++, "add" );
                    break;
                case "minus_op_NodeKind":
                    printf("%d %s", seqNum++, "sub" );
                    break;
                case "return_NodeKind":
                    printf("%d %s", seqNum++, "ret" );
                    break;
                case "id_NodeKind":
                    printf("%d %s", seqNum++, "ldv" );
                    break;
                case "int_NodeKind":
                    printf("%d %s", seqNum++, "ldc" );
                    break;
                case "double_NodeKind":
                    printf("%d %s", seqNum++, "ldc" );
                    break;
                    
                    
                default:
                    break;
                    
                    
            }
            traversal(t->child);
            traversal(t->sibling);
        }
    }
    
    
    
    
    
    
    int errorOccur = 0;


  releaseNode(t->sibling);
  releaseNode(t->child);

  free(t);
}

char nodeKindStr[][40] = {
  "varibale"
};

int errorOccur = 0;
