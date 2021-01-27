//
// Created by jakob on 1/23/21.
//

#ifndef CHESS_ENGINE_CPP_ENGINE_H
#define CHESS_ENGINE_CPP_ENGINE_H

//#define DEBUG_SEARCH
#define MIN -999
#define MAX  999

#define NEGAMAX                     1
#define NEGAMAX_ALPHABETA_FAILSOFT  2

#include <optional>

#include "Ply.h"
#include "Board.h"

class Engine {
public:
    static std::optional<Ply> find_best_move(Board &board, int color_to_move, int depth, int algorithm);

private:
    static int max(int a, int b);

    static int evaluation(Board &board);

    static std::optional<Ply> negamax(Board& board, int color_to_move, int depth);
    static int negamax_rec(Board& board, int color_to_move, int depth);

    static std::optional<Ply> negamax_alphabeta_failsoft(Board &board, int color_to_move, int depth);
    static int negamax_alphabeta_failsoft(Board &board, int color_to_move, int alpha, int beta, int depth);
};


#endif //CHESS_ENGINE_CPP_ENGINE_H
