#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

int arr[] = { 49, 23, 56, 29, 13, 15, 14, 44};

int get_second_largest(int arr[], int len)
{
    int largest=arr[0];
    int second_large=0;
    for (int i=1; i < len; i++)
    {
        if (arr[i] > largest) {
            second_large = largest;
            largest = arr[i];
        } else if (arr[i] > second_large) {
            second_large = arr[i];
        }
    }
    return second_large;
}

int main() {
    printf("Array size %d\n", ARRAY_SIZE(arr));
    printf("Second largest is %d\n", get_second_largest(arr, ARRAY_SIZE(arr)));
    return 0;
}
