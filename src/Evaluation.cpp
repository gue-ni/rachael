#include "Evaluation.h"

const int pawns_table[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 20, 30, 30, 20, 10, 10,
        5,  5, 10, 25, 25, 10,  5,  5,
        0,  5,  5, 20, 20,  5,  5,  0,
        5,  0,  0,  0,  0,  0,  0,  5,
        5, 10, 10,-20,-20, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
};
const int knight_table[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
};
const int bishop_table[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
};
const int rook_table[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
};
const int queen_table[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -5,  0,  5,  5,  5,  5,  0, -5,
        0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
};
const int king_table[64] = {
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        20, 20,  0,  0,  0,  0, 20, 20,
        20, 30, 10,  0,  0, 10, 30, 20
};

int Evaluation::basic_evaluation_function(Board &board) {
    // TODO does not account for actually legal moves, only pseudo legal moves
    int mobility = (int) board.pseudo_legal_moves(WHITE).size() - (int) board.pseudo_legal_moves(BLACK).size();
    int material = board.material(WHITE) - board.material(BLACK);
    //std::cout << "mobility: " << mobility << std::endl;
    //std::cout << "material: " << material << std::endl;
    return mobility + material;
}

int Evaluation::simplified_evaluation_function(Board &board){
    int squares = square_table(board);
    int material = board.material(WHITE) - board.material(BLACK);
    return squares + material;
}

int Evaluation::square_table(Board &board) {
    int value = 0;

    for (Square square : board.valid_squares){
        Piece piece = board.get_piece(square);

        if (piece == EMPTY_SQUARE) continue;

        Color color = Board::get_color_of_piece(piece);
        piece = abs(piece);
        int sq64 = convert_8x8(square);

        if (color == WHITE) sq64 = sq64 ^ 56; // mirror

        // position value
        switch (piece){
            case PAWN:
                value += (color * pawns_table[sq64]);
                break;
            case KNIGHT:
                value += (color * knight_table[sq64]);
                break;
            case ROOK:
                value += (color * rook_table[sq64]);
                break;
            case BISHOP:
                value += (color * bishop_table[sq64]);
                break;
            case QUEEN:
                value += (color * queen_table[sq64]);
                break;
            case KING:
                value += (color * king_table[sq64]);
                break;
            default:
                assert(false);
        }
    }
    return value;
}

