#include <iostream>
#include "../src/CachedBoard.h"
#include "../src/Engine.h"


double dt(clock_t tic, clock_t toc){
    return  (double)(toc - tic) / CLOCKS_PER_SEC;
}

int main(){

    clock_t tic, toc;

    CachedBoard cachedBoard(DEFAULT_BOARD, true);
    SimpleBoard board(DEFAULT_BOARD, true);

    tic = clock();
    cachedBoard.generate_valid_moves(WHITE);
    toc = clock();
    std::cout << "cached: ";
    printf(" %f\n", dt(tic, toc));

    tic = clock();
    board.generate_valid_moves(WHITE);
    toc = clock();
    std::cout << "non-cached: ";
    printf(" %f\n", dt(tic, toc));


    tic = clock();
    std::optional<Ply> p = Engine::find_best_move(cachedBoard, WHITE, 3, NEGAMAX_ALPHABETA_FAILSOFT);
    toc = clock();

    std::cout << "cached: ";
    std::cout << p.value() << std::endl;
    printf(" %f\n", dt(tic, toc));

    tic = clock();
    p = Engine::find_best_move(board, WHITE, 3, NEGAMAX_ALPHABETA_FAILSOFT);
    toc = clock();

    std::cout << "conventional: ";
    std::cout << p.value();
    printf(" %f\n", dt(tic, toc));
    return 0;
}
