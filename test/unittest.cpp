#include <iostream>
#include "../src/SimpleBoard.h"
#include "../src/CachedBoard.h"
#include "../src/Engine.h"


int main(){
    CachedBoard cachedBoard(DEFAULT_BOARD, true);
    SimpleBoard board(DEFAULT_BOARD, true);
    std::cout << cachedBoard << std::endl;

    //std::vector<Ply> history = { Ply("e2e4"), Ply("e7e5")};

    /*
    int color = WHITE;
    for (auto p : history){
        std::vector<Ply> moves = cachedBoard.generate_valid_moves_cached(-color);
        for (auto m : moves) std::cout << m << " ";
        std::cout << "\nmoves: " << moves.size() << std::endl;

        cachedBoard.execute_reversible_move(p);
        cachedBoard.update_cache_after_move();

        std::cout << cachedBoard << std::endl;
        std::cout << "exectued move: " << p << std::endl << std::endl;
        break;
    }
     */

    for (auto m : cachedBoard.generate_valid_moves(WHITE)) std::cout << m << " "; std::cout << std::endl;
    Reversible r = cachedBoard.make_move(Ply("e2e4"));
    std::cout << cachedBoard << std::endl;
    for (auto m : cachedBoard.generate_valid_moves(WHITE)) std::cout << m << " "; std::cout << std::endl;
    cachedBoard.undo_move(r);
    std::cout << cachedBoard << std::endl;
    for (auto m : cachedBoard.generate_valid_moves(WHITE)) std::cout << m << " "; std::cout << std::endl;

    clock_t tic = clock();
    std::optional<Ply> p = Engine::find_best_move(cachedBoard, WHITE, 3, NEGAMAX_ALPHABETA_FAILSOFT);
    clock_t toc = clock();
    double dt = (double)(toc - tic) / CLOCKS_PER_SEC;
    std::cout << p.value() << std::endl;
    printf("%f\n", dt);

    tic = clock();
    p = Engine::find_best_move(board, WHITE, 3, NEGAMAX_ALPHABETA_FAILSOFT);
    toc = clock();
    dt = (double)(toc - tic) / CLOCKS_PER_SEC;
    std::cout << p.value() << std::endl;
    printf("%f\n", dt);


}
