#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int glob=0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;		//Statically initialized mutex



static void *threadFunc(void * arg) {

	int loops = *((int *)arg);
	int loc, j, s;

	for (j=0; j < loops; j++) {
		s = pthread_mutex_lock(&mtx);
		if (s != 0) {
			perror("pthread_mutex_lock");
			exit(-1);
		}

		loc = glob;
		loc++;
		glob = loc;

		s = pthread_mutex_unlock(&mtx);
		if (s != 0) {
			perror("pthread_mutex_unlock");
			exit(-1);
		}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t t1, t2;
	int loops, s;

	loops = atoi(argv[1]);
	printf("Num of Loops %d\n", loops);

	s = pthread_create(&t1, NULL, threadFunc, &loops);
	if (s != 0) {
		perror("pthread_create");
		exit(-1);
	}

	s = pthread_create(&t2, NULL, threadFunc, &loops);
	if (s != 0) {
		perror("pthread_create");
		exit(-1);
	}


	s = pthread_join(t1, NULL);
	if (s != 0) {
		perror("pthread_join");
		exit(-1);
	}
	
	s = pthread_join(t2, NULL);
	if (s != 0) {
		perror("pthread_join");
		exit(-1);
	}

	printf("glob = %d\n", glob);
	exit(EXIT_SUCCESS);
}
