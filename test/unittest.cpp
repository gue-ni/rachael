#include <iostream>

#include "../src/Board.h"
#include "../src/Engine.h"

int main(){
    /*
    std::vector<int> brd = { 0,  1,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0, -5, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0, -5,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99 };
                             */


    Board board(DEFAULT_BOARD, true);

    board.make_move(Ply("e2e4"));
    board.make_move(Ply("e7e5"));

    board.make_move(Ply("g1f3"));
    board.make_move(Ply("g8h6"));

    board.make_move(Ply("f1c4"));
    board.make_move(Ply("f8c5"));

    board.set_piece(Square("b8"), 0);
    board.set_piece(Square("c8"), 0);
    board.set_piece(Square("d8"), 0);

    //board.make_move(Ply("h1g1"));
    //board.make_move(Ply("g1h1"));

    std::cout << board << std::endl;

    std::vector<Ply> moves = board.generate_valid_moves_square(Square("e8").index());
    for (auto &m : moves) std::cout << m << " ";
    std::cout << std::endl;

    board.make_move(Ply("e8c8"));

    std::cout << board << std::endl;



}
