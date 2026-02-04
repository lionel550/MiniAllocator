#ifndef LIST_OPS_H
#define LIST_OPS_H

#include "allocator.h"
#include "utils.h"

FreeChunk *find_first_free_chunk(HeapMetadata *heap_metadata, size_t size, size_t alignment, size_t *padding_, FreeChunk **prev_chunk_);
void insert_chunk(FreeChunk **phead, FreeChunk *prev_chunk, FreeChunk *new_chunk);
void remove_chunk(FreeChunk **phead, FreeChunk *prev_chunk, FreeChunk *del_chunk);

#endif