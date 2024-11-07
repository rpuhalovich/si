#ifndef ARENA_H
#define ARENA_H

#include "types.h"

#define KILOBYTES(number) ((number) * 1024ull)
#define MEGABYTES(number) (KILOBYTES(number) * 1024ull)
#define GIGABYTES(number) (MEGABYTES(number) * 1024ull)
#define TERABYTES(number) (GIGABYTES(number) * 1024ull)

// macos memory management:
// https://developer.apple.com/library/archive/documentation/Performance/Conceptual/ManagingMemory/Articles/AboutMemory.html

typedef struct {
    void* memory;
    void* ptr;
    u64 capacity;
} Arena;

Arena* initArena(u64 size);

void* allocate(Arena* a, u64 size);

void* reallocate(Arena* a, void* ptr, u64 oldsize, u64 newsize);

void freeArena(Arena* a);

#endif // ARENA_H
