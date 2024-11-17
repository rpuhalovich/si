#include <gtest/gtest.h>

#include "types.h"
#include "arena.c"
#include "line.c"

TEST(line, newLine) {
    const char* str = "foo";

    Arena* a = initArena(MEGABYTES(1));
    Line* l = newLines(a, str);

    EXPECT_EQ(3, l->length);
    EXPECT_EQ(4, l->capacity);
    EXPECT_EQ(0, strcmp(l->characters, str));
}
