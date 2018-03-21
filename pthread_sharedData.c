#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
// To compile gcc -o -g pthread_sharedData.c -o pthread_share -lpthread
/*
* Threads share same address space as that of process, hence sometimes known as light weight processes
* But each hread has its own set of private registers, thread control blocks and stack segment.
* 
* Linux thread use clone() system call to create threads internally
*/

static volatile int counter=0;
// Since above variable is shared between two threads, race condition occurs
// suppose one thread t1 enters the function with counter=50, it increments the counter, so counter=51, and it is yet to write updated value to data segment
// in betwwen interrupt occurs so context switch happens and data is pushed to stack,
// now before t1 can run, t2 gets chance to run, since counter is not updated in data segment its value is still 50, and it increaments it to 51
// and updates data segments, when t1 gets chance to run it pops data from stack and it also updates counter as 51 to data segment
// so due to this race conditional counter gets updated once instead of twice
// thats why every run of program gives different output


//pthread function definition
void * mythread(void *arg) {
	printf("%s: begin\n", (char *)arg);
	int i;
	for (i=0; i < 1e7; i++)
		counter= counter + 1;
	printf("%s: end\n", (char *)arg);
	return NULL;
}

int main (int argc, char *argv[]) {
	pthread_t p1, p2;	//Creating handles for new threads

	int rc;

	printf("main begin counter:%d\n", counter);
	/*
	* int pthread_create(pthread_t *thread_id, const pthread_attr_t *attributes, void *(*thread_function(void *)), void *arguments);
	* this function creates new thread.
	*
	* assert(scalar expression)
	* abort the programif the assertion is false
	* if expression is false prints error to standard output and terminates program with call to abort()
	*/
	rc = pthread_create(&p1, NULL, mythread, "A"); assert(rc == 0);
	rc = pthread_create(&p2, NULL, mythread, "B"); assert(rc == 0);

	/*
	* int pthread_join(pthread_t thread, void **status)
	* waits for the thread identified by thread to terminate
	*/
	rc = pthread_join(p1, NULL); assert(rc == 0);
	rc = pthread_join(p2, NULL); assert(rc == 0);

	printf(":main done with both counter: %d \n", counter);

	return 0;
}
