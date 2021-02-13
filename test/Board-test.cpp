#include "gtest/gtest.h"
#include "Board.h"


TEST(boardTest, boardTest_set_board_Test){
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

    board.set_board("8/1p3k2/8/8/1P6/r7/3K1rP1/8 w - - 0 1");
    EXPECT_EQ(board.fifty_moves, 0);
    EXPECT_EQ(board.plies, 1);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_QUEENSIDE), false);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), false);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_KINGSIDE), false);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);
    EXPECT_EQ(board.color_to_move, WHITE);
    EXPECT_EQ(board.w_king, D2);
    EXPECT_EQ(board.b_king, F7);
}

TEST(boardTest, boardTest_calculate_material_Test){
    Board board;

    board.set_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //EXPECT_EQ(board.material(WHITE), board.material(BLACK));
    //EXPECT_EQ(board.material(WHITE), 24000);

    board.set_board("r1bqkbnr/p1pp2pp/2p5/4p3/2P5/5p2/PP1P1PPP/RNBQK2R b KQkq - 3 3");
    //EXPECT_EQ(board.material(WHITE), 23250);
    //EXPECT_EQ(board.material(BLACK), 23680);

    board.set_board("8/1p3k2/8/8/1P6/r7/3K1rP1/8 w - - 0 1");
    //EXPECT_EQ(board.material(WHITE), 20200);
    //EXPECT_EQ(board.material(BLACK), 21100);
}

TEST(boardTest, boardTest_is_enemey_Test){
    Board board;

    board.set_board("8/1p3k2/8/8/1P6/r7/3K1rP1/8 w - - 0 1");
    EXPECT_EQ(board.is_enemy(A3, WHITE*KING), true);
    EXPECT_EQ(board.is_enemy(A3, BLACK*KING), false);
    EXPECT_EQ(board.is_enemy(A1, BLACK*KING), false);
    EXPECT_EQ(board.is_enemy(A1, WHITE*KING), false);
}

TEST(boardTest, boardTest_is_friendly_Test){
    Board board;

    board.set_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    EXPECT_EQ(board.is_friendly(C7, WHITE*KING), false);
    EXPECT_EQ(board.is_friendly(A1, WHITE*KING), true);

    EXPECT_EQ(board.is_friendly(A1, BLACK*KING), false);
    EXPECT_EQ(board.is_friendly(D8, BLACK*KING), true);
}

TEST(boardTest, boardTest_execute_move_Test){
    Board board;
    Move m;

    board.set_board("rn1qkbnr/pp2pppp/2p5/5b2/3PN3/8/PPP2PPP/R1BQKBNR w KQkq - 1 5");
    m = Move(D1, H5);
    int killed = board.execute_move(m);
    EXPECT_EQ(board.x88[D1], EMPTY_SQUARE);
    EXPECT_EQ(board.x88[H5], QUEEN);
    EXPECT_EQ(killed, EMPTY_SQUARE);

    board.set_board("rn1qkbnr/pp2pppp/2p5/5b2/3PN3/8/PPP2PPP/R1BQKBNR w KQkq - 1 5");
    //int wm = board.material(WHITE);
    m = Move(F5, E4);
    killed = board.execute_move(m);
    EXPECT_EQ(board.x88[F5], EMPTY_SQUARE);
    EXPECT_EQ(board.x88[E4], BLACK*BISHOP);
    EXPECT_EQ(killed, WHITE*KNIGHT);
    //EXPECT_EQ(board.material(WHITE), wm-320);


    board.set_board("8/1P6/8/8/8/8/8/8 w - - 0 1");
    m = Move(B7, B8);
    m.promote_to = QUEEN;
    killed = board.execute_move(m);
    EXPECT_EQ(killed, EMPTY_SQUARE);
    EXPECT_EQ(board.x88[B7], EMPTY_SQUARE);
    EXPECT_EQ(board.x88[B8], QUEEN);

    board.set_board("8/8/8/8/8/8/6p1/8 w - - 0 1");
    m = Move(G2, G1);
    m.promote_to = ROOK;
    killed = board.execute_move(m);
    EXPECT_EQ(killed, EMPTY_SQUARE);
    EXPECT_EQ(board.x88[G2], EMPTY_SQUARE);
    EXPECT_EQ(board.x88[G1], -ROOK);


    board.set_board("8/8/8/8/4K3/8/8/8 w - - 0 1");
    m = Move(E4, F4);
    board.execute_move(m);
    EXPECT_EQ(board.w_king, F4);
    EXPECT_EQ(board.x88[E4], EMPTY_SQUARE);
    EXPECT_EQ(board.x88[F4], KING);


    board.set_board("8/2P5/8/8/8/8/8/8 w - - 0 1");
    m = Move("c7c8q");
    //board.material(WHITE);
    //EXPECT_EQ(board.material(WHITE), 100);
    killed = board.execute_move(m);
    EXPECT_EQ(board.x88[C8], QUEEN);
    EXPECT_EQ(killed, EMPTY_SQUARE);
    //EXPECT_EQ(board.material(WHITE), 900);
}

