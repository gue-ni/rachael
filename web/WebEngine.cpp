//
// Created by jakob on 1/27/21.
//

#include <emscripten/bind.h>
#include <iostream>

#include "../SimpleBoard.h"

using namespace emscripten;

float lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}

std::string wow(std::string str){
    Board board(false);
    std::cout << board << std::endl;
    return str;
}

EMSCRIPTEN_BINDINGS(my_module) {
        function("lerp", &lerp);
        function("wow", &wow);
}



