//
// Created by jakob on 1/29/21.
//

#include "Board.h"

Reversible Board::make_move(Ply ply) {
    Reversible reversible(ply);
    int killed = 0;

    /*
    if (get_piece(ply.from) ==  1 && ply.from == Square("e1") && !w_king_moved)   {
        w_king_moved   = true;
        reversible.w_king_moved = true;
    } else if (get_piece(ply.from) ==  5 && ply.from == Square("a1") && !w_l_rook_moved) {
        w_l_rook_moved = true;
        reversible.w_l_rook_moved = true;
    } else if (get_piece(ply.from) ==  5 && ply.from == Square("h1") && !w_r_rook_moved) {
        w_r_rook_moved = true;
        reversible.w_r_rook_moved = true;
    } else if (get_piece(ply.from) == -1 && ply.from == Square("e8") && !b_king_moved)   {
        b_king_moved   = true;
        reversible.b_king_moved = true;
    } else if (get_piece(ply.from) == -5 && ply.from == Square("a8") && !b_l_rook_moved) {
        b_l_rook_moved = true;
        reversible.b_l_rook_moved = true;
    } else if (get_piece(ply.from) == -5 && ply.from == Square("h8") && !b_r_rook_moved) {
        b_r_rook_moved = true;
        reversible.b_r_rook_moved = true;
    }

    if (abs(get_piece(ply.from)) == 1) {
        if (ply == Ply("e1g1")) {
            //std::cout << "ply is e1g1" << std::endl;
            execute_move(Ply("e1g1"));
            execute_move(Ply("h1f1"));

        } else if (ply == Ply("e1c1")) {
            //std::cout << "ply is e1c1" << std::endl;
            execute_move(Ply("e1c1"));
            execute_move(Ply("a1d1"));

        } else if (ply == Ply("e8c8")) {
            //std::cout << "ply is e8c8" << std::endl;

            execute_move(Ply("e8c8"));
            execute_move(Ply("a8d8"));

        } else if (ply == Ply("e8g8")) {
            //std::cout << "ply is e8g8" << std::endl;
            execute_move(Ply("e8g8"));
            execute_move(Ply("h8f8"));
        } else {
            killed = execute_move(ply);
        }
    } else {
        killed = execute_move(ply);
    }

    */
    //Reversible reversible(ply);
    reversible.killed_piece = killed;
    return reversible;
}

void Board::undo_move(Reversible ply) {
//std::cout << "reverse move: " << ply << std::endl;

    if (ply.w_king_moved)   w_king_moved    = false;
    if (ply.w_r_rook_moved) w_r_rook_moved  = false;
    if (ply.w_l_rook_moved) w_l_rook_moved  = false;

    if (ply.b_king_moved)   b_king_moved    = false;
    if (ply.b_l_rook_moved) b_l_rook_moved  = false;
    if (ply.b_r_rook_moved) b_r_rook_moved  = false;

    if (abs(get_piece(ply.to)) == 1) {
        std::string move = ply.as_string();
        if (move == "e1g1") {
            reverse_move(Ply("e1g1"), 0);
            return reverse_move(Ply("h1f1"), 0);

        } else if (move == "e1c1") {
            reverse_move(Ply("e1c1"), 0);
            return reverse_move(Ply("a1d1"), 0);

        } else if (move == "e8c8") {
            reverse_move(Ply("e8c8"), 0);
            return reverse_move(Ply("a8d8"), 0);

        } else if (move == "e8g8") {
            reverse_move(Ply("e8g8"), 0);
            return reverse_move(Ply("h8f8"), 0);
        }
    }



    reverse_move(Ply(ply.from, ply.to), ply.killed_piece);}
