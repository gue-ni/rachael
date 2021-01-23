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

#include <vector>
#include "Algrebraic.h"
#include "Ply.h"

class Board {
public:
    Board(bool draw_color);

    int material(int color);

    int  get_piece(Algebraic alg);
    void set_piece(Algebraic alg, int piece);

    std::vector<Ply> generate_valid_moves(int color);
    std::vector<Ply> check_directions(Algebraic pos, std::vector<int> dirs, int max_steps);
    std::vector<Ply> generate_valid_moves_piece(Algebraic pos);

    int  execute_move(Ply ply);
    void reverse_move(Ply ply, int killed_piece);

    void draw();

    static uint8_t x88_conv(uint8_t x, uint8_t y);
    static uint8_t x88_conv(Algebraic alg);

    bool is_empty(int square);
    bool is_enemy(int square, int piece);
    bool is_friendly(int square, int piece);
    int get_color(int piece);
    static bool off_the_board(uint8_t square);

private:

    bool draw_color = false;
    char pieces[7] = {'.', 'K', 'Q', 'B', 'N', 'R', 'p'};
    int material_value[7] = { 0, 200, 9, 5, 3, 3, 1 };
    int x88[128] = {   5,  4,  3,  2,  1,  3,  4,  5, 99, 99, 99, 99, 99, 99, 99, 99,
                       6,  6,  6,  6,  6,  6,  6,  6, 99, 99, 99, 99, 99, 99, 99, 99,
                       0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                       0,  0,  0,  -1,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                       0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                       0,  0,  0,  0,  0,  0,  0,  0, 99, 99, 99, 99, 99, 99, 99, 99,
                      -6, -6, -6, -6, -6, -6, -6, -6, 99, 99, 99, 99, 99, 99, 99, 99,
                      -5, -4, -3, -2, -1, -3, -4, -5, 99, 99, 99, 99, 99, 99, 99, 99 };

    int w_material = -1;
    int b_material = -1;

    void calculate_material();



};


#endif //CHESS_ENGINE_CPP_BOARD_H
