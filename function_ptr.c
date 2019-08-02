#include <stdio.h>
#include <stdlib.h>

/*
 * Following are the uses of the function pointer
 * 1. As callback mechanisms
 * 2. They provide a way of abstraction as shown in the case of puts below
 * 3. Generally functions can not be part of structures but with use of function pointers
 *    we can put function pointers in structs and later make them point to functions*/

typedef struct node {
	int num1, num2;
	int (* addInt) (int, int);
}Node;

int (*funcPtr) (int, int);	//declaration of function pointer

int add(int a, int b) {
	return (a + b);
}
	
int main (int argc, char *argv[]) {
	int result;
	Node n1;
	n1.num1=20;
	n1.num2=30;
	n1.addInt=add;			// Accessing function pointers within structure
	printf("Adding intergers %d\n", n1.addInt(n1.num1, n1.num2));
	int (* say)(const char *);
	say = puts;			// this use of functino pointers provide abstraction	
	funcPtr = add;			// assigning function to function pointer
	result = funcPtr(10, 20);	// Calling function pointer or it can also be called as (* funcPtr(10,20))
	say("Hello calling through function pointer");
	printf("Result is %d\n", result);
}
