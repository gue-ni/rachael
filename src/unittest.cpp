#include <iostream>

#include "Board.h"
#include "Util.h"
#include "Search.h"
#include "Evaluation.h"



int main(){
    Board board("rnbqkb1r/pp2pppp/5n2/3p4/Q1PP1B2/2NB4/PP3PPP/R3K2R w Qkq - 2 6", true);
    //std::cout << board << std::endl;

    //int n;
    //Move moves[256];

    State s = board.make_move_alt(Move("a1b1"));
    //std::cout << board << std::endl;
    board.undo_move_alt(s, Move("a1b1"));

    //std::cout << board << std::endl;

    //n = board.pseudo_legal_for_square(moves, 0, E1);
    //for (int i = 0; i < n; i++) std::cout << moves[i] << std::endl;

    uint8_t x = 0x00;
    x |= W_CASTLE_KINGSIDE;
    x ^= W_CASTLE_KINGSIDE;
    x |= W_CASTLE_KINGSIDE;

    std::cout << (int)x << std::endl;




    return 0;
}
