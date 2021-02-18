#include <iostream>

#include "Board.h"
#include "Util.h"
#include "Search.h"
#include "Evaluation.h"



int main(){
    Board board("8/6pp/8/p5P1/1p5P/8/PP6/8 w - - 0 1", true);
    std::cout << board << std::endl;


    Move m1(A2, A4);
    Move m2(B2, B3);
    State s1 = board.make_move(m1);
    std::cout << board << std::endl;
    State s2 = board.make_move(m2);
    std::cout << board << std::endl;

    /*
    std::cout << "reverse" << std::endl;
    board.undo_move(s2, m2);
    std::cout << board << std::endl;
    board.undo_move(s1, m1);
    std::cout << board << std::endl;
    */

    Move moves[256];
    int n = board.pseudo_legal_for_square(moves, 0, B4);
    for (int i = 0; i < n; i++) std::cout << moves[i] << std::endl;

    return 0;
}
