   //
// Created by jakob on 1/28/21.
//

#ifndef CHESS_ENGINE_CPP_CACHEDBOARD_H
#define CHESS_ENGINE_CPP_CACHEDBOARD_H

#include <map>
#include "SimpleBoard.h"

class CachedBoard : public SimpleBoard {
public:
    CachedBoard(const std::vector<int> &brd, bool draw_color);
    std::vector<Ply> move_history;


    Reversible make_move(Ply ply) override;
    void undo_move(Reversible ply) override;

    std::map<int, std::vector<Ply>> cached_white_moves;
    std::map<int, std::vector<Ply>> cached_black_moves;


    std::vector<Ply> generate_valid_moves(int color_to_move) override;
    void update_cache_after_move();
    void update_cache_after_undo();
    void update_cache();
    std::vector<int> generate_squares_of_interest(int from , int to);

    std::vector<int> soi;
};


#endif //CHESS_ENGINE_CPP_CACHEDBOARD_H
