#include <gtest/gtest.h>

#include "appmath.c"

TEST(appmath, imin) {
    EXPECT_EQ(2, imin(2, 3));
    EXPECT_EQ(2, imin(3, 2));
    EXPECT_EQ(1, imin(1, 1));
}

TEST(appmath, imax) {
    EXPECT_EQ(2, imax(1, 2));
    EXPECT_EQ(2, imax(2, 1));
    EXPECT_EQ(1, imax(1, 1));
}
