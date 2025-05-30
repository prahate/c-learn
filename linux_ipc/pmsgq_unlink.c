#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>

int main( int argc, char *argv[])
{
	if(mq_unlink(argv[1]) == -1)
		perror("mq_unlink");

	return 0;
}
