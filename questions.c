#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "questions.h"

#define MAX_LEN 80

Node *new_node(char *info){
   if(info == NULL)
		return NULL;
	Node *i = malloc(sizeof(Node));
	size_t len = strlen(info);
	i->str = malloc(len+1);
	strcpy(i->str, info);
        i->next = 0;
	return i;
}

Node * get_list_from_file (char *input_file_name) {
	FILE *fp = fopen(input_file_name, "r");
	Node * head = NULL;
	Node * cur = NULL;
	char line[MAX_LEN+1];
    //read lines and add to the list
    if(fp==NULL) {
    	fprintf(stderr,"File does not exist!\n");
    	exit(0);
    }
    fgets(line, MAX_LEN+1, fp);
    line[strcspn(line, "\r\n")] = '\0';
    head= new_node(line);
    cur = head;

    while(fgets(line, MAX_LEN+1, fp)!=NULL) {
    	if (cur !=	NULL){
    		Node *i = NULL;
    		line[strcspn(line, "\r\n")] = '\0';
    		i = new_node(line);
    		cur->next = i;
    		
    	}
    	
    	cur= cur->next;
    }
    fclose(fp);
	return head;
}

void print_list (Node *head) {
	Node *temp;
	Node *i = head;
	while (i != NULL){
		temp = i;
		i = i->next;
		printf("%s\n", temp->str);
	}
	head = NULL;
}

void free_list (Node *head) {
	Node *temp;
	Node *i = head;
	while (i != NULL){
		temp = i;
		i = i->next;
		free(temp->str);
		free(temp);
	}
	head = NULL;
}
