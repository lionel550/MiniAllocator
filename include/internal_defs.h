#ifndef INTERNAL_DEFS_H
#define INTERNAL_DEFS_H

#include <stdio.h>

typedef struct ChunkHeader {
    size_t chunk_size;
    size_t padding;
} ChunkHeader;

typedef struct FreeChunk {
    size_t chunk_size;
    struct FreeChunk *next;
} FreeChunk;

typedef struct HeapMetadata {
    void *memory;
    size_t size;
    size_t used;
    FreeChunk *head;
} HeapMetadata;

#endif