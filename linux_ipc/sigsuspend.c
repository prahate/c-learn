#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>


static volatile sig_atomic_t gotSigquit = 0;

static void handler(int signum)
{
	printf("Caught signal %d (%s)\n", signum, strsignal(signum));
	
	if (signum == SIGQUIT)
		gotSigquit = 1;
}

/* Print list of signals within a signal set */
void printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
	int sig, cnt;
	cnt = 0;
	for (sig = 1; sig < NSIG; sig++) {
		// sigismember check if current signal is meber of sigset
		if (sigismember(sigset, sig)) {
			cnt++;
			fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
		}
	}
 	
	if (cnt == 0)
 		fprintf(of, "%s<empty signal set>\n", prefix);
}

/* Print mask of blocked signals for this process */
int printSigMask(FILE *of, const char *msg)
{
	sigset_t currMask;
	if (msg != NULL)
		fprintf(of, "%s", msg);
	
	// if newMsk arg to sigprocmask	is NULL, hten it will check if currMask for SIG_BLOCK
	if (sigprocmask(SIG_BLOCK, NULL, &currMask) == -1)
		return -1;

	// print blocked signals from currMask
	//printSigset(of, "\t\t", &currMask);
	int sig, cnt;
	cnt = 0;
	for (sig = 1; sig < NSIG; sig++) {
		// sigismember check if current signal is meber of sigset
		if (sigismember(&currMask, sig)) {
			cnt++;
			fprintf(of, "%s%d (%s)\n", "\t\t", sig, strsignal(sig));
		}
	}
 	
	if (cnt == 0)
 		fprintf(of, "%s<empty signal set>\n", "##");
	return 0;
}


/* Print signals currently pending for this process */
int printPendingSigs(FILE *of, const char *msg)
{
	sigset_t pendingSigs;
	if (msg != NULL)
		fprintf(of, "%s", msg);
	
	// sigpending updates pending signals for set	
	if (sigpending(&pendingSigs) == -1)
		return -1;
	
	printSigset(of, "\t\t", &pendingSigs);
	return 0;
}

int main( int argc, char * argv[])
{
	int loopNum;
	time_t startTime;
	sigset_t origMask, blockMask;
	struct sigaction sa;

	printSigMask(stdout, "Initial signal Mask: \n");


	sigemptyset(&blockMask);  //init a signal set
	// sigaddset is used to add signals to set
	sigaddset(&blockMask, SIGINT);  // add SIGINT to blockMask
	sigaddset(&blockMask, SIGQUIT); // add SIGQUIT to set blockMask
	
	// sigprocmask makes signal set as blocking
	if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
	{
		printf("Error sigprocmask\n");
		return -1;
	}


	// initialise sig action for both the siganls and register handler
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		printf("Error sigaction\n");
		return -1;
	}
	
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		printf("Error sigaction\n");
		return -1;
	}

	for(loopNum=1; !gotSigquit; loopNum++)
	{
		printf("==: LoopNum %d\n", loopNum);
		
		/*simulate critical section by delay*/
		//printSigMask(stdout, "Starting critical section, signal mask is:\n");

		for (startTime = time(NULL); time(NULL) < startTime + 4; )
			continue; /* Run for a few seconds elapsed time */

		//printPendingSigs(stdout,
			//	"Before sigsuspend() - pending signals:\n");

		if (sigsuspend(&origMask) == -1) {
			printf("Error sigsupend\n");
			return -1;
		}
	}

	// restore original mask
	if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
	{
		printf("Error sgiprocmask\n");
		return -1;
	}
	
	printSigMask(stdout, "=== Exited loop\nRestored signal mask to:\n");

	return 0;
}
