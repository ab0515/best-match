#include "qtree.h"

void print_greetings();
int valid_username(char s);
int print_friends (Node *parent,char *name);
void free_tree(QNode *root);

int main (int argc, char **argv){
	
	QNode *root = NULL;	
	char answer[MAX_LINE];	
	char name[MAX_LINE];
	

	Node * interests = NULL;

	if (argc < 2) {
        printf ("To run the program ./categorizer <name of input file>\n");
        return 1;
    }
	
    interests = get_list_from_file (argv[1]);
	
    if (interests == NULL)
        return 1;

	root = add_next_level (root,  interests);
	free_list (interests);

	//main application loop
	int break_x=0;
	int break_y=0;
	int break_z=0;
    while(1) { 
	 int total = 0;
	 int len = 0;
	 while(1) {
	 print_greetings();
    printf("Please enter your name. Type 'q' to quit.\n");
    while(1) {
    fgets(name, MAX_LINE, stdin);
	 name[strcspn(name, "\r\n")] = '\0';
    len = strlen(name);
    if (strcmp(name,"q")==0||strcmp(name,"Q")==0){
    	break_y=1;
    	break_z=1;
    	break;
    }
    else if(strcmp("\0",name)==0) {
     continue;
    } 
    else {
			if (len < 8 ) { // invalid length
				fprintf(stderr,"Sorry, the length of username should be at least 8.\n");
				printf("Please enter your name. Type 'q' to quit.\n");
				continue;
			} 
			else if (len >128 ) { // invalid length
				fprintf(stderr,"Sorry, the length of username should be at most 128.\n");
				printf("Please enter your name. Type 'q' to quit.\n");
				continue;
			} 
			else { // valid length
				total = 0;
				int i= 0;
				for (i = 0; i<len; i++) {	// check for alphanumeric
					if (valid_username(name[i]))
						total++;
				}

				if (total == len){
					 // success
					break; }
				else {
					fprintf(stderr,"Sorry, username only consists of alphanumeric characters.\n");
					printf("Please enter your name. Type 'q' to quit.\n");
				   continue;
				}
		   	}
	   }
    }
    if(break_y) break;
    Node *found;
    found = search_user(root,name);
    if(found == NULL) {
    QNode *temp = root;
    QNode *cur = NULL;

    while(temp != NULL) {
    int notvalid = 1;
	 int alen = 0;
	 while(notvalid) {
    printf("Do you like %s ?(y/n)\n",temp->question);
    scanf("%s",answer);
    alen = strlen(answer);
    if (alen>3) { // invalid length
				fprintf(stderr,"Sorry, the length of your answer should be at most 3.\n");
				continue;
			} 
	 else{
	 	if(answer[0]=='y'||answer[0]=='n'||answer[0]=='q'||answer[0]=='Y'||answer[0]=='N'||answer[0]=='Q'){
	 		break;
	 	}
	 	fprintf(stderr,"Sorry, the first letter of your answer should be 'y' or 'n' or 'q'.\n");
	 	continue;
	 }
    }
    if(answer[0]=='y'||answer[0]=='Y') {
    	cur = add_user(temp,1, name);
    }
    if(answer[0]=='n'||answer[0]=='N'){
    	cur = add_user(temp,0, name);
    	}
    if(answer[0]=='q'||answer[0]=='Q'){
    	break_x=1;
    	break_z=1;
    	break;
    	
      }
      temp = cur;	
      }
    found = search_user(root, name);

    }	
    if(break_x) break;
    if(strcmp(found->str,name)==0 && found->next==NULL){
    	printf("Sorry, no users with similar interests joined yet.\n");
    	
    }
    else {
    	int friend = 0;
    	printf("Friend recommendation for %s :\n",name);
    	friend = print_friends (found,name);
    	printf("You have total %d friend(s)!\n",friend);
 
    	}
    	
   }
   if(break_z) break;
	}
    //end of main loop - the user tyoped "q"
   print_qtree (root, 0);
   free_tree(root);
	return 0;
	
}

void print_greetings () {
	printf ("----------------------------------------------\n");
	printf ("Friend recommender system. Find people who are just like you!\n");
	printf ("CSC209 fall 2016 team. All rights reserved\n");
	printf ("----------------------------------------------\n");
}
int valid_username(char s) {
	if ((s >= 'a' && s <= 'z') ||
		(s >= 'A' && s <= 'Z') ||
		(s >= '0' && s <= '9')) {
		return 1;
	}
	return 0;
}
int print_friends (Node *parent, char *name) {
	int friends =0;
	if (parent == NULL){
		printf("NULL\n");
		return friends;}
	else {
		if(strcmp(parent->str,name)!=0) {
			friends++;
		printf("%s ", parent->str);}
		while (parent->next != NULL) {
			parent = parent->next;
			if(strcmp(parent->str,name)!=0) {
				friends++;
			printf("%s ", parent->str);}
		}
		printf ("\n");
		return friends;
	}
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
