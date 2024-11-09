#include <stdio.h>
#include <sys/errno.h>

#include "appmath.h"
#include "file.h"

Buffer* load(Arena* arena, Line* filePath)
{
    Buffer* b = newBuffer(arena);
    b->length = 0;

    FILE* fp = fopen(filePath->characters, "r");
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

void write(Arena* arena, Buffer* b, Line* filePath)
{
    if (!b->isDirty || b->isScratch)
        return;

    // FIXME: there's a bug where line pointers are being mutated

    FILE* fp = fopen(filePath->characters, "w");
    for (int i = 0; i < b->length; i++) {
        i32 len = b->lines[i]->length;
        b->lines[i]->characters[len] = '\0';
        fprintf(fp, "%s\n", b->lines[i]->characters);
    }
    fclose(fp);
}
