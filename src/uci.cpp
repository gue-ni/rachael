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
SearchState searchState;
Board board(DEFAULT_BOARD, true);

uint64_t get_time(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

}

void uci_stop(){
    stop = true;
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
			searchState.start_time = get_time();
            thrd = std::thread(iterative_deepening, std::ref(board), std::ref(p), std::ref(searchState), d, std::ref(stop));
            break;

        } else if (cmd == "depth"){
            ss >> cmd;
            int d = std::stoi(cmd);
            Ply p;
            thrd = std::thread(iterative_deepening, std::ref(board), std::ref(p), std::ref(searchState), d, std::ref(stop));
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
            //board.set_board(startpos);
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
    std::cout << board << std::endl;
}

bool startswith(std::string str, std::string prefix){
    return str.rfind(prefix, 0) == 0;
}

int main(){
    std::cout << "Rachael 1.0 by Jakob Maier (2021)" << std::endl;
    std::string input;

    while (true){
        std::getline(std::cin, input);

        if (input == "quit") {
            uci_stop();
            break;
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
            std::cout << "id name " << NAME << std::endl;
            std::cout << "id author " << AUTHOR << std::endl;
            std::cout << "uciok" << std::endl;

        } else {
            std::cout << "Unknown command: " << input << std::endl;
        }
    }
    return 0;
}

