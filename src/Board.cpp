#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <map>
#include <zconf.h>

#include "Board.h"
#include "Reversible.h"

Board::Board(const std::string& fen, bool draw_color) : draw_color(draw_color) {
    w_castle_q = false;
    w_castle_k = false;
    b_castle_q = false;
    b_castle_k = false;
    color_to_move = WHITE;
    fifty_moves = 0;
    plies = 0;
    set_board(fen);
    calculate_material();
}

int Board::material(Color color) {
    return color == WHITE ? w_material : b_material;
}

Piece Board::execute_move(Move move) {

    if (x88[move.from] == EMPTY_SQUARE){
        std::cout << "empty " << move << std::endl;
        assert(x88[move.from] != EMPTY_SQUARE);
    }

    Color color = get_color(x88[move.from]);

    if (x88[move.from] == WHITE * KING) w_king = move.to;
    if (x88[move.from] == BLACK * KING) b_king = move.to;

    int killed = x88[move.to];
    x88[move.to] = move.promote_to == 0 ? x88[move.from] : move.promote_to * color;
    x88[move.from] = 0;

    if (killed != EMPTY_SQUARE){
        if (get_color(killed) == WHITE){
            w_material -= material_value[abs(killed)];
        } else {
            b_material -= material_value[abs(killed)];
        }
    }
    return killed;
}

