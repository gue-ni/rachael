//
// Created by jakob on 1/22/21.
//

#ifndef CHESS_ENGINE_CPP_PLY_H
#define CHESS_ENGINE_CPP_PLY_H


#include <string>
#include "Square.h"

class Ply {
public:
    Square from;
    Square to;

    Ply();
    Ply(int f, int t);
    Ply(Square from, Square to);
    explicit Ply(std::string move);
    friend std::ostream& operator<<(std::ostream&, const Ply&);
};


#endif //CHESS_ENGINE_CPP_PLY_H
