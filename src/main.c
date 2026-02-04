#include <stdio.h>
#include "../include/allocator.h"

int main(void) {
    char buffer[1024];
    HeapMetadata heap;

    init_heap(&heap, buffer, 1024);
    printf("Heap initialized. Free memory: %zu bytes\n", heap.head->chunk_size);

    void* ptr = my_alloc(&heap, 128, 8);
    if (ptr) {
        printf("Allocated 128 bytes at %p\n", ptr);
    }

    // 4. Free it
    my_free(&heap, ptr);
    printf("Memory freed. Free memory: %zu bytes\n", heap.head->chunk_size);

    return 0;
}