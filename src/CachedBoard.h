   //
// Created by jakob on 1/28/21.
//

#ifndef CHESS_ENGINE_CPP_CACHEDBOARD_H
#define CHESS_ENGINE_CPP_CACHEDBOARD_H


#include "Board.h"

class CachedBoard : public Board {
public:
    CachedBoard(const std::vector<int> &brd, bool draw_color);
    std::vector<Ply> move_history;

    std::vector<Ply> generate_valid_moves_cached(int color_to_move);

    Reversible execute_reversible_move(Ply ply) override;
    void undo_reversible_move(Reversible ply) override;

    std::vector<Ply> white_moves;
    std::vector<Ply> black_moves;

    void update_cache();
    std::vector<int> generate_squares_of_interest(int sq);
};


#endif //CHESS_ENGINE_CPP_CACHEDBOARD_H
