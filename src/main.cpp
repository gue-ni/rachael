#include <iostream>
#include <memory>
#include "Board.h"
#include "Algrebraic.h"
#include "AI.h"

int search_depth = 3;

void take_turn(Board& board, int color){
    clock_t tic, toc;
    tic = clock();
    Ply best_move = AI::find_best_move(board, color, search_depth);
    toc = clock();
    double dt = (double)(toc - tic) / CLOCKS_PER_SEC;

    board.execute_move(best_move);

    board.draw();

    std::cout << best_move << " found after " << dt << " seconds" << std::endl;

}

int main() {

    Board board(true);
    //board.draw();


    std::vector<Ply> moves = board.generate_valid_moves(WHITE);
    for (auto &move : moves) std::cout << move << std::endl;
    std::cout << moves.size() << " moves" << std::endl;

    int eval = AI::evaluation(board);
    std::cout << "evaluation: " << eval << std::endl;

    Ply best_move = AI::find_best_move(board, WHITE, 4);
    std::cout << "best move: " << best_move << std::endl;




    return 0;
}
