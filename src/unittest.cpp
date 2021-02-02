#include <iostream>
#include <sstream>
#include <thread>

#include "../src/Board.h"
#include "../src/Search.h"
#include "Util.h"

std::thread thrd;

int main(){
    //Board board("2k2r2/pp3p2/8/1BbpB3/1P6/4P3/P2P1KPP/2R3NR w - - 0 1", true);
    Board board(DEFAULT_BOARD, true);
    std::cout << board << std::endl;

    clock_t tic, toc;
    tic = clock();
    SearchInfo info;
    info.stop = false;
    info.depth = 7;
    info.time_limit = false;
    info.start_time = get_time();
    thrd = std::thread(iterative_deepening, std::ref(board), std::ref(info));
    thrd.join();
    toc = clock();
    std::cout  << dt(tic, toc) << std::endl;
    return 0;
}
