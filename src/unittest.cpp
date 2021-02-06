#include <iostream>

#include "Board.h"
#include "Evaluation.h"


int main(){

    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", true);
    std::cout << board << std::endl;

    int val = Evaluation::evaluation_2(board);
    std::cout << "Evaluation: " << val << std::endl;


    return 0;
}
