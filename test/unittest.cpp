#include <iostream>
#include <thread>
#include <zconf.h>
#include "../src/Board.h"



int main(){
    Board board(RUY_LOPEZ, true);

    std::vector<Ply> moves = board.generate_valid_moves_threaded(WHITE);
    for (auto m : moves) std::cout << m << " ";
    std::cout << std::endl;


    /*
    std::cout << "Threads 1 and 2 and 3 "
            "operating independently" << std::endl;

    auto f = [](int x) {
        for (int i = 0; i < x; i++){
            sleep(3);
            std::cout << "Thread using lambda expression as callable\n";
        }
    };


    std::thread th1(foo, 3);
    std::thread th2(thread_obj(), 3);
    std::thread th3(f, 3);

    th1.join();
    th2.join();
    th3.join();

     */

}
