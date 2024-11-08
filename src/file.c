#include <stdio.h>
#include <sys/errno.h>

#include "appmath.h"
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

void write(Arena* arena, Buffer* b, Line* path)
{
    FILE* fp = fopen(path->characters, "w");
    for (int i = 0; i < b->length; i++)
        fprintf(fp, "%s\n", b->lines[i]->characters);
    fclose(fp);
}
