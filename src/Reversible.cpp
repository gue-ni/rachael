//
// Created by jakob on 1/28/21.
//

#include "Reversible.h"

Reversible::Reversible(Ply ply, int killed) : Ply(ply.from, ply.to), killed_piece(killed){}

std::ostream &operator<<(std::ostream &strm, const Reversible &p) {
    return strm << Square(p.from) << Square(p.to)
    << " killed=" << p.killed_piece
    << " w_king_moved=" << p.w_king_moved;
}

Reversible::Reversible(Ply ply) : Ply(ply.from, ply.to), killed_piece(0){}
