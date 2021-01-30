#include <iostream>

#include "../src/engine/SimpleBoard.h"
#include "../src/engine/Search.h"


int main(){

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    SimpleBoard board(fen, true);
    std::cout << board << std::endl;


    /*
    clock_t tic, toc;
    tic = clock();
    std::optional<Ply> move = search.find_best_move(board, WHITE, 4);
    toc = clock();
    std::cout << move.value() << " " << dt(tic, toc) << std::endl;
    */

   ;


}
