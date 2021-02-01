#include <iostream>
#include <sstream>

#include "../src/Board.h"
#include "../src/Search.h"
#include "util.h"


int main(){

    Board board(FRENCH_DEFENSE_BURN_VARIATION, true);
    std::cout << board << std::endl;

    clock_t tic, toc;
    Ply move;
    tic = clock();
    iterative_deepening(board, move, 7);
    toc = clock();
    std::cout << move << " " << dt(tic, toc) << std::endl;

    return 0;
}
