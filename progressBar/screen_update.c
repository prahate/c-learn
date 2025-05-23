#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


void test() {
	int count=100;

	while(count >= 0)
	{
		/*
		 * - After setting the bit width, the C program defaults to right alignment . 
		 *   We want the number to be displayed at the leftmost side of the current line, 
		 *   so we need to -use left alignment.
		 *   Not using '-' inverting will result in the numberNot Leftshow
		 * 3 used to control display bit width
		 * \r carrieg return, return to the beginning of the current line, and overwrite printing to achieve a countdown effect.
		 * */
		printf("%-3d\r", count);
		/*
		 * fflsuh() plays major role in achieving in place replacement
		 * to refresh the data in the buffer immediately
		 * */
		fflush(stdout);
		count--;
		// sleep for 1 sec before printing again
		sleep(1);
	}
	printf("\n");
}


int main()
{
	test();
	return 0;
}
