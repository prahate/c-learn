#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
 * Signal is notification sent to process also called as software inerrupts, that an event has occured.
 * Signal can be sent by kernel, by another process or by process itself.
 * Each signal is identified by its number, also each signal has its own default handler
 * Few examples of signals are SIGINT(Control-c), SIGHUP (Control-z), SIGKILL, SIGQUIT(Control-\) */

static void sigHandler(int sig) {
	static int count=0;

	if (sig == SIGINT) {
		count++;
		printf("Caught SIGINT count is %d\n", count);
		return;
	}

	/*Must be SIGQUIT print message and terminate*/
	printf("Caught SIGQUIT terminating.....");
	exit(EXIT_SUCCESS);
}


int main (int argc, char *argv[]) {

	//Implementing signal handler
	if (signal(SIGINT, sigHandler) == SIG_ERR)
		perror("SIGINT Error");
	if (signal(SIGQUIT, sigHandler) == SIG_ERR)
		perror("SIGQUIT Error");

	for (;;)		//loop forever, for signals to be delivered
		pause();	//block until signal is paused
	return 0;
}
