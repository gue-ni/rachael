//
// Created by jakob on 1/22/21.
//

#ifndef CHESS_ENGINE_CPP_PLY_H
#define CHESS_ENGINE_CPP_PLY_H


#include <string>
#include "Algrebraic.h"

class Ply {
public:
    Algebraic from;
    Algebraic to;

    Ply(Algebraic from, Algebraic to);
    Ply(int f, int t);
    explicit Ply(std::string move);
    friend std::ostream& operator<<(std::ostream&, const Ply&);
};


#endif //CHESS_ENGINE_CPP_PLY_H
