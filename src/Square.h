//
// Created by jakob on 1/22/21.
//

#ifndef CHESS_ENGINE_CPP_SQUARE_H
#define CHESS_ENGINE_CPP_SQUARE_H

#include <ostream>

class Square {
public:
    int  rank;
    char file;

    Square(char f, int r);
    Square(int x, int y);
    explicit Square(int x88);
    explicit Square(std::string str);

    uint8_t index();
    bool isValid();

    friend std::ostream& operator<<(std::ostream&, const Square&);
};


#endif //CHESS_ENGINE_CPP_SQUARE_H
