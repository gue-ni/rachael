#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <map>
#include <zconf.h>

#include "SimpleBoard.h"
#include "Reversible.h"

SimpleBoard::SimpleBoard(bool draw_color) : draw_color(draw_color) {
    w_material = 0;
    b_material = 0;
    calculate_material();
}

int SimpleBoard::material(int color) {
    return color == WHITE ? w_material : b_material;
}

int SimpleBoard::execute_move(Ply ply) {
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

void SimpleBoard::reverse_move(Ply ply, int killed_piece) {
    set_piece(ply.from, get_piece(ply.to));
    set_piece(ply.to, killed_piece);

    if (killed_piece != 0){
        if (killed_piece > 0){
            w_material += material_value[abs(killed_piece)];
        } else {
            b_material += material_value[abs(killed_piece)];
        }
    }
}

void SimpleBoard::calculate_material() {
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

bool SimpleBoard::is_threatened(int square, int color) {
    // Rook or Queen
    for (Ply move : check_directions(square, color, {N, S, E, W}, 8)){
        int p = abs(x88[move.to]);
        if (is_enemy(move.to, color) && (p == 5 || p == 2)){
            return true;
        }
    }

    // Bishop or Queen
    for (Ply move : check_directions(square, color, {NE, SE, SW, NW}, 8)){
        int p = abs(x88[move.to]);
        if (is_enemy(move.to, color) && (p == 3 || p == 2)) return true;
    }

    // Knight
    for (Ply move : check_directions(square, color, {NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW}, 1)){
        int p = abs(x88[move.to]);
        if (is_enemy(move.to, color) && (p == 4 || p == 2)) return true;
    }

    // King
    for (Ply move : check_directions(square, color, {NE, SE, SW, NW, N, S, E, W}, 1)){
        int p = abs(x88[move.to]);
        if (is_enemy(move.to, color) && p == 1) return true;
    }

    // Pawn
    if (color == WHITE){
        if (is_enemy(square+NE, color) && abs(x88[square+NE]) == 6) return true;
        if (is_enemy(square+NW, color) && abs(x88[square+NW]) == 6) return true;
    } else {
        if (is_enemy(square+SE, color) && abs(x88[square+SE]) == 6) return true;
        if (is_enemy(square+SW, color) && abs(x88[square+SW]) == 6) return true;
    }
    return false;
}

std::vector<Ply> SimpleBoard::check_directions(int from, int piece, const std::vector<int> &dirs, int max_steps) {
    std::vector<Ply> moves;
    int steps, to;
    assert(piece != 0);

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

std::ostream& operator<<(std::ostream &strm, const SimpleBoard &board) {
    std::string padding = " ";
    strm << padding << "Ply " << board.move_history.size() << ":\n";
    strm << padding << "\n   a  b  c  d  e  f  g  h" << std::endl;

    for (uint8_t y = 0; y < 8; y++){
        for (uint8_t x = 0; x < 8; x++){

            if (x == 0) strm << padding << 8 - y << " ";

            uint8_t sq = (7 - y) * 8 + x;
            int piece = board.x88[sq + (sq & ~(uint8_t)7)];
            int piece_symbol = board.pieces[abs(piece)];

            if (piece_symbol != '.'){
                if (board.get_color(piece) == WHITE){
                    if (board.draw_color){
                        strm << WHITE_TTY;
                    } else {
                        piece_symbol = tolower(piece_symbol);
                    }
                } else {
                    if (board.draw_color){
                        strm << BLACK_TTY;
                    } else {
                        piece_symbol = toupper(piece_symbol);
                    }
                }
            }

            strm << " " << (char)piece_symbol << " ";

            if (board.draw_color && piece_symbol != '.') strm << CLEAR_TTY;

            if (x == 7) strm <<" " << 8 - y;
        }
        printf("\n");
    }
    strm << padding << "   a  b  c  d  e  f  g  h" << std::endl;
    return strm;
}

/*
SimpleBoard::SimpleBoard(const std::vector<int> &brd, bool draw_color): SimpleBoard(draw_color) {
    assert(brd.size() == 128);
    for (unsigned int i = 0; i < brd.size(); i++) x88[i] = brd[i];
}
*/

void SimpleBoard::undo_move(Reversible ply) {
    move_history.pop_back();
    reverse_move(Ply(ply.from, ply.to), ply.killed_piece);
}

Reversible SimpleBoard::make_move(Ply ply) {
    move_history.push_back(ply);
    return Reversible(ply, execute_move(ply));
}

void SimpleBoard::generate_valid_moves_square(std::vector<Ply> &legal_moves, int square) {
    int piece = x88[square];

    if (piece == 0) return;

    int color = get_color(piece);

    switch (abs(piece)){
        case PAWN:{ // pawn
            if (is_empty(square + N * color) && !off_the_board(square + N * color)){
                legal_moves.emplace_back(square, square + N * color);

                if (Square(square).rank == (color == WHITE ? 2 : 7)
                    && is_empty(square + (2 * N) * color)
                    && !off_the_board(square + (2 * N) * color)){
                    legal_moves.emplace_back(square, square + (2 * N) * color);
                }
            }

            if (is_enemy(square + NE * color, piece) && !off_the_board(square + NE * color)){
                legal_moves.emplace_back(square, square + NE * color);
            }

            if (is_enemy(square + NW * color, piece) && !off_the_board(square + NW * color)){
                legal_moves.emplace_back(square, square + NW * color);
            }
            break;
        }
        case ROOK:{
            check_directions(legal_moves, square, piece, {N, S, E, W}, 8);
            break;
        }
        case KNIGHT:{
             check_directions(legal_moves, square, piece, {NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW}, 1);
            break;
        }
        case BISHOP:{
            check_directions(legal_moves, square, piece, {NE, SE, SW, NW}, 8);
            break;
        }
        case QUEEN:{
            check_directions(legal_moves, square, piece, {N, NE, E, SE, S, SW, W, NW}, 8);
            break;
        }
        case KING:{
            std::vector<Ply> possible;
            check_directions(possible, square, piece, {N, NE, E, SE, S, SW, W, NW}, 1);
            for (auto p : possible){
                int k = execute_move(p);

                if (!is_threatened(p.to, color)){
                    legal_moves.push_back(p);
                }

                reverse_move(p, k);
            }
            /*
            if (!is_threatened(square, color)){
                if (color == WHITE){
                    if (!w_king_moved && !w_r_rook_moved
                        && !is_threatened(0x05, color)
                        && !is_threatened(0x06, color)
                        && !is_threatened(square, color)
                        && x88[0x05] == EMPTY && x88[0x06] == EMPTY){
                        legal_moves.emplace_back("e1g1");
                    }

                    if (!w_king_moved && !w_l_rook_moved
                        && !is_threatened(0x01, color)
                        && !is_threatened(0x02, color)
                        && !is_threatened(0x03, color)
                        && !is_threatened(square, color)
                        && x88[0x01] == EMPTY && x88[0x02] == EMPTY && x88[0x03] == EMPTY){
                        legal_moves.emplace_back("e1c1");
                    }



                } else {
                    if (!b_king_moved && !b_r_rook_moved
                    && !is_threatened(0x76, color)
                    && !is_threatened(0x76, color)
                    && !is_threatened(square, color)
                    && x88[0x75] == EMPTY && x88[0x76] == EMPTY){
                        legal_moves.emplace_back("e8g8");
                    }

                    if (!b_king_moved && !b_l_rook_moved
                        && !is_threatened(0x71, color)
                        && !is_threatened(0x72, color)
                        && !is_threatened(0x73, color)
                        && !is_threatened(square, color)
                        && x88[0x71] == EMPTY && x88[0x72] == EMPTY && x88[0x73] == EMPTY){
                        legal_moves.emplace_back("e8c8");
                    }
                }
            }
             */
            break;
        }
    }
}

void SimpleBoard::check_directions(std::vector<Ply> &moves, int from, int piece, const std::vector<int> &dirs,
                                   int max_steps) {
    int steps, to;
    assert(piece != 0);

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

}

std::vector<Ply> SimpleBoard::generate_valid_moves(int color_to_move) {

    std::vector<Ply> valid_moves;

    for (int sq : valid_squares){
        if (!is_empty(sq) && get_color(x88[sq]) == color_to_move){
            generate_valid_moves_square(valid_moves, sq);
        }
    }
    return valid_moves;
}

SimpleBoard::SimpleBoard(const std::string& fen, bool draw_color) : draw_color(draw_color) {
    set_board(fen);
}

void SimpleBoard::set_board(const std::string &fen) {

    for (auto sq : valid_squares){
        x88[sq] = 0;
    }

    std::string substr;
    std::istringstream iss(fen);
    iss >> substr;

    std::map<char, int> pcs = {
            {'p', -6},{'r', -5},{'n', -4},{'b', -3},{'q', -2},{'k', -1},
            {'P',  6},{'R',  5},{'N',  4},{'B',  3},{'Q',  2},{'K',  1},
    };

    int sq = 0x70;
    for (char c : substr){
        if (isdigit(c)){
            sq += (c - 48);
        } else if (c == '/'){
            sq -= 0x18;
        } else {
            x88[sq++] = pcs[c];
        }
    }
}









