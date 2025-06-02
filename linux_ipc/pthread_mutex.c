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

static int glob = 0;

// Mutex ensures that glob is only read/ modified and updated by only one thread at a time.
// thereby achieving desired result. without mutex, every run of the program produces different
// value of glob.
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;  // statically allocated mutex


//pthread function definition
void * mythread(void *arg) {

	int loops = *(int *)arg;
	int loc, j, s;


	for (j=0; j < loops; j++)
	{
		// locking the mutex before read/modify/write operation
		s = pthread_mutex_lock(&mtx);
		if (s != 0)
			perror("mutex_lock");

		loc = glob;
		loc++;
		glob = loc;

		// unlock the mutex after read/modify/write operations
		s = pthread_mutex_unlock(&mtx);
		if (s != 0)
			perror("mutex_unlock");
	}
	return NULL;
}

int main (int argc, char *argv[]) {
	pthread_t t1, t2;	//Creating handles for new threads

	int rc;

	printf("main begin:\n");
	if (argc < 2) {
		printf(" <Usage> %s num_loops\n", argv[0]);
		return 0;
	}

	int loops = strtol(argv[1], 0, 0);
	/*
	* int pthread_create(pthread_t *thread_id, const pthread_attr_t *attributes, void *(*thread_function(void *)), void *arguments);
	* this function creates new thread.
	*
	* assert(scalar expression)
	* abort the programif the assertion is false
	* if expression is false prints error to standard output and terminates program with call to abort()
	*/
	rc = pthread_create(&t1, NULL, mythread, &loops); assert(rc == 0);
	rc = pthread_create(&t2, NULL, mythread, &loops); assert(rc == 0);

	/*
	* int pthread_join(pthread_t thread, void **status)
	* waits for the thread identified by thread to terminate
	*/
	rc = pthread_join(t1, NULL); assert(rc == 0);
	rc = pthread_join(t2, NULL); assert(rc == 0);

	printf(":main end\n");
	printf(" Glob = %d\n", glob);

	return 0;
}
