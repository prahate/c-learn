#include <stdio.h>
#include <stdlib.h>

struct node {
	int num;
	struct node *next_node;
};

struct node *front_q = NULL;	//Pointer front node of queue
struct node *rear_q = NULL; 	//Pointer rear node of queue

/*
* int enqueue(int num)
* Enqueues data to the queue
* Takes data as an argument and return -1 if failed to get memory
* else return 1.
*/
int enqueue(int num){
	struct node *n1, *temp;
	
	//Allocate memory to the new node
	n1 = (struct node *)malloc(sizeof(struct node));
	if (!n1) {
		printf("Failed to allocate memory to node\n");
		return -1;
	}
	
	printf("Enqueuing data %d to queue\n", num);
	n1->num = num;
	//Check if its the first node in the list
	if (front_q == NULL || rear_q == NULL )
	{
		n1->next_node = NULL;
		front_q = n1;
		rear_q = n1;
	}
	else {
		temp = rear_q;
		while(temp->next_node != NULL)
			temp = temp->next_node;
		temp->next_node = n1;
		n1->next_node = NULL;
		front_q = temp;
	}
	return 1;
}


/*
* void dequeue()
* Dequeue data out of the queue
*/
void dequeue() {
	struct node *temp;
	temp = rear_q;

	//Check front_q and rear_q are equal or NULL in both cases queue is empty 
	if (front_q == NULL || rear_q == NULL) {
		printf("Queue is empty\n");
	}
	else if (rear_q->next_node == NULL) {
		// check if it is last element in the queue, read value then set front_q and rear_q back to NULL
		printf("Dequeueing data %d out of queue\n", rear_q->num);
		front_q = NULL;
		free(rear_q);
		rear_q = NULL;
	}
	else {
		//Read data from rear_q and free element and change rear_q to temp
		printf("Dequeueing data %d out of queue\n", rear_q->num);
		temp = rear_q->next_node;
		free(rear_q);
		rear_q = temp;
	}
}

int main () {

	int ret=0;
	ret = enqueue(10);
	if (!ret)
		return -1;

	ret = enqueue(20);
	if (!ret)
		return -1;

	ret = enqueue(30);
	if (!ret) 
		return -1;

	dequeue();
	enqueue(40);
	dequeue();
	dequeue();
	dequeue();
	dequeue();

return 0;
}
