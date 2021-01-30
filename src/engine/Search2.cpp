//
// Created by jakob on 1/30/21.
//

#include <iostream>
#include "Search2.h"

void sort_moves(SimpleBoard &board, SearchState &ss, std::vector<Ply> &moves) {
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
                          ? ss.w_history_heuristic[moves[i].from][moves[i].to]
                          : ss.b_history_heuristic[moves[i].from][moves[i].to];

            //move_val[i] = ss.history(board.get_piece(moves[i].from), moves[i].from, moves[i].to);

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

            Ply tmp2 = moves[i];
            moves[i] = moves[max];
            moves[max] = tmp2;
        }
    }
}

void thread_search(SimpleBoard& board, int color_to_move, int depth, Ply &ply){
    std::optional<Ply> move = search(board, color_to_move, depth);
    ply = move.value();
}

std::optional<Ply> search(SimpleBoard &board, int color_to_move, int depth) {
    int score       = 0;
    int best_score  = MIN;

    std::optional<Ply> best_move = std::nullopt;
    std::vector<Ply> moves = board.gen_pseudo_legal_moves(color_to_move);
    if (!moves.empty()){
        best_move = moves.front();
    }

    SearchState ss;
    sort_moves(board, ss,moves);

    for (Ply move : moves) {

        if (abs(board.get_piece(move.to)) == 1){ // can capture enemy king
            return move;
        }

        Reversible r = board.make_move(move);
        score = -alpha_beta(board, ss, -color_to_move, MIN, MAX, depth);
        board.undo_move(r);

        if (score > best_score) {
            best_score  = score;
            best_move   = move;
        }
    }
    return best_move;
}

int alpha_beta(SimpleBoard &board, SearchState &ss, int color_to_move, int alpha, int beta, int depth) {
    if (depth == 0) {
        return color_to_move * evaluation(board);
    }

    int score;
    std::vector<Ply> moves = board.gen_pseudo_legal_moves(color_to_move);

    sort_moves(board, ss,moves);

    for (Ply move : moves){

        if (abs(board.get_piece(move.to)) == 1){
            return MAX+depth;
        }

        Reversible r = board.make_move(move);
        score = -alpha_beta(board, ss, -color_to_move, -beta, -alpha, depth - 1);
        board.undo_move(r);

        if (score >= beta){ // beta cutoff
            if (board.get_piece(move.to) == 0){
                ss.history(color_to_move, move.from, move.to, depth*depth);
            }
            return beta;
        }

        if (score > alpha){
            alpha = score;
        }
    }

    return alpha;
}

int evaluation(SimpleBoard &board) {
    int mobility =  ((int) board.gen_pseudo_legal_moves(WHITE).size()
                     - (int) board.gen_pseudo_legal_moves(BLACK).size());

    //std::cout << "mobility: " << mobility << std::endl;

    int material = board.material(WHITE) - board.material(BLACK);

    //std::cout << "material: " << material << std::endl;

    return mobility + material;
}

std::optional<Ply> iterative_deepening(SimpleBoard &board, int color_to_move) {
    std::optional<Ply> best_move = std::nullopt;

    SearchState ss;

    for (int i = 0; i < 8; i++){
        best_move = search(board, ss, color_to_move, i);
        std::cout << "Depth: " << i << ", best_move=" << best_move.value() << std::endl;
    }

    return best_move;
}



