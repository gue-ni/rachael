//
// Created by jakob on 1/28/21.
//

#include "ReversiblePly.h"

ReversiblePly::ReversiblePly(Ply ply, int killed) : Ply(ply.from, ply.to), killed_piece(killed){}
