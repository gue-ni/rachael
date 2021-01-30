//
// Created by jakob on 1/27/21.
//

#include <emscripten/bind.h>
#include "Web.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(web) {
        class_<Web>("Web")
                .constructor<std::string>()
                .function("generate_best_move", &Web::generate_best_move)
                .function("generate_valid_moves", &Web::generate_valid_moves);
}