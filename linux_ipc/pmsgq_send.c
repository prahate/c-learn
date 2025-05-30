#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

int main(int argc, char *argv[])
{
	mqd_t mqd;
	int flags = O_WRONLY;
	unsigned int prio;

	if (argc < 3)
	{
		printf("Usage: %s <mq_name> <msg> <msg_prio>\n", argv[0]);
		return 0;
	}

	mqd = mq_open(argv[1], flags);
	if (mqd == (mqd_t)-1)
		perror("mq_open");

	prio = argc > 3 ? atoi(argv[3]) : 0;
	if (mq_send(mqd, argv[2], strlen(argv[2]), prio) == -1)
		perror("mq_send");


	return 0;
}

