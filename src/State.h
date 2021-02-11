//
// Created by jakob on 2/10/21.
//

#ifndef RACHAEL_STATE_H
#define RACHAEL_STATE_H

#include <cstdint>
#include "Util.h"

struct State {
    uint8_t castling_rights = 0x00;
    int fifty_moves = 0;
    Piece killed;
};


#endif //RACHAEL_STATE_H
