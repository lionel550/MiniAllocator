#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "internal_defs.h"

void init_heap(HeapMetadata *heap_metadata, void *memory, size_t memory_size);
void *my_alloc(HeapMetadata *heap_metadata, size_t size, size_t alignment);
void my_free(HeapMetadata *heap_metadata, void *ptr);

#endif