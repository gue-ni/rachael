#include "gtest/gtest.h"
#include "Board.h"

TEST(boardTest, test1) {
    EXPECT_EQ (0x00,  0x00);
}

TEST(boardTest, test2){
    Board board(PAWNS_ONLY, true);
    std::cout << board << std::endl;



    EXPECT_EQ(1, 1);
}