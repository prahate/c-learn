#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <string.h>


int main(int argc, char *argv[])
{
	mqd_t mqd;
	struct mq_attr attr;
	void *buffer;
	int flag;
	unsigned int prio;
	ssize_t numread;

	flag |= O_RDONLY;

	mqd = mq_open(argv[1], flag);
	if (mqd == (mqd_t)-1)
		perror("mq_open");

	if (mq_getattr(mqd, &attr) == -1)
		perror("mq_getattr");

	buffer = malloc(attr.mq_msgsize);
	if (!buffer)
	{
		perror("malloc");
		return -1;
	}

	numread = mq_receive(mqd, buffer, attr.mq_msgsize, &prio);
	if (numread == -1)
	{
		perror("mq_recieve");
		return -1;
	}

	printf("Read %ld bytes, priority %d\n", numread, prio);
	write(STDOUT_FILENO, buffer, numread);
	write(STDOUT_FILENO, "\n", 1);

	return 0;
}

