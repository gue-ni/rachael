//
// Created by jakob on 1/28/21.
//

#ifndef CHESS_ENGINE_CPP_REVERSIBLEPLY_H
#define CHESS_ENGINE_CPP_REVERSIBLEPLY_H


#include "Ply.h"

class ReversiblePly : public Ply {
public:
    int killed_piece;
    bool w_king_first_move;
    bool w_l_rook_first_move;
    bool w_r_rook_first_move;

    bool b_king_first_move;
    bool b_l_rook_first_move;
    bool b_r_rook_first_move;

    ReversiblePly(Ply ply, int killed);

};


#endif //CHESS_ENGINE_CPP_REVERSIBLEPLY_H
