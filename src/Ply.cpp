
#include <cassert>
#include <sstream>
#include <iostream>

#include "Ply.h"

Ply::Ply(std::string move) : from(SquareClass(move[0], move[1] - 48).index()),
to(SquareClass(move[2], move[3] - 48).index()){
    assert(move.size() == 4);
}

Ply::Ply(Square f, Square t) : from(f), to(t) {}

std::ostream& operator<<(std::ostream &strm, const Ply &p) {
    return strm << SquareClass(p.from) << SquareClass(p.to);
}

bool operator==(const Ply &one, const Ply& two){
    return one.to == two.to && one.from == two.from;
}

std::string Ply::as_string() {
    std::ostringstream str;
    str << SquareClass(from) << SquareClass(to);
    return str.str();
}

Ply::Ply() : Ply("e1e1"){}

bool operator<(Ply &p1, Ply &p2) {
    return p1.as_string() < p2.as_string();
}




