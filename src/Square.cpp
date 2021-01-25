//
// Created by jakob on 1/22/21.
//

#include <cctype>
#include <cassert>
#include "Square.h"

bool Square::isValid() {
    file = _tolower(file);
    return (1 <= rank && rank <= 8) && ('a' <= file && file <= 'h');
}

Square::Square(char f, int r) : rank(r), file(f){
    //assert(isValid());
}

std::ostream& operator<<(std::ostream &strm, const Square &a) {
    return strm << a.file << a.rank;
}

Square::Square(std::string str) : rank(str[1] - 48), file(str[0]) {
    //assert(isValid());
}

Square::Square(int x, int y) : rank(y + 1), file(x + 97) {
    //assert(isValid());
}

uint8_t Square::x88_value() {
    //assert(isValid());
    int8_t f = file - 97;
    int8_t r = rank - 1;
    return 16 * r + f;
}

Square::Square(int x88) : Square((x88 & 7), (x88 >> 4)) {
    assert(isValid());
}