void Board::reverse_move(Move move, Piece killed) {
    // keep track of king
    if (x88[move.to] ==  1) w_king = move.from;
    if (x88[move.to] == -1) b_king = move.from;

    x88[move.from] = x88[move.to];
    x88[move.to] = killed;

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

std::ostream& operator<<(std::ostream &strm, const Board &board) {
    std::string padding = " ";
    strm << padding << "Plies " << board.plies << ":\n";
    strm << padding << "\n    a  b  c  d  e  f  g  h" << std::endl;

    for (uint8_t y = 0; y < 8; y++){
        for (uint8_t x = 0; x < 8; x++){

            if (x == 0) strm << padding << 8 - y << " ";

            uint8_t sq = (7 - y) * 8 + x;
            int piece = board.x88[sq + (sq & ~(uint8_t)7)];
            int piece_symbol = pieces[abs(piece)];

            if (piece_symbol != '.'){
                if (get_color(piece) == WHITE){
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
    strm << padding << "     K="
         << (int)(board.castling & W_CASTLE_KINGSIDE ? true : false)
         << ", Q=" << (int)(board.castling & W_CASTLE_QUEENSIDE ? true : false)
         << ", k=" << (int)(board.castling & B_CASTLE_KINGSIDE ? true : false)
         << ", q=" << (int)(board.castling & B_CASTLE_QUEENSIDE ? true : false) << std::endl;
    strm << padding << "     w_king="  << (int)board.w_king
    << ", b_king=" << (int)board.b_king << std::endl;
    strm << padding << "color_to_move=" << (int)board.color_to_move << ", fifty_moves=" << board.fifty_moves << std::endl;

    return strm;
}

void Board::undo_move(Reversible rev) {
    color_to_move = -color_to_move;
    plies--;
    move_history.pop_back();

#ifdef FIFTY_MOVES
    fifty_moves = rev.fifty_moves;
#endif
#ifdef CASTLING
    if (rev.w_castle_q) w_castle_q = true;
    if (rev.w_castle_k) w_castle_k = true;
    if (rev.b_castle_q) b_castle_q = true;
    if (rev.b_castle_k) b_castle_k = true;

    if (x88[rev.to] == 1) {
        if (rev.as_string() == "e1g1") {
            reverse_move(Move("e1g1"), 0);
            reverse_move(Move("h1f1"), 0);
            return;
        } else if (rev.as_string() == "e1c1") {
            reverse_move(Move("e1c1"), 0);
            reverse_move(Move("a1d1"), 0);
            return;
        }
    } else if (x88[rev.to] == -1){
        if (rev.as_string() == "e8c8") {
            reverse_move(Move("e8c8"), 0);
            reverse_move(Move("a8d8"), 0);
            return;
        } else if (rev.as_string() == "e8g8") {
            reverse_move(Move("e8g8"), 0);
            reverse_move(Move("h8f8"), 0);
            return;
        }
    }
#endif
#ifdef PROMOTION
    if (rev.promote_to != 0){
		assert(x88[rev.to] != EMPTY_SQUARE);
        Color color = get_color(x88[rev.to]);
        reverse_move(Move(rev.from, rev.to), rev.killed_piece);
        x88[rev.from] =  PAWN*color;
        return;
    }
#endif
    reverse_move(Move(rev.from, rev.to), rev.killed_piece);
}

Reversible Board::make_move(Move move) {
    color_to_move = -color_to_move;
    plies++;
    move_history.push_back(move);
    Reversible rev(move, EMPTY_SQUARE);

#ifdef FIFTY_MOVES
    rev.fifty_moves = fifty_moves;
    if (!is_empty(move.to) || abs(x88[move.from]) == PAWN){
        fifty_moves = 0;
    } else {
        fifty_moves++;
    }
#endif
#ifdef CASTLING
    Piece p = x88[move.from];
    if (p == KING && (w_castle_q || w_castle_k)){
        if (w_castle_q){
            w_castle_q = false;
            rev.w_castle_q = true;
        }
        if (w_castle_k){
            w_castle_k = false;
            rev.w_castle_k = true;
        }
    }

    /*
    if (x88[move.from] == ROOK && move.from == 0x07 && w_castle_k){
        w_castle_k      = false;
        rev.w_castle_k  = true;

    } else if (x88[move.from] == ROOK && move.from == 0x00 && w_castle_q){
        w_castle_q      = false;
        rev.w_castle_q  = true;

    } else if (x88[move.from] == KING && move.from == 0x04 && w_castle_q && w_castle_k){
        w_castle_q      = false;
        w_castle_k      = false;
        rev.w_castle_k  = true;
        rev.w_castle_q  = true;

    } else if (x88[move.from] == -ROOK && move.from == 0x77 && b_castle_k){
        b_castle_k      = false;
        rev.b_castle_k  = true;

    } else if (x88[move.from] == -ROOK && move.from == 0x70 && b_castle_q){
        b_castle_q      = false;
        rev.b_castle_q  = true;

    } else if (x88[move.from] == -KING && move.from == 0x74 && b_castle_q && b_castle_k){
        b_castle_q      = false;
        b_castle_k      = false;
        rev.b_castle_k  = true;
        rev.b_castle_q  = true;
    }
     */

    if (x88[move.from] == 1) {
        if (move.as_string() == "e1g1") {
            if (!(x88[0x07] == ROOK && x88[0x04] == KING)){
                std::cout << (*this) << std::endl;
                assert(x88[0x07] == ROOK && x88[0x04] == KING);
            }
            execute_move(Move("e1g1"));
            execute_move(Move("h1f1"));
            return rev;
        } else if (move.as_string() == "e1c1") {
            if (!(x88[0x00] == ROOK && x88[0x04] == KING)){
                std::cout << (*this) << std::endl;
                assert(x88[0x00] == ROOK && x88[0x04] == KING);
            }
            execute_move(Move("e1c1"));
            execute_move(Move("a1d1"));
            return rev;
        }
    } else if (x88[move.from] == -1){
        if (move.as_string() == "e8c8") {
            if (!(x88[0x77] == -ROOK && x88[0x74] == -KING)){
                std::cout << (*this) << std::endl;
                assert(x88[0x77] == -ROOK && x88[0x74] == -KING);
            }

            execute_move(Move("e8c8"));
            execute_move(Move("a8d8"));
            return rev;
        } else if (move.as_string() == "e8g8") {
            if (!(x88[0x70] == -ROOK && x88[0x74] == -KING)){
                std::cout << (*this) << std::endl;
                assert(x88[0x70] == -ROOK && x88[0x74] == -KING);
            }
            execute_move(Move("e8g8"));
            execute_move(Move("h8f8"));
            return rev;
        }
    }
#endif
#ifdef PROMOTION
    if (x88[move.from] == 6 && get_rank07(move.to) == 7){
        rev.killed_piece = execute_move(move);
        x88[move.to] = QUEEN;
        rev.promote_to = QUEEN;
        return rev;
    } else if (x88[move.from] == -6 && get_rank07(move.to) == 0){
        rev.killed_piece = execute_move(move);
        x88[move.to] = -QUEEN;
        rev.promote_to = QUEEN;
        return rev;
    }
#endif

    rev.killed_piece = execute_move(move);
    return rev;
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

    Square sq = A8;
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
            if (c == 'K') castling |= W_CASTLE_KINGSIDE;
            if (c == 'Q') castling |= W_CASTLE_QUEENSIDE;
            if (c == 'k') castling |= B_CASTLE_KINGSIDE;
            if (c == 'q') castling |= B_CASTLE_QUEENSIDE;
        }
    }

    iss >> substr;
    iss >> fifty_moves;
    iss >> plies;
}

bool Board::is_checked(Color color) {
    return color == WHITE ? is_attacked(w_king, WHITE) : is_attacked(b_king, BLACK);
}

int Board::pseudo_legal(Move *moves, Color color) {
    int n = 0;
    for (Square sq : valid_squares){
        if (x88[sq] != EMPTY_SQUARE && get_color(x88[sq]) == color){
            n = pseudo_legal_for_square(moves, n, sq);
        }
    }
    assert(n < 256);
    return n;
}

int Board::pseudo_legal_for_square(Move *moves, int n, Square from) {
    if (x88[from] == EMPTY_SQUARE) return n;

    Piece piece = x88[from];
    Color color = get_color(piece);
    Square to;

    switch (abs(piece)){
        case PAWN:{
            to = from + N*color;
            if (!off_the_board(to) && is_empty(to)){
                moves[n++] = Move(from, to);
                to = from + 2*N*color;
                if (!off_the_board(to) && get_rank07(from) == (color == WHITE ? 1 : 6) && is_empty(to)){
                    moves[n++] = Move(from, to);
                }
            }

            for (auto t : {from + NE * color, from + NW * color}){
                if (!off_the_board(t) && is_enemy(t, piece)) moves[n++] = Move(from, t);
            }
            break;
        }
        case ROOK:{
            n = check_dir(moves, n, from, 8, { N, S, E, W});
            break;
        }
		case KNIGHT:{
			n = check_dir(moves, n, from, 1, { NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW });
			break;
		}
		case BISHOP:{
			n = check_dir(moves, n, from, 8, { NE, SE, SW, NW });
			break;
		}
		case QUEEN:{
			n = check_dir(moves, n, from, 8, { N, NE, E, SE, S, SW, W, NW });
			break;
		}
		case KING:{
			n = check_dir(moves, n, from, 1, { N, NE, E, SE, S, SW, W, NW });

            if (color == WHITE && from == E1){
                if (castling & W_CASTLE_KINGSIDE
                    && !is_attacked(0x05, color)
                    && !is_attacked(from, color)
                    && x88[0x05] == EMPTY_SQUARE
                    && x88[0x06] == EMPTY_SQUARE
                    && x88[0x07] == ROOK){
                    moves[n++] = Move(0x04, 0x06);
                }
                if (castling & W_CASTLE_QUEENSIDE
                    && !is_attacked(0x01, color)
                    && !is_attacked(0x03, color)
                    && !is_attacked(from, color)
                    && x88[0x00] == ROOK
                    && x88[0x01] == EMPTY_SQUARE
                    && x88[0x02] == EMPTY_SQUARE
                    && x88[0x03] == EMPTY_SQUARE){
                    moves[n++] = Move(0x04, 0x02);
                }
            } else if (color == BLACK && from == E8) {
                if (castling & B_CASTLE_KINGSIDE
                    && !is_attacked(0x75, color)
                    && !is_attacked(from, color)
                    && x88[0x75] == EMPTY_SQUARE
                    && x88[0x76] == EMPTY_SQUARE
                    && x88[0x77] == -ROOK){
                    moves[n++] = Move(0x74, 0x76);
                }
                if (castling & B_CASTLE_QUEENSIDE
                    && !is_attacked(0x71, color)
                    && !is_attacked(0x73, color)
                    && !is_attacked(from, color)
                    && x88[0x70] == -ROOK
                    && x88[0x71] == EMPTY_SQUARE
                    && x88[0x72] == EMPTY_SQUARE
                    && x88[0x73] == EMPTY_SQUARE){
                    moves[n++] = Move(0x74, 0x72);
                }
            }
            break;
        }
    }
    return n;
}

int Board::check_dir(Move *moves, int n, Square from, int max_steps, const std::vector<int> &dirs) {
    int steps;
    Square to;
    Piece piece = x88[from];
    assert(piece != EMPTY_SQUARE);

    for (int dir : dirs){
        steps = 0;
        to = from;

        while(steps < max_steps) {
            to += dir;

            if (off_the_board(to) || is_friendly(to, piece)) break;

            if (is_enemy(to, piece)) {
                moves[n++] = Move(from,to);
                break;
            }

            if (is_empty(to)) {
                moves[n++] = Move(from,to);
                steps++;
            }
        }
    }
    return n;
}

Board::Board() : Board(DEFAULT_BOARD, true){}

bool Board::is_attacked(Square origin, Color color) {
    for (int dir : {NNE, ENE, ESE, SSE, SSW, WSW, WNW, NNW}){
        if (x88[origin+dir] == -color*KNIGHT) return true;
    }

    Square sq;
    int dirs[8] = {N, NE, E, SE, S, SW, W, NW};
    for (int i = 0; i < 8; i++){
        int steps = 0;
        sq = origin;

        while (steps < 7){
            sq += dirs[i];

            if (off_the_board(sq) || is_friendly(sq, color)) break;

            if (is_enemy(sq, color)){
                Piece p = abs(x88[sq]);
                if (p == QUEEN)                 return true;
                if (i % 2 == 0 && p == ROOK)    return true;
                if (i % 2 != 0 && p == BISHOP)  return true;
                if (steps == 0 && p == KING)    return true;
                break;
            }
            steps++;
        }
    }

    if (color == WHITE){
        for (int d : {NE, NW}) if (x88[origin+d] == -color*PAWN) return true;
    } else {
        for (int d : {SE, SW}) if (x88[origin+d] == -color*PAWN) return true;
    }

    return false;
}

State Board::make_move_alt(Move move) {
    State state;
    state.castling_rights = castling;
    state.fifty_moves = fifty_moves;

    color_to_move = -color_to_move;
    plies++;
    move_history.push_back(move);

    Piece p = x88[move.from];
    Color c = get_color(p);

    if (p == KING){
        castling ^= (W_CASTLE_QUEENSIDE | W_CASTLE_KINGSIDE);
    } else if(p == ROOK && move.from == H1 && castling & W_CASTLE_KINGSIDE){
        castling ^= W_CASTLE_KINGSIDE;
    } else if(p == ROOK && move.from == A1 && castling & W_CASTLE_QUEENSIDE){
        castling ^= W_CASTLE_QUEENSIDE;
    }

    if (p == -KING && castling & (B_CASTLE_KINGSIDE || castling & B_CASTLE_QUEENSIDE)){
        castling ^= (B_CASTLE_QUEENSIDE | B_CASTLE_KINGSIDE);
    } else if(p == -ROOK && move.from == H8 && castling & B_CASTLE_KINGSIDE){
        castling ^= B_CASTLE_KINGSIDE;
    } else if(p == -ROOK && move.from == A8 && castling & B_CASTLE_QUEENSIDE){
        castling ^= B_CASTLE_QUEENSIDE;
    }

    if (x88[move.from] == 1) {
        if (move.as_string() == "e1g1") {
            if (!(x88[H1] == ROOK && x88[E1] == KING)){
                std::cout << (*this) << std::endl;
                assert(x88[0x07] == ROOK && x88[E1] == KING);
            }
            execute_move(Move("e1g1"));
            execute_move(Move("h1f1"));
            return state;
        } else if (move.as_string() == "e1c1") {
            if (!(x88[A1] == ROOK && x88[E1] == KING)){
                std::cout << (*this) << std::endl;
                assert(x88[A1] == ROOK && x88[E1] == KING);
            }
            execute_move(Move("e1c1"));
            execute_move(Move("a1d1"));
            return state;
        }
    } else if (x88[move.from] == -1){
        if (move.as_string() == "e8c8") {
            if (!(x88[0x77] == -ROOK && x88[0x74] == -KING)){
                std::cout << (*this) << std::endl;
                assert(x88[0x77] == -ROOK && x88[0x74] == -KING);
            }

            execute_move(Move("e8c8"));
            execute_move(Move("a8d8"));
            return state;
        } else if (move.as_string() == "e8g8") {
            if (!(x88[0x70] == -ROOK && x88[0x74] == -KING)){
                std::cout << (*this) << std::endl;
                assert(x88[0x70] == -ROOK && x88[0x74] == -KING);
            }
            execute_move(Move("e8g8"));
            execute_move(Move("h8f8"));
            return state;
        }
    }

    state.killed = execute_move(move);
    return state;
}

void Board::undo_move_alt(State &state, Move rev) {
    castling = state.castling_rights;
    fifty_moves = state.fifty_moves;

    color_to_move = -color_to_move;
    plies--;
    move_history.pop_back();

    if (x88[rev.to] == KING) {
        if (rev.as_string() == "e1g1") {
            reverse_move(Move("e1g1"), 0);
            reverse_move(Move("h1f1"), 0);
            return;
        } else if (rev.as_string() == "e1c1") {
            reverse_move(Move("e1c1"), 0);
            reverse_move(Move("a1d1"), 0);
            return;
        }
    } else if (x88[rev.to] == -KING){
        if (rev.as_string() == "e8c8") {
            reverse_move(Move("e8c8"), 0);
            reverse_move(Move("a8d8"), 0);
            return;
        } else if (rev.as_string() == "e8g8") {
            reverse_move(Move("e8g8"), 0);
            reverse_move(Move("h8f8"), 0);
            return;
        }
    }
    reverse_move(rev, state.killed);
}





