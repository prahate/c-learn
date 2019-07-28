#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void *threadFunc(void *arg) {

	char *s = (char *) arg;
	printf("%s\n", s);
	return (void *) strlen(s);	// returning values from thread by type casting it to void *
}

int main (int argc, char *argv[]) {

	pthread_t t1;		//thread indentifier
	void *res;		// to get return value from thread
	int s;

	s = pthread_create(&t1, NULL, threadFunc, "Hello World\n");	// Passing arguments to thread
	if (s != 0) {
		perror("pthread_create");
		exit(-1);
	}

	printf("Message from Main thread\n");

	s = pthread_join(t1, &res);	// getting return value from thread in status field
	if (s != 0) {
		perror("pthread_join");
		exit(-1);
	}

	printf("Thread returned %ld\n", (long)res);
	exit(EXIT_SUCCESS);
}
