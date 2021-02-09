#include <iostream>
#include <optional>
#include <thread>

#include "Board.h"
#include "Search.h"
#include "Util.h"

#define AUTHOR "Jakob Maier"
#define NAME "Rachael 1.0"

std::string startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
std::thread thrd;
SearchInfo info;
Board board(DEFAULT_BOARD, false);

void uci_stop(){
    info.stop = true;
    if (thrd.joinable()) {
        thrd.join();
    }
}

void uci_go(const std::string& input){
    std::string cmd;
    std::istringstream ss(input);

    uci_stop();

    uint64_t time = -1, inc = 0;

    info.depth = 10;
    info.time_limit = false;
    info.stop = false;
	info.nodes = 0;

    while (ss >> cmd){
        if (cmd == "depth") {
            ss >> info.depth;
        } else if (cmd == "infinite"){
        } else if (cmd == "movetime"){ ss >> time;
        } else if (cmd == "btime" && board.color_to_move == BLACK){ ss >> time;
        } else if (cmd == "wtime" && board.color_to_move == WHITE){ ss >> time;
        } else if (cmd == "binc"  && board.color_to_move == BLACK){ ss >> inc;
        } else if (cmd == "winc"  && board.color_to_move == WHITE){ ss >> inc;
        }
    }

    info.start_time = get_time();
    info.stop_time  = info.start_time + ((time + inc) / 15); // estimating 25 moves left

    if (time != (uint64_t)-1){
        info.time_limit = true;
    }
    //printf("start_time=%lu, stop_time=%lu, time=%lu\n", info.start_time, info.stop_time, info.stop_time - info.start_time);
    thrd = std::thread(Search::iterative_deepening_search, std::ref(board), std::ref(info), board.color_to_move);
}

void uci_position(const std::string& input){
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
            board.set_board(fen);

        } else if (cmd == "startpos"){
            board.set_board(startpos);

        } else if (cmd == "moves"){
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
}

bool startswith(const std::string& str, const std::string& prefix){
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
            std::cout << "id name "     << NAME << std::endl;
            std::cout << "id author "   << AUTHOR << std::endl;
            std::cout << "uciok" << std::endl;

        } else {
            std::cout << "Unknown command: " << input << std::endl;
        }
    }
    return 0;
}

