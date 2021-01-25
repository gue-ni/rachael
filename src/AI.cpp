//
// Created by jakob on 1/23/21.
//

#include <vector>
#include <cassert>
#include <iostream>
#include <climits>
#include "AI.h"

int AI::negamax_alphabeta_failsoft(Board &board, const int color, int alpha, int beta, int depth) {
    if (depth == 0) return color * evaluation(board);

    int score = INT_MIN;
    std::vector<Ply> moves = board.generate_valid_moves(color);
    //assert(!moves.empty());

    for (Ply move : moves){

        if (abs(board.get_piece(move.to)) == 1){
            return INT_MAX;
        }

        int killed = board.execute_move(move);
        score = max(score, -negamax_alphabeta_failsoft(board, -color, -beta, -alpha, depth-1));
        board.reverse_move(move, killed);

        alpha = max(score, alpha);

        if (alpha >= beta)
            break;
    }
    return score;
}

Ply AI::negamax_alphabeta_failsoft(Board &board, const int color, const int search_depth) {
    Ply best_move("e1e2");
    int score       = 0;
    int best_score  = INT_MIN;

    std::vector<Ply> moves = board.generate_valid_moves(color);
    assert(!moves.empty());

    for (Ply move : moves) {

        if (abs(board.get_piece(move.to)) == 1){ // can capture enemy king
            return move;
        }

        int killed = board.execute_move(move);
        score = -negamax_alphabeta_failsoft(board, -color, INT_MIN, INT_MAX, search_depth);
        board.reverse_move(move, killed);

        if (score > best_score) {
            best_score  = score;
            best_move   = move;
        }
    }
    //std::cout << "best_score was " << best_score << std::endl;
    return best_move;
}

int AI::evaluation(Board &board) {

    int wn = board.generate_valid_moves(WHITE).size();
    int bn = board.generate_valid_moves(BLACK).size();

    int mobility =  (wn - bn);
    return mobility + (board.material(WHITE) - board.material(BLACK));
}

int AI::max(int a, int b) {
    return a > b ? a : b;
}

int AI::negamax(Board &board, int color, int depth) {
    if (depth == 0) return color * evaluation(board);
    std::vector<Ply> moves = board.generate_valid_moves(color);
    if (moves.empty()){
        std::cout << "possible checkmate" << std::endl;
        std::cout << board;
    }
    assert(!moves.empty());

    int best = INT_MIN;
    for (Ply move : moves){
        int killed = board.execute_move(move);
        int score = -negamax(board, -color, depth-1);
        board.reverse_move(move, killed);

        if (score > best)
            best = score;
    }
    return best;
}
