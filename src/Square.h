
#ifndef CHESS_ENGINE_CPP_SQUARE_H
#define CHESS_ENGINE_CPP_SQUARE_H

#include <ostream>

struct Square {
    int  rank;
    char file;

    Square(int x, int y);
    Square(char f, int r);
    explicit Square(int x88);
    explicit Square(std::string str);

    int index();
    bool is_valid();

    friend std::ostream& operator<<(std::ostream&, const Square&);
    friend bool operator==(const Square& sq1, const Square& sq2);

    static inline int sq8x8(int x88) {
        return (x88 + (x88 & 7)) >> 1;
    }

    static inline int sq0x88(int sq8x8) {
        return sq8x8 + (sq8x8 & ~7);
    }

    static inline bool off_the_board(int sq) {
        return sq & 0x88;
    }
};


#endif //CHESS_ENGINE_CPP_SQUARE_H
