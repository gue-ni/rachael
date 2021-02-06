
#ifndef CHESS_ENGINE_CPP_EVALUATION_H
#define CHESS_ENGINE_CPP_EVALUATION_H

#include "Board.h"

class Evaluation {
public:
    static int evaluation_1(Board &board);

    static int evaluation_2(Board& board);

    static int square_tables(Board& board);

};

#endif //CHESS_ENGINE_CPP_EVALUATION_H
