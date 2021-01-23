//
// Created by jakob on 1/22/21.
//

#include <cassert>
#include <cctype>
#include <iostream>
#include "Board.h"

Board::Board(bool draw_color) : draw_color(draw_color) {
    calculate_material();
}

std::vector<Ply> Board::generate_valid_moves(int color) {


    // TODO
}

int Board::get_piece(Algebraic alg) {
    return x88[x88_conv(alg)];
}

int Board::material(int color) {
    return color == WHITE ? w_material : b_material;
}

bool Board::off_the_board(uint8_t square) {
    return square & (uint8_t)0x88;
}

int Board::execute_move(Ply ply) {
    int killed = get_piece(ply.to);
    set_piece(ply.to, get_piece(ply.from));
    set_piece(ply.from, 0);

    if (killed != 0){
        if (killed > 0){
            w_material -= material_value[abs(killed)];
        } else {
            b_material -= material_value[abs(killed)];
        }
    }
    return killed;
}

void Board::reverse_move(Ply ply, int killed_piece) {
    set_piece(ply.from, get_piece(ply.to));
    set_piece(ply.to, killed_piece);
}

void Board::draw() {
    printf("\n");
    for (uint8_t y = 0; y < 8; y++){
        for (uint8_t x = 0; x < 8; x++){

            if (x == 0)
                printf("%d ", 8 - y);

            uint8_t sq = (7 - y) * 8 + x;

            int piece = x88[sq + (sq & ~(uint8_t)7)];
            int piece_symbol = pieces[abs(piece)];

            if (draw_color && piece_symbol != '.'){
                if (get_color(piece) == WHITE){
                    printf(WHITE_TTY);
                } else {
                    printf(BLACK_TTY);
                }
            }

            printf(" %c ", piece_symbol);

            if (draw_color && piece_symbol != '.'){
                printf(CLEAR_TTY);
            }
        }
        printf("\n");
    }
    printf("   a  b  c  d  e  f  g  h\n");
}

void Board::calculate_material() {
    w_material = 0;
    b_material = 0;

    for (uint8_t y = 0; y < 8; y++){
        for (uint8_t x = 0; x < 8; x++){
            int p = x88[x88_conv(x, y)];
            if (p == 0) continue;

            if (p > 0){
                w_material += material_value[abs(p)];
            } else {
                b_material += material_value[abs(p)];
            }
        }
    }
}

void Board::set_piece(Algebraic alg, int piece) {
    x88[x88_conv(alg)] = piece;
}

uint8_t Board::x88_conv(Algebraic alg) {
    assert(alg.isValid());
    int8_t file = alg.file - 97;
    int8_t rank = alg.rank - 1;
    return 16 * rank + file;
}

uint8_t Board::x88_conv(uint8_t x, uint8_t y) {
    uint8_t sq = y * 8 + x;
    return sq + (sq & ~(uint8_t)7);
}

std::vector<Ply> Board::generate_valid_moves_piece(Algebraic pos) {

    std::cout << "Generate valid moves for position " << pos << std::endl;

    int piece = get_piece(pos);
    int square = pos.x88_value();
    int color = get_color(piece);

    if (piece == 0) return std::vector<Ply>();

    std::vector<Ply> legal_moves;

    switch (abs(piece)){

        case PAWN:{ // pawn
            if (is_empty(square + N * color)){
                legal_moves.emplace_back(pos, Algebraic(square + N * color));
                if (pos.rank == (color == WHITE ? 2 : 7) && is_empty(square + (2 * N) * color)){
                    legal_moves.emplace_back(pos, Algebraic(square + (2 * N) * color));
                }
            }

            if (is_enemy(square + NE * color, piece)){
                legal_moves.emplace_back(pos, Algebraic(square + NE * color));
            }

            if (is_enemy(square + NW * color, piece)){
                legal_moves.emplace_back(pos, Algebraic(square + NW * color));
            }
            break;
        }

        case ROOK:{
            legal_moves = check_directions(pos, std::vector<int>{N, S, E, W}, 8);
            break;
        }

        case KNIGHT:{
            legal_moves = check_directions(pos, std::vector<int>{NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW }, 1);
            break;
        }

        case BISHOP:{
            legal_moves = check_directions(pos, std::vector<int>{NE, SE, SW, NW}, 8);
            break;
        }

        case QUEEN:{
            legal_moves = check_directions(pos, std::vector<int>{N, NE, E, SE, S, SW, W, NW}, 8);
            break;
        }

        case KING:{
            legal_moves = check_directions(pos, std::vector<int>{N, NE, E, SE, S, SW, W, NW}, 1);
            break;
        }
    }

    return legal_moves;
}

int Board::get_color(int piece) {
    assert(piece != EMPTY);
    return ((piece > 0) ? 1 : ((piece < 0) ? -1 : 0));
}

bool Board::is_enemy(int square, int piece) {
    if (x88[square] == EMPTY) return false;
    return !off_the_board(square) && (get_color(x88[square]) != get_color(piece));
}

bool Board::is_empty(int square) {
    return !off_the_board(square) && x88[square] == EMPTY;
}

std::vector<Ply> Board::check_directions(Algebraic pos, std::vector<int> dirs, int max_steps) {
    int piece = get_piece(pos);
    assert(piece != 0);

    std::vector<Ply> destinations;
    int steps, square;

    for (int dir : dirs){
        steps = 0;
        square = pos.x88_value();

        while(steps < max_steps){

            square+=dir;

            if (off_the_board(square) || is_friendly(square, piece)) break;

            if (is_enemy(square, piece)){
                destinations.emplace_back(pos, Algebraic(square));
                break;
            }

            if (is_empty(square)){
                destinations.emplace_back(pos, Algebraic(square));
                steps++;
            }
        }
    }

    return destinations;

}

bool Board::is_friendly(int square, int piece) {
    if (x88[square] == EMPTY) return false;
    return get_color(x88[square]) == get_color(piece);
}






