#include <iostream>
#include <sstream>

#include "../src/engine/SimpleBoard.h"
#include "../src/engine/Search2.h"


int main(){

    SimpleBoard board(RUY_LOPEZ, true);
    std::cout << board << std::endl;


    Search2 s2;
    std::optional<Ply> m1 = s2.search(board, WHITE, 4);
    std::cout << m1.value() << std::endl;



    std::optional<Ply> m2 = s2.iterative_deepening(board, WHITE);
    std::cout << m2.value() << std::endl;


    /*
    clock_t tic, toc;
    tic = clock();
    std::optional<Ply> move = search.search(board, WHITE, 4);
    toc = clock();
    std::cout << move.value() << " " << dt(tic, toc) << std::endl;
    */


    return 0;
}
