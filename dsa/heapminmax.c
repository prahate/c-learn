#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
* Array based implementation of min/max heap using recurrsion
*/

typedef struct sHeap {
    int *arr;   // dynamic array to hold the data
    int heapsz;
    int arrsz;
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
    if (index > 0)
        pIndex = (index - 1)/2;
    return pIndex;
}

int getLeftchildIndex(int index)
{
    int lindex=0;
    if (index > 0)
        lindex = (2 * index) + 1;
    return lindex;
}

int getRightchildIndex(int index)
{
    int rindex=0;
    if (index > 0)
        rindex = (2 * index) + 2;
    return rindex;
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

int main()
{
    heap_t *heap = create_heap(7);

    insert(heap, 10);
    insert(heap, 5);
    insert(heap, 3);
    insert(heap, 1);

    for (int i=1; i <= heap->heapsz; i++)
        printf("%d ", heap->arr[i-1]);
    printf("\n");
}
