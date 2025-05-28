#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/**
 *
 * output of the program
 *
 * spanidea@LT87:~/c-learn$ ./pipe_ls_wc
 * 25
 * spanidea@LT87:~/c-learn$
 * spanidea@LT87:~/c-learn$ ls | wc -l
 * 25
 *
 *
*/

int main( int rgc, char *argv[])
{
	int pfd[2];  //pfd[0] is read end and pfd[1] is write end

	if (pipe(pfd) == -1)
		perror("pipe");
	
	// create process to run ls command
	switch(fork())
	{
		case -1: // fork failed
			perror("fork");
			break;
		case 0:
			// close the read end
			if (close(pfd[0]) == -1) {
				perror("close 1");
				return -1;
			}
			// check of file desc no already in use
			if (pfd[1] != STDOUT_FILENO) {
				// duplicate file desc no
				if (dup2(pfd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 1");
					return -1;
				}

				if (close(pfd[1]) == -1) {
					perror("close 2");
					return -1;
				}

				execlp("ls", "ls", (char *)NULL); //write to the pipe


			}
		default:
			// parent falls through to create another child
			break;
	}
	
	// create child for wc command
	switch(fork())
	{
		case -1: // fork failed
			perror("fork");
			break;
		case 0:
			// close the write end
			if (close(pfd[1]) == -1) {
				perror("close 3");
				return -1;
			}
			// check of file desc no already in use
			if (pfd[0] != STDIN_FILENO) {
				// duplicate file desc no
				if (dup2(pfd[0], STDIN_FILENO) == -1)
				{
					perror("dup2 3");
					return -1;
				}

				if (close(pfd[0]) == -1) {
					perror("close 4");
					return -1;
				}

				execlp("wc", "wc", "-l", (char *)NULL); //write to the pipe
			}
		default:
			// parent falls through to create another child
			break;
	}



	if (pfd[0])
		close(pfd[0]);
	if ( pfd[1])
		close(pfd[1]);

	if (wait(NULL) == -1)
		perror("wait 1");
	if (wait(NULL) == -1)
		perror("wait 2");


	return 0;
}
