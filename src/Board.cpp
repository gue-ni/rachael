#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <map>

#include "Board.h"
#include "Reversible.h"

Board::Board(bool draw_color) : Board(DEFAULT_BOARD, draw_color) {}

Board::Board(const std::string& fen, bool draw_color) : draw_color(draw_color) {
    w_castle_q = false;
    w_castle_k = false;
    b_castle_q = false;
    b_castle_k = false;
    set_board(fen);
    calculate_material();
}

int Board::material(Color color) {
    return color == WHITE ? w_material : b_material;
}

Piece Board::execute_move(Ply ply) {

    if (x88[ply.from] ==  WHITE*KING) w_king = ply.to;
    if (x88[ply.from] ==  BLACK*KING) b_king = ply.to;

    int killed = get_piece(ply.to);
    set_piece(ply.to, get_piece(ply.from));
    set_piece(ply.from, 0);

    if (killed != EMPTY_SQUARE){
        if (get_color(killed) == WHITE){
            w_material -= material_value[abs(killed)];
        } else {
            b_material -= material_value[abs(killed)];
        }
    }
    return killed;
}

void Board::reverse_move(Ply ply, Piece killed) {

    // keep track of king
    if (x88[ply.to] ==  1) w_king = ply.from;
    if (x88[ply.to] == -1) b_king = ply.from;

    set_piece(ply.from, get_piece(ply.to));
    set_piece(ply.to, killed);

    if (killed != EMPTY_SQUARE){
        if (killed > 0){
            w_material += material_value[abs(killed)];
        } else {
            b_material += material_value[abs(killed)];
        }
    }
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

// TODO fix this
bool Board::is_threatened(Square square, Color color) {

    // Knight
    for (Ply move : check_directions(square, color, {NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW}, 1)){
        int p = abs(x88[move.to]);
        if (is_enemy(move.to, color) && p == 4) {
            //std::cout << "threatening move=" << move << std::endl;
            return true;
        }
    }


    // Rook or Queen
    for (Ply move : check_directions(square, color, {N, S, E, W}, 8)){
        int p = abs(x88[move.to]);
        if (is_enemy(move.to, color) && (p == 5 || p == 2)){
            //std::cout << "threatening move=" << move << std::endl;
            return true;
        }
    }

    // Bishop or Queen
    for (Ply move : check_directions(square, color, {NE, SE, SW, NW}, 8)){
        int p = abs(x88[move.to]);
        if (is_enemy(move.to, color) && (p == 3 || p == 2)) {
            //std::cout << "threatening move=" << move << std::endl;
            return true;
        }
    }

    // King
    for (Ply move : check_directions(square, color, {NE, SE, SW, NW, N, S, E, W}, 1)){
        int p = abs(x88[move.to]);
        if (is_enemy(move.to, color) && p == 1) {
            //std::cout << "threatening move=" << move << std::endl;
            return true;
        }
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

std::vector<Ply> Board::check_directions(Square from, Piece piece, const std::vector<int> &dirs, int max_steps) {
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

std::ostream& operator<<(std::ostream &strm, const Board &board) {
    std::string padding = " ";
    strm << padding << "Moves " << board.ply_count << ":\n";
    strm << padding << "\n    a  b  c  d  e  f  g  h" << std::endl;

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
                        piece_symbol = toupper(piece_symbol);
                    }
                } else {
                    if (board.draw_color){
                        strm << BLACK_TTY;
                    } else {
                        piece_symbol = tolower(piece_symbol);
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
    strm << padding << "     K=" << (int)board.w_castle_k << ", Q=" << (int)board.w_castle_q
    << ", k=" << (int)board.b_castle_k << ", q=" << (int)board.b_castle_q << std::endl;
    strm << padding << "     w_king="  << (int)board.w_king
    << ", b_king=" << (int)board.b_king << std::endl;
    strm << padding << "color_to_move=" << (int)board.color_to_move << std::endl;

    return strm;
}

void Board::undo_move(Reversible reversible) {
    color_to_move = -color_to_move;
    ply_count--;

#ifdef CASTLING
    if (reversible.w_castle_q) w_castle_q = true;
    if (reversible.w_castle_k) w_castle_k = true;
    if (reversible.b_castle_q) b_castle_q = true;
    if (reversible.b_castle_k) b_castle_k = true;

    if (x88[reversible.to] == 1) {
        if (reversible.as_string() == "e1g1") {
            reverse_move(Ply("e1g1"), 0);reverse_move(Ply("h1f1"), 0);return;
        } else if (reversible.as_string() == "e1c1") {
            reverse_move(Ply("e1c1"), 0);reverse_move(Ply("a1d1"), 0);return;
        }
    }

    if (x88[reversible.to] == -1){
        if (reversible.as_string() == "e8c8") {
            reverse_move(Ply("e8c8"), 0);reverse_move(Ply("a8d8"), 0);return;
        } else if (reversible.as_string() == "e8g8") {
            reverse_move(Ply("e8g8"), 0);reverse_move(Ply("h8f8"), 0);return;
        }
    }
#endif

    reverse_move(Ply(reversible.from, reversible.to), reversible.killed_piece);
}

Reversible Board::make_move(Ply ply) {
    color_to_move = -color_to_move;
    ply_count++;

    Reversible rev(ply, 0);

#ifdef CASTLING
    if (x88[ply.from]        ==  5 && ply.from == 0x07 && w_castle_k){
        w_castle_k = false; rev.w_castle_k = true;
    } else if (x88[ply.from] ==  5 && ply.from == 0x00 && w_castle_q){
        w_castle_q = false; rev.w_castle_q = true;
    } else if (x88[ply.from] ==  1 && ply.from == 0x04 && w_castle_q && w_castle_k){
        w_castle_q = false; w_castle_k = false;
        rev.w_castle_k = true; rev.w_castle_q = true;

    } else if (x88[ply.from] == -5 && ply.from == 0x77 && b_castle_k){
        b_castle_k = false; rev.b_castle_k = true;
    } else if (x88[ply.from] == -5 && ply.from == 0x70 && b_castle_q){
        b_castle_q = false; rev.b_castle_q = true;
    } else if (x88[ply.from] == -1 && ply.from == 0x74 && b_castle_q && b_castle_k){
        b_castle_q = false; b_castle_k = false;
        rev.b_castle_k = true; rev.b_castle_q = true;
    }

    if (x88[ply.from] ==  1) {
        if (ply.as_string() == "e1g1") {
            execute_move(Ply("e1g1"));execute_move(Ply("h1f1"));
            return rev;
        } else if (ply.as_string() == "e1c1") {
            execute_move(Ply("e1c1"));execute_move(Ply("a1d1"));
            return rev;
        }
    }
    if (x88[ply.from] == -1){
        if (ply.as_string() == "e8c8") {
            execute_move(Ply("e8c8"));execute_move(Ply("a8d8"));
            return rev;
        } else if (ply.as_string() == "e8g8") {
            execute_move(Ply("e8g8"));execute_move(Ply("h8f8"));
            return rev;
        }
    }
#endif

#ifdef PROMOTION
    if (x88[ply.from] == 6 && SquareClass(ply.to).rank == 8){
        rev.killed_piece = execute_move(ply);
        x88[ply.to] = 2;
        return rev;
    }

    if (x88[ply.from] == -6 && SquareClass(ply.to).rank == 1){
        rev.killed_piece = execute_move(ply);
        x88[ply.to] = -2;
        return rev;
    }
#endif

    rev.killed_piece = execute_move(ply);
    return rev;
}

void Board::legal_moves_square(std::vector<Ply> &legal_moves, Square square) {
    int piece = x88[square];

    if (piece == 0) return;

    int color = get_color(piece);

    switch (abs(piece)){
        case PAWN:{ // pawn
            if (is_empty(square + N * color) && !off_the_board(square + N * color)){
                legal_moves.emplace_back(square, square + N * color);

                if (SquareClass(square).rank == (color == WHITE ? 2 : 7)
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

void Board::check_directions(std::vector<Ply> &moves, Square from, Piece piece, const std::vector<int> &dirs, int max_steps) {
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

std::vector<Ply> Board::pseudo_legal_moves(Color color) {
    std::vector<Ply> valid_moves;

    for (int sq : valid_squares){
        if (!is_empty(sq) && get_color(x88[sq]) == color){
            legal_moves_square(valid_moves, sq);
        }
    }
    return valid_moves;
}

void Board::set_board(const std::string &fen) {
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
            if (c == 'K') w_king = sq;
            if (c == 'k') b_king = sq;
            x88[sq++] = pcs[c];
        }
    }

    iss >> substr;
    color_to_move = substr == "w" ? WHITE : BLACK;

    iss >> substr;

    if (substr != "-"){
        for (char c : substr){
            if (c == 'K') w_castle_k = true;
            if (c == 'Q') w_castle_q = true;
            if (c == 'k') b_castle_k = true;
            if (c == 'q') b_castle_q = true;
        }
    }

    iss >> substr;
    iss >> substr;
    iss >> ply_count;
}

bool Board::is_legal_move(Ply ply) {
    int color = get_color(x88[ply.from]);
    Reversible r = make_move(ply);
    bool val = !is_checked(color);
    undo_move(r);
    return val;
}

bool Board::is_checked(Color color) {
    return color == WHITE ? is_threatened(w_king, WHITE) : is_threatened(b_king, BLACK);
}









