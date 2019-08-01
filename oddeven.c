#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


static int glob=0;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *funcEven(void * arg) {
	int s;
	while(1) {
		s = pthread_mutex_lock(&mtx);
		if (s != 0) {
			perror("pthread_mutex_lock");
			exit(-1);
		}
		
		if (glob > 100)
			break;
		else if (glob == 0)
			goto skip;
		glob++;
skip:		printf("Thread Even %d\n", glob);

		s = pthread_mutex_unlock(&mtx);
		if (s != 0) {
			perror("pthread_mutex_unlock");
			exit(-1);
		}

		s = pthread_cond_signal(&cond);
		if (s != 0) {
			perror("pthread_cond_signal");
			exit(-1);
		}
		sleep(1);
	}

	s = pthread_mutex_unlock(&mtx);
	if (s != 0) {
		perror("pthread_mutex_unlock");
		exit(-1);
	}

	s = pthread_cond_signal(&cond);
	if (s != 0) {
		perror("pthread_cond_signal");
		exit(-1);
	}

	exit(EXIT_SUCCESS);
}

static void *funcOdd(void * arg) {
	int s;
	while(1) {
		s = pthread_mutex_lock(&mtx);
		if (s != 0) {
			perror("pthread_mutex_lock");
			exit(-1);
		}
		
		s = pthread_cond_wait(&cond, &mtx);
		if (s != 0) {
			perror("pthread_cond_wait");
			exit(-1);
		}
		
		//if (glob > 100)
		//	break;
		glob++;
		if (glob > 100)
			break;
		printf("Thread Odd %d\n", glob);

		s = pthread_mutex_unlock(&mtx);
		if (s != 0) {
			perror("pthread_mutex_unlock");
			exit(-1);
		}
	}

	s = pthread_mutex_unlock(&mtx);
	if (s != 0) {
		perror("pthread_mutex_unlock");
		exit(-1);
	}

	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	pthread_t t1, t2;
	int s;

	s = pthread_create(&t1, NULL, funcEven, NULL);
	if ( s !=0 ) {
		perror("pthread_create");
		exit(-1);
	}

	s = pthread_create(&t2, NULL, funcOdd, NULL);
	if ( s != 0) {
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
}
