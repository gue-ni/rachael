
#ifndef CHESS_ENGINE_CPP_EVALUATION_H
#define CHESS_ENGINE_CPP_EVALUATION_H

#include "Board.h"

class Evaluation {
public:
    static int evaluation_function(Board &board);

    static int simplified_evaluation_function(Board& board);

    static int square_tables(Board& board);

};

#endif //CHESS_ENGINE_CPP_EVALUATION_H
