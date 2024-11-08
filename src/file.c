#include <stdio.h>
#include <sys/errno.h>

#include "file.h"

Buffer* load(Arena* arena, Line* path)
{
    Buffer* b = newBuffer(arena);
    b->length = 0;

    FILE* fp = fopen(path->characters, "r");
    if (fp == NULL) {
        if (errno == ENOENT)
            printf("ENOENT: file not found");
        return NULL;
    }

    char* line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        Line* l = newLine(arena);
        insertString(arena, l, line, strlen(line) - 1, 0);
        append(arena, b, l);
    }

    free(line);
    fclose(fp);

    return b;
}

void write(Line* path)
{
}
