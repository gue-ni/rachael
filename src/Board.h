
#ifndef CHESS_ENGINE_CPP_BOARD_H
#define CHESS_ENGINE_CPP_BOARD_H

#include <cassert>
#include <cstdint>
#include <vector>

#include "Util.h"
#include "Ply.h"
#include "Reversible.h"

#define BLACK_TTY   "\033[0;31m"
#define WHITE_TTY   "\033[0;34m"
#define CLEAR_TTY   "\033[0m"

#define CASTLING
//#define PROMOTION

#define RUY_LOPEZ \
"r1bqk1nr/pppp1ppp/2n5/1Bb1p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4"

#define DEFAULT_BOARD \
"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define FRENCH_DEFENSE_BURN_VARIATION \
"rnbqkb1r/ppp2ppp/4pn2/3p2B1/3PP3/2N5/PPP2PPP/R2QKBNR b KQkq - 0 5"

#define SICILIAN_DEFENSE \
"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2"

#define SICILIAN_DEFENSE_NAJDORF_VARIATION \
"rnbqkb1r/1p2pppp/p2p1n2/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 6"

class Board {
public:
    explicit Board(bool draw_color);
    Board(const std::string& fen, bool draw_color);

    Color color_to_move;
    int ply_count;

    std::vector<Ply> pseudo_legal_moves(Color color);

    Reversible make_move(Ply ply);
    void undo_move(Reversible reversible);

    int  material(Color color);

    void set_board(const std::string &fen);

    bool is_legal_move(Ply ply);

    bool is_checked(Color color);

    inline Piece get_piece(Square square) {
        return x88[square];
    }

    inline bool is_empty(Square square){
        return x88[square] == EMPTY_SQUARE;
    }

    static inline Color get_color(Piece piece) {
        assert(piece != EMPTY_SQUARE);
        return ((piece > 0) ? 1 : ((piece < 0) ? -1 : 0));
    }

    friend std::ostream& operator<<(std::ostream&, const Board&);

    bool is_threatened(Square square, Color color);

    Piece x88[128]                    = { 0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                                        0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                                        0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                                        0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                                        0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                                        0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                                        0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99,
                                        0,0,0,0,0,0,0,0,99,99,99,99,99,99,99,99 };

    std::vector<Square> valid_squares = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                         0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                         0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                                         0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                                         0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                                         0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                                         0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                                         0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77 };
    Square b_king = 0;

    std::vector<Ply> check_directions(Square from, Piece piece, const std::vector<int> &dirs, int max_steps);

    void legal_moves_square(std::vector<Ply> &legal_moves, Square square);

private:
    const char pieces[7]            = {'.', 'K', 'Q', 'B', 'N', 'R', 'p'};
    const int material_value[7]     = { 0,   20000, 900,   330,   320,   500,   100 };
    //const int material_value[7]     = { 0,   200, 9,   3,   3,   5,   1 };

    int w_material = 0, b_material = 0;
    bool draw_color = true;

    bool w_castle_k, w_castle_q;
    bool b_castle_q, b_castle_k;
    Square w_king = 0;

    void reverse_move(Ply ply, Piece killed);

    Piece  execute_move(Ply ply);

    void calculate_material();

    void check_directions(std::vector<Ply> &moves, Square from, Piece piece, const std::vector<int> &dirs, int max_steps);

    inline bool is_enemy(Square square, Piece piece) {
        return x88[square] == EMPTY_SQUARE ? false : get_color(x88[square]) != get_color(piece);
    }

    inline bool is_friendly(Square square, Piece piece) {
        return x88[square] == EMPTY_SQUARE ? false : get_color(x88[square]) == get_color(piece);
    }

    inline void set_piece(Square square, Piece piece) {
        x88[square] = piece;
    }

    static inline bool off_the_board(Square square){
        return square & 0x88;
    }
};

#endif //CHESS_ENGINE_CPP_BOARD_H
