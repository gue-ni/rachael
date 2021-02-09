#ifndef CHESS_ENGINE_CPP_BOARD_H
#define CHESS_ENGINE_CPP_BOARD_H

#include <cassert>
#include <cstdint>
#include <vector>

#include "Util.h"
#include "Move.h"
#include "Reversible.h"

#define BLACK_TTY   "\033[0;31m"
#define WHITE_TTY   "\033[0;34m"
#define CLEAR_TTY   "\033[0m"

// implemented rules
#define CASTLING
#define PROMOTION
#define FIFTY_MOVES

class Board {
public:
    /* STATE */
    Color color_to_move;
    int plies, fifty_moves;
    Piece x88[128] = { 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99, 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                       0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99, 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                       0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99, 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                       0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99, 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99 };


    Board();
    Board(const std::string& fen, bool draw_color);
    friend std::ostream& operator<<(std::ostream&, const Board&);

    Reversible make_move(Move move);
    void undo_move(Reversible rev);

    int  material(Color color);
    void set_board(const std::string &fen);

    // this should be faster
    int pseudo_legal(Move *moves, Color color);
    int pseudo_legal_for_square(Move *moves, int n, Square from);
    int check_dir(Move *moves, int n, Square from, int max_steps, const std::vector<int> &dirs);


    std::vector<Move> check_directions(Square from, Piece piece, const std::vector<int> &dirs, int max_steps);
    std::vector<Move> pseudo_legal_moves(Color color);
    void legal_moves_square(std::vector<Move> &legal_moves, Square square);

    bool is_checked(Color color);
    bool is_threatened(Square square, Color color);

    inline bool is_empty(Square square){
        return x88[square] == EMPTY_SQUARE;
    }

    inline bool is_enemy(Square square, Piece piece) {
        return x88[square] == EMPTY_SQUARE ? false : get_color(x88[square]) != get_color(piece);
    }

    inline bool is_friendly(Square square, Piece piece) {
        return x88[square] == EMPTY_SQUARE ? false : get_color(x88[square]) == get_color(piece);
    }

private:

    int w_material = 0, b_material = 0;
    bool draw_color, w_castle_k, w_castle_q, b_castle_q, b_castle_k;
    Square w_king = 0, b_king = 0;

    void  reverse_move(Move move, Piece killed);
    Piece execute_move(Move move);

    void calculate_material();
    void check_directions(std::vector<Move> &moves, Square from, Piece piece, const std::vector<int> &dirs, int max_steps);
};

#endif //CHESS_ENGINE_CPP_BOARD_H
