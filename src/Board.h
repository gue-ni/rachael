#ifndef CHESS_ENGINE_CPP_BOARD_H
#define CHESS_ENGINE_CPP_BOARD_H

#include <cassert>
#include <cstdint>
#include <vector>

#include "Util.h"
#include "Move.h"
#include "State.h"

#define BLACK_TTY   "\033[0;31m"
#define WHITE_TTY   "\033[0;34m"
#define CLEAR_TTY   "\033[0m"

#define W_CASTLE_QUEENSIDE (uint8_t)0x01
#define W_CASTLE_KINGSIDE  (uint8_t)0x02

#define B_CASTLE_QUEENSIDE (uint8_t)0x10
#define B_CASTLE_KINGSIDE  (uint8_t)0x20

// implemented rules
#define CASTLING
#define PROMOTION
#define EN_PASSANT
#define FIFTY_MOVES

class Board {
public:
    Color color_to_move;
    int plies, fifty_moves, material;
    std::vector<Move> move_history;
    uint8_t castling = 0x00;
    Square b_king = INVALID_SQUARE, w_king = INVALID_SQUARE, en_passant = INVALID_SQUARE;
    Color en_passant_color;
    Piece x88[128] = { 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99, 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                       0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99, 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                       0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99, 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                       0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99, 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99 };

    Board();
    Board(const std::string& fen, bool draw_color);
    friend std::ostream& operator<<(std::ostream&, const Board&);

    void set_board(const std::string &fen);

    State make_move(Move move);
    void  undo_move(State &state, Move move);
    Piece execute_move(Move move);
    void  reverse_move(Move move, Piece killed);

    bool is_checked(Color color);
    int pseudo_legal(Move *moves, Color color);

    inline bool is_empty(Square square){
        return x88[square] == EMPTY_SQUARE;
    }

    inline bool is_enemy(Square square, Piece piece) {
        return x88[square] == EMPTY_SQUARE ? false : get_color(x88[square]) != get_color(piece);
    }

    inline bool is_friendly(Square square, Piece piece) {
        return x88[square] == EMPTY_SQUARE ? false : get_color(x88[square]) == get_color(piece);
    }

    bool is_attacked(Square origin, Color color);

    bool is_legal_move(Move move, Color color);

    int check_dir(Move *moves, int n, Square from, int max_steps, const std::vector<int> &dirs);

    int pseudo_legal_for_square(Move *moves, int n, Square from);




private:
    bool draw_color;
    void calculate_material();

};

#endif //CHESS_ENGINE_CPP_BOARD_H
