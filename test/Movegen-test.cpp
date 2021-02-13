#include "gtest/gtest.h"
#include "Board.h"

TEST(movegenTest, movegenTest_pseudo_legal_Test){}

TEST(movegenTest, movegenTest_pseudo_legal_for_square_Test){

}

TEST(movegenTest, movegenTest_check_dir_Test){
    int n = 0;
    Board board;
    Move moves[256];

    // knight
    board.set_board("7k/8/3N4/1n6/8/8/5N2/7K w - - 0 1");

    n = board.check_dir(moves, 0, F2,1, { NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW });
    EXPECT_EQ(n, 5);

    n = board.check_dir(moves, 0, D6,1, { NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW });
    EXPECT_EQ(n, 8);

    n = board.check_dir(moves, 0, B5,1, { NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW });
    EXPECT_EQ(n, 6);

    // bishop
    board.set_board("7k/n7/1n3p2/8/3B4/8/1P6/7K w - - 0 1");
    n = board.check_dir(moves, 0, D4, 8, { NE, SE, SW, NW });
    EXPECT_EQ(n, 8);

    // rook
    board.set_board("7k/3p4/8/3r1P2/8/8/8/3Q3K w - - 0 1");
    n = board.check_dir(moves, 0, D5, 8, { N, E, S, W });
    EXPECT_EQ(n, 10);



    //for (int i = 0; i < n; i++) std::cout << moves[i] << std::endl;


}

TEST(movegenTest, movegenTest_is_checked_Test){}

TEST(movegenTest, movegenTest_is_attacked_Test){}


