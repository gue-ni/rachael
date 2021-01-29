
#include <cassert>
#include <sstream>

#include "Ply.h"


Ply::Ply(Square from, Square to)  : from(from), to(to) {}

Ply::Ply(std::string move) : from(move[0], move[1]-48), to(move[2], move[3]-48){
    assert(move.size() == 4);
}

Ply::Ply(int f, int t) : from(Square(f)), to(Square(t)) {}

std::ostream& operator<<(std::ostream &strm, const Ply &p) {
    return strm << p.from.file << p.from.rank << p.to.file << p.to.rank;
}

bool Ply::is_valid() {
    return from.is_valid() && to.is_valid();
}

bool operator==(const Ply &one, const Ply& two){
    return one.to == two.to && one.from == two.from;
}

std::string Ply::as_string() {
    std::ostringstream str;
    str << from.file << from.rank << to.file << to.rank;
    return str.str();
}

Ply::Ply() : from(0x00), to(0x00){}


