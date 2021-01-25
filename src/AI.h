//
// Created by jakob on 1/23/21.
//

#ifndef CHESS_ENGINE_CPP_AI_H
#define CHESS_ENGINE_CPP_AI_H

//#define DEBUG

#include "Ply.h"
#include "Board.h"

class AI {
public:
    static Ply negamax_alphabeta_failsoft(Board &board, const int color, const int search_depth);
    static int evaluation(Board &board);
    static int negamax_alphabeta_failsoft(Board &board, int color, int alpha, int beta, int depth);
    static int negamax(Board& board, int color, int depth);

private:
    static int max(int a, int b);
};


#endif //CHESS_ENGINE_CPP_AI_H
