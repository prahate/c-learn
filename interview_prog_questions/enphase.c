#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * This question is asked in enphase interview
 * given and int array = { 3,6,7,2,1,4,9,8} and pivot element as 4
 * expected output is {3,2,1,4,6,7,9,8}
 * such that all element to left of pivot re smaller than it and to right are higher than it
 * order of the numbers is to be preserved
 * Questions: which data structure you will use and why?
 * Write logic/pseudo code first, then write c code.
 * Below is an approx solution using pointers**/


#define ARRAY_SIZE(x) sizeof(x)/sizeof(*x)

void swap(int *x, int*y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}



void enphase_sort(int *arr, int pivot)
{
	int *plow = arr;
	int *phigh = NULL;
	int *pend = arr + (int)sizeof arr + 1;
	int *ppivot;

	while(plow < pend)
	{
		if(*plow < pivot)
			plow++;
		else if(*plow > pivot)
		{
			if (!phigh)
				phigh = plow;
			while(plow <= pend)
			{
				if (*plow >= pivot)
					plow++;
				else {
					int *p2 = plow -1;
					int *p1 = plow;
					int temp = *plow;
					while(p2 >= phigh)
					{
						*p1 = *p2;
						p1--;
						p2--;
					}
					*phigh = temp;
					phigh++;
					plow++;
				}
			}
		}
	}

}


int main()
{
	int arr[] = { 3,1,9,7,3,4,2,5,8,1};
	int pivot = 4;

	enphase_sort(arr, pivot);

	for(int i=0; i< ARRAY_SIZE(arr); i++)
		printf("%d\n", *(arr + i));

	printf("\n");
	return 0;
}
