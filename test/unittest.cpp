#include <iostream>
#include <sstream>

#include "../src/engine/Board.h"
#include "../src/engine/Search2.h"
#include "util.h"


int main(){

    Board board(DEFAULT_BOARD, true);
    std::cout << board << std::endl;

    clock_t tic, toc;
    tic = clock();
    std::optional<Ply> move = iterative_deepening(board);
    toc = clock();
    std::cout << move.value() << " " << dt(tic, toc) << std::endl;

    return 0;
}
