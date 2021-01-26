#include <iostream>
#include "Board.h"
#include "Square.h"
#include "AI.h"

int take_turn(Board &board, int color, int ply, int search_depth) {
    clock_t tic = clock();
    std::optional<Ply> best_move = AI::negamax_alphabeta_failsoft(board, color, search_depth);
    clock_t toc = clock();
    double dt = (double)(toc - tic) / CLOCKS_PER_SEC;

    if (best_move.has_value()){
        board.execute_move(best_move.value());
        std::cout << "Ply " << ply << ":\n"
                  << board
                  << (color == WHITE ? "white" : "black")
                  << " moves " << best_move.value()
                  << ", found after " << dt << " seconds"
                  << std::endl
                  << std::endl;

        return 0;

    } else {
        std::cout
        << (color == WHITE ? "white" : "black")
        << " checkmate" << std::endl;
        return 1;
    }
}

int main(int argc, char **argv) {
    int plies = 1, search_depth = 3, turns = 5;

    if (argc == 3){
        search_depth    = atoi(argv[1]);
        turns           = atoi(argv[2]);
    }

    /*
    std::vector<int> brd = { 1,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0, -5, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0, -5,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                             0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99 };
    Board board(brd,true);
     */

    Board board(true);

    std::cout
    << "search_depth=" << search_depth
    << ", turns=" << turns
    << ", white_material=" << board.material(WHITE)
    << ", black_material=" << board.material(BLACK)
    << std::endl;

    std::cout << "\n" << board << std::endl;

    while (turns > 0){
         if (take_turn(board, WHITE, plies++, search_depth)) break;
         if (take_turn(board, BLACK, plies++, search_depth)) break;
         turns--;
     }

     std::cout
     <<   "white_material=" << board.material(WHITE)
     << ", black_material=" << board.material(BLACK)
     << std::endl;
    return 0;
}
