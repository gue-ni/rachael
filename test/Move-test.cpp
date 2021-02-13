#include "gtest/gtest.h"
#include "Move.h"

TEST(moveTest, moveTest_from_squares) {
    Move p1(A1, A2);
    EXPECT_EQ (p1.from,  A1);
    EXPECT_EQ (p1.to,  A2);

    Move p2(C7, C8, QUEEN);
    EXPECT_EQ (p2.from,  C7);
    EXPECT_EQ (p2.to,  C8);
    EXPECT_EQ(p2.promote_to, QUEEN);

    Move p3(C7, C8, ROOK);
    EXPECT_EQ (p3.from,  C7);
    EXPECT_EQ (p3.to,  C8);
    EXPECT_EQ(p3.promote_to, ROOK);
}

TEST(moveTest, moveTest_from_string) {
    Move p1("a1a2");
    EXPECT_EQ(p1.from,  A1);
    EXPECT_EQ(p1.to, A2);

    Move p2("g1g3");
    EXPECT_EQ(p2.from,  G1);
    EXPECT_EQ(p2.to, G3);
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

    Move p3(A7, A8, KNIGHT);
    EXPECT_EQ(p3.from,  A7);
    EXPECT_EQ(p3.to, A8);
    EXPECT_EQ(p3.promote_to, KNIGHT);
}


