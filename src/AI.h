//
// Created by jakob on 1/23/21.
//

#ifndef CHESS_ENGINE_CPP_AI_H
#define CHESS_ENGINE_CPP_AI_H


#include "Ply.h"
#include "Board.h"

class AI {
public:
    static Ply find_best_move(Board &board, int color, int search_depth);
    static int evaluation(Board &board);
    static int search(Board &board, int color, int alpha, int beta, int depth);

private:
    static int max(int a, int b);
};


#endif //CHESS_ENGINE_CPP_AI_H
