//
// Created by jakob on 1/29/21.
//

#ifndef CHESS_ENGINE_CPP_BOARD_H
#define CHESS_ENGINE_CPP_BOARD_H


#include "../SimpleBoard.h"
#include "../Reversible.h"

class Board : public SimpleBoard {
public:
    virtual Reversible make_move(Ply ply);
    virtual void undo_move(Reversible ply);

    bool w_king_moved       = false;
    bool w_l_rook_moved     = false;
    bool w_r_rook_moved     = false;
    bool b_king_moved       = false;
    bool b_l_rook_moved     = false;
    bool b_r_rook_moved     = false;
    bool draw_color         = false;
};


#endif //CHESS_ENGINE_CPP_BOARD_H
