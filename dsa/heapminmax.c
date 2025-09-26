#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
* Array based implementation of min/max heap using recurrsion
*
* Expected output after running 
span-62@:~/c-learn/dsa$ gcc heapminmax.c -o heap -g
span-62@:~/c-learn/dsa$
span-62@:~/c-learn/dsa$ ./heap
1 5 7 13 9 10 15 
Removed 1
5 9 7 13 15 10 
Removed 5
7 9 10 13 15
*/

typedef struct sHeap {
    int *arr;   // dynamic array to hold the data
    int heapsz;  // to track last available position in array
    int arrsz;  // to create arr of size
} heap_t;

heap_t * create_heap(int size)
{
    heap_t *h= NULL;
    h = (heap_t *)malloc(sizeof(heap_t));
    if (h) {
        h->arr = (int *)malloc(sizeof(int) * size);
        h->heapsz = 0;
        h->arrsz = size;
    }
    return h;
}

void free_heap(heap_t *h)
{
    if (h)
    {
        if (h->arr)
            free(h->arr);
        free(h);
    }
}

// some helper functions for heap
int getParentIndex(int index)
{
    int pIndex=0;
    return pIndex = (index - 1)/2;
}

int getLeftchildIndex(int index)
{
    int lindex=0;
    return lindex = (2 * index) + 1;
}

int getRightchildIndex(int index)
{
    int rindex=0;
    return rindex = (2 * index) + 2;
}

void swap(int *h, int i, int j)
{
    int temp = *(h+i);
    *(h+i) = *(h+j);
    *(h+j) = temp;
}

bool hasLeft(heap_t *h, int index)
{
    return getLeftchildIndex(index) < h->heapsz;
}

bool hasRight(heap_t *h, int index)
{
    return getRightchildIndex(index) < h->heapsz;
}

void heapifyUp(heap_t *h, int index)
{
    if (index == 0)
        return;     // if we are at index 0,meaning  we reached root node
    else {
        int pIndex = getParentIndex(index); // get parent index
        // check to see if child's data is less than parent for min heap and 
        // greater than for max heap,  if it is then
        if (h->arr[index] < h->arr[pIndex]) {   
            swap(h->arr, index, pIndex);        // swap the data
            heapifyUp(h, pIndex);               // recursively check till we reach root node
        }
    }
}


void insert(heap_t *h, int data)
{
    if (h->heapsz == h->arrsz)
        return;     // heap is full return; we can use realloc here to increase size
    else {
        h->heapsz++;    // increase heapsize
        h->arr[h->heapsz -1] = data; // add data at the last position 
        heapifyUp(h, h->heapsz -1); // call hepaifyUp which will take care of putting data
                                    // at proper place 
    }
}

void heapifyDown(heap_t *h, int index)
{
    int lindex = getLeftchildIndex(index);
    int rindex = getRightchildIndex(index);
    int minIndex = index;
    if (hasLeft(h, index) && (h->arr[lindex] < h->arr[minIndex])) {
        minIndex = lindex;
    }

    if (hasRight(h, index) && (h->arr[rindex] < h->arr[minIndex])) {
        minIndex = rindex;
    }
#if 0
    else
        return;

    if (h->arr[lindex] < h->arr[rindex])
        minIndex = lindex;
    else
        minIndex = rindex;
#endif
    if (minIndex != index) {
        swap(h->arr, index, minIndex);
        heapifyDown(h, minIndex);
    }
}

int remove_data(heap_t *h)
{
    int temp = h->arr[0]; // save the root node data
    h->arr[0] = h->arr[h->heapsz -1]; // replace with data at right most node
    h->heapsz--;    // decrement heap size
    if (h->heapsz > 1)
        heapifyDown(h, 0);

    return temp;
}

int main()
{
    heap_t *heap = create_heap(7);

    insert(heap, 7);
    insert(heap, 13);
    insert(heap, 5);
    insert(heap, 1);
    insert(heap, 9);
    insert(heap, 10);
    insert(heap, 15);

    for (int i=1; i <= heap->heapsz; i++)
        printf("%d ", heap->arr[i-1]);
    printf("\n");

    int data = remove_data(heap);
    printf("Removed %d\n", data);
    
    for (int i=1; i <= heap->heapsz; i++)
        printf("%d ", heap->arr[i-1]);
    printf("\n");
    
    data = remove_data(heap);
    printf("Removed %d\n", data);
    
    for (int i=1; i <= heap->heapsz; i++)
        printf("%d ", heap->arr[i-1]);
    printf("\n");
}
