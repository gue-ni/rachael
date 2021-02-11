#include <iostream>
#include <cstring>

#include "Search.h"
#include "Evaluation.h"
#include "Util.h"

int Search::quiesence(Board &board, SearchInfo &info, int alpha, int beta, Color color){
    int stand_pat = color * Evaluation::simplified_evaluation_function(board);

	info.nodes++;

    if (stand_pat >= beta)
        return beta;

    if (alpha < stand_pat)
        alpha = stand_pat;

    Move moves[256];
    int n = board.pseudo_legal(moves, color);

    int score = 0;
    for (int i = 0; i < n; i++){
        if (board.is_empty(moves[i].to)) continue;

        if (check_stop(info)) return 0;

        State r = board.make_move_alt(moves[i]);
        if (!board.is_checked(color))
            score = -quiesence(board, info, -beta, -alpha, -color);
        board.undo_move_alt(r,moves[i]);

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

int Search::alpha_beta(Board &board, SearchInfo &info, std::vector<Move> &pv, Color color, int alpha, int beta, int depth) {
    info.nodes++;
    assert(color == board.color_to_move); // just testing

    if (depth == 0) {
        pv.clear();
        //return get_color * Evaluation::simplified_evaluation_function(board);
        return quiesence(board, info, alpha, beta, color);
    }

    std::vector<Move> lpv;

    Move moves[256];
    int n = board.pseudo_legal(moves, color);
    sort_moves(board, info, moves, n);

    //std::vector<Move> moves;
    //moves = board.pseudo_legal_moves(color);
    //sort_moves(board, info, moves);

    int score = 0, legal_moves = 0;

    for (int i = 0; i < n; i++){
        lpv.clear();
		if (check_stop(info)) return 0;

        State r = board.make_move_alt(moves[i]);
        if (!board.is_checked(color)) {
            legal_moves++;
            score = -alpha_beta(board, info, lpv, -color, -beta, -alpha, depth-1);
        }
        board.undo_move_alt(r, moves[i]);

        if (score >= beta){ // beta cutoff
            if (board.x88[moves[i].to] == EMPTY_SQUARE)
                info.history_heuristic(color, moves[i].from, moves[i].to, depth*depth);
            return beta;
        }

        if (score > alpha){
            alpha = score;
            pv.clear();
            pv.push_back(moves[i]);
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

Move Search::iterative_deepening_search(Board &board, SearchInfo &info, Color color) {
	Move current_best_move, best_move;

    for (int depth = 1; depth <= info.depth; depth++){
        std::vector<Move> pv;

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

Move Search::search(Board &board, SearchInfo &info, std::vector<Move> &pv, Color color, int depth) {
    Move best_move;
    info.nodes++;

    Move moves[256];
    int n = board.pseudo_legal(moves, color);
    sort_moves(board, info, moves, n);

    int best_score = MIN;
    std::vector<Move> lpv;

    for (int i = 0; i < n; i++){

        Reversible r = board.make_move(moves[i]);
        int score = -alpha_beta(board, info, lpv, -color, MIN, MAX, depth);
        board.undo_move(r);

        //std::cout << move << " " << score << std::endl;

        if (score > best_score){
            best_score = score;
            best_move = moves[i];

            pv.clear();
            pv.push_back(moves[i]);
            pv.insert(pv.end(), lpv.begin(), lpv.end());
        }
    }

    return best_move;
}

unsigned long long int Search::perft(Board &board, SearchInfo &info, int depth, Color color) {
    unsigned long long nodes = 0;
    info.nodes++;

    if (depth == 0) {
        return 1ULL;
    }

    Move moves[256];
    int n = board.pseudo_legal(moves, color);

    for (int i = 0; i < n; i++){
        Reversible r = board.make_move(moves[i]);
        if (!board.is_checked(color)) nodes += perft(board, info, depth-1, -color);
        board.undo_move(r);
    }
    return nodes;
}

void Search::sort_moves(Board &board, SearchInfo &ss, Move *moves, int n) {
    if (n == 0) return;
    // https://www.chessprogramming.org/Move_Ordering

    int *move_val = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++){

        if (!board.is_empty(moves[i].to)){
            // most valuable victim - least valuable aggressor
            int val = 16 * abs(board.x88[moves[i].to]) - abs(board.x88[moves[i].from]);
            move_val[i] = val > 0 ? val : 0;

        } else {
            // history_heuristic heuristic
            move_val[i] = get_color(board.x88[moves[i].from]) == WHITE
                          ? ss.w_history_heuristic[moves[i].from][moves[i].to]
                          : ss.b_history_heuristic[moves[i].from][moves[i].to];
        }
    }

    for (int i = 0; i < n; i++){
        int max = i;

        for (int j = i+1; j < n; j++){
            if (move_val[j] > move_val[max]){
                max = j;
            }
        }

        if (max != i){
            int tmp = move_val[i];
            move_val[i] = move_val[max];
            move_val[max] = tmp;

            Move tmp_ply = moves[i];
            moves[i] = moves[max];
            moves[max] = tmp_ply;
        }
    }

    free(move_val);
}
