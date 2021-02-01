//
// Created by jakob on 1/30/21.
//

#ifndef CHESS_ENGINE_CPP_SEARCH2_H
#define CHESS_ENGINE_CPP_SEARCH2_H

#define MIN -999
#define MAX  999

#include <optional>
#include "Board.h"

struct SearchState {
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


void sort_moves(Board &board, std::vector<Ply> &moves);

void thread_search(Board& board, int color_to_move, int depth, Ply &ply);

std::optional<Ply> iterative_deepening(Board &board);

std::optional<Ply> search(Board &board, int depth);

int alpha_beta(Board &board, SearchState &ss, std::vector<Ply> &pv, int alpha, int beta, int depth);

#endif //CHESS_ENGINE_CPP_SEARCH2_H
