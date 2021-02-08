
#include <cctype>
#include <cassert>

#include "SquareClass.h"

bool SquareClass::is_valid() {
    file = _tolower(file);
    return (1 <= rank && rank <= 8) && ('a' <= file && file <= 'h');
}

SquareClass::SquareClass(char f, int r) : rank(r), file(f){
    assert(is_valid());
}

SquareClass::SquareClass(std::string str) : rank(str[1] - 48), file(str[0]) {
    assert(is_valid());
    assert(str.size() == 2);
}

SquareClass::SquareClass(int x, int y) : rank(y + 1), file(x + 97) {
    assert(is_valid());
}

int SquareClass::index() {
    assert(is_valid());
    return 16 * (rank - 1) + (file - 97);
}

SquareClass::SquareClass(int x88) : SquareClass((x88 & 7), (x88 >> 4)) {
    assert(is_valid());
}

bool operator==(const SquareClass &sq1, const SquareClass &sq2) {
    return sq1.rank == sq2.rank && sq1.file == sq2.file;
}

std::ostream& operator<<(std::ostream &strm, const SquareClass &a) {
    return strm << a.file << a.rank;
}



