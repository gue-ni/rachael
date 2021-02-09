#ifndef CHESS_ENGINE_CPP_REVERSIBLE_H
#define CHESS_ENGINE_CPP_REVERSIBLE_H


#include "Move.h"
#include "Util.h"

class Reversible : public Move {
public:

    Piece killed_piece = 0;
    int fifty_moves;

    bool w_castle_k = false, w_castle_q = false;
    bool b_castle_q = false, b_castle_k = false;

    Reversible(Move ply, Piece killed);
    explicit Reversible(Move ply);

    friend std::ostream& operator<<(std::ostream&, Reversible&);
};


#endif //CHESS_ENGINE_CPP_REVERSIBLE_H
