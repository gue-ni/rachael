
#include <iostream>

#include "Search.h"
#include "Evaluation.h"
#include "Util.h"

void Search::sort_moves(Board &board, SearchInfo &ss, std::vector<Ply> &moves) {
    if (moves.empty()) return;

    // https://www.chessprogramming.org/Move_Ordering

    std::vector<int> move_val(moves.size());

    for (unsigned int i = 0; i < moves.size(); i++){

        if (!board.is_empty(moves[i].to)){
            // most valuable victim - least valuable aggressor
            int val = 16 * abs(board.get_piece(moves[i].to)) - abs(board.get_piece(moves[i].from));
            move_val[i] = val > 0 ? val : 0;

        } else {
            // history_heuristic heuristic
            move_val[i] = Board::get_color(board.get_piece(moves[i].from)) == WHITE
                          ? ss.w_history_heuristic[moves[i].from][moves[i].to]
                          : ss.b_history_heuristic[moves[i].from][moves[i].to];
        }
    }

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

            Ply tmp_ply = moves[i];
            moves[i] = moves[max];
            moves[max] = tmp_ply;
        }
    }
}

/*
std::optional<Ply> search(Board &board, int depth, int color) {
    int score       = 0;
    int best_score  = MIN;

    std::optional<Ply> best_move = std::nullopt;
    std::vector<Ply> moves = board.pseudo_legal_moves(board.color_to_move);
    if (!moves.empty()){
        best_move = moves.front();
    }

    SearchInfo ss{};
    std::vector<Ply> pv, l_pv;

    sort_moves(board, ss,moves);

    for (Ply move : moves) {

        if (abs(board.get_piece(move.to)) == 1){ // can capture enemy king
            return move;
        }

        Reversible r = board.make_move(move);
        score = -alpha_beta(board, ss, l_pv, -color, MIN, MAX, depth);
        board.undo_move(r);

        if (score > best_score) {
            best_score  = score;
            best_move   = move;

            pv.clear();
            pv.push_back(move);
            pv.insert(pv.end(), l_pv.begin(), l_pv.end());
        }
    }

    for (auto p : l_pv) std::cout << p << " ";
    std::cout << std::endl;

    return best_move;
}
*/

int Search::quiesence(Board &board, SearchInfo &info, int alpha, int beta, int color){
    int stand_pat = color * Evaluation::evaluation_function(board);

    if (stand_pat >= beta){
        return beta;
    }

    if (alpha < stand_pat){
        alpha = stand_pat;
    }

    std::vector<Ply> moves = board.pseudo_legal_moves(color);

    for (Ply move : moves){
        if (!board.is_legal_move(move))
            continue;

        if (info.stop || (info.time_limit && get_time() > info.stop_time)) {
            return 0;
        }

        Reversible r = board.make_move(move);
        int score = -quiesence(board, info, -beta, -alpha, -color);
        board.undo_move(r);

        if (score >= beta){
            return beta;
        }

        if (score > alpha){
            alpha = score;
        }
    }
    return alpha;
}

void Search::check_stop(SearchInfo &info){
    if (info.time_limit && get_time() > info.stop_time){
        info.stop = true;
    }
}

int Search::alpha_beta(Board &board, SearchInfo &info, std::vector<Ply> &pv, int color, int alpha, int beta, int depth) {
    info.nodes++;

    assert(color == board.color_to_move);

    if (depth == 0) {
        pv.clear();
        return color * Evaluation::simplified_evaluation_function(board);
        //return quiesence(board, info, alpha, beta, color);
    }

    std::vector<Ply> l_pv;
    std::vector<Ply> moves = board.pseudo_legal_moves(color);

    sort_moves(board, info, moves);

    int score, legal_moves = 0;
    for (Ply move : moves){
        if (!board.is_legal_move(move)) continue;

        legal_moves++;

        if (info.nodes % 2048) check_stop(info);

        if (info.stop) return 0;

        Reversible r = board.make_move(move);
        score = -alpha_beta(board, info, l_pv, -color, -beta, -alpha, depth-1);
        board.undo_move(r);

        if (score >= beta){ // beta cutoff
            if (board.get_piece(move.to) == 0){
                info.history_heuristic(color, move.from, move.to, depth * depth);
            }
            return beta;
        }

        if (score > alpha){
            alpha = score;
            pv.clear();
            pv.push_back(move);
            pv.insert(pv.end(), l_pv.begin(), l_pv.end());
        }
    }

    if (legal_moves == 0){
        if (board.is_checked(color)){
            return MIN+100;
        }
    }
    return alpha;
}

void Search::iterative_deepening(Board &board, SearchInfo &info, int color) {
    std::vector<Ply> principal_variation;
	Ply current_best_move, best_move;

    for (int depth = 1; depth <= info.depth; depth++){

        int score = alpha_beta(board, info, principal_variation, color, MIN, MAX, depth);

        if (info.stop) break;

        std::cout
        << "info score cp " << score
        << " depth " << depth
        << " nodes " << info.nodes
        << " time " << get_time() - info.start_time
        << " pv ";
        for (auto m : principal_variation) std::cout << m << " ";
        std::cout << std::endl;

		if (!principal_variation.empty()) current_best_move = principal_variation[0];
    }
	best_move = current_best_move;
    std::cout << "bestmove " << best_move << std::endl;
}




