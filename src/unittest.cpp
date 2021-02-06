#include <iostream>

#include "Board.h"
#include "Search.h"

void test_pseudo_legal_moves(Board &board, int color){
    std::vector<Ply> moves = board.pseudo_legal_moves(color);
    for (auto m : moves) std::cout << m << " ";
    std::cout << std::endl;
}

void test_legal_moves(Board &board, int color){
    std::vector<Ply> moves = board.pseudo_legal_moves(color);
    for (auto m : moves) {
        if (board.is_legal_move(m)) std::cout << m << " ";
    }
    std::cout << std::endl;
}

int main(){

    Board board("1rb1k3/p7/3b1Q2/3Np3/3P4/8/PPPBBPPR/R3K3 w Q - 1 23", true);
    std::cout << board << std::endl;

    test_pseudo_legal_moves(board, WHITE);
    test_legal_moves(board, WHITE);

    SearchInfo info;
    //info.depth = 2;
    Search::iterative_deepening(board, info, WHITE);
    return 0;
}
