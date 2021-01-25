#include <iostream>
#include "Board.h"
#include "Square.h"
#include "AI.h"


void take_turn(Board &board, int color, int ply, int search_depth) {
    clock_t tic, toc;
    double dt;

    tic = clock();
    Ply best_move = AI::negamax_alphabeta_failsoft(board, color, search_depth);
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

int main(int argc, char **argv) {
    int plies = 1, search_depth, turns;

    if (argc == 3){
        search_depth    = atoi(argv[1]);
        turns           = atoi(argv[2]);
    } else {
        search_depth = 3;
        turns = 5;
    }
    std::vector<int> brd = { 1,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0, -5, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0, -5,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99 };

    Board board(brd,true);

    std::cout
    << "search_depth=" << search_depth
    << ", turns=" << turns
    << ", white_material=" << board.material(WHITE)
    << ", black_material=" << board.material(BLACK)
    << std::endl;

    std::cout << "\n" << board << std::endl;

    while (turns > 0){
         take_turn(board, WHITE, plies++, search_depth);
         take_turn(board, BLACK, plies++, search_depth);
         turns--;
     }

     std::cout
     << "white_material="   << board.material(WHITE)
     << ", black_material=" << board.material(BLACK)
     << std::endl;
    return 0;
}
