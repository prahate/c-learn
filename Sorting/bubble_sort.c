#include <stdio.h>
#include "util.h"

void bubble_sort(int *arr, int length)
{
    for(int i=0;i < length; i++)
    {
        for(int j=i+1; j< length; j++)
        {
            if(arr[i] > arr[j])
                SWAP(arr[i], arr[j]);
        }
    }
}

int main()
{
    //int a[] = {23, 34,67,12 ,3,56,78,25, 22};
    int a[] = {53,24,67,82,9,6,28,75,42};
    int len = ARRAY_LEN(a);
    bubble_sort(a, len);
    PRINT_ARRAY(a, len)
    printf("\n");
    return 0;
}
