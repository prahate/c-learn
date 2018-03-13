#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	printf("Hello world pid:%d\n", (int) getpid());
	int rc = fork();

	if (rc < 0) {
		fprintf(stderr, "fork() failed\n");
		exit(1);
	}
	else if (rc == 0) {	//child New Process
		printf("Hello world I am child pid:%d \n", (int) getpid());
	}
	else {			//Parent process
		int wc = wait(NULL);	//waits for child process to exit here
		printf("Hello world I am parent of %d wc:%d pid:%d \n", rc, wc, (int) getpid());
	}
	return 0;
}
