#include <iostream>

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

    /*
    int eval = AI::evaluation(board);
    std::cout << "evaluation: " << eval << std::endl;

    std::cout << "possible moves: ";
    for (auto m : board.generate_valid_moves(WHITE)) std::cout << m << " ";
    std::cout << std::endl;
    */

    std::optional<Ply> best = AI::negamax_alphabeta_failsoft(board, WHITE, 3);

    if (best.has_value()){
        std::cout << "best: " << best.value() << std::endl;
    } else {
        std::cout << "checkmate" << std::endl;
    }

    /*
    board.execute_move(best);
    std::cout << board << std::endl;

    best = AI::negamax_alphabeta_failsoft(board, WHITE, 3);
    std::cout << "best: " << best << std::endl;
     */


}
