#include "../include/allocator.h"
#include "../include/list_ops.h"

void free_all(HeapMetadata *heap_metadata) {
    FreeChunk *chunck = (FreeChunk *)heap_metadata->memory;
    chunck->chunk_size = heap_metadata->size;
    chunck->next = NULL;
    heap_metadata->head = chunck;
    heap_metadata->used = 0;
}

void init_heap(HeapMetadata *heap_metadata, void *memory, size_t memory_size) {
    heap_metadata->memory = memory;
    heap_metadata->size = memory_size;

    free_all(heap_metadata);
}

void *my_alloc(HeapMetadata *heap_metadata, size_t size, size_t alignment) {
    size_t padding = 0;
    FreeChunk *prev_chunk = NULL;
    FreeChunk *free_chunk = NULL;
    size_t alignment_padding, required_space, remaining;
    ChunkHeader *header_ptr;

    if (size < sizeof(FreeChunk)) {
        size = sizeof(FreeChunk);
    }

    if (alignment < 8) {
        alignment = 8;
    }

    free_chunk = find_first_free_chunk(heap_metadata, size, alignment, &padding, &prev_chunk);
    if (free_chunk == NULL) {
        fprintf(stderr, "No free memory\n");
        return NULL;
    }

    alignment_padding = padding - sizeof(ChunkHeader);
    required_space = size + padding;
    remaining = free_chunk->chunk_size - required_space;

    if (remaining > 0) {
        FreeChunk *new_chunk = (FreeChunk *)((char *)free_chunk + required_space);
        new_chunk->chunk_size = remaining;
        insert_chunk(&heap_metadata->head, free_chunk, new_chunk); 
    }

    remove_chunk(&heap_metadata->head, prev_chunk, free_chunk);

    header_ptr = (ChunkHeader *)((char *)free_chunk + alignment_padding);
    header_ptr->chunk_size = required_space;
    header_ptr->padding = alignment_padding;

    heap_metadata->used += required_space;

    return (void *)((char *)header_ptr + sizeof(ChunkHeader));
}

void coalescence(HeapMetadata *heap_metadata, FreeChunk *prev_chunk, FreeChunk *free_chunk) {
    if (free_chunk->next != NULL && (void *)((char *)free_chunk + free_chunk->chunk_size) == free_chunk->next) {
        free_chunk->chunk_size += free_chunk->next->chunk_size;
        remove_chunk(&heap_metadata->head, free_chunk, free_chunk->next);
    }

    if (prev_chunk != NULL && prev_chunk->next != NULL && (void *)((char *)prev_chunk + prev_chunk->chunk_size ) == free_chunk) {
        prev_chunk->chunk_size += free_chunk->next->chunk_size;
        remove_chunk(&heap_metadata->head, prev_chunk, free_chunk);
    }
}

void my_free(HeapMetadata *heap_metadata, void *ptr) {
    ChunkHeader *header;
    FreeChunk *free_chunk;
    FreeChunk *current_chunk;
    FreeChunk *prev_chunk = NULL;
    size_t chunk_size, alignment_padding;
    
    if (ptr == NULL) {
        return;
    }

    header = (ChunkHeader *)((char *)ptr - sizeof(ChunkHeader));
    chunk_size = header->chunk_size;
    alignment_padding = header->padding;

    free_chunk = (FreeChunk *)((char *)header - alignment_padding);
    free_chunk->chunk_size = chunk_size;
    free_chunk->next = NULL;

    current_chunk = heap_metadata->head;
    while (current_chunk != NULL) {
        if ((FreeChunk *)ptr < current_chunk) {
            insert_chunk(&heap_metadata->head, prev_chunk, free_chunk);
            break;
        }
        prev_chunk = current_chunk;
        current_chunk = current_chunk->next;
    }

    heap_metadata->used -= free_chunk->chunk_size;
    coalescence(heap_metadata, prev_chunk, free_chunk);
}
