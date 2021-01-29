#include <iostream>
#include <getopt.h>

#include "SimpleBoard.h"
#include "Square.h"
#include "Engine.h"

std::vector<Ply> move_history;

bool  human_take_turn(SimpleBoard &board, int color, int ply){
    std::vector<Ply> possible_moves = board.generate_valid_moves(color);

    if (possible_moves.empty()){
        std::cout << (color == WHITE ? "white" : "black") << " checkmate" << std::endl;
        return true;
    }

    std::string input;

    std::cout << "Ply " << ply << ":\n";
    std::cout << "Enter your move: " << std::endl;
    std::cin >> input;

    Ply move(input);

    board.make_move(move);
    move_history.push_back(move);
    std::cout << "\n"
              << board
              << (color == WHITE ? "white" : "black")
              <<  " moves " << move
              << std::endl
              << std::endl;

    return false;

}

bool engine_take_turn(SimpleBoard &board, int color, int ply, int search_depth) {
    clock_t tic = clock();
    std::optional<Ply> move = Engine::find_best_move(board, color, search_depth, NEGAMAX_ALPHABETA_FAILSOFT);
    clock_t toc = clock();
    double dt = (double)(toc - tic) / CLOCKS_PER_SEC;

    if (move.has_value()){
        board.make_move(move.value());
        move_history.push_back(move.value());
        std::cout << "Ply " << ply << ":\n"
                  << board
                  << (color == WHITE ? "white" : "black")
                  << " moves " << move.value()
                  //<< ", found after " << dt << " seconds"
                  << std::endl
                  << std::endl;

        return false;

    } else {
        std::cout
        << (color == WHITE ? "white" : "black")
        << " checkmate" << std::endl;
        return true;
    }
}

int main(int argc, char **argv) {
    int plies = 1, search_depth = 3, turns = 500;
    bool color_output = true, white_is_human = false, black_is_human = false;

    if (argc == 1){
        std::cerr
        << "Usage: " << argv[0]
        << " [-w white is human player]"
        << " [-b black is human player]"
        << " [-d search_depth]"
        << " [-t number of turns]"
        << " [-c color output (0 or 1)]"
        << std::endl;
        exit(EXIT_FAILURE);
    }

    int opt;
    while ((opt = getopt(argc, argv, "d:t:c:wb")) != -1){
        switch (opt){
            case 'd':
                search_depth    = atoi(optarg);
                break;
            case 't':
                turns           = atoi(optarg);
                break;
            case 'c':
                color_output    = atoi(optarg) == 1;
                break;
            case 'w':
                white_is_human = true;
                break;
            case 'b':
                black_is_human = true;
                break;
            default:
                std::cerr << "invalid option" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    SimpleBoard board(DEFAULT_BOARD, color_output);

    std::cout
    << "search_depth=" << search_depth
    << ", turns=" << turns
    << ", white_material=" << board.material(WHITE)
    << ", black_material=" << board.material(BLACK)
    << ", white_is_human=" << white_is_human
    << ", black_is_human=" << black_is_human
    << "\n\n"
    << board
    << "\n";

    bool checkmate;
    while (turns > 0){
        if (white_is_human){
            checkmate = human_take_turn(board, WHITE, plies++);
        } else {
            checkmate = engine_take_turn(board, WHITE, plies++, search_depth);
        }

        if (checkmate) break;

        if (black_is_human){
            checkmate = human_take_turn(board, BLACK, plies++);
        } else {
            checkmate = engine_take_turn(board, BLACK, plies++, search_depth);
        }

        if (checkmate) break;
        turns--;
     }

    std::cout
    <<   "white_material=" << board.material(WHITE)
    << ", black_material=" << board.material(BLACK)
    << std::endl;
    for (auto &m : move_history) std::cout << m << " ";
    std::cout << std::endl;
    return 0;
}
