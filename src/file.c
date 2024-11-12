#include <stdio.h>
#include <sys/errno.h>

#ifdef DEBUG
#include <signal.h>
#endif

#include "appmath.h"
#include "file.h"

Buffer* load(Arena* arena, Line* filePath)
{
    FILE* fp = fopen(filePath->characters, "r");
    if (fp == NULL) {
        return NULL;
    }

    Buffer* b = newBuffer(arena);
    b->length = 0;

    char* line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        Line* l = newLine(arena);
        insertString(arena, l, line, linelen - 1, 0);
        append(arena, b, l);
    }

    free(line);
    fclose(fp);

    return b;
}

void write(Buffer* b, Line* filePath)
{
    if (!b || !filePath || !b->isDirty || b->isScratch) {
        return;
    }

    // FIXME: there's a bug where line pointers are being mutated

    FILE* fp = fopen(filePath->characters, "w");
    if (fp == NULL) {
        return;
    }

    for (i32 i = 0; i < b->length; i++) {
        i32 len = b->lines[i]->length;
        b->lines[i]->characters[len] = '\0';
        fprintf(fp, "%s\n", b->lines[i]->characters); // NOLINT
    }

    fclose(fp);
}
