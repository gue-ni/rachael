//
// Created by jakob on 2/2/21.
//

#include "Util.h"

double dt(clock_t tic, clock_t toc){
    return  (double)(toc - tic) / CLOCKS_PER_SEC;
}

uint64_t get_time(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}