#ifndef CHESS_ENGINE_CPP_UTIL_H
#define CHESS_ENGINE_CPP_UTIL_H

#include <ctime>
#include <string>
#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>
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

#define A1 0x00
#define B1 0x01
#define C1 0x02
#define D1 0x03
#define E1 0x04
#define F1 0x05
#define G1 0x06
#define H1 0x07
#define A2 0x10
#define B2 0x11
#define C2 0x12
#define D2 0x13
#define E2 0x14
#define F2 0x15
#define G2 0x16
#define H2 0x17
#define A3 0x20
#define B3 0x21
#define C3 0x22
#define D3 0x23
#define E3 0x24
#define F3 0x25
#define G3 0x26
#define H3 0x27
#define A4 0x30
#define B4 0x31
#define C4 0x32
#define D4 0x33
#define E4 0x34
#define F4 0x35
#define G4 0x36
#define H4 0x37
#define A5 0x40
#define B5 0x41
#define C5 0x42
#define D5 0x43
#define E5 0x44
#define F5 0x45
#define G5 0x46
#define H5 0x47
#define A6 0x50
#define B6 0x51
#define C6 0x52
#define D6 0x53
#define E6 0x54
#define F6 0x55
#define G6 0x56
#define H6 0x57
#define A7 0x60
#define B7 0x61
#define C7 0x62
#define D7 0x63
#define E7 0x64
#define F7 0x65
#define G7 0x66
#define H7 0x67
#define A8 0x70
#define B8 0x71
#define C8 0x72
#define D8 0x73
#define E8 0x74
#define F8 0x75
#define G8 0x76
#define H8 0x77

#define RUY_LOPEZ \
"r1bqk1nr/pppp1ppp/2n5/1Bb1p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4"
#define DEFAULT_BOARD \
"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FRENCH_DEFENSE_BURN_VARIATION \
"rnbqkb1r/ppp2ppp/4pn2/3p2B1/3PP3/2N5/PPP2PPP/R2QKBNR b KQkq - 0 5"
#define SICILIAN_DEFENSE \
"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2"
#define SICILIAN_DEFENSE_NAJDORF_VARIATION \
"rnbqkb1r/1p2pppp/p2p1n2/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 6"
#define PAWNS_ONLY \
"8/pp1pp3/7p/8/2p2p2/2P1P3/PP1P1PPP/8 w - - 0 1"

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

extern const Square valid_squares[64];
extern const char pieces[7];
extern const int material_value[7];

class Move;

inline double dt(clock_t tic, clock_t toc){ return  (double)(toc - tic) / CLOCKS_PER_SEC; }

inline uint64_t get_time(){
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
}

inline Square convert_square(std::string sq){
    assert(sq.size() == 2 && 'a' <= sq[0] && sq[0] <= 'h' && '1' <= sq[1] && sq[1] <= '8');
    return 16 * (sq[1] - 49) + (sq[0] - 97);
}

inline int get_rank07(Square x88){ return x88 >> 4; }

inline int get_file07(Square x88){ return x88 & 7; }

inline int convert_8x8(Square sq0x88){ return (sq0x88 + (sq0x88 & 7)) >> 1;}

inline Square convert_x88(int sq8x8){ return sq8x8 + (sq8x8 & ~7); }

inline bool off_the_board(Square sq){ return sq & 0x88; }

inline std::string convert_string(Square sq){
    std::ostringstream str;
    str << (char)(get_file07(sq) + 97) << (char)(get_rank07(sq) + 49);
    return str.str();
}

inline Color get_color(Piece piece) {
    assert(piece != EMPTY_SQUARE);
    return ((piece > 0) ? 1 : ((piece < 0) ? -1 : 0));
}



#endif //CHESS_ENGINE_CPP_UTIL_H
