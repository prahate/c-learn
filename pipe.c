#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* pipe(int fiedesc[2]) system call is used to create pipe between two process
 * successfull call to pipe return two file descriptors one for read(fildesc[0]) and write(filedesc[1])
 * */


#define BUF_SIZE 10

int main(int argc, char *argv[]) {

	int pfd[2];	//Pipe file descriptors
	char buf[BUF_SIZE];	//Buffer to collect data
	ssize_t numRead;

	if(pipe(pfd) == -1) {
		perror("pipe");
		exit(-1);
	}

	switch(fork()) {
		case -1:
			perror("fork");
			exit(-1);
		case 0:
			if(close(pfd[1]) == -1) {	//closing the write end of the pipe in child as child
				perror("close");	// will only read from pipe
				exit(-1);
			}

			for(;;) {	//read data from pipe and echo to stdout
				numRead = read(pfd[0], buf, BUF_SIZE);
				if (numRead == -1) {
					perror("read-child");
					exit(-1);
				}

				if (numRead == 0)
					break;

				if (write(STDOUT_FILENO, buf, numRead) != numRead)
					perror("child write failed\n");
			}

			write(STDOUT_FILENO, "\n", 1);
			if(close(pfd[0]) == -1)		// closing read file descriptor as reading is done
				exit(-1);
			_exit(EXIT_SUCCESS);
		default:			
			if(close(pfd[0]) == -1) {		//closing read end of parent as parent only writes
				perror("close-parent");
				exit(-1);
			}

			if (write(pfd[1], argv[1], strlen(argv[1])) == -1) {
				perror("write-parent");
				exit(-1);
			}

			if (close(pfd[1]) == -1) {		// closing fd so that child sees EOF
				perror("close- parent");
				exit(-1);
			}

			wait(NULL);				// waiting for child to return or finish
			exit(EXIT_SUCCESS);
	}
}
