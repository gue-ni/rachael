#include <iostream>
#include <memory>
#include "Board.h"
#include "Algrebraic.h"
#include "AI.h"

int main() {
    //std::unique_ptr<Board> board (new Board());

    Board board(true);
    board.draw();

    AI ai;

    std::vector<Ply> legal_moves = board.generate_valid_moves(WHITE);
    for (auto &m : legal_moves) std::cout << m << std::endl;



    //std::cout << ai.find_best_move(board, WHITE, 2) << std::endl;

    return 0;
}
