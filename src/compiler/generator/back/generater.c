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
					t->variable_NodeKind
					variable_NodeKind->child
					child->sibling
					t->line_no
					printf("ldv %s", sibling->literal);
                    break;
				
				case "int_NodeKind":
					t->int_NodeKind
					int_NodeKind->type
					t->line_no
					printf("int %d", t->literal);
                    break;

                case "double_NodeKind":
					t->double_NodeKind
					double_NodeKind->type
					t->line_no	
					printf("double %lf", t->literal);
                    break;
                
				case "list_NodeKind":
					t->list_NodeKind
					list_NodeKind->type
					t->line_no
					printf("list %s", t->literal);
                    break;	
					
				case "bool_NodeKind":
					t->bool_NodeKind
					bool_NodeKind->type
					t->line_no
					printf("bool %s", t->literal);
                    break;
					
				case "id_NodeKind":
					t->id_NodeKind
					t->line_no
					printf("%s", t->literal);
                    break;
					
				case "equal_expression_NodeKind":
					t->equal_expression_NodeKind
					t->line_no
					printf("eq %s", t->literal);
                    break;
				
				case "greater_equal_NodeKind":
                    t->greater_equal_NodeKind
					t->line_no
					printf("ge %s", t->literal);
                    break;
					
				case "less_equal_NodeKind":
                    t->less_equal_NodeKind
					t->line_no
					printf("le %s", t->literal);
                    break;
				

                case "greater_than_NodeKind":
                    t->greater_equal_NodeKind
					t->line_no
					printf("gt %s", t->literal);
                    break;
                    
                case "less_than_NodeKind":
                    t->less_equal_NodeKind
					t->line_no
					printf("lt %s", t->literal);
                    break;
				
                case "not_equal_NodeKind":
                    t->not_equal_NodeKind
					t->line_no
					printf("neq %s", t->literal);
                    break;
					
				case "increase_one_NodeKind":
                    t->increase_one_NodeKind
					t->line_no
					printf("inco %s", t->literal);
                    break;
					
				case "decrease_one_NodeKind":
                    t->decrease_one_NodeKind
					t->line_no
					printf("deco %s", t->literal);
                    break;
					
				case "divide_op_NodeKind":
				    t->divide_op_NodeKind
					t->line_no
					printf("div %s", t->literal);
                    break;
					
				case "mul_op_NodeKind":
				    t->mul_op_NodeKind
					t->line_no
					printf("mul %s", t->literal);
                    break;
					
				case "plus_op_NodeKind":
				    t->plus_op_NodeKind
					t->line_no
					printf("add %s", t->literal);
                    break;
					
				case "minus_op_NodeKind":
				    t->minus_op_NodeKind
					t->line_no
					printf("sub %s", t->literal);
                    break;

				case "return_NodeKind":
					t->minus_op_NodeKind
					t->child
					t->line_no
					node_1->line_no
					releaseNode(minus_op_NodeKind)
                    break;					

				case "function_body_NodeKind":
					t->function_body_NodeKind
					t->child=temp
                    break;

				case "parameter_list_NodeKind":
					temp->parameter_list_NodeKind
					t->line_no
                    break;					

				case "functiondef_NodeKind":
					t->function_body_NodeKind
					t->child
					child->sibling
					function_body_NodeKind->line_no
					t->line_no
					releaseNode(function_body_NodeKind)
                    break;	
 
				case "num_id_NodeKind":
					t->num_id_NodeKind
					printf("%s", t->literal)
					
                    break;	

				case "term_NodeKind":
                    break;	

				case "list_expression_NodeKind":
                    break;	

				case "false_NodeKind":
					t->false_NodeKind
					t->line_no
                    break;	

				case "true_NodeKind":
					t->true_NodeKind
                    break;	

				case "bool_expression_NodeKind":
                    break;	

				case "brac_NodeKind":
					t->brac_NodeKind
					printf("(",")")
                    break;	

				case "expression_NodeKind":
                    break;

				case "argument_list_NodeKind":
                    break;

				case "functioncall_NodeKind":
					t->functioncall_NodeKind
					t->child
					child->sibling
					t->line_no
                    break;

				case "define_assign_NodeKind":
                    break;

				case "identifier_assign_NodeKind":
                    break;

				case "unary_assign_NodeKind":
					t->unary_assign_NodeKind
					t->child
					child->sibling
					t->line_no
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
