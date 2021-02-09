#ifndef CHESS_ENGINE_CPP_EVALUATION_H
#define CHESS_ENGINE_CPP_EVALUATION_H

#include "Board.h"

class Evaluation {
public:
    static int basic_evaluation_function(Board &board);
    static int simplified_evaluation_function(Board& board);

private:
    static int square_table(Board& board);
};

#endif //CHESS_ENGINE_CPP_EVALUATION_H
