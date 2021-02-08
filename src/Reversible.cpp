//
// Created by jakob on 1/28/21.
//

#include "Reversible.h"

Reversible::Reversible(Ply ply, Piece killed) : Ply(ply.from, ply.to), killed_piece(killed){}

std::ostream &operator<<(std::ostream &strm, const Reversible &p) {
    return strm << SquareClass(p.from) << SquareClass(p.to) << " killed=" << p.killed_piece;
}

Reversible::Reversible(Ply ply) : Ply(ply.from, ply.to), killed_piece(0){}
