#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* Output when program is run
 * span85@span85-Lenovo:~/c-learn$ gcc fork_child.c -o fork
   span85@span85-Lenovo:~/c-learn$ 
   span85@span85-Lenovo:~/c-learn$ 
   span85@span85-Lenovo:~/c-learn$ ./fork 
   PID=6074 child iData=333 iStack=666
   PID=6073 Parent iData=111 iStack=222
*
* */
static int iData=111;		//Will be store onto data segment

int main (int argc, char *argv[]) {

	int iStack=222;

	pid_t childPid;

	switch(childPid = fork()) {
	
		case -1:
			perror("Fork failed\n");
			exit(EXIT_FAILURE);
		case 0:
			iData *= 3;
			iStack *= 3;
			break;
		default:
			sleep(3);	//sleeping deliberatily so that child gets chance to run
			break;
	}

	printf("PID=%ld %s iData=%d iStack=%d\n", (long)getpid(), (childPid == 0) ? "child":"Parent", iData, iStack);
	exit(EXIT_SUCCESS);

return 0;
}
