#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define num1 0xFFFFFFFF
#define num2 0x00000000

#define setbit(x, pos) (x)|(0x1 << pos)
#define clearbit(x, pos) (x) & (~(0x1 << pos))
#define togglebit(x, pos) (x) ^ (0x01 << pos)

int main()
{
	printf("setbit 3: %x\n", setbit(num2, 3));
	printf("clearbit 5: %x\n", clearbit(num1, 5));
	printf("togglebit 6: %x\n", togglebit(num1, 6));
	printf("togglebit 13: %x\n", togglebit(num1, 13));

	return 0;
}

