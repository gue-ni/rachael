//
// Created by jakob on 1/23/21.
//

#include <vector>
#include <f2c.h>
#include "AI.h"

Ply AI::find_best_move(Board &board, const int color, const int search_depth) {

    Ply best_move("0000");
    int score = 0;
    int best_score = INT32_MIN;

    std::vector<Ply> moves = board.generate_valid_moves(color);

    for (Ply move : moves) {

        int killed = board.execute_move(move);
        score = -negamax_alpha_beta_failsoft(board, -color, INT32_MIN, INT32_MAX, search_depth);
        board.reverse_move(move, killed);

        if (score > best_score) {
            best_score = score;
            best_move = move;
        }
    }
    return best_move;
}

int AI::negamax_alpha_beta_failsoft(Board &board, const int color, int alpha, int beta, int depth) {
    if (depth == 0) return color * evaluation(board);

    std::vector<Ply> moves = board.generate_valid_moves(color);

    int score = INT32_MIN;

    for (Ply move : moves){
        int killed = board.execute_move(move);

        score = max(score, -negamax_alpha_beta_failsoft(board, -color, -beta, -alpha, depth - 1));

        board.reverse_move(move, killed);

        alpha = max(score, alpha);

        if (alpha >= beta)
            break;    }

    return score;
}

int AI::evaluation(Board &board) {
    int wn = board.generate_valid_moves(WHITE).size();
    int bn = board.generate_valid_moves(BLACK).size();

    int mobility =  (wn - bn);
    return mobility + (board.material(WHITE) - board.material(BLACK));
}
