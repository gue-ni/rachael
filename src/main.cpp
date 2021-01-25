#include <iostream>
#include "Board.h"
#include "Algrebraic.h"
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

    std::cout << "Ply " << ply << ":" << std::endl;
    board.draw();
    std::cout << (color == WHITE ? "white" : "black") << " moves "
    << best_move << ", found after " << dt << " seconds" << std::endl << std::endl;

}

double timer(clock_t tic, clock_t toc){
    return (double)(toc - tic) / CLOCKS_PER_SEC;
}

int main() {
    Board board(true);
    board.draw();

    /*
    clock_t tic, toc;
    std::vector<Ply> moves;
    tic = clock();
    moves = board.omp_generate_valid_moves(WHITE);
    toc = clock();
    printf("%zu moves %f\n", moves.size(), timer(tic, toc));

    tic = clock();
    moves = board.generate_valid_moves(WHITE);
    toc = clock();
    printf("%zu moves %f\n", moves.size(), timer(tic, toc));

    tic = clock();
    Ply best_move = AI::find_best_move(board, WHITE, 3);
    toc = clock();
    std::cout << best_move << " " << timer(tic, toc) << std::endl;
     */

    int turns = 4;
    int ply_count = 0;

    while (--turns > 0){
        take_turn(board, WHITE, ply_count++);
        take_turn(board, BLACK, ply_count++);
    }
    return 0;
}
