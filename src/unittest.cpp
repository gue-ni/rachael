#include <iostream>
#include <sstream>
#include <thread>

#include "../src/Board.h"
#include "../src/Search.h"
#include "util.h"

std::thread thrd;

int main(){


    //Board board("2k2r2/pp3p2/8/1BbpB3/1P6/4P3/P2P1KPP/2R3NR w - - 0 1", true);
    Board board(DEFAULT_BOARD, true);
    std::cout << board << std::endl;

    clock_t tic, toc;
    Ply move;
    tic = clock();
    bool stop = false;
    SearchState ss;
    thrd = std::thread(iterative_deepening, std::ref(board), std::ref(move), std::ref(ss), 99, std::ref(stop));
    thrd.join();
    toc = clock();
    std::cout << move << " " << dt(tic, toc) << std::endl;

    return 0;
}
