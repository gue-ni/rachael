#include <iostream>
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

double timer(clock_t tic, clock_t toc){
    return (double)(toc - tic) / CLOCKS_PER_SEC;
}

int main() {
    Board board(true);
    board.draw();

    clock_t tic, toc;
    double dt;


    tic = clock();
    std::vector<Ply> moves = board.generate_valid_moves(BLACK);
    toc = clock();
    for (auto &move : moves) std::cout << move << std::endl;
    printf("%zu moves %f\n", moves.size(), timer(tic, toc));


    /*
    Algebraic square("b7");
    std::cout << "moves for " << square << std::endl;
    for (auto &move : board.generate_valid_moves_piece(square.x88_value())) std::cout << move  << std::endl;
    */

    /*
    tic = clock();
    Ply best_move = AI::find_best_move(board, BLACK, 3);
    toc = clock();
    std::cout << best_move << " " << timer(tic, toc) << std::endl;
     */
    return 0;
}
