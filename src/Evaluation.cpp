//
// Created by jakob on 2/1/21.
//

#include "Evaluation.h"

int evaluation_1(Board &board) {
    int mobility =     (int) board.gen_pseudo_legal_moves(WHITE).size()
                       - (int) board.gen_pseudo_legal_moves(BLACK).size();

    //std::cout << "mobility: " << mobility << std::endl;

    int material = board.material(WHITE) - board.material(BLACK);

    //std::cout << "material: " << material << std::endl;

    return mobility + material;
}
