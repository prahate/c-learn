#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>


int main(int argc, char *argv[])
{
	int flags;
	mode_t perms;
	struct mq_attr attr, *attrp;

	mqd_t mqd;

	flags = O_CREAT | O_RDWR;

	attrp = NULL;
	attr.mq_maxmsg = 256;	// max # message queues
	attr.mq_msgsize = 32;	// max msg size of one msg
	attrp = &attr;
	
	perms = S_IRUSR | S_IWUSR;

	mqd = mq_open(argv[1], flags, perms, attrp);
      	if (mqd == (mqd_t) -1)
	{
		perror("mq_open");
		return -1;
	}	

	return 0;
}
