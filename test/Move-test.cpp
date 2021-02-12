#include "gtest/gtest.h"
#include "Move.h"

TEST(moveTest, test1) {
    Move p1(0x00, 0x01);
    EXPECT_EQ (p1.from,  0x00);
}

TEST(moveTest, test2) {
    Move p1("a1a2");
    EXPECT_EQ(p1.from,  A1);
    EXPECT_EQ(p1.to, A2);
}

TEST(moveTest, test_promotion) {
    Move p1("a7a8q");
    EXPECT_EQ(p1.from,  A7);
    EXPECT_EQ(p1.to, A8);
    EXPECT_EQ(p1.promote_to, QUEEN);

    Move p2("a7a8N");
    EXPECT_EQ(p2.from,  A7);
    EXPECT_EQ(p2.to, A8);
    EXPECT_EQ(p2.promote_to, KNIGHT);
}


