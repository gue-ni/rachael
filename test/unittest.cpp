#include <iostream>
#include <sstream>

#include "../src/engine/SimpleBoard.h"
#include "../src/engine/Search2.h"
#include "util.h"


int main(){

    SimpleBoard board(DEFAULT_BOARD, true);
    std::cout << board << std::endl;

    clock_t tic, toc;
    tic = clock();
    std::optional<Ply> move = search(board, WHITE, 4);
    toc = clock();
    std::cout << move.value() << " " << dt(tic, toc) << std::endl;



    return 0;
}
