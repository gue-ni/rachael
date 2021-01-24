//
// Created by jakob on 1/23/21.
//

#include <vector>
#include <cassert>
#include <iostream>
#include <climits>
#include "AI.h"

Ply AI::find_best_move(Board &board, const int color, const int search_depth) {

    Ply best_move("e1e2");
    int score = 0;
    int best_score = INT_MIN;

    std::vector<Ply> moves = board.generate_valid_moves(color);
    assert(!moves.empty());

    for (Ply move : moves) {

        int killed = board.execute_move(move);
        score = -search(board, -color, INT_MIN, INT_MAX, search_depth);
        board.reverse_move(move, killed);

        if (score > best_score) {
            best_score = score;
            best_move = move;
        }
    }
    return best_move;
}

int AI::search(Board &board, const int color, int alpha, int beta, int depth) {
    // negamax alpha beta failsoft

    if (depth == 0) return color * evaluation(board);

    std::vector<Ply> moves = board.generate_valid_moves(color);
    assert(!moves.empty());

    int score = INT_MIN;

    for (Ply move : moves){
        int killed = board.execute_move(move);

        score = max(score, -search(board, -color, -beta, -alpha, depth - 1));

        board.reverse_move(move, killed);

        alpha = max(score, alpha);

        if (alpha >= beta)
            break;
    }

    return score;
}

int AI::evaluation(Board &board) {
    int wn = board.generate_valid_moves(WHITE).size();
    int bn = board.generate_valid_moves(BLACK).size();

    //printf("mobility:\nwhite=%d, black=%d\n\nmaterial:\nwhite=%d,black=%d\n",
    //        wn, bn, board.material(WHITE), board.material(BLACK));

    int mobility =  (wn - bn);
    return mobility + (board.material(WHITE) - board.material(BLACK));
}

int AI::max(int a, int b) {
    return a > b ? a : b;
}
