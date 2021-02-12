#include "gtest/gtest.h"
#include "Board.h"


TEST(boardTest, boardTest_set_board_starting_position_Test){
    Board board;

    board.set_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    EXPECT_EQ(board.fifty_moves, 0);
    EXPECT_EQ(board.plies, 1);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_KINGSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), true);
    EXPECT_EQ(board.color_to_move, WHITE);
    EXPECT_EQ(board.w_king, E1);
    EXPECT_EQ(board.b_king, E8);

    board.set_board("r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 4 4");
    EXPECT_EQ(board.fifty_moves, 4);
    EXPECT_EQ(board.plies, 4);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_KINGSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), true);
    EXPECT_EQ(board.color_to_move, WHITE);
    EXPECT_EQ(board.w_king, E1);
    EXPECT_EQ(board.b_king, E8);
    EXPECT_EQ(board.x88[C3], KNIGHT);
    EXPECT_EQ(board.x88[C6], -KNIGHT);


    board.set_board("rn1q1k1r/ppp1pp1p/3pbnpb/8/2BPP3/2N2N2/PPP2PPP/R1BQK1R1 b Qkq - 1 4");
    //std::cout << board << std::endl;
    EXPECT_EQ(board.fifty_moves, 1);
    EXPECT_EQ(board.plies, 4);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_KINGSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);
    EXPECT_EQ(board.color_to_move, BLACK);
    EXPECT_EQ(board.w_king, E1);
    EXPECT_EQ(board.b_king, F8);
}

TEST(boardTest, boardTest_calculate_material_Test){
    Board board;

    board.set_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::cout << board << std::endl;
    EXPECT_EQ(board.material(WHITE), board.material(BLACK));
    EXPECT_EQ(board.material(WHITE), 24000);

}

















/*

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

 */