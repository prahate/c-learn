#define ARRAY_LEN(arr) (sizeof arr / sizeof( *arr))

#define PRINT_ARRAY(arr, length) \
    for(int i =0; i < length; i++) \
        printf("%d ", arr[i]); 

#define SWAP(x,y) (x ^= y ^= x ^= y)
