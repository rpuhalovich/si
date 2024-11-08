#ifndef FILE_H
#define FILE_H

#include "arena.h"
#include "buffer.h"
#include "line.h"
#include "types.h"

Buffer* load(Arena* arena, Line* path);

void write(Line* path);

#endif // FILE_H
