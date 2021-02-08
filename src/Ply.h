
#ifndef CHESS_ENGINE_CPP_PLY_H
#define CHESS_ENGINE_CPP_PLY_H

#include <string>

#include "Util.h"

struct Ply {
    Square from, to;
    Piece promote_to;

    Ply();
    Ply(Square f, Square t);

    explicit Ply(const std::string& move);

    std::string as_string();

    friend std::ostream& operator<<(std::ostream&, Ply&);

    friend bool operator==(const Ply& one, const Ply& two);
    friend bool operator<(Ply& p1, Ply& p2);
};


#endif //CHESS_ENGINE_CPP_PLY_H
