#include <stdio.h>

#include "file.h"

Buffer* load(Arena* arena, Line* path)
{
    Buffer* b = newBuffer(arena);
    FILE* fp = fopen(path->characters, "r");

    char* line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        // fwrite(line, linelen, 1, stdout);
        Line* l = newLines(arena, line);
        append(arena, b, l);
    }

    fclose(fp);
    return b;
}

void write(Line* path)
{
}
