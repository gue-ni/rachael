//
// Created by jakob on 1/30/21.
//

#ifndef CHESS_ENGINE_CPP_SEARCH2_H
#define CHESS_ENGINE_CPP_SEARCH2_H

#define MIN -999
#define MAX  999

#include <optional>
#include "SimpleBoard.h"

class Search2 {
public:
    Search2();

    int w_history_heuristic[128][128];
    int b_history_heuristic[128][128];

    static int evaluation(SimpleBoard &board);
    void sort_moves(SimpleBoard &board, std::vector<Ply> &moves);

    std::optional<Ply> iterative_deepening(SimpleBoard &board, int color_to_move);

    std::optional<Ply> search(SimpleBoard &board, int color_to_move, int depth);
    int _search(SimpleBoard &board, int color_to_move, int alpha, int beta, int depth);
};


#endif //CHESS_ENGINE_CPP_SEARCH2_H
