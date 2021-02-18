
#include <cassert>
#include <sstream>

#include "Move.h"
#include "Util.h"


Move::Move() : Move(-1, -1){}

Move::Move(const std::string& move) :
from(convert_square(move.substr(0,2))), to(  convert_square(move.substr(2,2))), promote_to(0) {

    if (move.size() == 5){
        switch (tolower(move[4])){
            case 'q':
                promote_to = QUEEN;
                break;
            case 'b':
                promote_to = BISHOP;
                break;
            case 'r':
                promote_to = ROOK;
                break;
            case 'n':
                promote_to = KNIGHT;
                break;
            default:
                assert(false);
        }
    }
}

Move::Move(Square f, Square t) : from(f), to(t), promote_to(0) {}

std::ostream& operator<<(std::ostream &strm, Move &p) {
    return strm << p.as_string();
}

bool operator==(const Move &m1, const Move& m2){
    return m1.to == m2.to && m1.from == m2.from;
}

std::string Move::as_string() {
    if (from == -1 || to == -1) return "0000";
    std::ostringstream str;
    str << convert_string(from) << convert_string(to);
    if (promote_to != 0){
        str << (char)tolower(pieces[promote_to]);
    }
    return str.str();
}

bool operator<(Move &p1, Move &p2) {
    return p1.as_string() < p2.as_string();
}

Move::Move(Square f, Square t, Piece promote) : Move(f, t){
    promote_to = promote;
}

Move::Move(const std::string &move, Piece promote) : Move(move) {
    promote_to = promote;
}




