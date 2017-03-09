#include "qtree.h"

QNode *add_next_level (QNode *current, Node *list_node) {
	int str_len;
	
	str_len = strlen (list_node->str);
	current = (QNode *) calloc (1, sizeof(QNode));

	current->question =  (char *) calloc (str_len +1, sizeof(char ));
	strncpy ( current->question, list_node->str, str_len );
	current->question [str_len] = '\0';  
	current->node_type = REGULAR;
	
	if (list_node->next == NULL) {
		current->node_type = LEAF;
		return current;
	}
	
	current->children[0].qchild = add_next_level ( current->children[0].qchild, list_node->next);
	current->children[1].qchild = add_next_level ( current->children[1].qchild, list_node->next);

	return current;
}
void dfs(QNode *root){
	QNode *cur = root;
	if (cur->node_type == LEAF)
		return;
	else {
		if (cur != NULL) {
			if (cur->children[0].qchild != NULL){ //left node
				
				dfs(cur->children[0].qchild);
			}	
				
			if (cur->children[1].qchild != NULL){ // right node
				
				dfs(cur->children[1].qchild);
			}
		}
	}	
}

QNode *add_user(QNode *cur, int ans, char *username) {
	// ans: no = child 0
	// ans: yes = child 1
	int index;
	if (ans == 0) 
		index = 0;
	else 
		index = 1;

	if (cur->node_type != LEAF){
		return cur->children[index].qchild;
	}
	else{
		if (cur->children[index].fchild == NULL){
			cur->children[index].fchild = new_node(username);
		}
		else {
			Node *temp;
			temp = cur->children[index].fchild;
			Node *newnode;
	        newnode = new_node(username);
	        newnode->next = temp;
	        cur->children[index].fchild = newnode;
		}
	}
	return NULL;
}

Node *search_user(QNode *root, char *username){
	QNode *cur = root;
	int flagl=0;
	int flagr=0;
	Node *result1 = NULL;
	Node *result2 = NULL;
	if (cur->node_type == LEAF) {
		flagl = loop_ll(cur->children[0].fchild, username);
		flagr = loop_ll(cur->children[1].fchild, username);

		if (flagl == 1){
			return cur->children[0].fchild;}
		else if(flagr == 1){
			return cur->children[1].fchild;
		}
		else {
			return 0;
		}
	}
		
	else {
				result1 = search_user(cur->children[0].qchild, username);	
			// right node
				result2 = search_user(cur->children[1].qchild, username);
				if(result1){

					return result1;
				}
				else if(result2){
					return result2;
				}
				else {

					return 0;
					}

			}
		
	
	return 0;
}

// helper function to loop through linked list
int loop_ll(Node *cur, char *name) {
	Node *temp=cur;
	while (temp != NULL) {
		if (strcmp(temp->str, name) == 0)
			return 1;
		else {
			temp= temp-> next;
		}
	}
	return -1;
}
	
void print_qtree (QNode *parent, int level) {
	int i;
	for (i=0; i<level; i++)
		printf("\t");
	
	printf ("%s type:%d\n", parent->question, parent->node_type);
	if(parent->node_type == REGULAR) {
		print_qtree (parent->children[0].qchild, level+1);
		print_qtree (parent->children[1].qchild, level+1);
	}//Task
	else { //leaf node
		for (i=0; i<(level+1); i++)
			printf("\t");
		print_users (parent->children[0].fchild);
		for (i=0; i<(level+1); i++)
			printf("\t");
		print_users (parent->children[1].fchild);
	}
}

void print_users (Node *parent) {
	if (parent == NULL)
		printf("NULL\n");
	else {
		printf("%s, ", parent->str);
		while (parent->next != NULL) {
			parent = parent->next;
			printf("%s, ", parent->str);
		}
		printf ("\n");
	}
}
