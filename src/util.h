//
// Created by jakob on 1/29/21.
//

#ifndef CHESS_ENGINE_CPP_UTIL_H
#define CHESS_ENGINE_CPP_UTIL_H

#include <ctime>

double dt(clock_t tic, clock_t toc){
    return  (double)(toc - tic) / CLOCKS_PER_SEC;
}

#endif //CHESS_ENGINE_CPP_UTIL_H
