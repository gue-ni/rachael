//
// Created by jakob on 1/23/21.
//

#ifndef CHESS_ENGINE_CPP_AI_H
#define CHESS_ENGINE_CPP_AI_H

//#define DEBUG_SEARCH
#define MIN -999
#define MAX  999

#include <optional>

#include "Ply.h"
#include "Board.h"

class AI {
public:
    static int evaluation(Board &board);
    static int negamax(Board& board, int color, int depth);
    static std::optional<Ply> negamax_alphabeta_failsoft(Board &board, int color, int depth);
    static int negamax_alphabeta_failsoft(Board &board, int color, int alpha, int beta, int depth);

private:
    static int max(int a, int b);
};


#endif //CHESS_ENGINE_CPP_AI_H
