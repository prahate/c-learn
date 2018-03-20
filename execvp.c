#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	printf("Hello PID: %d\n", (int) getpid());
	
	int rc = fork();	//creating new process using fork

	if ( rc < 0 ) {
		printf("Failed to create process using fork\n");
		exit(1);
	}
	else if ( rc == 0 ) {	//child process
		printf("Hello I am child PID : %d\n", (int) getpid());
		char *args[] = {"./hello", NULL};
		// Exec replaces the child process's code segment  with contents of hello executable, also reinitialises stack
		// So exec does not create separate process but rather it replaces existing process
		execvp(args[0], args);
		printf("This line wont be printed\n");
	}
	else {			//Parent process
		int wc = wait(NULL);
		printf("Hello I am Parent PID: %d\n", (int) getpid());
	}

return 0;
}
