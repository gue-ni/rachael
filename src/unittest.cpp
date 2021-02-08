#include <iostream>

#include "Board.h"
#include "Util.h"
#include "Search.h"
#include "Evaluation.h"

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

    //Board board("1rb1k3/p7/3b1Q2/3Np3/3P4/8/PPPBBPPR/R3K3 w Q - 1 23", true);
    //Board board("4k3/8/5Q2/3N4/8/8/8/3K4 w - - 1 24", true);
    Board board(DEFAULT_BOARD, true);
    std::cout << board << std::endl;

    Ply p;
    p = Ply("e2e4r");
    std::cout << p << std::endl;
    std::cout << (int)p.promote_to << std::endl;


    return 0;
}
