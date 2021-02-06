//
// Created by jakob on 1/28/21.
//

#ifndef CHESS_ENGINE_CPP_REVERSIBLE_H
#define CHESS_ENGINE_CPP_REVERSIBLE_H


#include "Ply.h"

class Reversible : public Ply {
public:
    int killed_piece = 0;

    bool w_castle_k = false, w_castle_q = false;
    bool b_castle_q = false, b_castle_k = false;

    Reversible(Ply ply, int killed);
    explicit Reversible(Ply ply);

    friend std::ostream& operator<<(std::ostream&, const Reversible&);
};


#endif //CHESS_ENGINE_CPP_REVERSIBLE_H
