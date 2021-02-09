#include "gtest/gtest.h"
#include "Move.h"

TEST(plyTest, test1) {
    Move p1(0x00, 0x01);
    EXPECT_EQ (p1.from,  0x00);
}

TEST(plyTest, test2) {
    Move p1("a1a2");
    EXPECT_EQ (p1.from,  0x00);
}
