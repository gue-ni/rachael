#include <iostream>
#include <sstream>

#include "../src/engine/SimpleBoard.h"
#include "../src/engine/Search.h"


int main(){

    SimpleBoard board(RUY_LOPEZ, true);
    std::cout << board << std::endl;

    std::istringstream ss("wow this works");

    do {
        std::string cmd;
        ss >> cmd;
        std::cout << cmd << std::endl;
    } while (ss);


    /*
    clock_t tic, toc;
    tic = clock();
    std::optional<Ply> move = search.search(board, WHITE, 4);
    toc = clock();
    std::cout << move.value() << " " << dt(tic, toc) << std::endl;
    */


    return 0;
}
