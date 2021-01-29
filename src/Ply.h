
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

    bool is_valid();
    std::string as_string();

    friend std::ostream& operator<<(std::ostream&, const Ply&);
    friend bool operator==(const Ply& one, const Ply& two);
};


#endif //CHESS_ENGINE_CPP_PLY_H
