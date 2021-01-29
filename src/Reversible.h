//
// Created by jakob on 1/28/21.
//

#ifndef CHESS_ENGINE_CPP_REVERSIBLE_H
#define CHESS_ENGINE_CPP_REVERSIBLE_H


#include "Ply.h"

class Reversible : public Ply {
public:
    int killed_piece = 0;

    // previous state
    /*
    bool w_king_moved       = false;
    bool w_l_rook_moved     = false;
    bool w_r_rook_moved     = false;
    bool b_king_moved       = false;
    bool b_l_rook_moved     = false;
    bool b_r_rook_moved     = false;
    */

    Reversible(Ply ply, int killed);
    explicit Reversible(Ply ply);

    friend std::ostream& operator<<(std::ostream&, const Reversible&);
};


#endif //CHESS_ENGINE_CPP_REVERSIBLE_H
