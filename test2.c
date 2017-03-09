#include "qtree.h"
void free_tree(QNode *root);
int main (int argc, char ** argv) {
   QNode *root = NULL;
	Node *q_list;
    
    if (argc < 2) {
        printf ("To run the program ./test2 <name of input file>\n");
        return 1;
    }
    
    q_list = get_list_from_file (argv[1]);
    
    if (q_list == NULL) {
        printf ("The list is empty\n");
        return 1;
    }
    
    //that is only the first test to test creation of the question tree
    root = add_next_level (root, q_list);
	 print_qtree (root, 0);
    
    
    //your tests here
    int count=0;
    Node *pt;
    pt=q_list;
	 while (pt != NULL) {
			count++;
			pt= pt->next;
	}
    QNode *temp = root;
    QNode *cur = NULL;
    char *ptr;
    if(count != (argc-3)){
    	fprintf(stderr,"Number of answers doesn't match the number of questions!\n");
    	free_list(q_list);
    	free_tree(root);
    	return 1;
    }
    int i = 0;
    for (i =3; i<argc; i++){
    	if(strcmp(argv[i],"0")!=0 && strcmp(argv[i],"1")!=0) {
    		fprintf(stderr,"Invalid Answer!\n");
    		free_list(q_list);
    		free_tree(root);
    		return 1;
    	}
    	cur = add_user(temp, (int)strtol(argv[i], &ptr, 10), argv[2]);
    	if(cur != NULL){
    		temp = cur;
    	}
    }
    print_qtree (root, 0);
    free_tree(root);
    free_list(q_list);
    return 0;
}
void free_tree(QNode *root){
	if (root->node_type == LEAF){
	    free_list(root->children[0].fchild);
	    free_list(root->children[1].fchild);
		}
	else {
			if (root->children[0].qchild != NULL){ //left node
				
				free_tree(root->children[0].qchild);
			}	
				
			if (root->children[1].qchild != NULL){ // right node
				
				free_tree(root->children[1].qchild);
			}
		}
	free(root->question);
	free(root);	
}
