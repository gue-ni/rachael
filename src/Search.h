//
// Created by jakob on 1/30/21.
//

#ifndef CHESS_ENGINE_CPP_SEARCH_H
#define CHESS_ENGINE_CPP_SEARCH_H

#define MIN -999
#define MAX  999

# define NOW std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()

#include <optional>
#include "Board.h"

/**
 * https://www.chessprogramming.org/Move_Ordering
 * https://www.chessprogramming.org/History_Heuristic
 * https://www.chessprogramming.org/Triangular_PV-Table
 * https://www.chessprogramming.org/Transposition_Table
 * https://stackoverflow.com/questions/9964496/alpha-beta-move-ordering
 *
 * TODO implment move ordering
 * 16*victimValue - attacherValue
 *
 * TODO implement hash table for good moves
 */

struct SearchState {
    int w_history_heuristic[128][128];
    int b_history_heuristic[128][128];

    uint64_t start_time;
    int nodes = 0;

    inline void history_heuristic(int color, int from, int to, int val){
        if (color == WHITE){
            w_history_heuristic[from][to] = val;
        } else {
            b_history_heuristic[from][to] = val;
        }
    }
};

void iterative_deepening(Board &board, Ply &best_move,  SearchState &ss, int max_depth, bool &stop);

std::optional<Ply> search(Board &board, int depth);

int alpha_beta(Board &board, SearchState &ss, std::vector<Ply> &pv, int alpha, int beta, int depth, bool &stop);

int quiesence(int alpha, int beta);

void test(int d, int b);

#endif //CHESS_ENGINE_CPP_SEARCH_H
