#include <iostream>

#include "../src/Board.h"
#include "../src/Util.h"
#include "../src/Search.h"
#include "../src/Evaluation.h"

void test_pseudo_legal_moves(Board &board, int color){
    std::vector<Ply> moves = board.pseudo_legal_moves(color);
    std::cout << "pseudo legal moves: ";
    for (auto m : moves) std::cout << m << " ";
    std::cout << std::endl;
}

void test_legal_moves(Board &board, int color){
    std::cout << "legal moves: ";
    std::vector<Ply> moves = board.pseudo_legal_moves(color);
    for (auto m : moves) {
        if (board.is_legal_move(m)) {
            std::cout << m << " ";
        }
    }
    std::cout << std::endl;
}

int main(){



    Board board("8/1P2k3/8/8/8/8/8/7K w - - 0 1", true);
    //Board board(DEFAULT_BOARD, true);
    std::cout << board << std::endl;


    /*std::vector<Ply> moves = board.pseudo_legal_moves(WHITE);
    for (auto m : moves) std::cout << m << " ";
    std::cout << std::endl;*/



    return 0;
}
