#include <iostream>
#include <memory>
#include "Board.h"
#include "Algrebraic.h"

int main() {
    //std::unique_ptr<Board> board (new Board());

    Board board(true);
    board.draw();


    std::vector<Ply> legal_moves = board.generate_valid_moves_piece(Algebraic("d4"));
    for (auto &m : legal_moves) std::cout << m << std::endl;

    //std::vector<int> directions{N, S, E, W};
    //std::vector<Ply> legal_moves = board.check_directions(Algebraic("c4"), std::vector<int>{N, S, E, W}, 1);
    //for (auto &d : legal_moves) std::cout << d << std::endl;




    return 0;
}
