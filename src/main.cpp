#include <iostream>
#include "Board.h"
#include "Square.h"
#include "AI.h"

int search_depth = 3;

void take_turn(Board& board, int color, int ply){
    clock_t tic, toc;
    double dt;

    tic = clock();
    Ply best_move = AI::find_best_move(board, color, search_depth);
    toc = clock();
    dt = (double)(toc - tic) / CLOCKS_PER_SEC;

    board.execute_move(best_move);

    std::cout << "Ply " << ply << ":\n"
    << board
    << (color == WHITE ? "white" : "black") << " moves " << best_move
    << ", found after " << dt << " seconds" << std::endl << std::endl;
}

double timer(clock_t tic, clock_t toc){
    return (double)(toc - tic) / CLOCKS_PER_SEC;
}

int main() {
    Board board(true);
    std::cout << board;

    /*
    clock_t tic, toc;

    tic = clock();
    std::vector<Ply> moves = board.generate_valid_moves(WHITE);
    toc = clock();
    printf("%zu moves %f\n", moves.size(), timer(tic, toc));

    tic = clock();
    Ply best_move = AI::find_best_move(board, WHITE, 3);
    toc = clock();
    std::cout << best_move << " " << timer(tic, toc) << std::endl;
     */

    int turns = 10, plies = 0;

    while (turns > 0){
        take_turn(board, WHITE, plies++);
        take_turn(board, BLACK, plies++);
        turns--;
    }

    return 0;
}
