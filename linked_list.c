#include <stdio.h>
#include <stdlib.h>

struct node {
	int num;
	struct node *next_node;
};

struct node *head=NULL;

/*
* int add_node(int num)
* Adds a node at the end of the list.
* Takes data as an argument and return -1 if failed to get memory
* else return 1.
*/
int add_node(int num){
	struct node *n1, *temp;
	
	//Allocate memory to the new node
	n1 = (struct node *)malloc(sizeof(struct node));
	if (!n1) {
		printf("Failed to allocate memory to node\n");
		return -1;
	}

	n1->num = num;
	//Check if its the first node in the list
	if (head == NULL)
	{
		n1->next_node = NULL;
		head = n1;
	}
	else {
		temp = head;
		while(temp->next_node != NULL)
			temp = temp->next_node;
		temp->next_node = n1;
		n1->next_node = NULL;
	}
	return 1;
}


/*
* void delete_node()
* Deletes the last node int the list
*/
void delete_node() {
	struct node *temp;
	temp = head;

	// check if head is NULL in that case there is nothing to delete
	if (temp == NULL) {
		printf("No node to delete\n");
	}
	//Check if the current node is the only node in the list
	else if (temp->next_node == NULL) {
		printf("Deleting last node\n");
		free(temp);
		head = NULL;
	}
	else {
		// Go till the second last node of the list
		while (temp->next_node->next_node != NULL)
			temp =  temp->next_node;
	
		//Free the last node using pointer of second last node
		printf("Deleting last node\n");
		free(temp->next_node);
		//make second last node as last node by setting its next_node to NULL
		temp->next_node = NULL;
	}
}


/*
* void print_list()
* Prints the linked list
*/
void print_list() {
	struct node *temp;
	temp = head;

	if (temp == NULL) {
		printf("Linked list is empty\n");
	}
	else {
		while (temp->next_node != NULL) {
			printf("Value in the node is %d\n",temp->num);
			temp = temp->next_node;
		}
		printf("Value in the node is %d\n", temp->num);
	}
}

int main () {

	int ret=0;
	ret = add_node(10);
	if (!ret)
		return -1;
	ret = add_node(20);
	if (!ret)
		return -1;
	ret = add_node(30);
	if (!ret) 
		return -1;
	print_list();

	delete_node();
	delete_node();
	delete_node();

	print_list();



return 0;
}
