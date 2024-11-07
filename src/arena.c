#include "arena.h"

Arena* initArena(u64 size)
{
    Arena* a = malloc(sizeof(Arena));
    memset(a, 0, sizeof(Arena));

    a->memory = malloc(size);
    memset(a->memory, 0, size);

    a->ptr = a->memory;
    a->capacity = size;

    return a;
}

void* allocate(Arena* a, u64 size)
{
    // ASSERT(sizeof(a->ptr + a->capacity + size) < sizeof(a->ptr + a->capacity));
    void* ptr = a->ptr;
    a->ptr += size;
    return ptr;
}

void* reallocate(Arena* a, void* ptr, u64 oldsize, u64 newsize)
{
    void* newptr = a->ptr;
    a->ptr += newsize;
    memcpy(newptr, ptr, oldsize);
    return newptr;
}

void freeArena(Arena* a)
{
    free(a->memory);
    free(a);
}
