#include "../include/list_ops.h"

// find_first_free_chunk use the fit first strategie
FreeChunk *find_first_free_chunk(HeapMetadata *heap_metadata, size_t size, size_t alignment, size_t *padding_, FreeChunk **prev_chunk_) {
    FreeChunk *current_chunk = heap_metadata->head;
    FreeChunk *prev_chunk = NULL;

    size_t padding = 0;

    while (current_chunk != NULL) {
        padding = calc_padding_with_header((uintptr_t)current_chunk, alignment, sizeof(ChunkHeader));
        size_t required_space = size + padding;

        if (current_chunk->chunk_size >= required_space) {
            break;
        }

        prev_chunk = current_chunk;
        current_chunk = current_chunk->next;
    }

    if (padding_) {
        *padding_ = padding;
    }

    if (prev_chunk_) {
        *prev_chunk_ = prev_chunk;
    }
    
    return current_chunk;
}

void insert_chunk(FreeChunk **phead, FreeChunk *prev_chunk, FreeChunk *new_chunk) {
    if (prev_chunk == NULL) {
        if (*phead != NULL) {
            new_chunk->next = *phead;
        }
        *phead = new_chunk;
    } else {
        if (prev_chunk->next == NULL) {
            prev_chunk->next = new_chunk;
            new_chunk->next = NULL;
        } else {
            new_chunk->next = prev_chunk->next;
            prev_chunk->next = new_chunk;
        }
    }
}

void remove_chunk(FreeChunk **phead, FreeChunk *prev_chunk, FreeChunk *del_chunk) {
    if (prev_chunk == NULL) {
        *phead = del_chunk->next;
    } else {
        prev_chunk->next = del_chunk->next;
    }
}