#include <iostream>
#include <cstring>

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
            move_val[i] = Board::get_color_of_piece(board.get_piece(moves[i].from)) == WHITE
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

int Search::quiesence(Board &board, SearchInfo &info, int alpha, int beta, Color color){
    int stand_pat = color * Evaluation::simplified_evaluation_function(board);

    if (stand_pat >= beta)
        return beta;

    if (alpha < stand_pat)
        alpha = stand_pat;

    std::vector<Ply> moves = board.pseudo_legal_moves(color);

    for (Ply move : moves){
        if (!board.is_legal_move(move) || board.is_empty(move.to)) continue;

        if (check_stop(info)) return 0;

        Reversible r = board.make_move(move);
        int score = -quiesence(board, info, -beta, -alpha, -color);
        board.undo_move(r);

        if (score >= beta)
            return beta;

        if (score > alpha)
            alpha = score;
    }
    return alpha;
}

bool Search::check_stop(SearchInfo &info){
    if (info.nodes % 2048){
        if (info.time_limit && get_time() > info.stop_time){
            info.stop = true;
        }
    }
    return info.stop;
}

int Search::alpha_beta(Board &board, SearchInfo &info, std::vector<Ply> &pv, Color color, int alpha, int beta, int depth) {
    info.nodes++;
    assert(color == board.color_to_move); // just testing

    if (depth == 0) {
        pv.clear();
        //return color * Evaluation::simplified_evaluation_function(board);
        return quiesence(board, info, alpha, beta, color);
    }

    if (board.fifty_moves == 50) return 0;

    std::vector<Ply> moves, lpv;
    moves = board.pseudo_legal_moves(color);
    sort_moves(board, info, moves);

    int score = 0, legal_moves = 0;

    for (Ply move : moves){
        if (!board.is_legal_move(move)) continue;

        lpv.clear();
        legal_moves++;

		if (check_stop(info)) return 0;

        Reversible r = board.make_move(move);
        score = -alpha_beta(board, info, lpv, -color, -beta, -alpha, depth-1);
        board.undo_move(r);

        if (score >= beta){ // beta cutoff
            if (board.get_piece(move.to) == 0) info.history_heuristic(color, move.from, move.to, depth*depth);
            return beta;
        }

        if (score > alpha){
            alpha = score;
            pv.clear();
            pv.push_back(move);
            pv.insert(pv.end(), lpv.begin(), lpv.end());
        }
    }

    if (legal_moves == 0){
        if (board.is_checked(color)){
            return MIN+1000;    // checkmate
        } else {
            return 0;           // stalemate
        }
    }
    return alpha;
}

Ply Search::iterative_deepening_search(Board &board, SearchInfo &info, Color color) {
	Ply current_best_move, best_move;

    for (int depth = 1; depth <= info.depth; depth++){
        std::vector<Ply> pv;

        int score = alpha_beta(board, info, pv, color, MIN, MAX, depth);

        if (info.stop) break;

        std::cout
        << "info"
        << " score cp " << score
        << " depth " << depth
        << " nodes " << info.nodes
        << " time " << get_time() - info.start_time
        << " pv ";
        for (auto m : pv) std::cout << m << " ";
        std::cout << std::endl;

		if (!pv.empty()) current_best_move = pv[0];
    }
	best_move = current_best_move;
    std::cout << "bestmove " << best_move << std::endl;
    return best_move;
}

Ply Search::search(Board &board, SearchInfo &info, std::vector<Ply> &pv, Color color, int depth) {
    Ply best_move;
    info.nodes++;

    std::vector<Ply> moves = board.pseudo_legal_moves(color);
    sort_moves(board, info, moves);

    int best_score = MIN;
    std::vector<Ply> lpv;

    for (Ply move : moves){

        Reversible r = board.make_move(move);
        int score = -alpha_beta(board, info, lpv, -color, MIN, MAX, depth);
        board.undo_move(r);

        //std::cout << move << " " << score << std::endl;

        if (score > best_score){
            best_score = score;
            best_move = move;

            pv.clear();
            pv.push_back(move);
            pv.insert(pv.end(), lpv.begin(), lpv.end());
        }
    }

    return best_move;
}
