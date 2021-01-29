#include <iostream>
#include "../src/Search.h"
#include "util.h"


int main(){

    SimpleBoard board(RUY_LOPEZ, true);

    Search s1(NEGAMAX_ALPHABETA_FAILHARD, true);
    Search s2(NEGAMAX_ALPHABETA_FAILHARD, false);

    clock_t tic, toc;

    int depth = 5;
    
    tic = clock();
    std::optional<Ply> p1 = s1.find_best_move(board, WHITE, depth);
    toc = clock();
    std::cout << p1.value();
    printf(" depth=%d, order_moves=true %f\n", depth, dt(tic, toc));

    tic = clock();
    std::optional<Ply> p2 = s2.find_best_move(board, WHITE, depth);
    toc = clock();
    std::cout << p2.value();
    printf(" depth=%d, order_moves=false %f\n", depth, dt(tic, toc));

    return 0;
}
