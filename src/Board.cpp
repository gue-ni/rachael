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
    std::vector<Ply> valid_moves;
    std::vector<Ply> moves;

    int squares[64] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                       0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                       0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                       0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                       0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                       0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                       0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                       0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77 };

    for (int sq : squares){
        if (is_empty(sq)) continue;

        if (get_color(x88[sq]) == color){
            moves = generate_valid_moves_piece(sq);
            valid_moves.insert(valid_moves.end(), moves.begin(), moves.end());
        }
    }
    return valid_moves;
}

int Board::get_piece(Algebraic alg) {
    return x88[alg.x88_value()];
}

int Board::material(int color) {
    return color == WHITE ? w_material : b_material;
}

bool Board::off_the_board(int square) {
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
    if (killed_piece != 0){
        if (killed_piece > 0){
            w_material += material_value[abs(killed_piece)];
        } else {
            b_material += material_value[abs(killed_piece)];
        }
    }
    set_piece(ply.from, get_piece(ply.to));
    set_piece(ply.to, killed_piece);
}

void Board::draw() {
    printf("\n");
    for (uint8_t y = 0; y < 8; y++){
        for (uint8_t x = 0; x < 8; x++){

            if (x == 0) printf("%d ", 8 - y);

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
            if (draw_color && piece_symbol != '.') printf(CLEAR_TTY);
        }
        printf("\n");
    }
    printf("   a  b  c  d  e  f  g  h\n\n");
}

void Board::calculate_material() {
    w_material = 0;
    b_material = 0;

    for (int sq : valid_squares()){
        int p = x88[sq];
        if (p == 0) continue;

        if (p > 0){
            w_material += material_value[abs(p)];
        } else {
            b_material += material_value[abs(p)];
        }
    }
}

void Board::set_piece(Algebraic alg, int piece) {
    x88[alg.x88_value()] = piece;
}

uint8_t Board::x88_conv(uint8_t x, uint8_t y) {
    uint8_t sq = y * 8 + x;
    return sq + (sq & ~(uint8_t)7);
}

std::vector<Ply> Board::generate_valid_moves_piece(int square) {
    int piece = x88[square];
    int color = get_color(piece);

    if (piece == 0) return std::vector<Ply>();

    std::vector<Ply> legal_moves;

    switch (abs(piece)){

        case PAWN:{ // pawn
            if (is_empty(square + N * color)){

                legal_moves.emplace_back(square, square + N * color);

                if (Algebraic(square).rank == (color == WHITE ? 2 : 7) && is_empty(square + (2 * N) * color)){
                    legal_moves.emplace_back(square, square + (2 * N) * color);
                }
            }

            if (is_enemy(square + NE * color, piece)){
                legal_moves.emplace_back(square, square + NE * color);
            }

            if (is_enemy(square + NW * color, piece)){
                legal_moves.emplace_back(square, square + NW * color);
            }
            break;
        }

        case ROOK:{
            legal_moves = check_directions(square, std::vector<int>{N, S, E, W}, 8);
            break;
        }

        case KNIGHT:{
            legal_moves = check_directions(square, std::vector<int>{NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW }, 1);
            break;
        }

        case BISHOP:{
            legal_moves = check_directions(square, std::vector<int>{NE, SE, SW, NW}, 8);
            break;
        }

        case QUEEN:{
            legal_moves = check_directions(square, std::vector<int>{N, NE, E, SE, S, SW, W, NW}, 8);
            break;
        }

        case KING:{
            legal_moves = check_directions(square, std::vector<int>{N, NE, E, SE, S, SW, W, NW}, 1);
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

bool Board::is_friendly(int square, int piece) {
    if (x88[square] == EMPTY) return false;
    return get_color(x88[square]) == get_color(piece);
}

std::vector<Ply> Board::check_directions(int from, const std::vector<int>& dirs, int max_steps) {
    int piece = x88[from];

    assert(piece != 0);

    std::vector<Ply> moves;
    int steps, to;

    for (int dir : dirs){
        steps = 0;
        to = from;

        while(steps < max_steps){

            to+=dir;

            if (off_the_board(to) || is_friendly(to, piece)) break;

            if (is_enemy(to, piece)){
                moves.emplace_back(from, to);
                break;
            }

            if (is_empty(to)){
                moves.emplace_back(from, to);
                steps++;
            }
        }
    }
    return moves;
}

std::vector<int> Board::valid_squares() {
    return std::vector<int>{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                            0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                            0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                            0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                            0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                            0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                            0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77 };
}









