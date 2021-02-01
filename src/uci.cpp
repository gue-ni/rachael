#include <iostream>
#include <sstream>
#include <optional>
#include <thread>
#include "Board.h"
#include "Search.h"

#define AUTHOR "Jakob Maier"
#define NAME "Rachael 1.0"

std::string startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
std::thread thrd;
bool stop = false;
Board board(DEFAULT_BOARD, true);

void uci_stop(){
    stop = true;
    //std::cout << "stop thread " << stop << std::endl;
    if (thrd.joinable()) {
        thrd.join();
    }
}

void uci_go(std::string input){
    std::string cmd;
    std::istringstream ss(input);

    uci_stop();
    stop = false;

    do {
        ss >> cmd;

        if (cmd == "infinite"){
			Ply p;
			int d = 99;
            thrd = std::thread(iterative_deepening, std::ref(board), std::ref(p), d, std::ref(stop));
            break;

        } else if (cmd == "depth"){
            ss >> cmd;
            int d = std::stoi(cmd);
            Ply p;
            thrd = std::thread(iterative_deepening, std::ref(board), std::ref(p), d, std::ref(stop));
            thrd.join();
        }

    } while (ss);
}

void uci_position(std::string input){
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
                    //std::cout << "make move " << move << std::endl;
                    board.make_move(Ply(move));
                }
            } while (ss);
        }
    } while (ss);
    //std::cout << board << std::endl;
}

bool startswith(std::string str, std::string prefix){
    return str.rfind(prefix, 0) == 0;
}

int main(){
    std::cout << "Rachael 1.0 by Jakob Maier (2021)" << std::endl;
    std::string input;

    while (true){
        std::getline(std::cin, input);

        if (input == "quit") { break;
        } else if (startswith(input, "position")){
            uci_position(input);

        } else if (startswith(input, "go")){
            uci_go(input);

        } else if (startswith(input,  "debug")) {
        } else if (startswith(input,   "stop")) {
            uci_stop();

        } else if (startswith(input,"isready")) {
            std::cout << "readyok" << std::endl;

        } else if(startswith(input, "uci")) {
            std::cout << "id name " << NAME << "\n" << "id author " << AUTHOR << "\n" << "uciok" << std::endl;

        } else {
            std::cout << "Unknown command: " << input << std::endl;
            break;
        }
    }
    return 0;
}

