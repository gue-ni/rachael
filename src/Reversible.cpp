//
// Created by jakob on 1/28/21.
//

#include "Reversible.h"

Reversible::Reversible(Move ply, Piece killed) : Move(ply.from, ply.to), killed_piece(killed){}

std::ostream &operator<<(std::ostream &strm, Reversible &p) {
    return strm << p.as_string() << " killed=" << p.killed_piece;
}

Reversible::Reversible(Move ply) : Move(ply.from, ply.to), killed_piece(0){}
