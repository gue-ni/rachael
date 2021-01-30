
#include <vector>
#include <cassert>
#include <iostream>

#include "Search.h"


int Search::evaluation(SimpleBoard &board) {
    int mobility =  ((int)board.generate_valid_moves(WHITE).size()
            - (int)board.generate_valid_moves(BLACK).size());
    std::cout << "mobility: " << mobility << std::endl;

    int material = board.material(WHITE) - board.material(BLACK);
    std::cout << "material: " << material << std::endl;

    return mobility + material;
}

int Search::max(int a, int b) {
    return a > b ? a : b;
}

std::optional<Ply> Search::find_best_move(SimpleBoard &board, int color_to_move, int depth) {
    switch (algorithm){
        case NEGAMAX:                       return negamax(board, color_to_move, depth);
        case NEGAMAX_ALPHABETA_FAILSOFT:    return alphabeta_failsoft(board, color_to_move, depth);
        case NEGAMAX_ALPHABETA_FAILHARD:    return alphabeta_failhard(board, color_to_move, depth);
        default:
            assert(false);
            return std::nullopt;
    }
}

std::optional<Ply> Search::negamax(SimpleBoard &board, int color_to_move, int depth) {
    std::optional<Ply> best_move = std::nullopt;
    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);

    int best = MIN;

    if (order_moves) move_ordering(board, moves);

    for (Ply move : moves){
        int killed = board.execute_move(move);
        int score = -_negamax(board, -color_to_move, depth - 1);
        board.reverse_move(move, killed);

        if (score > best)
            best = score;
    }
    return best_move;
}

int Search::_negamax(SimpleBoard &board, int color_to_move, int depth) {
    if (depth == 0) return color_to_move * evaluation(board);

    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);
    int best = MIN-depth;

    if (order_moves) move_ordering(board, moves);

    for (Ply move : moves){
        int killed = board.execute_move(move);
        int score = -_negamax(board, -color_to_move, depth - 1);
        board.reverse_move(move, killed);

        if (score > best)
            best = score;
    }
    return best;
}

std::optional<Ply> Search::alphabeta_failsoft(SimpleBoard &board, int color_to_move, int depth) {
    int score       = 0;
    int best_score  = MIN;

    std::optional<Ply> best_move = std::nullopt;
    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);
    if (!moves.empty()){
        best_move = moves.front();
    }

    if (order_moves) move_ordering(board, moves);

    for (Ply move : moves) {

        if (abs(board.get_piece(move.to)) == 1){ // can capture enemy king
#ifdef DEBUG_SEARCH
            std::cout << move << " can capture king" << std::endl;
#endif
            return move;
        }

        //int killed = board.execute_move(move);
        Reversible rp = board.make_move(move);
        score = -_alphabeta_failsoft(board, -color_to_move, MIN, MAX, depth);
#ifdef DEBUG_SEARCH
        std::cout << "[ROOT] " << move << " " << score << std::endl;
#endif
        //board.reverse_move(move, killed);
        board.undo_move(rp);

        if (score > best_score) {
            best_score  = score;
            best_move   = move;
        }
    }
    return best_move;
}

int Search::_alphabeta_failsoft(SimpleBoard &board, int color_to_move, int alpha, int beta, int depth) {
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

    if (order_moves) move_ordering(board, moves);

    for (Ply move : moves){

        if (abs(board.get_piece(move.to)) == 1){
            return MAX+depth;
        }

        Reversible rp = board.make_move(move);
        score = max(score, -_alphabeta_failsoft(board, -color_to_move, -beta, -alpha, depth - 1));
        board.undo_move(rp);

        alpha = max(score, alpha);

        if (alpha >= beta) {
            if (board.get_piece(move.to) == 0) {
                if (color_to_move == WHITE) {
                    w_history_heuristic[move.from][move.to] = depth * depth;
                } else {
                    b_history_heuristic[move.from][move.to] = depth * depth;
                }
            }
            break;
        }
    }
    return score;
}

std::optional<Ply> Search::alphabeta_failhard(SimpleBoard &board, int color_to_move, int depth) {
    int score       = 0;
    int best_score  = MIN;

    std::optional<Ply> best_move = std::nullopt;
    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);
    if (!moves.empty()){
        best_move = moves.front();
    }

    if (order_moves) move_ordering(board, moves);

    for (Ply move : moves) {

        if (abs(board.get_piece(move.to)) == 1){ // can capture enemy king
            return move;
        }

        Reversible r = board.make_move(move);
        score = -_alphabeta_failhard(board, -color_to_move, MIN, MAX, depth);
        board.undo_move(r);

        if (score > best_score) {
            best_score  = score;
            best_move   = move;
        }
    }
    return best_move;
}

int Search::_alphabeta_failhard(SimpleBoard &board, int color_to_move, int alpha, int beta, int depth) {
    if (depth == 0) {
        return color_to_move * evaluation(board);
    }

    int score;
    std::vector<Ply> moves = board.generate_valid_moves(color_to_move);

    if (order_moves) move_ordering(board, moves);

    for (Ply move : moves){

        if (abs(board.get_piece(move.to)) == 1){
            return MAX+depth;
        }

        Reversible r = board.make_move(move);
        score = -_alphabeta_failhard(board, -color_to_move, -beta, -alpha, depth - 1);
        board.undo_move(r);

        if (score >= beta){ // beta cutoff
            if (board.get_piece(move.to) == 0){
                if (color_to_move == WHITE){
                    w_history_heuristic[move.from][move.to] = depth * depth;
                } else {
                    b_history_heuristic[move.from][move.to] = depth * depth;
                }
            }

            return beta;
        }

        if (score > alpha){
            alpha = score;
        }
    }

    return alpha;
}

Search::Search(int algorithm) : algorithm(algorithm) {}

void Search::move_ordering(SimpleBoard &board, std::vector<Ply> &moves) {
    // https://www.chessprogramming.org/Move_Ordering

    std::vector<int> move_val(moves.size());

    for (unsigned int i = 0; i < moves.size(); i++){

        if (!board.is_empty(moves[i].to)){
            // most valuable victim - least valuable aggressor
            int val = 16 * abs(board.get_piece(moves[i].to)) - abs(board.get_piece(moves[i].from));
            move_val[i] = val > 0 ? val : 0;

        } else {
            // history heuristic
            move_val[i] = board.get_color(board.get_piece(moves[i].from)) == WHITE
                          ? w_history_heuristic[moves[i].from][moves[i].to]
                          : b_history_heuristic[moves[i].from][moves[i].to];
        }
    }

    //for (int i = 0; i < moves.size(); i++) std::cout << move_val[i] << " ";
    //std::cout << std::endl;

    // selection sort
    for (unsigned int i = 0; i < moves.size()-1; i++){
        unsigned int max = i;

        for (unsigned int j = i+1; j < moves.size(); j++){
            if (move_val[j] > move_val[max]){
                max = j;
            }
        }

        if (max != i){
            int tmp = move_val[i];
            move_val[i] = move_val[max];
            move_val[max] = tmp;

            Ply tmp2 = moves[i];
            moves[i] = moves[max];
            moves[max] = tmp2;
        }
    }
}

Search::Search(int algorithm, bool order_moves) : algorithm(algorithm), order_moves(order_moves){}



