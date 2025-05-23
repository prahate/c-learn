#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "progress_bar.h"

char bar[NUM] = {0};
const char *label = "|/-\\";

void progress_bar(int speed) {
	memset(bar, '\0', sizeof(bar));

	int len = strlen(label);

	int count =0;
	while(count <= TOP)
	{
		printf("[%-100s][%d%%][%c]\r", bar, count, label[count % len]);
		fflush(stdout);
		bar[count++] = BODY;
		if (count < TOP)
			bar[count] = HEAD;

		usleep(speed);
	}
	printf("\n");
}


int main()
{
	progress_bar(500000);
	return 0;
}

