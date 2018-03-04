#include <stdio.h>
#include <stdlib.h>

struct node {
	int num;
	struct node *next_node;
};

struct node *tos=NULL;	//Pointer to top of the stack
struct node *head=NULL; //Pointer to start of linked list

/*
* int push(int num)
* Pushes data to top of the stack
* Takes data as an argument and return -1 if failed to get memory
* else return 1.
*/
int push(int num){
	struct node *n1;
	
	//Allocate memory to the new node
	n1 = (struct node *)malloc(sizeof(struct node));
	if (!n1) {
		printf("Failed to allocate memory to node\n");
		return -1;
	}
	
	printf("Pushing data %d to stack\n", num);
	n1->num = num;
	//Check if its the first node in the list
	if (tos == NULL || head == NULL)
	{
		n1->next_node = NULL;
		tos = n1;
		head = n1;
	}
	else {
		while(tos->next_node != NULL)
			tos = tos->next_node;
		tos->next_node = n1;
		n1->next_node = NULL;
		tos = n1;
	}
	return 1;
}


/*
* void pop()
* Pop data out of the stack
*/
void pop() {
	struct node *temp;
	temp = head;

	//Check if tos or head is NULL 
	if (head == NULL || tos == NULL) {
		printf("Stack is empty\n");
	}
	else if (temp->next_node == NULL) {
		// check if it is last element in the stack, read value then set tos and head back to NULL
		printf("Popping data %d out of stack\n", temp->num);
		free(temp);
		head = NULL;
		tos = NULL;
	}
	else {
		// Go till the second element from tos
		while (temp->next_node->next_node != NULL)
			temp =  temp->next_node;
	
		//Read data from tos and free element and change tos to temp
		printf("Popping data %d out of stack\n", tos->num);
		free(tos);
		tos = temp;
		//make tos->next_node NULL
		temp->next_node = NULL;
	}
}

int main () {

	int ret=0;
	ret = push(10);
	if (!ret)
		return -1;
	ret = push(20);
	if (!ret)
		return -1;
	ret = push(30);
	if (!ret) 
		return -1;

	pop();
	push(40);
	pop();
	pop();
	pop();

return 0;
}
