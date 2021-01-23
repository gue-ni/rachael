//
// Created by jakob on 1/22/21.
//

#include <cctype>
#include <cassert>
#include "Algrebraic.h"

bool Algebraic::isValid() {
    file = _tolower(file);
    return (1 <= rank && rank <= 8) && ('a' <= file && file <= 'h');
}

Algebraic::Algebraic(char f, int r) : rank(r), file(f){
    assert(isValid());
}

std::ostream& operator<<(std::ostream &strm, const Algebraic &a) {
    return strm << a.file << a.rank;
}

Algebraic::Algebraic(std::string str) : file(str[0]), rank(str[1]-48){
    assert(isValid());
}

Algebraic::Algebraic(int x, int y) : rank(y + 1), file(x + 97) {
    assert(isValid());
}

uint8_t Algebraic::x88_value() {
    assert(isValid());
    int8_t f = file - 97;
    int8_t r = rank - 1;
    return 16 * r + f;
}

Algebraic::Algebraic(int x88) : Algebraic((x88 & 7), (x88 >> 4)) {
    assert(isValid());
}

