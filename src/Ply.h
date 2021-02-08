
#ifndef CHESS_ENGINE_CPP_PLY_H
#define CHESS_ENGINE_CPP_PLY_H


#include <string>

#include "SquareClass.h"
#include "Util.h"

struct Ply {
    Square from;
    Square to;

    Ply();
    Ply(Square f, Square t);

    explicit Ply(std::string move);

    std::string as_string();

    friend std::ostream& operator<<(std::ostream&, const Ply&);
    friend bool operator==(const Ply& one, const Ply& two);
    friend bool operator<(Ply& p1, Ply& p2);

};


#endif //CHESS_ENGINE_CPP_PLY_H
