
#include <iostream>
#include "CachedBoard.h"

std::vector<Ply> CachedBoard::generate_valid_moves_cached(int color_to_move) {
    return color_to_move == WHITE ? white_moves : black_moves;
}

CachedBoard::CachedBoard(const std::vector<int> &brd, bool draw_color) : Board(brd, draw_color) {
    std::vector<Ply> moves;

    for (int sq : valid_squares){
        if (!is_empty(sq)){
            moves = generate_valid_moves_square(sq);
            if (get_color(x88[sq]) == WHITE){
                white_moves.insert(white_moves.end(), moves.begin(), moves.end());
            } else {
                black_moves.insert(black_moves.end(), moves.begin(), moves.end());
            }
        }
    }
}

Reversible CachedBoard::execute_reversible_move(Ply ply) {
    move_history.push_back(ply);
    return Board::execute_reversible_move(ply);
}

void CachedBoard::undo_reversible_move(Reversible ply) {
    move_history.pop_back();
    Board::undo_reversible_move(ply);
}

std::vector<int> CachedBoard::generate_squares_of_interest(int sq) {
    std::vector<int> soi = { sq };

    for (int dir : { N, NE, E, SE, S, SW, W, NW }){
        int d = sq;
        while (true){
            d+=dir;

            if (off_the_board(d))
                break;

            if (!is_empty(d)){
                soi.push_back(d);
                break;
            }
        }
    }

    for (int s : { sq+NNE, sq+ENE, sq+ESE, sq+SSE, sq+SSW, sq+WSW, sq+WNW, sq+NNW }){
        if (!off_the_board(s)){
            soi.push_back(s);
        }
    }

    return soi;
}

void CachedBoard::update_cache() {
    Ply last_move = move_history.back();

    std::vector<int> soi;
    std::vector<int> s;

    s = generate_squares_of_interest(last_move.from.index());
    soi.insert(soi.end(), s.begin(), s.end());
    s = generate_squares_of_interest(last_move.to.index());
    soi.insert(soi.end(), s.begin(), s.end());

    std::cout << soi.size() << " ";

    for (auto s : soi) std::cout << Square(s) << " ";
    std::cout << std::endl;


}
