//
// Created by jakob on 1/28/21.
//

#include "Reversible.h"

Reversible::Reversible(Ply ply, Piece killed) : Ply(ply.from, ply.to), killed_piece(killed){}

std::ostream &operator<<(std::ostream &strm, Reversible &p) {
    return strm << p.as_string() << " killed=" << p.killed_piece;
}

Reversible::Reversible(Ply ply) : Ply(ply.from, ply.to), killed_piece(0){}
