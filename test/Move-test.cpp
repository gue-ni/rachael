#include "gtest/gtest.h"
#include "Move.h"

TEST(moveTest, test1) {
    Move p1(0x00, 0x01);
    EXPECT_EQ (p1.from,  0x00);
}

TEST(moveTest, test2) {
    Move p1("a1a2");
    EXPECT_EQ(p1.from,  0x00);
    EXPECT_EQ(p1.to, 0x10);
}

TEST(moveTest, test_promotion) {
    Move p1("a7a8q");
    EXPECT_EQ(p1.from,  0x60);
    EXPECT_EQ(p1.to, 0x70);
    EXPECT_EQ(p1.promote_to, QUEEN);

    Move p2("a7a8N");
    EXPECT_EQ(p2.from,  0x60);
    EXPECT_EQ(p2.to, 0x70);
    EXPECT_EQ(p2.promote_to, KNIGHT);
}


