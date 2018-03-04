#include <stdio.h>
#include <stdlib.h>

struct node {
	int num;
	struct node *next_node;
};

struct node *head=NULL;

void add_node(int num){
	struct node *n1, *temp;
	n1 = (struct node *)malloc(sizeof(struct node));
	if (!n1)
		printf("Failed to allocate memory to node\n");

	n1->num = num;
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
}

void print_list() {
	struct node *temp;
	temp = head;

	while (temp->next_node != NULL) {
		printf("Value in the node is %d\n",temp->num);
		temp = temp->next_node;
	}
	printf("Value in the node is %d\n", temp->num);
}

int main () {

	add_node(10);
	add_node(20);
	add_node(30);
	print_list();

return 0;
}
