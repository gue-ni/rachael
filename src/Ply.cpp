//
// Created by jakob on 1/22/21.
//

#include <iostream>
#include "Ply.h"


Ply::Ply(Square from, Square to)  : from(from), to(to) {}

Ply::Ply(std::string move) : from(move[0], move[1]-48), to(move[2], move[3]-48){}

Ply::Ply(int f, int t) : from(Square(f)), to(Square(t)) {}

std::ostream& operator<<(std::ostream &strm, const Ply &p) {
    return strm << p.from.file << p.from.rank << p.to.file << p.to.rank;
}

Ply::Ply() : from(0), to(0){}


