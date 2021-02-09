
#ifndef CHESS_ENGINE_CPP_PLY_H
#define CHESS_ENGINE_CPP_PLY_H

#include <string>

#include "Util.h"

struct Move {
    Square from, to;
    Piece promote_to;

    Move();
    Move(Square f, Square t);
    Move(Square f, Square t, Piece promote);
    explicit Move(const std::string& move);
    Move(const std::string &move, Piece promote);

    std::string as_string();

    friend std::ostream& operator<<(std::ostream&, Move&);
    friend bool operator==(const Move& one, const Move& two);
    friend bool operator<(Move& p1, Move& p2);
};

#endif //CHESS_ENGINE_CPP_PLY_H
