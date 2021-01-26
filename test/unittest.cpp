#include <iostream>
#include <climits>

#include "../src/Board.h"
#include "../src/AI.h"

int main(){

    std::vector<int> brd = { 0,  1,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0, -5, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0, -5,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99 };

    Board board(brd, false);
    std::cout << board << std::endl;

    int eval = AI::evaluation(board);
    std::cout << "evaluation: " << eval << std::endl;

    std::cout << "possible moves: ";
    for (auto m : board.generate_valid_moves(BLACK)) std::cout << m << " ";
    std::cout << std::endl;

    Ply best = AI::negamax_alphabeta_failsoft(board, BLACK, 3);
    std::cout << "best: " << best << std::endl;

}
