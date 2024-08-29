#include <stdio.h>
#include "util.h"
/*
#define ARRAY_LEN(arr) (sizeof arr / sizeof( *arr))

#define PRINT_ARRAY(arr, length) \
    for(int i =0; i < length; i++) \
        printf("%d ", arr[i]); 

#define SWAP(x,y) (x ^= y ^= x ^= y)*/

void selection_sort(int *arr, int len)
{
    int min_index = 0;

    for (int i=0; i < len; i++)
    {
        min_index = i;
        for(int j= i+1; j< len; j++)
        {
            if( arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (i != min_index)
            SWAP(arr[i], arr[min_index]);
    }
}


int main()
{
    int a[] = {41,2,12,84,65,36,82,29,37};
    PRINT_ARRAY(a, 9);
    printf("\n");
    //printf("Array length is %ld\n", ARRAY_LEN(a));
    selection_sort(a, ARRAY_LEN(a));
    PRINT_ARRAY(a, 9);
    printf("\n");
    return 0;
}
