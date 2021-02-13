#include <iostream>

#include "Board.h"
#include "Util.h"
#include "Search.h"
#include "Evaluation.h"



int main(){
    Board board("8/R2P4/8/8/8/8/3p4/8 w - - 0 1", true);
    std::cout << board << std::endl;
    std::cout << board.material << std::endl;
    Move m("d2d1q");
    State s = board.make_move_alt(m);
    std::cout << board << std::endl;
    std::cout << board.material << std::endl;
    board.undo_move_alt(s, m);
    std::cout << board << std::endl;
    std::cout << board.material << std::endl;

    return 0;
}
