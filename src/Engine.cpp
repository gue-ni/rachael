//
// Created by jakob on 1/23/21.
//

#include <vector>
#include <cassert>
#include <iostream>
#include <climits>
#include "Engine.h"


int Engine::evaluation(Board &board) {
    int wn = board.generate_valid_moves(WHITE).size();
    int bn = board.generate_valid_moves(BLACK).size();

    int mobility =  (wn - bn);
    return mobility + (board.material(WHITE) - board.material(BLACK));
}

int Engine::max(int a, int b) {
    return a > b ? a : b;
}


std::optional<Ply> Engine::find_best_move(Board &board, int color_to_move, int depth, int algorithm) {
    switch (algorithm){
        case NEGAMAX:
            return negamax(board, color_to_move, depth);

        case NEGAMAX_ALPHABETA_FAILSOFT:
            return negamax_alphabeta_failsoft(board, color_to_move, depth);

        default:
            assert(false);
            return std::nullopt;
    }
}


std::optional<Ply> Engine::negamax(Board &board, int color_to_move, int depth) {
    std::optional<Ply> best_move = std::nullopt;
    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);

    int best = MIN;

    for (Ply move : moves){
        int killed = board.execute_move(move);
        int score = -negamax_rec(board, -color_to_move, depth - 1);
        board.reverse_move(move, killed);

        if (score > best)
            best = score;
    }
    return best_move;
}

int Engine::negamax_rec(Board &board, int color_to_move, int depth) {
    if (depth == 0) return color_to_move * evaluation(board);

    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);
    int best = MIN-depth;

    for (Ply move : moves){
        int killed = board.execute_move(move);
        int score = -negamax_rec(board, -color_to_move, depth - 1);
        board.reverse_move(move, killed);

        if (score > best)
            best = score;
    }
    return best;
}


std::optional<Ply> Engine::negamax_alphabeta_failsoft(Board &board, int color_to_move, int depth) {
    int score       = 0;
    int best_score  = MIN;

    std::optional<Ply> best_move = std::nullopt;
    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);
    if (!moves.empty()){
        best_move = moves.front();
    }

    for (Ply move : moves) {

        if (abs(board.get_piece(move.to)) == 1){ // can capture enemy king
#ifdef DEBUG_SEARCH
            std::cout << move << " can capture king" << std::endl;
#endif
            return move;
        }

        int killed = board.execute_move(move);
        score = -negamax_alphabeta_failsoft(board, -color_to_move, MIN, MAX, depth);
#ifdef DEBUG_SEARCH
        std::cout << "[ROOT] " << move << " " << score << std::endl;
#endif
        board.reverse_move(move, killed);

        if (score > best_score) {
            best_score  = score;
            best_move   = move;
        }
    }
    return best_move;
}

int Engine::negamax_alphabeta_failsoft(Board &board, const int color_to_move, int alpha, int beta, int depth) {
    if (depth == 0) {
        int eval = color_to_move * evaluation(board);
#ifdef DEBUG_SEARCH
        std::cout << "[SEARCH] depth=" << depth << ", color_to_move=" << color_to_move << ", eval=" << eval << std::endl;
#endif
        return eval;
    }

    int score = MIN-depth;
    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);

#ifdef DEBUG_SEARCH
    std::cout << "[SEARCH] depth=" << depth << ", color_to_move=" << color_to_move << ", moves=" << moves.size() << " ";
    for (auto &p : moves) std::cout << p << " ";
    std::cout << std::endl;
#endif

    for (Ply move : moves){

        if (abs(board.get_piece(move.to)) == 1){
            return MAX+depth;
        }

        int killed = board.execute_move(move);
        score = max(score, -negamax_alphabeta_failsoft(board, -color_to_move, -beta, -alpha, depth - 1));
        board.reverse_move(move, killed);

        alpha = max(score, alpha);

        if (alpha >= beta)
            break;
    }
    return score;
}


