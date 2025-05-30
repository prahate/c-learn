#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>
#include <sys/types.h>


int main(int argc, char* argv[])
{
	mqd_t mqd;
	struct mq_attr attr;

	mqd = mq_open(argv[1], O_RDONLY);
	if (mqd == (mqd_t)-1)
		perror("mq_open");

	if (mq_getattr(mqd, &attr) == -1)
		perror("mq_getattr");

	printf("Max # msgs in messge queue: %ld\n", attr.mq_maxmsg);
	printf("Max size of message : %ld\n", attr.mq_msgsize);
	printf("Current # msg in queue : %ld\n", attr.mq_curmsgs);

	return 0;
}
