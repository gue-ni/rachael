
#include <iostream>
#include <set>
#include <unordered_set>
#include <algorithm>
#include "CachedBoard.h"

std::vector<Ply> CachedBoard::generate_valid_moves_cached(int color_to_move) {
    if (color_to_move == WHITE){
        std::vector<Ply> white_moves;
        for (const auto &p : cached_white_moves){
            if (!p.second.empty())
                white_moves.insert(white_moves.end(), p.second.begin(), p.second.end());
        }
        return white_moves;
    } else {
        std::vector<Ply> black_moves;
        for (const auto &p : cached_white_moves){
            if (!p.second.empty())
                black_moves.insert(black_moves.end(), p.second.begin(), p.second.end());
        }
        return black_moves;
    }
}

CachedBoard::CachedBoard(const std::vector<int> &brd, bool draw_color) : Board(brd, draw_color) {
    std::vector<Ply> moves;
    for (int sq : valid_squares){
        if (x88[sq] == EMPTY) continue;
        moves = generate_valid_moves_square(sq);
        if (get_color(x88[sq]) == WHITE){
            cached_white_moves[sq] = moves;
        } else {
            cached_black_moves[sq] = moves;
        }
    }
}

Reversible CachedBoard::execute_reversible_move(Ply ply) {
    move_history.push_back(ply);
    Reversible rev =  Board::execute_reversible_move(ply);
    update_cache_after_move();
    return rev;
}

void CachedBoard::undo_reversible_move(Reversible ply) {
    Board::undo_reversible_move(ply);
    update_cache_after_undo();
    move_history.pop_back();
}

std::vector<int> CachedBoard::generate_squares_of_interest(int from , int to) {
    soi.clear();
    soi.push_back(from);
    soi.push_back(to);

    for (int sq : { from,to}){
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
            if (!off_the_board(s) && abs(x88[s]) == 4){
                soi.push_back(s);
            }
        }
    }
    return soi;
}

void CachedBoard::update_cache_after_move() {
    Ply last_move = move_history.back();
    soi = generate_squares_of_interest(last_move.from.index(), last_move.to.index());

    /*
    std::cout << soi.size() << " ";
    for (auto s : soi) std::cout << Square(s) << " ";
    std::cout << std::endl;
     */

    update_cache();
}

void CachedBoard::update_cache_after_undo() {
    update_cache();
}

void CachedBoard::update_cache() {
    std::vector<Ply> moves;
    for (int sq : soi){
        if (x88[sq] == 0){
            cached_white_moves[sq] = std::vector<Ply>();
            cached_black_moves[sq] = std::vector<Ply>();
            continue;
        }

        moves = generate_valid_moves_square(sq);
        if (get_color(x88[sq]) == WHITE){
            cached_white_moves[sq] = moves;
        } else {
            cached_black_moves[sq] = moves;
        }
    }
}


