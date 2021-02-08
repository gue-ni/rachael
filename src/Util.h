

#ifndef CHESS_ENGINE_CPP_UTIL_H
#define CHESS_ENGINE_CPP_UTIL_H

#include <ctime>
#include <chrono>

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


#endif //CHESS_ENGINE_CPP_UTIL_H
