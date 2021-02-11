#ifndef CHESS_ENGINE_CPP_SEARCH_H
#define CHESS_ENGINE_CPP_SEARCH_H

#define MIN -99999
#define MAX  99999

#include "Board.h"
#include "Util.h"

/**
 * https://www.chessprogramming.org/Move_Ordering
 * https://www.chessprogramming.org/History_Heuristic
 * https://www.chessprogramming.org/Triangular_PV-Table
 * https://www.chessprogramming.org/Transposition_Table
 * https://stackoverflow.com/questions/9964496/alpha-beta-move-ordering
 *
 */

struct SearchInfo {
    SearchInfo(){
        start_time = get_time(), stop_time = 0;
        depth = 99, nodes = 0;
        stop = false, time_limit = false;
    }

    int w_history_heuristic[128][128]{};
    int b_history_heuristic[128][128]{};

    uint64_t start_time, stop_time;
    int nodes, depth;
    bool stop, time_limit;

    inline void history_heuristic(Color color, int from, int to, int val){
        if (color == WHITE){
            w_history_heuristic[from][to] = val;
        } else {
            b_history_heuristic[from][to] = val;
        }
    }

    inline void clear(){
        for (int i = 0; i < 128; i++){
            for (int j = 0; j < 128; j++){
                w_history_heuristic[i][j] = 0;
                b_history_heuristic[i][j] = 0;
            }
        }
    }
};

class Search {
public:
    static Move iterative_deepening_search(Board &board, SearchInfo &info, Color color);
    static Move search(Board &board, SearchInfo &info, std::vector<Move> &pv, Color color, int depth);
    static unsigned long long int perft(Board &board, SearchInfo &info, int depth, Color color);


private:
    static void sort_moves(Board &board, SearchInfo &ss, Move *moves, int n);
    static int quiesence(Board &board, SearchInfo &info, int alpha, int beta, Color color);
    static int alpha_beta(Board &board, SearchInfo &info, std::vector<Move> &pv, Color color, int alpha, int beta, int depth);
    static bool check_stop(SearchInfo &info);
};



#endif //CHESS_ENGINE_CPP_SEARCH_H
