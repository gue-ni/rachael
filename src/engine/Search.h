
#ifndef CHESS_ENGINE_CPP_SEARCH_H
#define CHESS_ENGINE_CPP_SEARCH_H

//#define DEBUG_SEARCH
#define PRINT_PV

#define MIN -999
#define MAX  999

#define NEGAMAX                     1
#define NEGAMAX_ALPHABETA_FAILSOFT  2
#define NEGAMAX_ALPHABETA_FAILHARD  3


#include <optional>

#include "Ply.h"
#include "SimpleBoard.h"

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

class Search {
public:
    explicit Search(int algorithm);
    Search(int algorithm, bool order_moves);

    std::optional<Ply> search(SimpleBoard &board, int color_to_move, int depth);

    int algorithm;
    bool order_moves = true;

    int w_history_heuristic[128][128];
    int b_history_heuristic[128][128];

    static int max(int a, int b);
    static int evaluation(SimpleBoard &board);
    void move_ordering(SimpleBoard &board, std::vector<Ply> &moves);

    std::optional<Ply> negamax(SimpleBoard& board, int color_to_move, int depth);
    int _negamax(SimpleBoard& board, int color_to_move, int depth);

    std::optional<Ply> alphabeta_failsoft(SimpleBoard &board, int color_to_move, int depth);
    int _alphabeta_failsoft(SimpleBoard &board, int color_to_move, int alpha, int beta, int depth);

    std::optional<Ply> alphabeta_failhard(SimpleBoard &board, int color_to_move, int depth);
    int _alphabeta_failhard(SimpleBoard &board, int color_to_move, int alpha, int beta, int depth);
};


#endif //CHESS_ENGINE_CPP_SEARCH_H
