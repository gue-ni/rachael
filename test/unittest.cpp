#include <iostream>
#include "../src/SimpleBoard.h"
#include "../src/Search.h"
#include "util.h"


int main(){
    SimpleBoard board(RUY_LOPEZ, true);
    std::cout << board << std::endl;

    Search s1(NEGAMAX_ALPHABETA_FAILHARD, true);

    std::vector<Ply> moves = board.generate_valid_moves(WHITE);
    s1.move_ordering(board, moves);

}
