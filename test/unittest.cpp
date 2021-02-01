#include <iostream>
#include <sstream>
#include <thread>

#include "../src/Board.h"
#include "../src/Search.h"
#include "util.h"

std::thread thrd;

int main(){

    Board board(FRENCH_DEFENSE_BURN_VARIATION, true);
    std::cout << board << std::endl;

    clock_t tic, toc;
    Ply move;
    tic = clock();
    bool stop = false;
    thrd = std::thread(iterative_deepening, std::ref(board), std::ref(move), 7, std::ref(stop));
    //thrd.join();
    toc = clock();
    std::cout << move << " " << dt(tic, toc) << std::endl;

    return 0;
}
