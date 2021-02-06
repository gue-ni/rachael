
#include <cctype>
#include <cassert>

#include "Square.h"

bool Square::is_valid() {
    file = _tolower(file);
    return (1 <= rank && rank <= 8) && ('a' <= file && file <= 'h');
}

Square::Square(char f, int r) : rank(r), file(f){
    assert(is_valid());
}

Square::Square(std::string str) : rank(str[1] - 48), file(str[0]) {
    assert(is_valid());
    assert(str.size() == 2);
}

Square::Square(int x, int y) : rank(y + 1), file(x + 97) {
    assert(is_valid());
}

int Square::index() {
    assert(is_valid());
    return 16 * (rank - 1) + (file - 97);
}

Square::Square(int x88) : Square((x88 & 7), (x88 >> 4)) {
    assert(is_valid());
}

bool operator==(const Square &sq1, const Square &sq2) {
    return sq1.rank == sq2.rank && sq1.file == sq2.file;
}

std::ostream& operator<<(std::ostream &strm, const Square &a) {
    return strm << a.file << a.rank;
}



