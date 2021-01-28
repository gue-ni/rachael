#include <iostream>
#include "../src/Board.h"



int main(){
    Board board(RUY_LOPEZ, true);
    //std::cout << board << std::endl;

    /*
    ReversiblePly rp = board.execute_move_rev(Ply("a2a4"));
    //ReversiblePly rp = board.execute_move_rev(Ply("e1g1"));
    //std::cout << rp << std::endl;
    std::cout << board << std::endl;
    std::cout << "white king moved " << board.w_king_moved << std::endl;
    board.reverse_move_rev(rp);
    std::cout << board << std::endl;
    std::cout << "white king moved " << board.w_king_moved << std::endl;
     */


    ReversiblePly p1 = board.execute_move_rev(Ply("e1f1"));
    ReversiblePly p2 = board.execute_move_rev(Ply("h1g1"));

    //board.make_move(Ply("e1f1"));
    std::cout << board << std::endl;
    std::cout
    << "w_king_moved=" << board.w_king_moved
    << ", w_l_rook_moved=" << board.w_l_rook_moved
    << ", w_r_rook_moved=" << board.w_r_rook_moved
    << std::endl;

    board.reverse_move_rev(p2);
    //board.reverse_move_rev(p1);


    std::cout << board << std::endl;
    std::cout
    << "w_king_moved=" << board.w_king_moved
    << ", w_l_rook_moved=" << board.w_l_rook_moved
    << ", w_r_rook_moved=" << board.w_r_rook_moved
    << std::endl;



}
