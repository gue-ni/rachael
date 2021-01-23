//
// Created by jakob on 1/23/21.
//

#ifndef CHESS_ENGINE_CPP_AI_H
#define CHESS_ENGINE_CPP_AI_H


#include "Ply.h"
#include "Board.h"

class AI {
public:
    virtual Ply find_best_move(Board &board, int color, int search_depth);
    int evaluation(Board &board);
    int negamax_alpha_beta_failsoft(Board &board, const int color, int alpha, int beta, int depth);
};


#endif //CHESS_ENGINE_CPP_AI_H