TEST(boardTest, boardTest_reverse_move_Test){
    Board board;
    Move m;

    board.set_board("8/8/8/8/5K2/8/8/8 w - - 0 1");
    m = Move(E4, F4);
    board.reverse_move(m, EMPTY_SQUARE);
    EXPECT_EQ(board.w_king, E4);
    EXPECT_EQ(board.x88[E4], KING);
    EXPECT_EQ(board.x88[F4], EMPTY_SQUARE);

    board.set_board("8/8/8/2n5/4R3/8/8/8 w - - 0 1");
    m = Move(C5, E4);
    //int wm = board.material(WHITE);
    //int bm = board.material(BLACK);
    int k = board.execute_move(m);
    board.reverse_move(m, k);
    //EXPECT_EQ(wm, board.material(WHITE));
    //EXPECT_EQ(bm, board.material(BLACK));

    board.set_board("8/1P6/8/8/8/8/8/8 w - - 0 1");
    m = Move(B7, B8, QUEEN);
    //EXPECT_EQ(board.material(WHITE), 100);
    board.execute_move(m);
    EXPECT_EQ(board.x88[B8], QUEEN);
    //EXPECT_EQ(board.material(WHITE), 900);
    board.reverse_move(m, EMPTY_SQUARE);
    EXPECT_EQ(board.x88[B7], PAWN);
    //EXPECT_EQ(board.material(WHITE), 100);
}

