//
// Created by jakob on 1/22/21.
//

#ifndef CHESS_ENGINE_CPP_ALGREBRAIC_H
#define CHESS_ENGINE_CPP_ALGREBRAIC_H

#include <ostream>

class Algebraic {
public:
    int  rank;
    char file;

    Algebraic(char f, int r);
    Algebraic(int x, int y);
    explicit Algebraic(int x88);
    explicit Algebraic(std::string str);

    uint8_t x88_value();
    bool isValid();

    friend std::ostream& operator<<(std::ostream&, const Algebraic&);
};


#endif //CHESS_ENGINE_CPP_ALGREBRAIC_H
