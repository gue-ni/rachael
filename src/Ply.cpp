
#include <cassert>
#include <sstream>

#include "Ply.h"
#include "Util.h"


Ply::Ply() : Ply(-1, -1){}

Ply::Ply(const std::string& move) :
from(convert_square(move.substr(0,2))), to(  convert_square(move.substr(2,2))){

    if (move.size() == 5){
        switch (toupper(move[4])){
            case 'Q':
                promote_to = QUEEN;
                break;
            case 'B':
                promote_to = BISHOP;
                break;
            case 'R':
                promote_to = ROOK;
                break;
            case 'N':
                promote_to = KNIGHT;
                break;
            default:
                assert(false);
        }
    }
}

Ply::Ply(Square f, Square t) : from(f), to(t) {}

std::ostream& operator<<(std::ostream &strm, Ply &p) {
    return strm << p.as_string();
}

bool operator==(const Ply &one, const Ply& two){
    return one.to == two.to && one.from == two.from;
}

std::string Ply::as_string() {
    if (from == -1 || to == -1) return "0000";
    std::ostringstream str;
    str << convert_string(from) << convert_string(to);
    return str.str();
}

bool operator<(Ply &p1, Ply &p2) {
    return p1.as_string() < p2.as_string();
}




