//
// Created by jakob on 2/9/21.
//

#ifndef RACHAEL_MOVEGEN_H
#define RACHAEL_MOVEGEN_H


#include "Util.h"
#include "Move.h"

class MoveGen {
public:
    static int pseudo_legal(Move* moves, Color color);
    static int pseudo_legal_square(Move *moves, Square square);
};


#endif //RACHAEL_MOVEGEN_H
