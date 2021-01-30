#include <iostream>
#include "../src/Search.h"
#include "util.h"


int main(){

    SimpleBoard board(RUY_LOPEZ, true);

    Search s1(NEGAMAX_ALPHABETA_FAILHARD, true);
    Search s2(NEGAMAX_ALPHABETA_FAILHARD, false);
    Search s3(NEGAMAX_ALPHABETA_FAILSOFT, true);
    Search s4(NEGAMAX_ALPHABETA_FAILSOFT, false);

    clock_t tic, toc;

    int depth = 4;

    tic = clock();
    std::optional<Ply> p1 = s1.find_best_move(board, WHITE, depth);
    toc = clock();
    std::cout << p1.value();
    printf(" depth=%d, order_moves=%d %f\n", depth, s1.order_moves, dt(tic, toc));

    tic = clock();
    std::optional<Ply> p2 = s2.find_best_move(board, WHITE, depth);
    toc = clock();
    std::cout << p2.value();
    printf(" depth=%d, order_moves=%d %f\n", depth, s2.order_moves, dt(tic, toc));

    tic = clock();
    std::optional<Ply> p3 = s3.find_best_move(board, WHITE, depth);
    toc = clock();
    std::cout << p3.value();
    printf(" depth=%d, order_moves=%d %f\n", depth, s3.order_moves,  dt(tic, toc));

    tic = clock();
    std::optional<Ply> p4 = s4.find_best_move(board, WHITE, depth);
    toc = clock();
    std::cout << p4.value();
    printf(" depth=%d, order_moves=%d %f\n", depth, s4.order_moves, dt(tic, toc));

    return 0;
}
