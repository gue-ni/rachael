#ifndef CHESS_ENGINE_CPP_UTIL_H
#define CHESS_ENGINE_CPP_UTIL_H

#include <ctime>
#include <string>
#include <cassert>
#include <chrono>
#include <iostream>
#include <sstream>

#define WHITE  1
#define BLACK -1

#define N    16
#define S   -16
#define E     1
#define W    -1
#define NE   17
#define NW   15
#define SE  -15
#define SW  -17
#define NNE  33
#define ENE  18
#define ESE -14
#define SSE -31
#define SSW -33
#define WSW -18
#define WNW  14
#define NNW  31

#define EMPTY_SQUARE    0
#define KING            1
#define QUEEN           2
#define BISHOP          3
#define KNIGHT          4
#define ROOK            5
#define PAWN            6

typedef int8_t Color;
typedef int8_t Piece;
typedef int8_t Square;

inline double dt(clock_t tic, clock_t toc){
    return  (double)(toc - tic) / CLOCKS_PER_SEC;
}

inline uint64_t get_time(){
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
}

inline Square convert_square(std::string sq){
    assert(sq.size() == 2 && 'a' <= sq[0] && sq[0] <= 'h' && '1' <= sq[1] && sq[1] <= '8');
    return 16 * (sq[1] - 49) + (sq[0] - 97);
}

inline int get_rank07(Square x88){
    return x88 >> 4;
}

inline int get_file07(Square x88){
    return x88 & 7;
}
inline std::string convert_string(Square sq){
    //int8_t file07 = sq & 7;
    //int8_t rank07 = sq >> 4;
    //std::cout << "file=" << (int)file07 << ", rank=" << (int)rank07 << std::endl;
    std::ostringstream str;
    str << (char)(get_file07(sq) + 97) << (char)(get_rank07(sq) + 49);
    return str.str();
}

inline int convert_8x8(Square sq0x88) {
    return (sq0x88 + (sq0x88 & 7)) >> 1;
}

inline Square convert_x88(int sq8x8) {
    return sq8x8 + (sq8x8 & ~7);
}

inline bool off_the_board(Square sq) {
    return sq & 0x88;
}


#endif //CHESS_ENGINE_CPP_UTIL_H
