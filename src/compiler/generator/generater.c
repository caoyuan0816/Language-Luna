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
			
				case "variable_NodeKind"
                    printf("ldv ");
					t->child
					child->sibling
					t->line_no
                    break;
				
				case "int_NodeKind":
					printf("ldc %s", t->line_no );
					t->int_NodeKind
					int_NodeKind->line_no
                    break;

                case "double_NodeKind":
					printf("ldc %s", t->line_no );
					double_NodeKind->type	
                    break;
                
				case "list_NodeKind":
					list_NodeKind->line_no
					list_NodeKind->child
					printf("ldc %s ", t->line_no );
                    break;	
					
				case "bool_NodeKind":
                    break;
					
				case "id_NodeKind":
                    printf("%d %s", seqNum++, "ldv" );
                    break;
					
				case "equal_expression_NodeKind":
                    break;
				
				case "greater_equal_NodeKind":
                    printf("ge" );
                    break;
					
				case "less_equal_NodeKind":
                    printf("%d %s", seqNum++, "le" );
                    break;
				

                case "greater_than_NodeKind":
                    printf("%d %s", seqNum++, "gt" );
                    break;
                    
                case "less_than_NodeKind":
                    printf("%d %s", seqNum++, "lt" );
                    break;
				
                case "not_equal_NodeKind":
                    printf("%d %s", seqNum++, "neq" );
                    break;
					
				case "increase_one_NodeKind":
                    break;
					
				case "decrease_one_NodeKind":
                    break;
					
				case "divide_op_NodeKind":
                    break;
					
				case "plus_op_NodeKind":
                    break;
					
				case "minus_op_NodeKind":
                    break;

				case "return_NodeKind":
                    break;					

				case "function_body_NodeKind":
                    break;

				case "parameter_list_NodeKind":
                    break;					

				case "functiondef_NodeKind":
                    break;	
 
				case "num_id_NodeKind":
                    break;	

				case "term_NodeKind":
                    break;	

				case "list_expression_NodeKind":
                    break;	

				case "false_NodeKind":
                    break;	

				case "true_NodeKind":
                    break;	

				case "bool_expression_NodeKind":
                    break;	

				case "brac_NodeKind":
                    break;	

				case "expression_NodeKind":
                    break;

				case "argument_list_NodeKind":
                    break;

				case "functioncall_NodeKind":
                    break;

				case "define_assign_NodeKind":
                    break;

				case "identifier_assign_NodeKind":
                    break;

				case "unary_assign_NodeKind":
                    break;

				case "else_statement_NodeKind":
                    break;

				case "if_statement_NodeKind":
                    break;

				case "math_expression_NodeKind":
                    break;

				case "functiondef_list_NodeKind":
                    break;

				case "file_NodeKind":
                    break;

				case "main_function_NodeKind":
                    break;
					
				case "block_NodeKind":
                    break;
					
				case "do_statement_NodeKind":
                    break;
					
				case "while_statement_NodeKind":
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