#include <iostream>
#include <sstream>
#include <optional>
#include "engine/SimpleBoard.h"
#include "engine/Search.h"

#define AUTHOR "Jakob Maier"
#define NAME "Rachael 1.0"

std::string startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

bool startswith(std::string str, std::string prefix){
    return str.rfind(prefix, 0) == 0;
}

int main(){
    std::cout << "Rachael 1.0 by Jakob Maier (2021)" << std::endl;
    SimpleBoard board(DEFAULT_BOARD, true);
    std::string input;

    while (true){
        std::getline(std::cin, input);

        if (input == "quit"){
            break;
        } else if(startswith(input, "uci")) {
            std::cout
                    << "id name " << NAME << "\n"
                    << "id author " << AUTHOR << "\n"
                    << "uciok"
                    << std::endl;

        } else if (startswith(input, "stop")){


        } else if (startswith(input, "position")){
            std::string cmd;
            std::istringstream ss(input);

            do {
                ss >> cmd;

                if (cmd == "fen"){
                    std::string fen;
                    for (int i = 0; i < 6; i++) {
                        ss >> cmd;
                        fen += (cmd + " ");
                    }
                    //std::cout << "fen: " << fen << std::endl;
                    board.set_board(fen);

                } else if (cmd == "startpos"){
                    board.set_board(startpos);

                } else if (cmd == "moves"){
                    board.set_board(startpos);
                    do {
                        std::string move;
                        ss >> move;
                        if (!move.empty()){
                            board.make_move(Ply(move));
                        }
                    } while (ss);
                }

            } while (ss);
            std::cout << board << std::endl;

        } else if (startswith(input, "go")){
            std::string cmd;
            std::istringstream ss(input);

            do {
                ss >> cmd;

                if (cmd == "infinite"){

                } else if (cmd == "depth"){
                    ss >> cmd;
                    int d = std::stoi(cmd);
                    Search search(NEGAMAX_ALPHABETA_FAILHARD);
                    std::optional<Ply> best_move = search.search(board, WHITE, d);
                    std::cout << "bestmove " << best_move.value() << std::endl;
                }

            } while (ss);
        } else {
            std::cout
            << "Unknown command: "
            << input
            << std::endl;
            break;
        }
    }
    return 0;
}