TEST(boardTest, boardTest_make_move_alt_Test){
    Board board;
    Move m;
    int wm, bm;

    board.set_board("r1bqkb1r/ppp2ppp/2n2n2/4P3/4p3/2N1B2P/PPP2PP1/R2QKBNR w KQkq - 0 1");
    EXPECT_EQ((bool)(board.castling & B_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_KINGSIDE), true);
    m = Move(A8, B8);
    board.make_move_alt(m);
    std::cout << board << std::endl;
    EXPECT_EQ((bool)(board.castling & B_CASTLE_QUEENSIDE), false);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_KINGSIDE), true);

    board.set_board("rn1qkbnr/pp2pppp/2p5/5b2/3PN3/8/PPP2PPP/R1BQKBNR w KQkq - 1 5");
    //wm = board.material(WHITE);
    m = Move(F5, E4);
    board.make_move_alt(m);
    EXPECT_EQ(board.x88[F5], EMPTY_SQUARE);
    EXPECT_EQ(board.x88[E4], BLACK*BISHOP);
    //EXPECT_EQ(board.material(WHITE), wm-320);

    board.set_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //wm = board.material(WHITE);
    //bm = board.material(BLACK);
    m = Move(E2, E4);
    board.make_move_alt(m);
    EXPECT_EQ(board.x88[E4], PAWN);
    EXPECT_EQ(board.x88[E2], EMPTY_SQUARE);
    //EXPECT_EQ(wm, board.material(WHITE));
    //EXPECT_EQ(bm, board.material(BLACK));

    board.set_board("r1bqkb1r/pppp1ppp/2n2n2/4p3/3PP3/2N2N2/PPP2PPP/R1BQKB1R b KQkq - 0 4");
    //wm = board.material(WHITE);
    //bm = board.material(BLACK);
    m = Move(E5, D4);
    board.make_move_alt(m);
    EXPECT_EQ(board.x88[D4], BLACK*PAWN);
    EXPECT_EQ(board.x88[E5], EMPTY_SQUARE);
    //EXPECT_EQ(wm-100, board.material(WHITE));
    //EXPECT_EQ(bm, board.material(BLACK));

    board.set_board("rnbqkb1r/ppp2ppp/5n2/3pp3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 3");
    m = Move(H1, G1);
    board.make_move_alt(m);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);

    board.set_board("rnbqkb1r/ppp2ppp/5n2/3pp3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 3");
    m = Move(E1, E2);
    board.make_move_alt(m);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), false);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);
    m = Move(E2, E1);
    board.make_move_alt(m);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), false);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);


    board.set_board("rnbqkb1r/ppp2ppp/5n2/3pp3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 3");
    m = Move(H1, G1);
    board.make_move_alt(m);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);
    m = Move(G1, F1);
    board.make_move_alt(m);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);

    // white castle kingside
    board.set_board("rnbqkb1r/ppp2ppp/5n2/3pp3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 3");
    m = Move(E1, G1);
    board.make_move_alt(m);
    EXPECT_EQ(board.x88[G1], KING);
    EXPECT_EQ(board.x88[F1], ROOK);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), false);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);

    // black castle queenside
    board.set_board("r3kb1r/ppp2ppp/2n1bn2/3qp3/4P3/1PP2N2/P2P1PPP/RNBQK2R w KQkq - 2 3");
    m = Move(E8, C8);
    board.make_move_alt(m);
    EXPECT_EQ(board.x88[C8], BLACK*KING);
    EXPECT_EQ(board.x88[D8], BLACK*ROOK);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_QUEENSIDE), false);
    EXPECT_EQ((bool)(board.castling & B_CASTLE_KINGSIDE), false);






}

TEST(boardTest, boardTest_undo_move_alt_Test){
    Board board;
    Move m;
    State s;
    int wm, bm;

    board.set_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //wm = board.material(WHITE);
    //bm = board.material(BLACK);
    m = Move(E2, E4);
    s = board.make_move_alt(m);
    board.undo_move_alt(s, m);
    EXPECT_EQ(board.x88[E2], PAWN);
    EXPECT_EQ(board.x88[E4], EMPTY_SQUARE);


    board.set_board("r1bqkb1r/pppp1ppp/2n2n2/4p3/3PP3/2N2N2/PPP2PPP/R1BQKB1R b KQkq - 0 4");
    //wm = board.material(WHITE);
    //bm = board.material(BLACK);
    m = Move(C6, D4);
    s = board.make_move_alt(m);
    board.undo_move_alt(s, m);
    EXPECT_EQ(board.x88[C6], BLACK*KNIGHT);
    EXPECT_EQ(board.x88[D4], PAWN);
    //EXPECT_EQ(wm, board.material(WHITE));
   // EXPECT_EQ(bm, board.material(BLACK));

// white castle kingside
    board.set_board("rnbqkb1r/ppp2ppp/5n2/3pp3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 3");
    m = Move(E1, G1);
    s = board.make_move_alt(m);
    EXPECT_EQ(board.x88[G1], KING);
    EXPECT_EQ(board.x88[F1], ROOK);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), false);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), false);
    board.undo_move_alt(s, m);
    EXPECT_EQ(board.x88[E1], KING);
    EXPECT_EQ(board.x88[H1], ROOK);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_QUEENSIDE), true);
    EXPECT_EQ((bool)(board.castling & W_CASTLE_KINGSIDE), true);




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