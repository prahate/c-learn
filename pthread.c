#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

/*
* Threads share same address space as that of process, hence sometimes known as light weight processes
* But each hread has its own set of private registers, thread control blocks and stack segment.
* 
* Linux thread use clone() system call to create threads internally
*/

//pthread function definition
void * mythread(void *arg) {
	printf("%s\n", (char *)arg);
	return NULL;
}

int main (int argc, char *argv[]) {
	pthread_t p1, p2;	//Creating handles for new threads

	int rc;

	printf("main begin:\n");
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

	printf(":main end\n");

	return 0;
}
