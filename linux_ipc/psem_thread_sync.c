#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>

static int glob=0;

static sem_t sem;  //unnamed semphore

static void *threadFunc(void *arg)
{
	int loop = *((int*) arg);
	int loc, j;

	for(j=0; j < loop; j++)
	{
		// wait for semaphore to be available
		if (sem_wait(&sem) == -1) {
			perror("sem_wait");
		}
	
		loc = glob;
		loc++;
		glob = loc;
		
		// post the semphore after the opertion
		if (sem_post(&sem) == -1) {
			perror("sem_post");
		}
	}
}

int main(int argc, char *argv[])
{
	pthread_t t1, t2;
	int status;

	int loops = atoi(argv[1]);
	printf("# Loops : %d\n", loops);

	/* sem_init creates unnamed semaphores and inits it with values specified as last arg.
	 * middle argument indicates whether sem is shared between threads or process, 0- shared between thread
	 * this program uses this semaphore to sync two threads instead of mutex.*/
	if (sem_init(&sem, 0, 1) == -1)
	{
		perror("sem_init\n");
		return -1;
	}

	status = pthread_create(&t1, NULL, threadFunc, &loops);
	if (status == -1)
	{
		perror("pthread_create");
		return -1;
	}
	
	status = pthread_create(&t2, NULL, threadFunc, &loops);
	if (status == -1)
	{
		perror("pthread_create");
		return -1;
	}


	status = pthread_join(t1, NULL);
	if (status != 0) {
		perror("pthread_join");
		return -1;
	}
	
	status = pthread_join(t2, NULL);
	if (status != 0) {
		perror("pthread_join");
		return -1;
	}

	printf("Glob : %d\n", glob);

	sem_destroy(&sem);
	return 0;
}
