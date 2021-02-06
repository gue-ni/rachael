//
// Created by jakob on 1/30/21.
//

#ifndef CHESS_ENGINE_CPP_SEARCH_H
#define CHESS_ENGINE_CPP_SEARCH_H

#define MIN -999
#define MAX  999

#include <optional>
#include "Board.h"
#include "Util.h"

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

struct SearchInfo {

    SearchInfo(){
        start_time = get_time();
        depth = 99;
        nodes = 0;
        stop = false;
        time_limit = false;
    }

    int w_history_heuristic[128][128]{};
    int b_history_heuristic[128][128]{};

    uint64_t start_time = 0;
    uint64_t stop_time  = 0;
    int nodes, depth;
    bool stop = false, time_limit = true;

    inline void history_heuristic(int color, int from, int to, int val){
        if (color == WHITE){
            w_history_heuristic[from][to] = val;
        } else {
            b_history_heuristic[from][to] = val;
        }
    }
};

class Search {
public:
    static void iterative_deepening(Board &board, SearchInfo &info, int color);
    /*
    std::optional<Ply> search(Board &board, int depth, int color);
    */

private:
    static void sort_moves(Board &board, SearchInfo &ss, std::vector<Ply> &moves);
    static int quiesence(Board &board, SearchInfo &info, int alpha, int beta, int color);
    static int alpha_beta(Board &board, SearchInfo &info, std::vector<Ply> &pv, int color, int alpha, int beta, int depth);
    static void check_stop(SearchInfo &info);
};



#endif //CHESS_ENGINE_CPP_SEARCH_H
