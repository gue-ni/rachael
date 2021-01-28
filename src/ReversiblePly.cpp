//
// Created by jakob on 1/28/21.
//

#include "ReversiblePly.h"

ReversiblePly::ReversiblePly(Ply ply, int killed) : Ply(ply.from, ply.to), killed_piece(killed){}

std::ostream &operator<<(std::ostream &strm, const ReversiblePly &p) {
    return strm << p.from.file << p.from.rank << p.to.file << p.to.rank
    << " killed=" << p.killed_piece
    << " w_king_moved=" << p.w_king_moved;
}

ReversiblePly::ReversiblePly(Ply ply) : Ply(ply.from, ply.to), killed_piece(0){}
