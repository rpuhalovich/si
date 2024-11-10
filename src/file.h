#ifndef FILE_H
#define FILE_H

#include "arena.h"
#include "buffer.h"
#include "line.h"
#include "types.h"

Buffer* load(Arena* arena, Line* filePath);

void write(Buffer* b, Line* filePath);

#endif // FILE_H
