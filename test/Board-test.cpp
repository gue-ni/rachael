#include "gtest/gtest.h"
#include "Board.h"

TEST(boardTest, is_attacked){
    Board board;
    board.set_board("1n1qk1nr/1p2pp1p/7b/p1p2bp1/3PN2r/8/PPP2PPP/R1BQKBNR w KQk - 1 5");
    //std::cout << board << std::endl;

    EXPECT_EQ(board.is_attacked(0x34, WHITE), true);
    EXPECT_EQ(board.is_attacked(0x33, WHITE), true);
    EXPECT_EQ(board.is_attacked(0x04, WHITE), false);
    EXPECT_EQ(board.is_attacked(0x17, WHITE), true);

    EXPECT_EQ(board.is_attacked(0x42, BLACK), true);
    EXPECT_EQ(board.is_attacked(0x73, BLACK), false);
    EXPECT_EQ(board.is_attacked(0x46, BLACK), true);
}

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

TEST(boardTest, pseudo_legal_moves_king){
    Board board;
    int n = 0;
    Move moves[256];

    board.set_board("rnbqkbnr/pp2pppp/2p5/3P4/2BP4/5N2/PPP2PPP/RNBQK2R w KQkq - 0 4");
    n = board.pseudo_legal_for_square(moves, 0, 0x04);
    EXPECT_EQ(n, 4);

    //for (int i = 0; i < n; i++) std::cout << moves[i] << std::endl;




    board.set_board("rnb1kbnr/pp2p1pp/2p2p2/3P4/1qBP4/P4N2/1PP2PPP/RNBQK2R W KQkq - 0 3");


    board.set_board("rnb1kbnr/pp2p1pp/2p2p2/3P4/1qBP4/P4N2/1PP2PPP/RNBQK2R b Qkq - 0 3");

}