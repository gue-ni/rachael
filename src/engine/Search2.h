//
// Created by jakob on 1/30/21.
//

#ifndef CHESS_ENGINE_CPP_SEARCH2_H
#define CHESS_ENGINE_CPP_SEARCH2_H

#define MIN -999
#define MAX  999

#include <optional>
#include "SimpleBoard.h"

struct SearchState {
    std::vector<Ply> principal_variation;

    int w_history_heuristic[128][128];
    int b_history_heuristic[128][128];

    inline void history(int color, int from, int to, int val){
        if (color == WHITE){
            w_history_heuristic[from][to] = val;
        } else {
            b_history_heuristic[from][to] = val;
        }
    }
};

int evaluation(SimpleBoard &board);

void sort_moves(SimpleBoard &board, std::vector<Ply> &moves);

void thread_search(SimpleBoard& board, int color_to_move, int depth, Ply &ply);

std::optional<Ply> iterative_deepening(SimpleBoard &board, int color_to_move);

std::optional<Ply> search(SimpleBoard &board, int color_to_move, int depth);

int alpha_beta(SimpleBoard &board, SearchState &ss, int color_to_move, int alpha, int beta, int depth);



#endif //CHESS_ENGINE_CPP_SEARCH2_H
