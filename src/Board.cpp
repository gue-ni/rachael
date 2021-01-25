//
// Created by jakob on 1/22/21.
//

#include <cassert>
#include <iostream>

#include "Board.h"

Board::Board(bool draw_color) : draw_color(draw_color) {
    calculate_material();
    //std::cout << material(WHITE) << " " << material(BLACK) << std::endl;
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
    std::string padding = " ";

    std::cout << padding << "   a  b  c  d  e  f  g  h" << std::endl;
    for (uint8_t y = 0; y < 8; y++){
        for (uint8_t x = 0; x < 8; x++){

            if (x == 0) std::cout << padding << 8 - y << " ";

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
            std::cout << " " << (char)piece_symbol << " ";
            if (draw_color && piece_symbol != '.') printf(CLEAR_TTY);

            if (x == 7) std::cout <<" " << 8 - y;
        }
        printf("\n");
    }
    std::cout << padding << "   a  b  c  d  e  f  g  h\n" << std::endl;
}

void Board::calculate_material() {
    w_material = 0;
    b_material = 0;

    for (int sq : valid_squares){
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

std::vector<Ply> Board::generate_valid_moves_piece(int square) {
    int piece = x88[square];

    if (piece == 0) return std::vector<Ply>();

    int color = get_color(piece);
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
            legal_moves = check_directions(square, std::vector<int>{ N, NE, E, SE, S, SW, W, NW }, 8);
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

        while(steps < max_steps) {
            to += dir;

            if (off_the_board(to) || is_friendly(to, piece)) break;

            if (is_enemy(to, piece)) {
                moves.emplace_back(from, to);
                break;
            }

            if (is_empty(to)) {
                moves.emplace_back(from, to);
                steps++;
            }
        }
    }
    return moves;
}

std::vector<Ply> Board::omp_generate_valid_moves(int color) {
    std::vector<Ply> valid_moves;

    #pragma omp parallel
    {
        #pragma omp for
        for (int sq : valid_squares){
            if (!is_empty(sq) && get_color(x88[sq]) == color){
                std::vector<Ply> moves = generate_valid_moves_piece(sq);
                valid_moves.insert(valid_moves.end(), moves.begin(), moves.end());
            }
        }
    }
    return valid_moves;
}

std::vector<Ply> Board::generate_valid_moves(int color) {
    std::vector<Ply> valid_moves, moves;

    for (int sq : valid_squares){
        if (!is_empty(sq) && get_color(x88[sq]) == color){
            moves = generate_valid_moves_piece(sq);
            valid_moves.insert(valid_moves.end(), moves.begin(), moves.end());
        }
    }
    return valid_moves;
}

