//
// Created by jakob on 1/22/21.
//

#ifndef CHESS_ENGINE_CPP_BOARD_H
#define CHESS_ENGINE_CPP_BOARD_H

#define WHITE  1
#define BLACK -1

#define BLACK_TTY   "\033[0;31m"
#define WHITE_TTY   "\033[0;34m"
#define CLEAR_TTY   "\033[0m"

#define N   16
#define S  -16
#define E    1
#define W   -1
#define NE  17
#define NW  15
#define SE -15
#define SW -17
#define NNE 33
#define ENE 18
#define ESE -14
#define SSE -31
#define SSW -33
#define WSW -18
#define WNW 14
#define NNW 31

#define EMPTY 0
#define KING  1
#define QUEEN 2
#define BISHOP 3
#define KNIGHT 4
#define ROOK 5
#define PAWN 6

#define RUY_LOPEZ \
{  5,  4,  3,  2,  1,  0,  0,  5, 99, 99, 99, 99, 99, 99, 99, 99, \
   6,  6,  6,  6,  0,  6,  6,  6, 99, 99, 99, 99, 99, 99, 99, 99, \
   0,  0,  0,  0,  0,  4,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
   0,  0,  0,  0,  6,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
   0,  3,  0,  0, -6,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
   0,  0, -4,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  -6, -6, -6, -6,  0, -6, -6, -6, 99, 99, 99, 99, 99, 99, 99, 99, \
  -5,  0, -3, -2, -1, -3, -4, -5, 99, 99, 99, 99, 99, 99, 99, 99 }

#define DEFAULT_BOARD \
{ 5,  4,  3,  2,  1,  3,  4,  5, 99, 99, 99, 99, 99, 99, 99, 99, \
  6,  6,  6,  6,  6,  6,  6,  6, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
 -6, -6, -6, -6, -6, -6, -6, -6, 99, 99, 99, 99, 99, 99, 99, 99, \
 -5, -4, -3, -2, -1, -3, -4, -5, 99, 99, 99, 99, 99, 99, 99, 99 }

#define EMPTY_BOARD \
{ 0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99, \
  0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99 } \

#include <vector>
#include "Square.h"
#include "Ply.h"

class Board {
public:
    explicit Board(bool draw_color);
    Board(const std::vector<int> &brd, bool draw_color);

    int  get_piece(Square alg);
    void set_piece(Square alg, int piece);

    std::vector<Ply> generate_valid_moves(int color_to_move);
    std::vector<Ply> generate_valid_moves_piece(int square);
    std::vector<Ply> check_directions(int from, int piece, const std::vector<int> &dirs, int max_steps);
    bool is_threatened(int square, int color);

    int  execute_move(Ply ply);
    void reverse_move(Ply ply, int killed_piece);
    int material(int color);

    friend std::ostream& operator<<(std::ostream&, const Board&);

private:
    bool draw_color         = false;
    char pieces[7]          = {'.', 'K', 'Q', 'B', 'N', 'R', 'p'};
    int material_value[7]   = { 0, 200, 9, 5, 3, 3, 1 };
    int x88[128]            = RUY_LOPEZ;
    int w_material          = 0;
    int b_material          = 0;

    int valid_squares[64] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                             0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                             0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                             0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                             0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                             0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                             0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                             0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77};

    void calculate_material();
    inline bool is_empty(int square);
    inline bool is_enemy(int square, int piece);
    inline bool is_friendly(int square, int piece);
    static inline int  get_color(int piece);
    static inline bool off_the_board(int square);
};


#endif //CHESS_ENGINE_CPP_BOARD_H
