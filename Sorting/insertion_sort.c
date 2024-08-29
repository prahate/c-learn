#include <stdio.h>
#include "util.h"

void insertion_sort( int *arr, int len)
{
    int j;
    for(int i=1; i < len; i++)
    {
        int value = arr[i];
        for(j= i- 1; j >= 0 && arr[j] > value; j--)
        {
            arr[j+1] = arr[j];
        }
        arr[j+1]= value;
    }
}

int main()
{
    int a[] = {12,34,25,67,34,87,32,11,4};
    int len = ARRAY_LEN(a);

    PRINT_ARRAY(a, len);
    printf("\n");
    insertion_sort(a, len);

    PRINT_ARRAY(a, len);
    printf("\n");
    return 0;
}
