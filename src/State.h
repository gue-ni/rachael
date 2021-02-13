#ifndef RACHAEL_STATE_H
#define RACHAEL_STATE_H

#include <cstdint>

#include "Util.h"
#include "Move.h"

struct State {
    uint8_t castling_rights = 0x00;
    int fifty_moves = 0;
    Piece killed = 0;
    Move move;
};


#endif //RACHAEL_STATE_H
