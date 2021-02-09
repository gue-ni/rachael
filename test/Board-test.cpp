#include "gtest/gtest.h"
#include "Board.h"



TEST(boardTest, checkdir){
    Board board;
    int n = 0;
    Move moves[256];
    board.set_board("8/8/5n2/2p1R2P/4P3/8/8/8 w - - 0 1");
    n = board.check_dir(moves, n, 0x44, 8, { N, S, E, W});
    EXPECT_EQ(n, 7);
}

TEST(boardTest, pseudo_legal_moves_rook){
    Board board;
    int n = 0;
    Move moves[256];

    board.set_board("8/8/8/4R3/8/8/8/8 w - - 0 1");
    n = board.pseudo_legal_for_square(moves, 0, 0x44);
    EXPECT_EQ(n, 14);

    board.set_board("8/8/5n2/2p1R2P/4P3/8/8/8 w - - 0 1");
    n = board.pseudo_legal_for_square(moves, 0, 0x44);
    EXPECT_EQ(n, 7);
}

TEST(boardTest, pseudo_legal_moves_pawn){
    Board board;
    int n = 0;
    Move moves[256];

    board.set_board("rnbqkbnr/pppp1ppp/8/8/3pP3/2P5/PP3PPP/RNBQKBNR b KQkq - 0 3");
    n = board.pseudo_legal_for_square(moves, 0, 0x33);
    EXPECT_EQ(n, 2);

    board.set_board("rnbqkbnr/pppp1ppp/8/8/3pP3/2P5/PP3PPP/RNBQKBNR b KQkq - 0 3");
    n = board.pseudo_legal_for_square(moves, 0, 0x63);
    EXPECT_EQ(n, 2);

    //for (int i = 0; i < n; i++) std::cout << moves[i] << std::endl;
    //std::cout << n << std::endl;
}